// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: user.proto

#include "user.pb.h"
#include "user.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace user {

static const char* UserFacade_method_names[] = {
  "/user.UserFacade/Login",
};

std::unique_ptr< UserFacade::Stub> UserFacade::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< UserFacade::Stub> stub(new UserFacade::Stub(channel));
  return stub;
}

UserFacade::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Login_(UserFacade_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status UserFacade::Stub::Login(::grpc::ClientContext* context, const ::user::UserLoginRequest& request, ::user::UserLoginResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Login_, context, request, response);
}

void UserFacade::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::user::UserLoginRequest* request, ::user::UserLoginResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void UserFacade::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::user::UserLoginResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void UserFacade::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::user::UserLoginRequest* request, ::user::UserLoginResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

void UserFacade::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::user::UserLoginResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::user::UserLoginResponse>* UserFacade::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::user::UserLoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::user::UserLoginResponse>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::user::UserLoginResponse>* UserFacade::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::user::UserLoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::user::UserLoginResponse>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, false);
}

UserFacade::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      UserFacade_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< UserFacade::Service, ::user::UserLoginRequest, ::user::UserLoginResponse>(
          std::mem_fn(&UserFacade::Service::Login), this)));
}

UserFacade::Service::~Service() {
}

::grpc::Status UserFacade::Service::Login(::grpc::ServerContext* context, const ::user::UserLoginRequest* request, ::user::UserLoginResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace user
