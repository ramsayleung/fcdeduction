#include "database_manager.hpp"

std::unique_ptr<sqlpp::mysql::connection>
fcdeduction::manager::DatabaseManager::getConnection() {
  return std::move(connection);
}