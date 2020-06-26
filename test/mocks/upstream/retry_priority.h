#pragma once

#include <functional>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "envoy/config/bootstrap/v3/bootstrap.pb.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/config/core/v3/address.pb.h"
#include "envoy/config/core/v3/config_source.pb.h"
#include "envoy/data/core/v3/health_check_event.pb.h"
#include "envoy/http/async_client.h"
#include "envoy/upstream/cluster_manager.h"
#include "envoy/upstream/health_checker.h"
#include "envoy/upstream/upstream.h"

#include "common/common/callback_impl.h"
#include "common/upstream/health_discovery_service.h"
#include "common/upstream/load_balancer_impl.h"
#include "common/upstream/upstream_impl.h"

#include "test/mocks/config/mocks.h"
#include "test/mocks/grpc/mocks.h"
#include "test/mocks/http/mocks.h"
#include "test/mocks/runtime/mocks.h"
#include "test/mocks/secret/mocks.h"
#include "test/mocks/stats/mocks.h"
#include "test/mocks/tcp/mocks.h"
#include "test/mocks/upstream/cluster_info.h"
#include "test/mocks/upstream/load_balancer_context.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace Envoy {
namespace Upstream {
class MockRetryPriority : public RetryPriority {
public:
  MockRetryPriority(const HealthyLoad& healthy_priority_load,
                    const DegradedLoad& degraded_priority_load)
      : priority_load_({healthy_priority_load, degraded_priority_load}) {}
  MockRetryPriority(const MockRetryPriority& other) : priority_load_(other.priority_load_) {}
  ~MockRetryPriority() override;

  const HealthyAndDegradedLoad& determinePriorityLoad(const PrioritySet&,
                                                      const HealthyAndDegradedLoad&,
                                                      const PriorityMappingFunc&) override {
    return priority_load_;
  }

  MOCK_METHOD(void, onHostAttempted, (HostDescriptionConstSharedPtr));

private:
  const HealthyAndDegradedLoad priority_load_;
};
}

}
