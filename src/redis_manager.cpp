#include "redis_manager.hpp"
std::string RedisManager::get(const std::string &key) {
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"GET %s", key.c_str());
    std::string value;
    if (reply->str != NULL) {
      value = reply->str;
    }
    freeReplyObject(reply);
    return value;
}
void RedisManager::set(const std::string &key, const std::string &value) {
    redisReply *reply;
    reply = (redisReply*)redisCommand(context,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}

void RedisManager::del(const std::string &key) {
    redisReply *reply;
    reply = (redisReply*)redisCommand(context,"DEL %s", key.c_str());
    freeReplyObject(reply);
}
