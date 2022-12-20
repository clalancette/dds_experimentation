#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/TopicListener.hpp>

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

class MySubscriberListener final : public eprosima::fastdds::dds::SubscriberListener
{
public:
  // override from SubscriberListener
  void on_data_on_readers(eprosima::fastdds::dds::Subscriber * sub) override
  {
    (void)sub;
    fprintf(stderr, "SubscriberListener: on_data_on_readers\n");
  }

  // override from DataReaderListener
  void on_data_available(eprosima::fastdds::dds::DataReader * reader) override
  {
    (void)reader;
    fprintf(stderr, "SubscriberListener: on_data_available\n");
  }

  // override from DataReaderListener
  void on_subscription_matched(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override
  {
    (void)reader;
    (void)info;
    fprintf(stderr, "SubscriberListener: on_subscription_matched\n");
  }

  // override from DataReaderListener
  void on_requested_deadline_missed(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastrtps::RequestedDeadlineMissedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_requested_deadline_missed\n");
  }

  // override from DataReaderListener
  void on_liveliness_changed(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastrtps::LivelinessChangedStatus& status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_liveliness_changed\n");
  }

  // override from DataReaderListener
  void on_sample_rejected(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastrtps::SampleRejectedStatus& status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_sample_rejected\n");
  }

  // override from DataReaderListener
  void on_requested_incompatible_qos(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastdds::dds::RequestedIncompatibleQosStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_requested_incompatible_qos\n");
  }

  // override from DataReaderListener
  void on_sample_lost(
          eprosima::fastdds::dds::DataReader * reader,
          const eprosima::fastdds::dds::SampleLostStatus& status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_sample_lost\n");
  }
};

class MyTopicListener final : public eprosima::fastdds::dds::TopicListener
{
public:
  void on_inconsistent_topic(
    eprosima::fastdds::dds::Topic* topic,
    eprosima::fastdds::dds::InconsistentTopicStatus status) override
  {
    (void)topic;
    (void)status;
    fprintf(stderr, "TopicListener: on_inconsistent_topic\n");
  }
};

class SubBase
{
public:
  virtual bool init() = 0;

  virtual void run() = 0;
};

template<typename TYPE, typename PUBSUBTYPE>
class HelloWorldSubscriber final : public SubBase
{
public:

  HelloWorldSubscriber()
  : participant_(nullptr),
    subscriber_(nullptr),
    topic_(nullptr),
    reader_(nullptr),
    type_(new PUBSUBTYPE())
  {
  }

  virtual ~HelloWorldSubscriber()
  {
    if (reader_ != nullptr) {
      subscriber_->delete_datareader(reader_);
    }
    if (topic_ != nullptr) {
      participant_->delete_topic(topic_);
    }
    if (subscriber_ != nullptr) {
      participant_->delete_subscriber(subscriber_);
    }
    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);

    delete participant_listener_;

    delete subscriber_listener_;

    delete topic_listener_;
  }

  //!Initialize the subscriber
  bool init() override
  {
    participant_listener_ = new MyParticipantListener;

    eprosima::fastdds::dds::DomainParticipantQos pqos;
    pqos.name("Participant_sub");
    //participant_ = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, pqos, participant_listener_);
    participant_ = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, pqos);

    if (participant_ == nullptr) {
      return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    subscriber_listener_ = new MySubscriberListener;

    //CREATE THE SUBSCRIBER
    //subscriber_ = participant_->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, subscriber_listener_);
    subscriber_ = participant_->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);

    if (subscriber_ == nullptr) {
      return false;
    }

    std::cout << " Print data type: " << type_.get_type_name() << std::endl;

    topic_listener_ = new MyTopicListener;

    //CREATE THE TOPIC
    topic_ = participant_->create_topic(
        "HelloWorldTopic",
        type_.get_type_name(),
        eprosima::fastdds::dds::TOPIC_QOS_DEFAULT,
        topic_listener_
        );

    if (topic_ == nullptr) {
      return false;
    }

    // CREATE THE READER
    eprosima::fastdds::dds::DataReaderQos rqos = eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT;
    rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    reader_ = subscriber_->create_datareader(topic_, rqos, &listener_);

    listener_.listener_participant_ = participant_;

    if (reader_ == nullptr) {
      return false;
    }

