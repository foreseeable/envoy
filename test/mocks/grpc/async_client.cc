#include "async_client.h"

#include "test/mocks/http/async_client.h"

namespace Envoy {
namespace Grpc {
MockAsyncClient::MockAsyncClient() {
  async_request_ = std::make_unique<testing::NiceMock<Grpc::MockAsyncRequest>>();
  ON_CALL(*this, sendRaw(_, _, _, _, _, _)).WillByDefault(Return(async_request_.get()));
}

MockAsyncClient::~MockAsyncClient() = default;



}

}
