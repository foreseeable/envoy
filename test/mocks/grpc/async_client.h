#pragma once

#include <cstdint>
#include <string>

#include "envoy/config/core/v3/grpc_service.pb.h"
#include "envoy/grpc/async_client.h"
#include "envoy/grpc/async_client_manager.h"
#include "envoy/stats/scope.h"

#include "common/grpc/typed_async_client.h"

#include "test/test_common/utility.h"

#include "gmock/gmock.h"

#include "async_request.h"
namespace Envoy {
namespace Grpc {
class MockAsyncClient : public RawAsyncClient {
public:
  MockAsyncClient();
  ~MockAsyncClient() override;

  MOCK_METHOD(AsyncRequest*, sendRaw,
              (absl::string_view service_full_name, absl::string_view method_name,
               Buffer::InstancePtr&& request, RawAsyncRequestCallbacks& callbacks,
               Tracing::Span& parent_span, const Http::AsyncClient::RequestOptions& options));
  MOCK_METHOD(RawAsyncStream*, startRaw,
              (absl::string_view service_full_name, absl::string_view method_name,
               RawAsyncStreamCallbacks& callbacks,
               const Http::AsyncClient::StreamOptions& options));

  std::unique_ptr<testing::NiceMock<Grpc::MockAsyncRequest>> async_request_;
};
}

}
