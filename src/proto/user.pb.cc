// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: user.proto

#include "user.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace user {
class UserLoginRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<UserLoginRequest> _instance;
} _UserLoginRequest_default_instance_;
class UserLoginResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<UserLoginResponse> _instance;
} _UserLoginResponse_default_instance_;
}  // namespace user
static void InitDefaultsscc_info_UserLoginRequest_user_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::user::_UserLoginRequest_default_instance_;
    new (ptr) ::user::UserLoginRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::user::UserLoginRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_UserLoginRequest_user_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_UserLoginRequest_user_2eproto}, {}};

static void InitDefaultsscc_info_UserLoginResponse_user_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::user::_UserLoginResponse_default_instance_;
    new (ptr) ::user::UserLoginResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::user::UserLoginResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_UserLoginResponse_user_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_UserLoginResponse_user_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_user_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_user_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_user_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_user_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::user::UserLoginRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::user::UserLoginRequest, loginkey_),
  PROTOBUF_FIELD_OFFSET(::user::UserLoginRequest, loginvalue_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, status_),
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, code_),
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, desc_),
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, token_),
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, refreshtoken_),
  PROTOBUF_FIELD_OFFSET(::user::UserLoginResponse, expiretime_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::user::UserLoginRequest)},
  { 7, -1, sizeof(::user::UserLoginResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::user::_UserLoginRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::user::_UserLoginResponse_default_instance_),
};

const char descriptor_table_protodef_user_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nuser.proto\022\004user\"8\n\020UserLoginRequest\022\020"
  "\n\010loginKey\030\001 \001(\t\022\022\n\nloginValue\030\002 \001(\t\"x\n\021"
  "UserLoginResponse\022\016\n\006status\030\001 \001(\t\022\014\n\004cod"
  "e\030\002 \001(\t\022\014\n\004desc\030\003 \001(\t\022\r\n\005token\030\004 \001(\t\022\024\n\014"
  "refreshToken\030\005 \001(\t\022\022\n\nexpireTime\030\006 \001(\t2H"
  "\n\nUserFacade\022:\n\005Login\022\026.user.UserLoginRe"
  "quest\032\027.user.UserLoginResponse\"\000b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_user_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_user_2eproto_sccs[2] = {
  &scc_info_UserLoginRequest_user_2eproto.base,
  &scc_info_UserLoginResponse_user_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_user_2eproto_once;
static bool descriptor_table_user_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_user_2eproto = {
  &descriptor_table_user_2eproto_initialized, descriptor_table_protodef_user_2eproto, "user.proto", 280,
  &descriptor_table_user_2eproto_once, descriptor_table_user_2eproto_sccs, descriptor_table_user_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_user_2eproto::offsets,
  file_level_metadata_user_2eproto, 2, file_level_enum_descriptors_user_2eproto, file_level_service_descriptors_user_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_user_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_user_2eproto), true);
namespace user {

// ===================================================================

void UserLoginRequest::InitAsDefaultInstance() {
}
class UserLoginRequest::_Internal {
 public:
};

UserLoginRequest::UserLoginRequest()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:user.UserLoginRequest)
}
UserLoginRequest::UserLoginRequest(const UserLoginRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  loginkey_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_loginkey().empty()) {
    loginkey_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.loginkey_);
  }
  loginvalue_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_loginvalue().empty()) {
    loginvalue_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.loginvalue_);
  }
  // @@protoc_insertion_point(copy_constructor:user.UserLoginRequest)
}

void UserLoginRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_UserLoginRequest_user_2eproto.base);
  loginkey_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  loginvalue_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

UserLoginRequest::~UserLoginRequest() {
  // @@protoc_insertion_point(destructor:user.UserLoginRequest)
  SharedDtor();
}

void UserLoginRequest::SharedDtor() {
  loginkey_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  loginvalue_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void UserLoginRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const UserLoginRequest& UserLoginRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_UserLoginRequest_user_2eproto.base);
  return *internal_default_instance();
}


void UserLoginRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:user.UserLoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  loginkey_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  loginvalue_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

const char* UserLoginRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string loginKey = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_loginkey();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginRequest.loginKey"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string loginValue = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_loginvalue();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginRequest.loginValue"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* UserLoginRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:user.UserLoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string loginKey = 1;
  if (this->loginkey().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_loginkey().data(), static_cast<int>(this->_internal_loginkey().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginRequest.loginKey");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_loginkey(), target);
  }

  // string loginValue = 2;
  if (this->loginvalue().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_loginvalue().data(), static_cast<int>(this->_internal_loginvalue().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginRequest.loginValue");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_loginvalue(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:user.UserLoginRequest)
  return target;
}

size_t UserLoginRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:user.UserLoginRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string loginKey = 1;
  if (this->loginkey().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_loginkey());
  }

  // string loginValue = 2;
  if (this->loginvalue().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_loginvalue());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void UserLoginRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:user.UserLoginRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const UserLoginRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<UserLoginRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:user.UserLoginRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:user.UserLoginRequest)
    MergeFrom(*source);
  }
}

void UserLoginRequest::MergeFrom(const UserLoginRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:user.UserLoginRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.loginkey().size() > 0) {

    loginkey_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.loginkey_);
  }
  if (from.loginvalue().size() > 0) {

    loginvalue_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.loginvalue_);
  }
}

void UserLoginRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:user.UserLoginRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void UserLoginRequest::CopyFrom(const UserLoginRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:user.UserLoginRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserLoginRequest::IsInitialized() const {
  return true;
}

void UserLoginRequest::InternalSwap(UserLoginRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  loginkey_.Swap(&other->loginkey_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  loginvalue_.Swap(&other->loginvalue_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata UserLoginRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void UserLoginResponse::InitAsDefaultInstance() {
}
class UserLoginResponse::_Internal {
 public:
};

UserLoginResponse::UserLoginResponse()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:user.UserLoginResponse)
}
UserLoginResponse::UserLoginResponse(const UserLoginResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  status_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_status().empty()) {
    status_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.status_);
  }
  code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_code().empty()) {
    code_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.code_);
  }
  desc_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_desc().empty()) {
    desc_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.desc_);
  }
  token_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_token().empty()) {
    token_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.token_);
  }
  refreshtoken_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_refreshtoken().empty()) {
    refreshtoken_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.refreshtoken_);
  }
  expiretime_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_expiretime().empty()) {
    expiretime_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.expiretime_);
  }
  // @@protoc_insertion_point(copy_constructor:user.UserLoginResponse)
}

void UserLoginResponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_UserLoginResponse_user_2eproto.base);
  status_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  desc_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  token_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  refreshtoken_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  expiretime_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

UserLoginResponse::~UserLoginResponse() {
  // @@protoc_insertion_point(destructor:user.UserLoginResponse)
  SharedDtor();
}

void UserLoginResponse::SharedDtor() {
  status_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  code_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  desc_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  token_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  refreshtoken_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  expiretime_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void UserLoginResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const UserLoginResponse& UserLoginResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_UserLoginResponse_user_2eproto.base);
  return *internal_default_instance();
}


void UserLoginResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:user.UserLoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  status_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  code_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  desc_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  token_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  refreshtoken_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  expiretime_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

const char* UserLoginResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string status = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_status();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginResponse.status"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string code = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_code();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginResponse.code"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string desc = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_desc();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginResponse.desc"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string token = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          auto str = _internal_mutable_token();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginResponse.token"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string refreshToken = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_refreshtoken();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginResponse.refreshToken"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string expireTime = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
          auto str = _internal_mutable_expiretime();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "user.UserLoginResponse.expireTime"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* UserLoginResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:user.UserLoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string status = 1;
  if (this->status().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_status().data(), static_cast<int>(this->_internal_status().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginResponse.status");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_status(), target);
  }

  // string code = 2;
  if (this->code().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_code().data(), static_cast<int>(this->_internal_code().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginResponse.code");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_code(), target);
  }

  // string desc = 3;
  if (this->desc().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_desc().data(), static_cast<int>(this->_internal_desc().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginResponse.desc");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_desc(), target);
  }

  // string token = 4;
  if (this->token().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_token().data(), static_cast<int>(this->_internal_token().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginResponse.token");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_token(), target);
  }

  // string refreshToken = 5;
  if (this->refreshtoken().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_refreshtoken().data(), static_cast<int>(this->_internal_refreshtoken().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginResponse.refreshToken");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_refreshtoken(), target);
  }

  // string expireTime = 6;
  if (this->expiretime().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_expiretime().data(), static_cast<int>(this->_internal_expiretime().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "user.UserLoginResponse.expireTime");
    target = stream->WriteStringMaybeAliased(
        6, this->_internal_expiretime(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:user.UserLoginResponse)
  return target;
}

size_t UserLoginResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:user.UserLoginResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string status = 1;
  if (this->status().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_status());
  }

  // string code = 2;
  if (this->code().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_code());
  }

  // string desc = 3;
  if (this->desc().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_desc());
  }

  // string token = 4;
  if (this->token().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_token());
  }

  // string refreshToken = 5;
  if (this->refreshtoken().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_refreshtoken());
  }

  // string expireTime = 6;
  if (this->expiretime().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_expiretime());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void UserLoginResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:user.UserLoginResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const UserLoginResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<UserLoginResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:user.UserLoginResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:user.UserLoginResponse)
    MergeFrom(*source);
  }
}

void UserLoginResponse::MergeFrom(const UserLoginResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:user.UserLoginResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.status().size() > 0) {

    status_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.status_);
  }
  if (from.code().size() > 0) {

    code_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.code_);
  }
  if (from.desc().size() > 0) {

    desc_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.desc_);
  }
  if (from.token().size() > 0) {

    token_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.token_);
  }
  if (from.refreshtoken().size() > 0) {

    refreshtoken_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.refreshtoken_);
  }
  if (from.expiretime().size() > 0) {

    expiretime_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.expiretime_);
  }
}

void UserLoginResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:user.UserLoginResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void UserLoginResponse::CopyFrom(const UserLoginResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:user.UserLoginResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserLoginResponse::IsInitialized() const {
  return true;
}

void UserLoginResponse::InternalSwap(UserLoginResponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  status_.Swap(&other->status_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  code_.Swap(&other->code_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  desc_.Swap(&other->desc_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  token_.Swap(&other->token_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  refreshtoken_.Swap(&other->refreshtoken_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  expiretime_.Swap(&other->expiretime_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata UserLoginResponse::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace user
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::user::UserLoginRequest* Arena::CreateMaybeMessage< ::user::UserLoginRequest >(Arena* arena) {
  return Arena::CreateInternal< ::user::UserLoginRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::user::UserLoginResponse* Arena::CreateMaybeMessage< ::user::UserLoginResponse >(Arena* arena) {
  return Arena::CreateInternal< ::user::UserLoginResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
