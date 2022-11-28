#include <iostream>
#include <memory>

#include <ndds/ndds_cpp.h>

#include "HelloWorld_v1.h"
#include "HelloWorld_v1Support.h"

#include "HelloWorld_v2.h"
#include "HelloWorld_v2Support.h"

#include "HelloWorld_v3.h"
#include "HelloWorld_v3Support.h"

// DDSDomainParticipantListener derives from DDSTopicListener, DDSPublisherListener (DDSDataWriterListener), and DDSSubscriberListener (DDSDataReaderListener)
class ParticipantListener final : public DDSDomainParticipantListener
{
public:
  // override on DDSTopicListener
  void on_inconsistent_topic(DDSTopic * topic, const DDS_InconsistentTopicStatus & status) override
  {
    (void)topic;
    (void)status;
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

class PublisherListener final : public DDSPublisherListener
{
public:
  // override from DDSDataWriterListener
  void on_offered_deadline_missed(DDSDataWriter * writer, const DDS_OfferedDeadlineMissedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_offered_deadline_missed\n");
  }

  // override from DDSDataWriterListener
  void on_liveliness_lost(DDSDataWriter * writer, const DDS_LivelinessLostStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_liveliness_lost\n");
  }

  // override from DDSDataWriterListener
  void on_offered_incompatible_qos(DDSDataWriter * writer, const DDS_OfferedIncompatibleQosStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_offered_incompatible_qos\n");
  }

  // override from DDSDataWriterListener
  void on_publication_matched(DDSDataWriter * writer, const DDS_PublicationMatchedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_publication_matched\n");
  }

  // override from DDSDataWriterListener
  void on_reliable_writer_cache_changed(DDSDataWriter * writer, const DDS_ReliableWriterCacheChangedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_reliable_writer_cache_changed\n");
  }

  // override from DDSDataWriterListener
  void on_reliable_reader_activity_changed(DDSDataWriter * writer, const DDS_ReliableReaderActivityChangedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_reliable_reader_activity_changed\n");
  }

  // override from DDSDataWriterListener
  void on_destination_unreachable(DDSDataWriter * writer, const DDS_InstanceHandle_t & handle, const DDS_Locator_t & destination) override
  {
    (void)writer;
    (void)handle;
    (void)destination;
    fprintf(stderr, "PublisherListener: on_destination_unreachable\n");
  }

  // override from DDSDataWriterListener
  void * on_data_request(DDSDataWriter * writer, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "PublisherListener: on_data_request\n");
    return nullptr;
  }

  // override from DDSDataWriterListener
  void on_data_return(DDSDataWriter * writer, void * instance_data, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "PublisherListener: on_data_return\n");
  }

  // override from DDSDataWriterListener
  void on_sample_removed(DDSDataWriter * writer, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "PublisherListener: on_sample_removed\n");
  }

  // override from DDSDataWriterListener
  void on_instance_replaced(DDSDataWriter * writer, const DDS_InstanceHandle_t & handle) override
  {
    (void)writer;
    (void)handle;
    fprintf(stderr, "PublisherListener: on_instance_replaced\n");
  }

  // override from DDSDataWriterListener
  void on_application_acknowledgment(DDSDataWriter * writer, const DDS_AcknowledgmentInfo & info) override
  {
    (void)writer;
    (void)info;
    fprintf(stderr, "PublisherListener: on_application_acknowledgement\n");
  }

  // override from DDSDataWriterListener
  void on_service_request_accepted(DDSDataWriter * writer, const DDS_ServiceRequestAcceptedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "PublisherListener: on_service_request_accepted\n");
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

class DataWriterListener final : public DDSDataWriterListener
{
public:
  void on_offered_deadline_missed(DDSDataWriter * writer, const DDS_OfferedDeadlineMissedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_offered_deadline_missed\n");
  }

  void on_liveliness_lost(DDSDataWriter * writer, const DDS_LivelinessLostStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_liveliness_lost\n");
  }

  void on_offered_incompatible_qos(DDSDataWriter * writer, const DDS_OfferedIncompatibleQosStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_offered_incompatible_qos\n");
  }

  void on_publication_matched(DDSDataWriter * writer, const DDS_PublicationMatchedStatus & status) override
  {
    (void)writer;
    fprintf(stderr, "DataWriterListener: on_publication_matched\n");
    if (status.current_count_change == 1) {
      matched_ = status.total_count;
      first_connected_ = true;
    } else if (status.current_count_change == -1) {
      matched_ = status.total_count;
    }
  }

  void on_reliable_writer_cache_changed(DDSDataWriter * writer, const DDS_ReliableWriterCacheChangedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_reliable_writer_cache_changed\n");
  }

  void on_reliable_reader_activity_changed(DDSDataWriter * writer, const DDS_ReliableReaderActivityChangedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_reliable_reader_activity_changed\n");
  }

  void on_destination_unreachable(DDSDataWriter * writer, const DDS_InstanceHandle_t & handle, const DDS_Locator_t & destination) override
  {
    (void)writer;
    (void)handle;
    (void)destination;
    fprintf(stderr, "DataWriterListener: on_destination_unreachable\n");
  }

