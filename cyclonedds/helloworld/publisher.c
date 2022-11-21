#include "dds/dds.h"
#include "HelloWorld_v1.h"
#include "HelloWorld_v1t1.h"
#include "HelloWorld_v1t2.h"
#include "HelloWorld_v1t3.h"
#include "HelloWorld_v2t1.h"
#include "HelloWorld_v2t2.h"
#include "HelloWorld_v2t3.h"
#include "HelloWorld_v2t4.h"
#include "HelloWorld_v3t1.h"
#include "HelloWorld_v3t2.h"
#include "HelloWorld_v3t3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void send_data_v1t1(int i, dds_entity_t writer)
{
  HelloWorld_v1t1 msg;
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

static void send_data_v1t2(int i, dds_entity_t writer)
{
  HelloWorld_v1t2 msg;
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

static void send_data_v1t3(int i, dds_entity_t writer)
{
  HelloWorld_v1t3 msg;
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

static void send_data_v2t1(int i, dds_entity_t writer)
{
  HelloWorld_v2t1 msg;
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

static void send_data_v2t2(int i, dds_entity_t writer)
{
  HelloWorld_v2t2 msg;
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

static void send_data_v2t3(int i, dds_entity_t writer)
{
  HelloWorld_v2t3 msg;
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

static void send_data_v2t4(int i, dds_entity_t writer)
{
  HelloWorld_v2t4 msg;
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

static void send_data_v3t1(int i, dds_entity_t writer)
{
  HelloWorld_v3t1 msg;
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

static void send_data_v3t2(int i, dds_entity_t writer)
{
  HelloWorld_v3t2 msg;
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

static void send_data_v3t3(int i, dds_entity_t writer)
{
  HelloWorld_v3t3 msg;
  dds_return_t rc;

  msg.index = i;
  msg.message = 56.4;

  printf ("=== [Publisher]  Writing : ");
  printf ("Message (%"PRId32", %f)\n", msg.index, msg.message);
  fflush (stdout);

  rc = dds_write (writer, &msg);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
}

static void send_data_v1(int i, dds_entity_t writer)
{
  HelloWorld_v1_Msg msg;
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

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t writer;
  dds_return_t rc;
  uint32_t status = 0;
  void (*send_data)(int, dds_entity_t) = NULL;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1t1|v1t2|v1t3|v2t1|v2t2|v2t3|v2t4|v3t1|v3t2|v3t3>\n", argv[0]);
    return 1;
  }

  const char * type = argv[1];
  const dds_topic_descriptor_t * descriptor = NULL;
  if (strcmp(type, "v1t1") == 0) {
    descriptor = &HelloWorld_v1t1_desc;
    send_data = send_data_v1t1;
  } else if (strcmp(type, "v1t2") == 0) {
    descriptor = &HelloWorld_v1t2_desc;
    send_data = send_data_v1t2;
  } else if (strcmp(type, "v1t3") == 0) {
    descriptor = &HelloWorld_v1t3_desc;
    send_data = send_data_v1t3;
  } else if (strcmp(type, "v2t1") == 0) {
    descriptor = &HelloWorld_v2t1_desc;
    send_data = send_data_v2t1;
  } else if (strcmp(type, "v2t2") == 0) {
    descriptor = &HelloWorld_v2t2_desc;
    send_data = send_data_v2t2;
  } else if (strcmp(type, "v2t3") == 0) {
    descriptor = &HelloWorld_v2t3_desc;
    send_data = send_data_v2t3;
  } else if (strcmp(type, "v2t4") == 0) {
    descriptor = &HelloWorld_v2t4_desc;
    send_data = send_data_v2t4;
  } else if (strcmp(type, "v3t1") == 0) {
    descriptor = &HelloWorld_v3t1_desc;
    send_data = send_data_v3t1;
  } else if (strcmp(type, "v3t2") == 0) {
    descriptor = &HelloWorld_v3t2_desc;
    send_data = send_data_v3t2;
  } else if (strcmp(type, "v3t3") == 0) {
    descriptor = &HelloWorld_v3t3_desc;
    send_data = send_data_v3t3;
  } else {
    fprintf(stderr, "Invalid argument; must be one of v1t1, v1t2, v1t3, v2t1, v2t2, v2t3, v2t4, v3t1, v3t2, v3t3\n");
    return 2;
  }

  descriptor = &HelloWorld_v1_Msg_desc;
  send_data = send_data_v1;

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
