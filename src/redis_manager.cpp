#include "redis_manager.hpp"
std::string RedisManager::get(const std::string &key) {
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"GET ramsay");
    std::string value = reply->str;
    freeReplyObject(reply);
    return value;
}
void RedisManager::set(const std::string &key, const std::string &value) {
    redisReply *reply;
    reply = (redisReply*)redisCommand(context,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}
