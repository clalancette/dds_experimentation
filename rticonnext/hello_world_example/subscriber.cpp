#include <signal.h>

#include <iostream>
#include <memory>

#include <ndds/ndds_cpp.h>

#include "HelloWorld_v1.h"
#include "HelloWorld_v1Support.h"

#include "HelloWorld_v2.h"
#include "HelloWorld_v2Support.h"

#include "HelloWorld_v3.h"
#include "HelloWorld_v3Support.h"

static volatile int running = 1;

static void sigint_handler(int signal)
{
  running = 0;
}

class ParticipantListener final : public DDSDomainParticipantListener
{
public:
  // override on DDSTopicListener
  void on_inconsistent_topic(DDSTopic * topic, const DDS_InconsistentTopicStatus & status) override
  {
    fprintf(stderr, "ParticipantListener: on_inconsistent_topic\n");
  }

  // override on DDSSubscriberListener
  void on_data_on_readers(DDSSubscriber * sub) override
  {
    (void)sub;
    fprintf(stderr, "ParticipantListener: on_data_on_readers\n");
  }

  // override from DDSDataWriterListener
  void on_offered_deadline_missed(DDSDataWriter * writer, const DDS_OfferedDeadlineMissedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_offered_deadline_missed\n");
  }

  // override from DDSDataWriterListener
  void on_liveliness_lost(DDSDataWriter * writer, const DDS_LivelinessLostStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_liveliness_lost\n");
  }

  // override from DDSDataWriterListener
  void on_offered_incompatible_qos(DDSDataWriter * writer, const DDS_OfferedIncompatibleQosStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_offered_incompatible_qos\n");
  }

  // override from DDSDataWriterListener
  void on_publication_matched(DDSDataWriter * writer, const DDS_PublicationMatchedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_publication_matched\n");
  }

  // override from DDSDataWriterListener
  void on_reliable_writer_cache_changed(DDSDataWriter * writer, const DDS_ReliableWriterCacheChangedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_reliable_writer_cache_changed\n");
  }

  // override from DDSDataWriterListener
  void on_reliable_reader_activity_changed(DDSDataWriter * writer, const DDS_ReliableReaderActivityChangedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_reliable_reader_activity_changed\n");
  }

  // override from DDSDataWriterListener
  void on_destination_unreachable(DDSDataWriter * writer, const DDS_InstanceHandle_t & handle, const DDS_Locator_t & destination) override
  {
    (void)writer;
    (void)handle;
    (void)destination;
    fprintf(stderr, "ParticipantListener: on_destination_unreachable\n");
  }

  // override from DDSDataWriterListener
  void * on_data_request(DDSDataWriter * writer, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "ParticipantListener: on_data_request\n");
    return nullptr;
  }

  // override from DDSDataWriterListener
  void on_data_return(DDSDataWriter * writer, void * instance_data, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "ParticipantListener: on_data_return\n");
  }

  // override from DDSDataWriterListener
  void on_sample_removed(DDSDataWriter * writer, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "ParticipantListener: on_sample_removed\n");
  }

  // override from DDSDataWriterListener
  void on_instance_replaced(DDSDataWriter * writer, const DDS_InstanceHandle_t & handle) override
  {
    (void)writer;
    (void)handle;
    fprintf(stderr, "ParticipantListener: on_instance_replaced\n");
  }

  // override from DDSDataWriterListener
  void on_application_acknowledgment(DDSDataWriter * writer, const DDS_AcknowledgmentInfo & info) override
  {
    (void)writer;
    (void)info;
    fprintf(stderr, "ParticipantListener: on_application_acknowledgement\n");
  }

  // override from DDSDataWriterListener
  void on_service_request_accepted(DDSDataWriter * writer, const DDS_ServiceRequestAcceptedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_service_request_accepted\n");
  }

  // override from DDSDataReaderListener
  void on_requested_deadline_missed(DDSDataReader * reader, const DDS_RequestedDeadlineMissedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_requested_deadline_missed\n");
  }

  // override from DDSDataReaderListener
  void on_liveliness_changed(DDSDataReader * reader, const DDS_LivelinessChangedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_liveliness_changed\n");
  }

  // override from DDSDataReaderListener
  void on_requested_incompatible_qos(DDSDataReader * reader, const DDS_RequestedIncompatibleQosStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_requested_incompatible_qos\n");
  }

  // override from DDSDataReaderListener
  void on_sample_rejected(DDSDataReader * reader, const DDS_SampleRejectedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_sample_rejected\n");
  }

  // override from DDSDataReaderListener
  void on_data_available(DDSDataReader * reader) override
  {
    (void)reader;
    fprintf(stderr, "ParticipantListener: on_data_available\n");
  }

  // override from DDSDataReaderListener
  void on_sample_lost(DDSDataReader * reader, const DDS_SampleLostStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_sample_lost\n");
  }

  // override from DDSDataReaderListener
  void on_subscription_matched(DDSDataReader * reader, const DDS_SubscriptionMatchedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ParticipantListener: on_subscription_matched\n");
  }
};

