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

#include "async_client.h"
namespace Envoy {
namespace Grpc {
class MockAsyncClientFactory : public AsyncClientFactory {
public:
  MockAsyncClientFactory();
  ~MockAsyncClientFactory() override;

  MOCK_METHOD(RawAsyncClientPtr, create, ());
};
}

}
