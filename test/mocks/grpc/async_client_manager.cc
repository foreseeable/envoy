#include "async_client_manager.h"

#include "test/mocks/http/async_client_manager.h"

namespace Envoy {
namespace Grpc {
MockAsyncClientManager::MockAsyncClientManager() {
  ON_CALL(*this, factoryForGrpcService(_, _, _))
      .WillByDefault(Invoke([](const envoy::config::core::v3::GrpcService&, Stats::Scope&, bool) {
        return std::make_unique<testing::NiceMock<Grpc::MockAsyncClientFactory>>();
      }));
}


MockAsyncClientManager::~MockAsyncClientManager() = default;



}

}
