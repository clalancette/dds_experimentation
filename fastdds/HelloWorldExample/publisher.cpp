#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/PublisherListener.hpp>

#include "HelloWorld_v1PubSubTypes.h"
#include "HelloWorld_v2PubSubTypes.h"
#include "HelloWorld_v3PubSubTypes.h"

class MyParticipantListener final : public eprosima::fastdds::dds::DomainParticipantListener
{
public:
  // override from DomainParticipantListener
  void on_participant_discovery(
          eprosima::fastdds::dds::DomainParticipant * participant,
          eprosima::fastrtps::rtps::ParticipantDiscoveryInfo && info) override
  {
    (void)participant;
    (void)info;
    fprintf(stderr, "ParticipantListener: on_participant_discovery\n");
  }

  // override from DomainParticipantListener
  void on_subscriber_discovery(
          eprosima::fastdds::dds::DomainParticipant * participant,
          eprosima::fastrtps::rtps::ReaderDiscoveryInfo && info) override
  {
    (void)participant;
    (void)info;
    fprintf(stderr, "ParticipantListener: on_subscriber_discovery\n");
  }

  // override from DomainParticipantListener
  void on_publisher_discovery(
          eprosima::fastdds::dds::DomainParticipant * participant,
          eprosima::fastrtps::rtps::WriterDiscoveryInfo && info) override
  {
    (void)participant;
    (void)info;
    fprintf(stderr, "ParticipantListener: on_publisher_discovery\n");
  }

  // override from DomainParticipantListener
  void on_type_discovery(
          eprosima::fastdds::dds::DomainParticipant * participant,
          const eprosima::fastrtps::rtps::SampleIdentity & request_sample_id,
          const eprosima::fastrtps::string_255 & topic,
          const eprosima::fastrtps::types::TypeIdentifier * identifier,
          const eprosima::fastrtps::types::TypeObject * object,
          eprosima::fastrtps::types::DynamicType_ptr dyn_type) override
  {
    (void)participant;
    (void)request_sample_id;
    (void)topic;
    (void)identifier;
    (void)object;
    (void)dyn_type;
    fprintf(stderr, "ParticipantListener: on_type_discovery\n");
  }

  // override from DomainParticipantListener
  void on_type_dependencies_reply(
          eprosima::fastdds::dds::DomainParticipant* participant,
          const eprosima::fastrtps::rtps::SampleIdentity & request_sample_id,
          const eprosima::fastrtps::types::TypeIdentifierWithSizeSeq & dependencies) override
  {
    (void)participant;
    (void)request_sample_id;
    (void)dependencies;
    fprintf(stderr, "ParticipantListener: on_type_dependencies_reply\n");
  }

  // override from DomainParticipantListener
  void on_type_information_received(
          eprosima::fastdds::dds::DomainParticipant * participant,
          const eprosima::fastrtps::string_255 topic_name,
          const eprosima::fastrtps::string_255 type_name,
          const eprosima::fastrtps::types::TypeInformation & type_information) override
  {
    (void)participant;
    (void)topic_name;
    (void)type_name;
    (void)type_information;
    fprintf(stderr, "ParticipantListener: on_type_information_received\n");
  }

  // override from PublisherListener
  void on_publication_matched(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::PublicationMatchedStatus & info) override
  {
    (void)writer;
    (void)info;
    fprintf(stderr, "ParticipantListener: on_publication_matched\n");
  }

  // override from PublisherListener
  void on_offered_deadline_missed(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::OfferedDeadlineMissedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_offered_deadline_missed\n");
  }

  // override from PublisherListener
  void on_offered_incompatible_qos(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::OfferedIncompatibleQosStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_offered_incompatible_qos\n");
  }

  // override from PublisherListener
  void on_liveliness_lost(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::LivelinessLostStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_liveliness_lost\n");
  }

  // override from SubscriberListener
  void on_data_on_readers(eprosima::fastdds::dds::Subscriber * sub) override
  {
    (void)sub;
    fprintf(stderr, "ParticipantListener: on_data_on_readers\n");
  }

  // override from DataReaderListener
  void on_data_available(eprosima::fastdds::dds::DataReader * reader) override
  {
    (void)reader;
    fprintf(stderr, "ParticipantListener: on_data_available\n");
  }

