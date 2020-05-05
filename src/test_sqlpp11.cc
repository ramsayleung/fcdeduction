#include "src/user.h"
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>
#include <iostream>

namespace mysql = sqlpp::mysql;
int main()
{
auto config = std::make_shared<mysql::connection_config>();
 config->host="127.0.0.1";
 config->user = getenv("mysql_user");
 config->database = "fcdeduction";
 config->password = getenv("mysql_password");
 config->debug = true;
 try{
   mysql::connection db(config);
 } catch (const std::exception &e) {
    std::cerr << "For testing, you'll need to create a database sqlpp_mysql for user root (no password)" << std::endl;
    std::cerr << e.what() << std::endl;
    return 1;
 }
 mysql::connection db(config);
  model::DeUser deuser = {};
  for (const auto& row : db(sqlpp::select(all_of(deuser)).from(deuser).unconditionally())){
		std::cerr << "row.name: " << row.userName << ", row.id: " << row.userId <<  std::endl;
	};
  return 0;
}
