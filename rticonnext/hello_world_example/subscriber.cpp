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
    // A DomainParticipant allows an application to begin communicating in
    // a DDS domain. Typically there is one DomainParticipant per application.
    // DomainParticipant QoS is configured in USER_QOS_PROFILES.xml
    participant_ = DDSDomainParticipantFactory::get_instance()->create_participant(0, DDS_PARTICIPANT_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
    if (participant_ == nullptr) {
      fprintf(stderr, "Failed to create participant\n");
      return false;
    }

    // A Subscriber allows an application to create one or more DataReaders
    // Subscriber QoS is configured in USER_QOS_PROFILES.xml
    subscriber_ = participant_->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
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

    // A Topic has a name and a datatype. Create a Topic called
    // "HelloWorld Topic" with your registered data type
    topic_ = participant_->create_topic("hello_world_topic", type_name, DDS_TOPIC_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
    if (topic_ == nullptr) {
      fprintf(stderr, "Failed to create topic\n");
      return false;
    }

    // This DataReader will read data of type HelloWorld on Topic
    // "HelloWorld Topic". DataReader QoS is configured in
    // USER_QOS_PROFILES.xml
    reader_ = subscriber_->create_datareader(topic_, DDS_DATAREADER_QOS_DEFAULT, nullptr, DDS_STATUS_MASK_NONE);
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