  // override from DataReaderListener
  void on_subscription_matched(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override
  {
    (void)reader;
    (void)info;
    fprintf(stderr, "ParticipantListener: on_subscription_matched\n");
  }

  // override from DataReaderListener
  void on_requested_deadline_missed(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastrtps::RequestedDeadlineMissedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_requested_deadline_missed\n");
  }

  // override from DataReaderListener
  void on_liveliness_changed(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastrtps::LivelinessChangedStatus& status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_liveliness_changed\n");
  }

  // override from DataReaderListener
  void on_sample_rejected(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastrtps::SampleRejectedStatus& status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_sample_rejected\n");
  }

  // override from DataReaderListener
  void on_requested_incompatible_qos(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastdds::dds::RequestedIncompatibleQosStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_requested_incompatible_qos\n");
  }

  // override from DataReaderListener
  void on_sample_lost(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastdds::dds::SampleLostStatus& status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_sample_lost\n");
  }

  // override from TopicListener
  void on_inconsistent_topic(
          eprosima::fastdds::dds::Topic * topic,
          eprosima::fastdds::dds::InconsistentTopicStatus status)
  {
    (void)topic;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_inconsistent_topic\n");
  }
};

class MyPublisherListener final : public eprosima::fastdds::dds::PublisherListener
{
public:
  void on_publication_matched(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::PublicationMatchedStatus & info) override
  {
    (void)writer;
    (void)info;
    fprintf(stderr, "PublisherListener: on_publication_matched\n");
  }

  void on_offered_deadline_missed(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::OfferedDeadlineMissedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_offered_deadline_missed\n");
  }

  void on_offered_incompatible_qos(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::OfferedIncompatibleQosStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_offered_incompatible_qos\n");
  }

  void on_liveliness_lost(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::LivelinessLostStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_liveliness_lost\n");
  }
};

class MyDataWriterListener final : public eprosima::fastdds::dds::DataWriterListener
{
public:
  void on_publication_matched(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::PublicationMatchedStatus & info) override
  {
    (void)writer;
    (void)info;
    fprintf(stderr, "DataWriterListener: on_publication_matched\n");
    if (info.current_count_change == 1) {
      matched_ = info.total_count;
      firstConnected_ = true;
    } else if (info.current_count_change == -1) {
      matched_ = info.total_count;
    }
  }

  void on_offered_deadline_missed(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::OfferedDeadlineMissedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_offered_deadline_missed\n");
  }

  void on_offered_incompatible_qos(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::OfferedIncompatibleQosStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_offered_incompatible_qos\n");
  }

  void on_liveliness_lost(
          eprosima::fastdds::dds::DataWriter * writer,
          const eprosima::fastdds::dds::LivelinessLostStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_liveliness_lost\n");
  }

  int matched_;

  bool firstConnected_;
};

class PubBase
{
public:
  virtual bool init() = 0;

  virtual void run(uint32_t samples, uint32_t sleep_ms) = 0;
};

template<typename TYPE, typename PUBSUBTYPE, bool isV3>
class HelloWorldPublisher final : public PubBase
{
public:

  HelloWorldPublisher()
  : participant_(nullptr),
    publisher_(nullptr),
    topic_(nullptr),
    writer_(nullptr),
    type_(new PUBSUBTYPE())
  {
  }

  virtual ~HelloWorldPublisher()
  {
    if (writer_ != nullptr) {
      publisher_->delete_datawriter(writer_);
    }
    if (publisher_ != nullptr) {
      participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr) {
      participant_->delete_topic(topic_);
    }

    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);

    delete participant_listener_;

    delete pub_listener_;

    delete data_writer_listener_;
  }

  //!Initialize
  bool init() override
  {
    hello_.index(0);
    if constexpr(isV3) {
#if defined(V3T1) || defined(V3T2)
      hello_.message("Hello World");
#elif defined(V3T3)
      hello_.message(54.34);
#endif
    } else {
      hello_.message("Hello World");
    }

    participant_listener_ = new MyParticipantListener;

    eprosima::fastdds::dds::DomainParticipantQos pqos;
    pqos.name("Participant_pub");
    participant_ = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, pqos, participant_listener_);
    // ====================================================

