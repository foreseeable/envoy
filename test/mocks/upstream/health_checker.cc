#include "health_checker.h"

#include <chrono>
#include <functional>

#include "envoy/upstream/load_balancer.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::_;
using testing::Eq;
using testing::Invoke;
using testing::Return;
using testing::ReturnRef;
using testing::SaveArg;

namespace Envoy {
namespace Upstream {
MockHealthChecker::MockHealthChecker() {
  ON_CALL(*this, addHostCheckCompleteCb(_)).WillByDefault(Invoke([this](HostStatusCb cb) -> void {
    callbacks_.push_back(cb);
  }));
}


MockHealthChecker::~MockHealthChecker() = default;



}

}
