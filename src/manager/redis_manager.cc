#include "redis_manager.h"
std::optional<std::string> fcdeduction::manager::RedisManager::get(const std::string &key) {
    redisReply *reply;
    reply = (redisReply *)redisCommand(pcontext.get(), "GET %s", key.c_str());
    std::optional<std::string> value;
    if (reply->str != NULL) {
        value = reply->str;
    }
    freeReplyObject(reply);
    return value;
}
void fcdeduction::manager::RedisManager::set(const std::string &key,
                                             const std::string &value) {
    redisReply *reply;
    reply = (redisReply *)redisCommand(pcontext.get(), "SET %s %s", key.c_str(),
                                       value.c_str());
    freeReplyObject(reply);
}

void fcdeduction::manager::RedisManager::del(const std::string &key) {
    redisReply *reply;
    reply = (redisReply *)redisCommand(pcontext.get(), "DEL %s", key.c_str());
    freeReplyObject(reply);
}