    if (participant_ == nullptr) {
      return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    pub_listener_ = new MyPublisherListener;

    //CREATE THE PUBLISHER
    publisher_ = participant_->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT, pub_listener_);

    if (publisher_ == nullptr) {
      return false;
    }

    topic_ = participant_->create_topic(
        "HelloWorldTopic",
        type_.get_type_name(),
        eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr) {
      return false;
    }

    data_writer_listener_ = new MyDataWriterListener;

    // CREATE THE WRITER
    writer_ = publisher_->create_datawriter(topic_, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, data_writer_listener_);

    if (writer_ == nullptr) {
      return false;
    }
    return true;
  }

  //!Publish a sample
  bool publish(bool waitForListener = true)
  {
    /// return false if no match, script will just wait for matching listener
    if (data_writer_listener_->firstConnected_ || !waitForListener || data_writer_listener_->matched_ > 0)
    {
      hello_.index(hello_.index() + 1);
      writer_->write(&hello_);
      return true;
    }
    return false;
  }

  //!Run for number samples
  void run(uint32_t samples, uint32_t sleep_ms) override
  {
    stop_ = false;
    std::thread thread(&HelloWorldPublisher::runThread, this, samples, sleep_ms);
    if (samples == 0) {
      std::cout << "Publisher running. Please press enter to stop the Publisher at any time." << std::endl;
      std::cin.ignore();
      stop_ = true;
    } else {
      std::cout << "Publisher running " << samples << " samples." << std::endl;
    }
    thread.join();
  }

private:

  TYPE hello_;

  eprosima::fastdds::dds::DomainParticipant* participant_;

  eprosima::fastdds::dds::Publisher* publisher_;

  eprosima::fastdds::dds::Topic* topic_;

  eprosima::fastdds::dds::DataWriter* writer_;

  MyParticipantListener * participant_listener_{nullptr};

  MyPublisherListener * pub_listener_{nullptr};

  MyDataWriterListener * data_writer_listener_{nullptr};

  bool stop_;

  void runThread(uint32_t samples, uint32_t sleep_ms)
  {
    if (samples == 0) {
      while (!stop_) {
        if (publish(false)) {
          std::cout << "Message: " << hello_.message() << " with index: " << hello_.index()
                    << " SENT" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
      }
    } else {
      for (uint32_t i = 0; i < samples; ++i) {
        if (!publish()) {
          --i;
        } else {
          std::cout << "=== [Publisher]  Writing : " << std::endl;
          std::cout << "Message: (" << hello_.index() << ", " << hello_.message() << ")" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
      }
    }
  }

  eprosima::fastdds::dds::TypeSupport type_;
};

int main(int argc, char ** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1|v2|v3>\n", argv[0]);
    return 1;
  }

  uint32_t count = 10;
  uint32_t sleep_ms = 100;

  std::string type = argv[1];

  std::unique_ptr<PubBase> mypub;

  if (type == "v1") {
    mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v1, HelloWorld_v1PubSubType, false>>();
#if defined(V1T1)
    printf("Publishing type V1T1\n");
#elif defined(V1T2)
    printf("Publishing type V1T2\n");
#elif defined(V1T3)
    printf("Publishing type V1T3\n");
#endif
  } else if (type == "v2") {
    mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v2, HelloWorld_v2PubSubType, false>>();
#if defined(V2T1)
    printf("Publishing type V2T1\n");
#elif defined(V2T2)
    printf("Publishing type V2T2\n");
#elif defined(V2T3)
    printf("Publishing type V2T3\n");
#elif defined(V2T4)
    printf("Publishing type V2T4\n");
#endif
  } else if (type == "v3") {
    mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v3, HelloWorld_v3PubSubType, true>>();
#if defined(V3T1)
    printf("Publishing type V3T1\n");
#elif defined(V3T2)
    printf("Publishing type V3T2\n");
#elif defined(V3T3)
    printf("Publishing type V3T2\n");
#endif

  } else {
    fprintf(stderr, "Invalid argument; must be one of v1, v2, v3\n");
    return 2;
  }

  if (!mypub->init()) {
    fprintf(stderr, "Failed to initialize publisher\n");
    return 1;
  }

  mypub->run(count, sleep_ms);

  return 0;
}
