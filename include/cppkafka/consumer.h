#ifndef CPP_KAFKA_CONSUMER_H
#define CPP_KAFKA_CONSUMER_H

#include <vector>
#include <string>
#include <chrono>
#include "kafka_handle_base.h"
#include "topic_partition_list.h"
#include "message.h"

namespace cppkafka {

class Configuration;
class TopicConfiguration;

class Consumer : public KafkaHandleBase {
public:
    Consumer(const Configuration& config);

    void set_timeout(const std::chrono::milliseconds timeout);

    void subscribe(const std::vector<std::string>& topics);
    void unsubscribe();

    void assign(const TopicPartitionList& topic_partitions);

    void commit(const Message& msg);
    void async_commit(const Message& msg);
    void commit(const TopicPartitionList& topic_partitions);
    void async_commit(const TopicPartitionList& topic_partitions);

    TopicPartitionList get_committed(const TopicPartitionList& topic_partitions);
    TopicPartitionList get_position(const TopicPartitionList& topic_partitions);

    Message poll();
private:
    static const std::chrono::milliseconds DEFAULT_TIMEOUT;

    void commit(const Message& msg, bool async);
    void commit(const TopicPartitionList& topic_partitions, bool async);
    void check_error(rd_kafka_resp_err_t error);

    std::chrono::milliseconds timeout_ms_;
};

} // cppkafka

#endif // CPP_KAFKA_CONSUMER_H