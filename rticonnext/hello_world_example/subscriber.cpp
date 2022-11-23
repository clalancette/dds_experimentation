#include <dds/dds.hpp>

#include "HelloWorld_v1.h"
#include "HelloWorld_v1Support.h"

static int running = 1;

int main(int argc, char ** argv)
{
  // A DomainParticipant allows an application to begin communicating in
  // a DDS domain. Typically there is one DomainParticipant per application.
  // DomainParticipant QoS is configured in USER_QOS_PROFILES.xml
  DDSDomainParticipant * participant = DDSDomainParticipantFactory::get_instance()->create_participant(0, DDS_PARTICIPANT_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
  if (participant == nullptr) {
    fprintf(stderr, "Failed to create participant\n");
    return 1;
  }

  // A Subscriber allows an application to create one or more DataReaders
  // Subscriber QoS is configured in USER_QOS_PROFILES.xml
  DDSSubscriber * subscriber = participant->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
  if (subscriber == NULL) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to create subscriber\n");
    return 2;
  }

  // Register the datatype to use when creating the Topic
  const char * type_name = HelloWorld_v1TypeSupport::get_type_name();
  DDS_ReturnCode_t retcode = HelloWorld_v1TypeSupport::register_type(participant, type_name);
  if (retcode != DDS_RETCODE_OK) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to register type\n");
    return 3;
  }

  // A Topic has a name and a datatype. Create a Topic called
  // "HelloWorld Topic" with your registered data type
  DDSTopic * topic = participant->create_topic("hello_world_topic", type_name, DDS_TOPIC_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
  if (topic == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to create topic\n");
    return 4;
  }

  // This DataReader will read data of type HelloWorld on Topic
  // "HelloWorld Topic". DataReader QoS is configured in
  // USER_QOS_PROFILES.xml
  DDSDataReader * reader = subscriber->create_datareader(topic, DDS_DATAREADER_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
  if (reader == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to create datareader\n");
    return 5;
  }

  // Get status condition: Each entity has a Status Condition, which
  // gets triggered when a status becomes true
  DDSStatusCondition * status_condition = reader->get_statuscondition();
  if (status_condition == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to get status condition\n");
    return 6;
  }

  // Enable only the status we are interested in:
  //   DDS_DATA_AVAILABLE_STATUS
  retcode = status_condition->set_enabled_statuses(DDS_DATA_AVAILABLE_STATUS);
  if (retcode != DDS_RETCODE_OK) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to set enabled statuses\n");
    return 7;
  }

  // Create the WaitSet and attach the Status Condition to it. The WaitSet
  // will be woken when the condition is triggered.
  DDSWaitSet waitset;
  retcode = waitset.attach_condition(status_condition);
  if (retcode != DDS_RETCODE_OK) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to attach condition to waitset\n");
    return 8;
  }

  // A narrow is a cast from a generic DataReader to one that is specific
  // to your type. Use the type specific DataReader to read data
  HelloWorld_v1DataReader * hello_world_reader = HelloWorld_v1DataReader::narrow(reader);
  if (hello_world_reader == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to narrow type\n");
    return 8;
  }

  while (running) {
    DDSConditionSeq active_conditions_seq;

    // wait() blocks execution of the thread until one or more attached
    // Conditions become true, or until a user-specified timeout expires.
    DDS_Duration_t wait_timeout = { 0, 100 * 1000 * 1000 };
    retcode = waitset.wait(active_conditions_seq, wait_timeout);

    // You get a timeout if no conditions were triggered before the timeout
    if (retcode == DDS_RETCODE_TIMEOUT) {
      continue;
    } else if (retcode != DDS_RETCODE_OK) {
      std::cerr << "wait returned error: " << retcode << std::endl;
      break;
    }

    // Get the status changes to check which status condition
    // triggered the WaitSet to wake
    DDS_StatusMask triggeredmask = hello_world_reader->get_status_changes();

    // If the status is "Data Available"
    if (triggeredmask & DDS_DATA_AVAILABLE_STATUS) {
      HelloWorld_v1Seq data_seq;
      DDS_SampleInfoSeq info_seq;

      retcode = hello_world_reader->take(data_seq, info_seq);
      if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "Take error\n");
        continue;
      }

      for (DDS_Long i = 0; i < HelloWorld_v1Seq_get_length(&data_seq); ++i) {
#if 0
        if (!info_seq[i].valid_data) {
          fprintf(stderr, "Received instance state notification\n");
          continue;
        }

        HelloWorld_v1TypeSupport::print_data(&data_seq[i]);
#endif
      }
      hello_world_reader->return_loan(data_seq, info_seq);
    }
  }

  retcode = participant->delete_contained_entities();
  DDSDomainParticipantFactory::get_instance()->delete_participant(participant);

  DDSDomainParticipantFactory::finalize_instance();

  return 0;
}
