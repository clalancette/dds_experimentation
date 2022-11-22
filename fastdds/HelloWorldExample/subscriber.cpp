#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/TopicListener.hpp>

#include "HelloWorld_v1PubSubTypes.h"

class CustomTopicListener final : public eprosima::fastdds::dds::TopicListener
{
public:

    CustomTopicListener()
    : TopicListener()
    {
      std::cout << " create custom topic listener" << std::endl;
    }

    //// Not working
    virtual void on_inconsistent_topic(
      eprosima::fastdds::dds::Topic* topic,
      eprosima::fastdds::dds::InconsistentTopicStatus status)
    {
      (void)topic;
      (void)status;
      std::cout << " Inconsistent topic received discovered" << std::endl;
    }
};

class HelloWorldSubscriber final
{
public:

  HelloWorldSubscriber()
  : participant_(nullptr),
    subscriber_(nullptr),
    topic_(nullptr),
    reader_(nullptr),
    type_(new HelloWorld_v1PubSubType())
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
  }

  //!Initialize the subscriber
  bool init()
  {
    eprosima::fastdds::dds::DomainParticipantQos pqos;
    pqos.name("Participant_sub");
    participant_ = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, pqos);

    if (participant_ == nullptr) {
      return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE SUBSCRIBER
    subscriber_ = participant_->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);

    if (subscriber_ == nullptr) {
      return false;
    }

    std::cout << " Print data type: " << type_.get_type_name() << std::endl;
    CustomTopicListener custom_listener;

    //CREATE THE TOPIC
    topic_ = participant_->create_topic(
        "HelloWorldTopic",
        type_.get_type_name(),
        eprosima::fastdds::dds::TOPIC_QOS_DEFAULT,
        &custom_listener
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
  void run()
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

  class SubListener final : public eprosima::fastdds::dds::DataReaderListener
  {
  public:

    SubListener()
    : matched_(0),
      samples_(0)
    {
    }

    ~SubListener() override
    {
    }

    void on_data_available(
      eprosima::fastdds::dds::DataReader* reader) override
    {
      eprosima::fastdds::dds::SampleInfo info;
      HelloWorld_v1 msg;

      //// Note: experimentation
      eprosima::fastdds::dds::InstanceHandle_t no_handle;
      eprosima::fastdds::dds::builtin::PublicationBuiltinTopicData publications;
      reader->get_matched_publication_data(publications, no_handle);
      const auto vec2 = publications.user_data.data_vec();
      for (auto &x: vec2) {
        std::cout << x << std::endl;
      }
      std::cout << "--> Finished printing pub user data of size: " << vec2.size() << std::endl;

      if (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.instance_state == eprosima::fastdds::dds::ALIVE_INSTANCE_STATE) {
          samples_++;
          // Print your structure data here.
          std::cout << "Message " << msg.message() << " " << " RECEIVED" << std::endl;
        }
      }
    }

    void on_subscription_matched(
      eprosima::fastdds::dds::DataReader* reader,
      const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override
    {
      if (info.current_count_change == 1) {
        matched_ = info.total_count;
        std::cout << "Subscriber matched." << std::endl;

        /// TODO: (YL) test implementation of user data
        std::cout << "--- detected participants: " << std::endl;
        const auto parts = listener_participant_->get_participant_names();
        for (auto &p: parts) {
          std::cout << p << std::endl;
        }

        std::vector<eprosima::fastdds::dds::InstanceHandle_t> test_handles;
        listener_participant_->get_discovered_participants(test_handles);
        std::cout << "--- Handle participant sizes "
                  << test_handles.size() << std::endl;

        eprosima::fastdds::dds::InstanceHandle_t no_handle;
        eprosima::fastdds::dds::builtin::ParticipantBuiltinTopicData participants_data;
        listener_participant_->get_discovered_participant_data(participants_data, no_handle);
        const auto vec = participants_data.user_data.data_vec();
        for (auto &x: vec) {
          std::cout << x << std::endl;
        }
        std::cout << "--> Finished printing part user data of size: " << vec.size() << std::endl;
      } else if (info.current_count_change == -1) {
        matched_ = info.total_count;
        std::cout << "Subscriber unmatched." << std::endl;
      } else {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
      }
    }

    int matched_;

    uint32_t samples_;
    eprosima::fastdds::dds::DomainParticipant* listener_participant_;
  }
  listener_;
};


int main(int argc, char** argv)
{
  HelloWorldSubscriber mysub;

  if (!mysub.init()) {
    fprintf(stderr, "Failed to initialize subscriber\n");
    return 1;
  }

  mysub.run(10);

  return 0;
}
