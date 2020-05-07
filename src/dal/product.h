// generated by /home/ramsay/code/cpp/sqlpp11/scripts/ddl2cpp /home/ramsay/code/cpp/fcdeduction/conf/de_prod.sql /home/ramsay/code/cpp/fcdeduction/src/product model
#ifndef MODEL_PRODUCT_H
#define MODEL_PRODUCT_H

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

namespace model
{
  namespace DeProd_
  {
    struct TntInstId
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "tnt_inst_id";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T tntInstId;
            T& operator()() { return tntInstId; }
            const T& operator()() const { return tntInstId; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct PdCode
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "pd_code";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T pdCode;
            T& operator()() { return pdCode; }
            const T& operator()() const { return pdCode; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct PdName
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "pd_name";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T pdName;
            T& operator()() { return pdName; }
            const T& operator()() const { return pdName; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct PdDesc
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "pd_desc";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T pdDesc;
            T& operator()() { return pdDesc; }
            const T& operator()() const { return pdDesc; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct PdOrgName
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "pd_org_name";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T pdOrgName;
            T& operator()() { return pdOrgName; }
            const T& operator()() const { return pdOrgName; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct Memo
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "memo";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T memo;
            T& operator()() { return memo; }
            const T& operator()() const { return memo; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };
    struct GmtCreate
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "gmt_create";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T gmtCreate;
            T& operator()() { return gmtCreate; }
            const T& operator()() const { return gmtCreate; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::time_point, sqlpp::tag::require_insert>;
    };
    struct GmtModified
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "gmt_modified";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T gmtModified;
            T& operator()() { return gmtModified; }
            const T& operator()() const { return gmtModified; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::time_point, sqlpp::tag::require_insert>;
    };
  } // namespace DeProd_

  struct DeProd: sqlpp::table_t<DeProd,
               DeProd_::TntInstId,
               DeProd_::PdCode,
               DeProd_::PdName,
               DeProd_::PdDesc,
               DeProd_::PdOrgName,
               DeProd_::Memo,
               DeProd_::GmtCreate,
               DeProd_::GmtModified>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "de_prod";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T deProd;
        T& operator()() { return deProd; }
        const T& operator()() const { return deProd; }
      };
    };
  };
} // namespace model
#endif