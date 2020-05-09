#ifndef DAL_IDENTIFICATION_H
#define DAL_IDENTIFICATION_H
#include "base_dao.h"
#include "identification.h"
#include "identification_do.h"
#include "src/util/ident_type_enum.h"
namespace fcdeduction {
namespace dao {
class IdentificationDao : public fcdeduction::dao::BaseDao {
 public:
  using BaseDao::BaseDao;
  // 判断用户对应的识别key与识别value是否正确
  bool identMatch(const std::string &tntInstId, const std::string &userId,
                  const std::string &identKey, const std::string &identValue,
                  const fcdeduction::util::IdentTypeEnum &identType);
  // 新增识别记录
  void insertIdent(fcdeduction::dataobject::Identification &ident);
  // 通过唯一键删除识别记录
  void deleteIdent(const std::string &tntInstId, const std::string &userId,
                   const std::string &identKey, const std::string &identType);
};
}  // namespace dao
}  // namespace fcdeduction
#endif