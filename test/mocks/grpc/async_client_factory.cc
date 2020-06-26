#include "async_client_factory.h"

#include "test/mocks/http/async_client_factory.h"

namespace Envoy {
namespace Grpc {
MockAsyncClientFactory::MockAsyncClientFactory() {
  ON_CALL(*this, create()).WillByDefault(Invoke([] {
    return std::make_unique<testing::NiceMock<Grpc::MockAsyncClient>>();
  }));
}

MockAsyncClientFactory::~MockAsyncClientFactory() = default;



}

}
