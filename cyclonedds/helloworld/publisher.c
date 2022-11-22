#include "dds/dds.h"
#include "HelloWorld_v1.h"
#include "HelloWorld_v2.h"
#include "HelloWorld_v3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// As of 2022-11-22, CycloneDDS supports setting the inconsistent topic
// callback, but will never call it.  See https://github.com/eclipse-cyclonedds/cyclonedds/blob/d37952bd64007e5412f1a1eb734dbefc645086cf/src/core/ddsc/src/dds_topic.c#L132-L162

static void send_data_v1(int i, dds_entity_t writer)
{
  HelloWorld_v1 msg;
  dds_return_t rc;

  msg.index = i;
  msg.message = "Hello World";

  printf ("=== [Publisher]  Writing : ");
  printf ("Message (%"PRId32", %s)\n", msg.index, msg.message);
  fflush (stdout);

  rc = dds_write (writer, &msg);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
}

static void send_data_v2(int i, dds_entity_t writer)
{
  HelloWorld_v2 msg;
  dds_return_t rc;

  msg.index = i;
  msg.message = "Hello World";

  printf ("=== [Publisher]  Writing : ");
  printf ("Message (%"PRId32", %s)\n", msg.index, msg.message);
  fflush (stdout);

  rc = dds_write (writer, &msg);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
}

static void send_data_v3(int i, dds_entity_t writer)
{
  // T1 TYPE_MAP_CDR_SZ_HelloWorld_v3 == 326u
  // T2 TYPE_MAP_CDR_SZ_HelloWorld_v3 == 278u
  // T3 TYPE_MAP_CDR_SZ_HelloWorld_v3 == 278u

  HelloWorld_v3 msg;
  dds_return_t rc;

  msg.index = i;

  printf ("=== [Publisher]  Writing : ");
#if defined(V3T1) || defined(V3T2)
  // T1 or T2, message is a string
  msg.message = "Hello World";
  printf ("Message (%"PRId32", %s)\n", msg.index, msg.message);
#elif defined(V3T3)
  // T3, message is a float
  msg.message = 54.34;
  printf ("Message (%"PRId32", %f)\n", msg.index, msg.message);
#endif

  fflush (stdout);

  rc = dds_write (writer, &msg);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
}

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t writer;
  dds_return_t rc;
  uint32_t status = 0;
  void (*send_data)(int, dds_entity_t) = NULL;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1|v2|v3>\n", argv[0]);
    return 1;
  }

  const char * type = argv[1];
  const dds_topic_descriptor_t * descriptor = NULL;
  if (strcmp(type, "v1") == 0) {
    descriptor = &HelloWorld_v1_desc;
    send_data = send_data_v1;
  } else if (strcmp(type, "v2") == 0) {
    descriptor = &HelloWorld_v2_desc;
    send_data = send_data_v2;
  } else if (strcmp(type, "v3") == 0) {
    descriptor = &HelloWorld_v3_desc;
    send_data = send_data_v3;
  } else {
    fprintf(stderr, "Invalid argument; must be one of v1, v2, v3\n");
    return 2;
  }

#if defined(V1T1)
  printf("Publishing type V1T1\n");
#elif defined(V1T2)
  printf("Publishing type V1T2\n");
#elif defined(V1T3)
  printf("Publishing type V1T3\n");
#elif defined(V2T1)
  printf("Publishing type V2T1\n");
#elif defined(V2T2)
  printf("Publishing type V2T2\n");
#elif defined(V2T3)
  printf("Publishing type V2T3\n");
#elif defined(V2T4)
  printf("Publishing type V2T4\n");
#elif defined(V3T1)
  printf("Publishing type V3T1\n");
#elif defined(V3T2)
  printf("Publishing type V3T2\n");
#elif defined(V3T3)
  printf("Publishing type V3T2\n");
#endif

  /* Create a Participant. */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  /* Create a Topic. */
  topic = dds_create_topic (
    participant, descriptor, "hello_world_topic", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Create a Writer. */
  writer = dds_create_writer (participant, topic, NULL, NULL);
  if (writer < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));

  printf("=== [Publisher]  Waiting for a reader to be discovered ...\n");
  fflush (stdout);

  rc = dds_set_status_mask(writer, DDS_PUBLICATION_MATCHED_STATUS);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_set_status_mask: %s\n", dds_strretcode(-rc));

  while(!(status & DDS_PUBLICATION_MATCHED_STATUS))
  {
    rc = dds_get_status_changes (writer, &status);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_get_status_changes: %s\n", dds_strretcode(-rc));

    /* Polling sleep. */
    dds_sleepfor (DDS_MSECS (20));
  }

  /* Create a message to write. */
  for (int i = 1; i < 5; ++i)
  {
    send_data(i, writer);
  }

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}
