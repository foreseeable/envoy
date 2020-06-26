#include "cluster_update_callbacks.h"

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
MockClusterUpdateCallbacks::MockClusterUpdateCallbacks() = default;

MockClusterUpdateCallbacks::~MockClusterUpdateCallbacks() = default;



}

}
