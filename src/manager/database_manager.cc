#include "database_manager.h"

std::unique_ptr<sqlpp::mysql::connection>
fcdeduction::manager::DatabaseManager::getConnection() {
  return std::move(connection);
}