  void * on_data_request(DDSDataWriter * writer, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "DataWriterListener: on_data_request\n");
    return nullptr;
  }

  void on_data_return(DDSDataWriter * writer, void * instance_data, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "DataWriterListener: on_data_return\n");
  }

  void on_sample_removed(DDSDataWriter * writer, const DDS_Cookie_t & cookie) override
  {
    (void)writer;
    (void)cookie;
    fprintf(stderr, "DataWriterListener: on_sample_removed\n");
  }

  void on_instance_replaced(DDSDataWriter * writer, const DDS_InstanceHandle_t & handle) override
  {
    (void)writer;
    (void)handle;
    fprintf(stderr, "DataWriterListener: on_instance_replaced\n");
  }

  void on_application_acknowledgment(DDSDataWriter * writer, const DDS_AcknowledgmentInfo & info) override
  {
    (void)writer;
    (void)info;
    fprintf(stderr, "DataWriterListener: on_application_acknowledgement\n");
  }

  void on_service_request_accepted(DDSDataWriter * writer, const DDS_ServiceRequestAcceptedStatus & status) override
  {
    (void)writer;
    (void)status;
    fprintf(stderr, "DataWriterListener: on_service_request_accepted\n");
  }

  int matched_{0};

  bool first_connected_{false};
};

class PubBase
{
public:
  virtual bool init() = 0;

  virtual void run(uint32_t samples, uint32_t sleep_ms) = 0;

  virtual ~PubBase()
  {
  }
};

template<typename T, typename TS, typename DW, bool isV3>
class HelloWorldPublisher final : public PubBase
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

    publisher_listener_ = new PublisherListener;

    // A Publisher allows an application to create one or more DataWriters
    // Publisher QoS is configured in USER_QOS_PROFILES.xml
    publisher_ = participant_->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, publisher_listener_, DDS_STATUS_MASK_ALL);
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

    topic_listener_ = new TopicListener;

    // A Topic has a name and a datatype. Create a Topic called
    // "HelloWorld Topic" with your registered data type
    topic_ = participant_->create_topic("hello_world_topic", type_name, DDS_TOPIC_QOS_DEFAULT, topic_listener_, DDS_STATUS_MASK_ALL);
    if (topic_ == nullptr) {
      fprintf(stderr, "Failed to create topic\n");
      return false;
    }

    writer_listener_ = new DataWriterListener;

    // This DataWriter will write data on Topic "HelloWorld Topic"
    // DataWriter QoS is configured in USER_QOS_PROFILES.xml
    writer_ = publisher_->create_datawriter(topic_, DDS_DATAWRITER_QOS_DEFAULT, writer_listener_, DDS_STATUS_MASK_ALL);
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

    unsigned long count = 0;
    while (count < samples) {
      if (writer_listener_->first_connected_ && writer_listener_->matched_ > 0) {
        sample->index = count;
        if constexpr(isV3) {
#if defined(V3T1) || defined(V3T2)
          strcpy(sample->message, "Hello World");
#elif defined(V3T3)
          sample->message = 54.34;
#endif
        } else {
          strcpy(sample->message, "Hello World");
        }

        std::cout << "Writing HelloWorld, count " << count << std::endl;
        retcode = hello_world_writer_->write(*sample, DDS_HANDLE_NIL);
        if (retcode != DDS_RETCODE_OK) {
          std::cerr << "write error " << retcode << std::endl;
        }

        // We only increment the count if we successfully connected
        ++count;
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
    delete participant_listener_;

    delete publisher_listener_;

    delete topic_listener_;

    delete writer_listener_;

    if (participant_ != nullptr) {
      DDS_ReturnCode_t retcode = participant_->delete_contained_entities();
      (void)retcode;
      DDSDomainParticipantFactory::get_instance()->delete_participant(participant_);
    }
  }

private:
  ParticipantListener * participant_listener_{nullptr};
  DDSDomainParticipant * participant_{nullptr};
  PublisherListener * publisher_listener_{nullptr};
  DDSPublisher * publisher_{nullptr};
  TopicListener * topic_listener_{nullptr};
  DDSTopic * topic_{nullptr};
  DDSDataWriter * writer_{nullptr};
  DataWriterListener * writer_listener_{nullptr};
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
      mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v1, HelloWorld_v1TypeSupport, HelloWorld_v1DataWriter, false>>();
#if defined(V1T1)
    printf("Publishing type V1T1\n");
#elif defined(V1T2)
    printf("Publishing type V1T2\n");
#elif defined(V1T3)
    printf("Publishing type V1T3\n");
#endif
    } else if (user_type == "v2") {
      mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v2, HelloWorld_v2TypeSupport, HelloWorld_v2DataWriter, false>>();
#if defined(V2T1)
    printf("Publishing type V2T1\n");
#elif defined(V2T2)
    printf("Publishing type V2T2\n");
#elif defined(V2T3)
    printf("Publishing type V2T3\n");
#elif defined(V2T4)
    printf("Publishing type V2T4\n");
#endif
    } else if (user_type == "v3") {
      mypub = std::make_unique<HelloWorldPublisher<HelloWorld_v3, HelloWorld_v3TypeSupport, HelloWorld_v3DataWriter, true>>();
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

    fflush(stdout);

    if (!mypub->init()) {
      fprintf(stderr, "Failed to initialize publisher\n");
      return 3;
    }

    mypub->run(10, 100);
  }

  DDSDomainParticipantFactory::finalize_instance();

  return 0;
}
