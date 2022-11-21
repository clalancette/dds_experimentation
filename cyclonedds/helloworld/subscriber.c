#define MSG_VERSION 1 /// Toggle this

#include "dds/dds.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HelloWorld_v1.h"
#include "HelloWorld_v2.h"
#include "HelloWorld_v3.h"

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 1

static void inconsistent_topic_cb(dds_entity_t topic, const dds_inconsistent_topic_status_t status, void* arg)
{
    /* do stuff and things with the event */
  printf("calling inconsistent!\n");
  fflush(stdout);
}

static void data_available_handler (dds_entity_t reader, void *arg)
{

  printf("data avail\n");
  fflush(stdout);

//  (void)arg;
//  (void) do_take (reader);
}

static void * alloc_v1()
{
  return HelloWorld_v1__alloc();
}

static void free_v1(void * data)
{
  HelloWorld_v1_free(data, DDS_FREE_ALL);
}

static void print_v1(const void * const data)
{
  HelloWorld_v1 *msg = (HelloWorld_v1*) data;
  printf ("=== [Subscriber] Received : ");
  printf ("Message (%"PRId32", %s)\n", msg->index, msg->message);
  fflush (stdout);
}

static void * alloc_v2()
{
  return HelloWorld_v2__alloc();
}

static void free_v2(void * data)
{
  HelloWorld_v2_free(data, DDS_FREE_ALL);
}

static void print_v2(const void * const data)
{
  HelloWorld_v2 *msg = (HelloWorld_v2*) data;
  printf ("=== [Subscriber] Received : ");
  printf ("Message (%"PRId32", %s)\n", msg->index, msg->message);
  fflush (stdout);
}

static void * alloc_v3()
{
  return HelloWorld_v3__alloc();
}

static void free_v3(void * data)
{
  HelloWorld_v3_free(data, DDS_FREE_ALL);
}

static void print_v3(const void * const data)
{
  HelloWorld_v3 *msg = (HelloWorld_v3*) data;
  printf ("=== [Subscriber] Received : ");
  printf ("Message (%"PRId32", %s)\n", msg->index, msg->message);
  fflush (stdout);
}

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t reader;

  void *samples[MAX_SAMPLES];
  dds_sample_info_t infos[MAX_SAMPLES];
  dds_return_t rc;
  dds_qos_t *qos;
  void * (*alloc_msg)() = NULL;
  void (*free_msg)(void *) = NULL;
  void (*print_msg)(const void * const) = NULL;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1|v2|v3>\n", argv[0]);
    return 1;
  }

  const char * type = argv[1];
  const dds_topic_descriptor_t * descriptor = NULL;
  if (strcmp(type, "v1") == 0) {
    descriptor = &HelloWorld_v1_desc;
    alloc_msg = alloc_v1;
    free_msg = free_v1;
    print_msg = print_v1;
  } else if (strcmp(type, "v2") == 0) {
    descriptor = &HelloWorld_v2_desc;
    alloc_msg = alloc_v2;
    free_msg = free_v2;
    print_msg = print_v2;
  } else if (strcmp(type, "v3") == 0) {
    descriptor = &HelloWorld_v3_desc;
    alloc_msg = alloc_v3;
    free_msg = free_v3;
    print_msg = print_v3;
  } else {
    fprintf(stderr, "Invalid argument; must be one of v1, v2, v3\n");
    return 2;
  }

  /* create listener*/
  dds_listener_t* listener;
  listener = dds_create_listener(NULL);
  dds_lset_inconsistent_topic(listener, inconsistent_topic_cb);
  dds_lset_data_available(listener, data_available_handler);

  /* Create a Participant. */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, listener);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  /* Create a Topic. */
  topic = dds_create_topic (
    participant, descriptor, "hello_world_topic", NULL, listener);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Create a reliable Reader. */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  reader = dds_create_reader (participant, topic, qos, listener);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  dds_delete_qos(qos);

  printf ("\n=== [Subscriber] Waiting for a sample ...\n");
  fflush (stdout);

  /* Initialize sample buffer, by pointing the void pointer within
   * the buffer array to a valid sample memory location. */
  samples[0] = alloc_msg();

  /* Poll until data has been read. */
  while (true)
  {
    /* Do the actual read.
     * The return value contains the number of read samples. */
    rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    if (rc < 0)
      DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));

    /* Check if we read some data and it is valid. */
    if ((rc > 0) && (infos[0].valid_data))
    {
      print_msg(samples[0]);
      break;
    }
    else
    {
      /* Polling sleep. */
      dds_sleepfor (DDS_MSECS (20));
    }
  }

  /* Free the data location. */
  free_msg(samples[0]);

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}