class SubscriberListener final : public DDSSubscriberListener
{
public:
  // override on DDSSubscriberListener
  void on_data_on_readers(DDSSubscriber * sub) override
  {
    (void)sub;
    fprintf(stderr, "SubscriberListener: on_data_on_readers\n");
  }

  // override from DDSDataReaderListener
  void on_requested_deadline_missed(DDSDataReader * reader, const DDS_RequestedDeadlineMissedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_requested_deadline_missed\n");
  }

  // override from DDSDataReaderListener
  void on_liveliness_changed(DDSDataReader * reader, const DDS_LivelinessChangedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_liveliness_changed\n");
  }

  // override from DDSDataReaderListener
  void on_requested_incompatible_qos(DDSDataReader * reader, const DDS_RequestedIncompatibleQosStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_requested_incompatible_qos\n");
  }

  // override from DDSDataReaderListener
  void on_sample_rejected(DDSDataReader * reader, const DDS_SampleRejectedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_sample_rejected\n");
  }

  // override from DDSDataReaderListener
  void on_data_available(DDSDataReader * reader) override
  {
    (void)reader;
    fprintf(stderr, "SubscriberListener: on_data_available\n");
  }

  // override from DDSDataReaderListener
  void on_sample_lost(DDSDataReader * reader, const DDS_SampleLostStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_sample_lost\n");
  }

  // override from DDSDataReaderListener
  void on_subscription_matched(DDSDataReader * reader, const DDS_SubscriptionMatchedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "SubscriberListener: on_subscription_matched\n");
  }
};

class ReaderListener final : public DDSDataReaderListener
{
public:
  // override from DDSDataReaderListener
  void on_requested_deadline_missed(DDSDataReader * reader, const DDS_RequestedDeadlineMissedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ReaderListener: on_requested_deadline_missed\n");
  }

  // override from DDSDataReaderListener
  void on_liveliness_changed(DDSDataReader * reader, const DDS_LivelinessChangedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ReaderListener: on_liveliness_changed\n");
  }

  // override from DDSDataReaderListener
  void on_requested_incompatible_qos(DDSDataReader * reader, const DDS_RequestedIncompatibleQosStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ReaderListener: on_requested_incompatible_qos\n");
  }

  // override from DDSDataReaderListener
  void on_sample_rejected(DDSDataReader * reader, const DDS_SampleRejectedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ReaderListener: on_sample_rejected\n");
  }

  // override from DDSDataReaderListener
  void on_data_available(DDSDataReader * reader) override
  {
    (void)reader;
    fprintf(stderr, "ReaderListener: on_data_available\n");
  }

  // override from DDSDataReaderListener
  void on_sample_lost(DDSDataReader * reader, const DDS_SampleLostStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ReaderListener: on_sample_lost\n");
  }

  // override from DDSDataReaderListener
  void on_subscription_matched(DDSDataReader * reader, const DDS_SubscriptionMatchedStatus & status) override
  {
    (void)reader;
    (void)status;
    fprintf(stderr, "ReaderListener: on_subscription_matched\n");
  }
};