    return true;
  }

  //!RUN the subscriber
  void run() override
  {
    std::cout << "Subscriber running. Please press enter to stop the Subscriber" << std::endl;
    std::cin.ignore();
  }

  //!Run the subscriber until number samples have been received.
  void run(uint32_t number)
  {
    std::cout << "Subscriber running until " << number << " samples have been received" << std::endl;
    while (number > listener_.samples_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }

private:

  eprosima::fastdds::dds::DomainParticipant* participant_;

  eprosima::fastdds::dds::Subscriber* subscriber_;

  eprosima::fastdds::dds::Topic* topic_;

  eprosima::fastdds::dds::DataReader* reader_;

  eprosima::fastdds::dds::TypeSupport type_;

  MyParticipantListener * participant_listener_{nullptr};

  MySubscriberListener * subscriber_listener_{nullptr};

  MyTopicListener * topic_listener_{nullptr};

  class MyDataReaderListener final : public eprosima::fastdds::dds::DataReaderListener
  {
  public:

    MyDataReaderListener()
    : matched_(0),
      samples_(0)
    {
    }

    ~MyDataReaderListener() override
    {
    }

    void on_data_available(
      eprosima::fastdds::dds::DataReader* reader) override
    {
      fprintf(stderr, "DataReaderListener: on_data_available\n");

      eprosima::fastdds::dds::SampleInfo info;
      TYPE msg;

      if (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.instance_state == eprosima::fastdds::dds::ALIVE_INSTANCE_STATE) {
          samples_++;
          // Print your structure data here.
          std::cout << "Message " << msg.index() << ", " << msg.message() << std::endl;
        }
      }
    }

    void on_subscription_matched(
      eprosima::fastdds::dds::DataReader* reader,
      const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override
    {
      fprintf(stderr, "DataReaderListener: on_subscription_matched\n");

      if (info.current_count_change == 1) {
        matched_ = info.total_count;
      } else if (info.current_count_change == -1) {
        matched_ = info.total_count;
      } else {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
      }
    }

    void on_requested_deadline_missed(
      eprosima::fastdds::dds::DataReader * reader,
      const eprosima::fastrtps::RequestedDeadlineMissedStatus & status) override
    {
      (void)reader;
      (void)status;
      fprintf(stderr, "DataReaderListener: on_requested_deadline_missed\n");
    }

    void on_liveliness_changed(
      eprosima::fastdds::dds::DataReader * reader,
      const eprosima::fastrtps::LivelinessChangedStatus& status) override
    {
      (void)reader;
      (void)status;
      fprintf(stderr, "DataReaderListener: on_liveliness_changed\n");
    }

    void on_sample_rejected(
      eprosima::fastdds::dds::DataReader * reader,
      const eprosima::fastrtps::SampleRejectedStatus& status) override
    {
      (void)reader;
      (void)status;
      fprintf(stderr, "DataReaderListener: on_sample_rejected\n");
    }

    void on_requested_incompatible_qos(
      eprosima::fastdds::dds::DataReader * reader,
      const eprosima::fastdds::dds::RequestedIncompatibleQosStatus & status) override
    {
      (void)reader;
      (void)status;
      fprintf(stderr, "DataReaderListener: on_requested_incompatible_qos\n");
    }

    void on_sample_lost(
      eprosima::fastdds::dds::DataReader * reader,
      const eprosima::fastdds::dds::SampleLostStatus& status) override
    {
      (void)reader;
      (void)status;
      fprintf(stderr, "DataReaderListener: on_sample_lost\n");
    }

    int matched_;

    uint32_t samples_;
    eprosima::fastdds::dds::DomainParticipant* listener_participant_;
  }
  listener_;
};


int main(int argc, char ** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1|v2|v3>\n", argv[0]);
    return 1;
  }

  std::string type = argv[1];

  std::unique_ptr<SubBase> mysub;
  if (type == "v1") {
    mysub = std::make_unique<HelloWorldSubscriber<HelloWorld_v1, HelloWorld_v1PubSubType>>();
  } else if (type == "v2") {
    mysub = std::make_unique<HelloWorldSubscriber<HelloWorld_v2, HelloWorld_v2PubSubType>>();
  } else if (type == "v3") {
    mysub = std::make_unique<HelloWorldSubscriber<HelloWorld_v3, HelloWorld_v3PubSubType>>();
  } else {
    fprintf(stderr, "Invalid argument; must be one of v1, v2, v3\n");
    return 2;
  }

  if (!mysub->init()) {
    fprintf(stderr, "Failed to initialize subscriber\n");
    return 1;
  }

  mysub->run();

  return 0;
}
