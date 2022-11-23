#include <dds/dds.hpp>

#include "HelloWorld_v1.h"
#include "HelloWorld_v1Support.h"

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

  // A Publisher allows an application to create one or more DataWriters
  // Publisher QoS is configured in USER_QOS_PROFILES.xml
  DDSPublisher * publisher = participant->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, NULL, DDS_STATUS_MASK_NONE);
  if (publisher == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to create publisher\n");
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

  // This DataWriter will write data on Topic "HelloWorld Topic"
  // DataWriter QoS is configured in USER_QOS_PROFILES.xml
  DDSDataWriter * writer = publisher->create_datawriter(topic, DDS_DATAWRITER_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
  if (writer == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to create writer\n");
    return 5;
  }

  // A narrow is a cast from a generic DataWriter to one that is specific
  // to your type. Use the type specific DataWriter to write()
  HelloWorld_v1DataWriter * hello_world_writer = HelloWorld_v1DataWriter::narrow(writer);
  if (hello_world_writer == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to narrow writer\n");
    return 6;
  }

  // Create data sample for writing
  HelloWorld_v1 * sample = HelloWorld_v1TypeSupport::create_data();
  if (sample == nullptr) {
    DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
    fprintf(stderr, "Failed to create sample data\n");
    return 7;
  }

  for (unsigned long count = 0; count < 10; ++count) {
    sample->index = count;
    strcpy(sample->message, "Hello World");

    std::cout << "Writing HelloWorld, count " << count << std::endl;
    retcode = hello_world_writer->write(*sample, DDS_HANDLE_NIL);
    if (retcode != DDS_RETCODE_OK) {
      std::cerr << "write error " << retcode << std::endl;
    }

    // Send every 4 seconds
    DDS_Duration_t send_period = { 0, 100 };
    NDDSUtility::sleep(send_period);
  }

  retcode = HelloWorld_v1TypeSupport::delete_data(sample);
  if (retcode != DDS_RETCODE_OK) {
    std::cerr << "HelloWorldTypeSupport::delete_data error " << retcode
              << std::endl;
  }

  retcode = participant->delete_contained_entities();
  DDSDomainParticipantFactory::get_instance()->delete_participant(participant);

  DDSDomainParticipantFactory::finalize_instance();

  return 0;
}