class TopicListener final : public DDSTopicListener
{
public:
  // When there is both a participant listener and a topic listener on_inconsistent_topic callback registered, only the Topic one gets called
  void on_inconsistent_topic(DDSTopic * topic, const DDS_InconsistentTopicStatus & status) override
  {
    fprintf(stderr, "TopicListener: on_inconsistent_topic\n");
  }
};

class SubBase
{
public:
  virtual bool init() = 0;

  virtual void run() = 0;

  virtual ~SubBase()
  {
  }
};

template<typename TSEQ, typename TS, typename DR>
class HelloWorldSubscriber final : public SubBase
{
public:
  bool init() override
  {
    participant_listener_ = new ParticipantListener;

    // A DomainParticipant allows an application to begin communicating in
    // a DDS domain. Typically there is one DomainParticipant per application.
    // DomainParticipant QoS is configured in USER_QOS_PROFILES.xml
    participant_ = DDSDomainParticipantFactory::get_instance()->create_participant(0, DDS_PARTICIPANT_QOS_DEFAULT, participant_listener_, DDS_STATUS_MASK_ALL);
    if (participant_ == nullptr) {
      fprintf(stderr, "Failed to create participant\n");
      return false;
    }

    subscriber_listener_ = new SubscriberListener;

    // A Subscriber allows an application to create one or more DataReaders
    // Subscriber QoS is configured in USER_QOS_PROFILES.xml
    subscriber_ = participant_->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, subscriber_listener_, DDS_STATUS_MASK_ALL);
    if (subscriber_ == NULL) {
      fprintf(stderr, "Failed to create subscriber\n");
      return false;
    }

    // Register the datatype to use when creating the Topic
    const char * type_name = TS::get_type_name();
    DDS_ReturnCode_t retcode = TS::register_type(participant_, type_name);
    if (retcode != DDS_RETCODE_OK) {
      fprintf(stderr, "Failed to register type\n");
      return false;
    }

    topic_listener_ = new TopicListener;

    // A Topic has a name and a datatype. Create a Topic called
    // "HelloWorld Topic" with your registered data type
    topic_ = participant_->create_topic("hello_world_topic", type_name, DDS_TOPIC_QOS_DEFAULT, topic_listener_, DDS_STATUS_MASK_ALL);
    if (topic_ == nullptr) {
      fprintf(stderr, "Failed to create topic\n");
      return false;
    }

    reader_listener_ = new ReaderListener;

    // This DataReader will read data of type HelloWorld on Topic
    // "HelloWorld Topic". DataReader QoS is configured in
    // USER_QOS_PROFILES.xml
    reader_ = subscriber_->create_datareader(topic_, DDS_DATAREADER_QOS_DEFAULT, reader_listener_, DDS_STATUS_MASK_ALL);
    if (reader_ == nullptr) {
      fprintf(stderr, "Failed to create datareader\n");
      return false;
    }

    // Get status condition: Each entity has a Status Condition, which
    // gets triggered when a status becomes true
    DDSStatusCondition * status_condition = reader_->get_statuscondition();
    if (status_condition == nullptr) {
      fprintf(stderr, "Failed to get status condition\n");
      return false;
    }

    // Enable only the status we are interested in:
    //   DDS_DATA_AVAILABLE_STATUS
    retcode = status_condition->set_enabled_statuses(DDS_DATA_AVAILABLE_STATUS);
    if (retcode != DDS_RETCODE_OK) {
      fprintf(stderr, "Failed to set enabled statuses\n");
      return false;
    }

    // Create the WaitSet and attach the Status Condition to it. The WaitSet
    // will be woken when the condition is triggered.
    // This needs to be allocated so we can destroy it before finalizing in main
    waitset_ = new DDSWaitSet;
    retcode = waitset_->attach_condition(status_condition);
    if (retcode != DDS_RETCODE_OK) {
      fprintf(stderr, "Failed to attach condition to waitset\n");
      return false;
    }

