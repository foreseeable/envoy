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

namespace Envoy {
namespace Grpc {
class MockAsyncStream : public RawAsyncStream {
public:
  MockAsyncStream();
  ~MockAsyncStream() override;

  void sendMessageRaw(Buffer::InstancePtr&& request, bool end_stream) override {
    sendMessageRaw_(request, end_stream);
  }
  MOCK_METHOD(void, sendMessageRaw_, (Buffer::InstancePtr & request, bool end_stream));
  MOCK_METHOD(void, closeStream, ());
  MOCK_METHOD(void, resetStream, ());
  MOCK_METHOD(bool, isAboveWriteBufferHighWatermark, (), (const));
};
}

}
