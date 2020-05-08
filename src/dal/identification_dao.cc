#include "identification_dao.h"

#include "identification.h"
model::DeIdent deindent;
bool fcdeduction::dao::IdentificationDao::identMatch(
    sqlpp::mysql::connection &connection, const std::string &tntInstId,
    const std::string &userId, const std::string &identKey,
    const std::string &identValue,
    const fcdeduction::util::IdentTypeEnum &identType) {
  return connection(
             sqlpp::select(exists(
                 select(deindent.identId)
                     .from(deindent)
                     .where(deindent.tntInstId == tntInstId &&
                            deindent.userId == userId &&
                            deindent.identKey == identKey &&
                            deindent.identValue == identValue &&
                            deindent.identType ==
                                fcdeduction::util::enumToString(identType)))))
      .front()
      .exists;
}