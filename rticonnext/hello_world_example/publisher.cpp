#include <iostream>
#include <memory>

#include <ndds/ndds_cpp.h>

#include "HelloWorld_v1.h"
#include "HelloWorld_v1Support.h"

#include "HelloWorld_v2.h"
#include "HelloWorld_v2Support.h"

#include "HelloWorld_v3.h"
#include "HelloWorld_v3Support.h"

class PubBase
{
public:
  virtual bool init() = 0;

  virtual void run(uint32_t samples, uint32_t sleep_ms) = 0;
};

template<typename T, typename TS, typename DW>
class HelloWorldPublisher final : public PubBase
{
public:
  bool init() override
  {
    // A DomainParticipant allows an application to begin communicating in
    // a DDS domain. Typically there is one DomainParticipant per application.
    // DomainParticipant QoS is configured in USER_QOS_PROFILES.xml
    participant_ = DDSDomainParticipantFactory::get_instance()->create_participant(0, DDS_PARTICIPANT_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
    if (participant_ == nullptr) {
      fprintf(stderr, "Failed to create participant\n");
      return false;
    }

    // A Publisher allows an application to create one or more DataWriters
    // Publisher QoS is configured in USER_QOS_PROFILES.xml
    publisher_ = participant_->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, NULL, DDS_STATUS_MASK_NONE);
    if (publisher_ == nullptr) {
      fprintf(stderr, "Failed to create publisher\n");
      return false;
    }

    // Register the datatype to use when creating the Topic
    const char * type_name = TS::get_type_name();
    DDS_ReturnCode_t retcode = TS::register_type(participant_, type_name);
    if (retcode != DDS_RETCODE_OK) {
      fprintf(stderr, "Failed to register type\n");
      return false;
    }

    // A Topic has a name and a datatype. Create a Topic called
    // "HelloWorld Topic" with your registered data type
    topic_ = participant_->create_topic("hello_world_topic", type_name, DDS_TOPIC_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
    if (topic_ == nullptr) {
      fprintf(stderr, "Failed to create topic\n");
      return false;
    }

    // This DataWriter will write data on Topic "HelloWorld Topic"
    // DataWriter QoS is configured in USER_QOS_PROFILES.xml
    writer_ = publisher_->create_datawriter(topic_, DDS_DATAWRITER_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
    if (writer_ == nullptr) {
      fprintf(stderr, "Failed to create writer\n");
      return false;
    }

    // A narrow is a cast from a generic DataWriter to one that is specific
    // to your type. Use the type specific DataWriter to write()
    hello_world_writer_ = DW::narrow(writer_);
    if (hello_world_writer_ == nullptr) {
      fprintf(stderr, "Failed to narrow writer\n");
      return false;
    }

    return true;
  }

  void run(uint32_t samples, uint32_t sleep_ms) override
  {
    DDS_ReturnCode_t retcode;

    // Create data sample for writing
    T * sample = TS::create_data();
    if (sample == nullptr) {
      fprintf(stderr, "Failed to create sample data\n");
      return;
    }

    for (unsigned long count = 0; count < samples; ++count) {
      sample->index = count;
      strcpy(sample->message, "Hello World");

      std::cout << "Writing HelloWorld, count " << count << std::endl;
      retcode = hello_world_writer_->write(*sample, DDS_HANDLE_NIL);
      if (retcode != DDS_RETCODE_OK) {
        std::cerr << "write error " << retcode << std::endl;
      }

      DDS_Duration_t send_period = { 0, sleep_ms * 1000 * 1000 };
      NDDSUtility::sleep(send_period);
    }

    retcode = TS::delete_data(sample);
    if (retcode != DDS_RETCODE_OK) {
      std::cerr << "HelloWorldTypeSupport::delete_data error " << retcode
                << std::endl;
    }
  }

  ~HelloWorldPublisher()
  {
    if (participant_ != nullptr) {
      DDS_ReturnCode_t retcode = participant_->delete_contained_entities();
      (void)retcode;
      DDSDomainParticipantFactory::get_instance()->delete_participant(participant_);
    }
  }

private:
  DDSDomainParticipant * participant_{nullptr};
  DDSPublisher * publisher_{nullptr};
  DDSTopic * topic_{nullptr};
  DDSDataWriter * writer_{nullptr};
  DW * hello_world_writer_{nullptr};
};

int main(int argc, char ** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1|v2|v3>\n", argv[0]);
    return 1;
  }

  std::string user_type = argv[1];

  {
    std::unique_ptr<PubBase> mypub;

    if (user_type == "v1") {
      mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v1, HelloWorld_v1TypeSupport, HelloWorld_v1DataWriter>>();
    } else if (user_type == "v2") {
      mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v2, HelloWorld_v2TypeSupport, HelloWorld_v2DataWriter>>();
    } else if (user_type == "v3") {
      mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v3, HelloWorld_v3TypeSupport, HelloWorld_v3DataWriter>>();
    } else {
      fprintf(stderr, "Invalid argument; must be one of v1, v2, v3\n");
      return 2;
    }

    if (!mypub->init()) {
      fprintf(stderr, "Failed to initialize publisher\n");
      return 3;
    }

    mypub->run(10, 100);
  }

  DDSDomainParticipantFactory::finalize_instance();

  return 0;
}