    // A narrow is a cast from a generic DataReader to one that is specific
    // to your type. Use the type specific DataReader to read data
    hello_world_reader_ = DR::narrow(reader_);
    if (hello_world_reader_ == nullptr) {
      fprintf(stderr, "Failed to narrow type\n");
      return false;
    }

    return true;
  }

  ~HelloWorldSubscriber()
  {
    delete waitset_;

    delete subscriber_listener_;

    delete reader_listener_;

    delete participant_listener_;

    delete topic_listener_;

    if (participant_ != nullptr) {
      DDS_ReturnCode_t retcode = participant_->delete_contained_entities();
      DDSDomainParticipantFactory::get_instance()->delete_participant(participant_);
    }
  }

  void run() override
  {
    DDS_ReturnCode_t retcode;

    while (running) {
      DDSConditionSeq active_conditions_seq;

      // wait() blocks execution of the thread until one or more attached
      // Conditions become true, or until a user-specified timeout expires.
      DDS_Duration_t wait_timeout = { 0, 100 * 1000 * 1000 };
      retcode = waitset_->wait(active_conditions_seq, wait_timeout);

      // You get a timeout if no conditions were triggered before the timeout
      if (retcode == DDS_RETCODE_TIMEOUT) {
        continue;
      } else if (retcode != DDS_RETCODE_OK) {
        std::cerr << "wait returned error: " << retcode << std::endl;
        break;
      }

      // Get the status changes to check which status condition
      // triggered the WaitSet to wake
      DDS_StatusMask triggeredmask = hello_world_reader_->get_status_changes();

      // If the status is "Data Available"
      if (triggeredmask & DDS_DATA_AVAILABLE_STATUS) {
        fprintf(stderr, "Data available\n");
        TSEQ data_seq;
        DDS_SampleInfoSeq info_seq;

        retcode = hello_world_reader_->take(data_seq, info_seq);
        if (retcode != DDS_RETCODE_OK) {
          fprintf(stderr, "Take error\n");
          continue;
        }

        for (int i = 0; i < data_seq.length(); ++i) {
          if (!info_seq[i].valid_data) {
            fprintf(stderr, "Received instance state notification\n");
            continue;
          }

          TS::print_data(&data_seq[i]);
        }

        hello_world_reader_->return_loan(data_seq, info_seq);
      }
    }
  }

private:
  DDSDomainParticipant * participant_{nullptr};
  DDSSubscriber * subscriber_{nullptr};
  DDSTopic * topic_{nullptr};
  DDSDataReader * reader_{nullptr};
  DDSWaitSet * waitset_{nullptr};
  SubscriberListener * subscriber_listener_{nullptr};
  ReaderListener * reader_listener_{nullptr};
  ParticipantListener * participant_listener_{nullptr};
  TopicListener * topic_listener_{nullptr};
  DR * hello_world_reader_{nullptr};
};

int main(int argc, char ** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <v1|v2|v3>\n", argv[0]);
    return 1;
  }

  std::string user_type = argv[1];

  {
    std::unique_ptr<SubBase> mysub;
    if (user_type == "v1") {
      mysub = std::make_unique<HelloWorldSubscriber<HelloWorld_v1Seq, HelloWorld_v1TypeSupport, HelloWorld_v1DataReader>>();
    } else if (user_type == "v2") {
      mysub = std::make_unique<HelloWorldSubscriber<HelloWorld_v2Seq, HelloWorld_v2TypeSupport, HelloWorld_v2DataReader>>();
    } else if (user_type == "v3") {
      mysub = std::make_unique<HelloWorldSubscriber<HelloWorld_v3Seq, HelloWorld_v3TypeSupport, HelloWorld_v3DataReader>>();
    } else {
      fprintf(stderr, "Invalid argument; must be one of v1, v2, v3\n");
      return 1;
    }

    if (!mysub->init()) {
      fprintf(stderr, "Failed to initialize subscriber\n");
      return 1;
    }

    signal(SIGINT, sigint_handler);

    mysub->run();
  }

  DDSDomainParticipantFactory::finalize_instance();

  return 0;
}
