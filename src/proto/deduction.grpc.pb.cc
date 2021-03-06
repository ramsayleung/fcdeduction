// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: deduction.proto

#include "deduction.pb.h"
#include "deduction.grpc.pb.h"

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
namespace deduction {

static const char* DeductionFacade_method_names[] = {
  "/deduction.DeductionFacade/CreateDeductionService",
  "/deduction.DeductionFacade/CloseDeductionService",
  "/deduction.DeductionFacade/QueryDeductionListByUserIdAndArType",
};

std::unique_ptr< DeductionFacade::Stub> DeductionFacade::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DeductionFacade::Stub> stub(new DeductionFacade::Stub(channel));
  return stub;
}

DeductionFacade::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_CreateDeductionService_(DeductionFacade_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CloseDeductionService_(DeductionFacade_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_QueryDeductionListByUserIdAndArType_(DeductionFacade_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DeductionFacade::Stub::CreateDeductionService(::grpc::ClientContext* context, const ::deduction::DeduceRequest& request, ::deduction::DeduceResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CreateDeductionService_, context, request, response);
}

void DeductionFacade::Stub::experimental_async::CreateDeductionService(::grpc::ClientContext* context, const ::deduction::DeduceRequest* request, ::deduction::DeduceResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CreateDeductionService_, context, request, response, std::move(f));
}

void DeductionFacade::Stub::experimental_async::CreateDeductionService(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::deduction::DeduceResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CreateDeductionService_, context, request, response, std::move(f));
}

void DeductionFacade::Stub::experimental_async::CreateDeductionService(::grpc::ClientContext* context, const ::deduction::DeduceRequest* request, ::deduction::DeduceResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CreateDeductionService_, context, request, response, reactor);
}

void DeductionFacade::Stub::experimental_async::CreateDeductionService(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::deduction::DeduceResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CreateDeductionService_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::deduction::DeduceResponse>* DeductionFacade::Stub::AsyncCreateDeductionServiceRaw(::grpc::ClientContext* context, const ::deduction::DeduceRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::deduction::DeduceResponse>::Create(channel_.get(), cq, rpcmethod_CreateDeductionService_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::deduction::DeduceResponse>* DeductionFacade::Stub::PrepareAsyncCreateDeductionServiceRaw(::grpc::ClientContext* context, const ::deduction::DeduceRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::deduction::DeduceResponse>::Create(channel_.get(), cq, rpcmethod_CreateDeductionService_, context, request, false);
}

::grpc::Status DeductionFacade::Stub::CloseDeductionService(::grpc::ClientContext* context, const ::deduction::DeduceRequest& request, ::deduction::DeduceResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CloseDeductionService_, context, request, response);
}

void DeductionFacade::Stub::experimental_async::CloseDeductionService(::grpc::ClientContext* context, const ::deduction::DeduceRequest* request, ::deduction::DeduceResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CloseDeductionService_, context, request, response, std::move(f));
}

void DeductionFacade::Stub::experimental_async::CloseDeductionService(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::deduction::DeduceResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CloseDeductionService_, context, request, response, std::move(f));
}

void DeductionFacade::Stub::experimental_async::CloseDeductionService(::grpc::ClientContext* context, const ::deduction::DeduceRequest* request, ::deduction::DeduceResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CloseDeductionService_, context, request, response, reactor);
}

void DeductionFacade::Stub::experimental_async::CloseDeductionService(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::deduction::DeduceResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CloseDeductionService_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::deduction::DeduceResponse>* DeductionFacade::Stub::AsyncCloseDeductionServiceRaw(::grpc::ClientContext* context, const ::deduction::DeduceRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::deduction::DeduceResponse>::Create(channel_.get(), cq, rpcmethod_CloseDeductionService_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::deduction::DeduceResponse>* DeductionFacade::Stub::PrepareAsyncCloseDeductionServiceRaw(::grpc::ClientContext* context, const ::deduction::DeduceRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::deduction::DeduceResponse>::Create(channel_.get(), cq, rpcmethod_CloseDeductionService_, context, request, false);
}

::grpc::Status DeductionFacade::Stub::QueryDeductionListByUserIdAndArType(::grpc::ClientContext* context, const ::deduction::DeductionListQueryRequest& request, ::deduction::DeductionListQueryResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, response);
}

void DeductionFacade::Stub::experimental_async::QueryDeductionListByUserIdAndArType(::grpc::ClientContext* context, const ::deduction::DeductionListQueryRequest* request, ::deduction::DeductionListQueryResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, response, std::move(f));
}

void DeductionFacade::Stub::experimental_async::QueryDeductionListByUserIdAndArType(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::deduction::DeductionListQueryResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, response, std::move(f));
}

void DeductionFacade::Stub::experimental_async::QueryDeductionListByUserIdAndArType(::grpc::ClientContext* context, const ::deduction::DeductionListQueryRequest* request, ::deduction::DeductionListQueryResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, response, reactor);
}

void DeductionFacade::Stub::experimental_async::QueryDeductionListByUserIdAndArType(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::deduction::DeductionListQueryResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::deduction::DeductionListQueryResponse>* DeductionFacade::Stub::AsyncQueryDeductionListByUserIdAndArTypeRaw(::grpc::ClientContext* context, const ::deduction::DeductionListQueryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::deduction::DeductionListQueryResponse>::Create(channel_.get(), cq, rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::deduction::DeductionListQueryResponse>* DeductionFacade::Stub::PrepareAsyncQueryDeductionListByUserIdAndArTypeRaw(::grpc::ClientContext* context, const ::deduction::DeductionListQueryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::deduction::DeductionListQueryResponse>::Create(channel_.get(), cq, rpcmethod_QueryDeductionListByUserIdAndArType_, context, request, false);
}

DeductionFacade::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DeductionFacade_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DeductionFacade::Service, ::deduction::DeduceRequest, ::deduction::DeduceResponse>(
          std::mem_fn(&DeductionFacade::Service::CreateDeductionService), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DeductionFacade_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DeductionFacade::Service, ::deduction::DeduceRequest, ::deduction::DeduceResponse>(
          std::mem_fn(&DeductionFacade::Service::CloseDeductionService), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DeductionFacade_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DeductionFacade::Service, ::deduction::DeductionListQueryRequest, ::deduction::DeductionListQueryResponse>(
          std::mem_fn(&DeductionFacade::Service::QueryDeductionListByUserIdAndArType), this)));
}

DeductionFacade::Service::~Service() {
}

::grpc::Status DeductionFacade::Service::CreateDeductionService(::grpc::ServerContext* context, const ::deduction::DeduceRequest* request, ::deduction::DeduceResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DeductionFacade::Service::CloseDeductionService(::grpc::ServerContext* context, const ::deduction::DeduceRequest* request, ::deduction::DeduceResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DeductionFacade::Service::QueryDeductionListByUserIdAndArType(::grpc::ServerContext* context, const ::deduction::DeductionListQueryRequest* request, ::deduction::DeductionListQueryResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace deduction

