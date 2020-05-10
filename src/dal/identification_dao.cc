#include "identification_dao.h"
model::DeIdent deindent;
bool fcdeduction::dao::IdentificationDao::identMatch(
    const std::string &tntInstId, const std::string &userId,
    const std::string &identKey, const std::string &identValue,
    const fcdeduction::util::IdentTypeEnum &identType) {
    sqlpp::mysql::connection &connection = *pconnection;
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
std::optional<std::string> fcdeduction::dao::IdentificationDao::findUserIdByIdentKeyAndIdentType(const std::string &tntInstId, const std::string &identKey, const fcdeduction::util::IdentTypeEnum &identType) {
    sqlpp::mysql::connection &connection = *pconnection;
    for (auto const& row : connection(
             sqlpp::select(deindent.userId)
                 .from(deindent)
                 .where(deindent.tntInstId == tntInstId and
                        deindent.identKey == identKey &&
                        deindent.identType ==
                            fcdeduction::util::enumToString(identType)))) {
        return std::optional<std::string>{row.userId};
    }
    return std::nullopt;
}
void fcdeduction::dao::IdentificationDao::insertIdent(
    fcdeduction::dataobject::Identification &ident) {
    sqlpp::mysql::connection &connection = *pconnection;
    connection(sqlpp::insert_into(deindent).set(
        deindent.tntInstId = ident.tntInstId, deindent.userId = ident.userId,
        deindent.identType = ident.identType, deindent.identKey = ident.identKey,
        deindent.identValue = ident.identValue, deindent.identId = ident.identId,
        deindent.gmtCreate = std::chrono::system_clock::now(),
        deindent.gmtModified = std::chrono::system_clock::now()));
}

void fcdeduction::dao::IdentificationDao::deleteIdent(
    const std::string &tntInstId, const std::string &userId,
    const std::string &identKey, const std::string &identType) {
    sqlpp::mysql::connection &connection = *pconnection;
    connection(sqlpp::remove_from(deindent).where(
        deindent.tntInstId == tntInstId and deindent.userId == userId and
        deindent.identType == identType and deindent.identKey == identKey));
}