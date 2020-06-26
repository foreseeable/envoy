#include "load_balancer.h"

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
MockLoadBalancer::MockLoadBalancer() { ON_CALL(*this, chooseHost(_)).WillByDefault(Return(host_)); }

MockLoadBalancer::~MockLoadBalancer() = default;



}

}
