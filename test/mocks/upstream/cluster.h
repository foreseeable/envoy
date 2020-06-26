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
class MockCluster : public Cluster {
public:
  MockCluster();
  ~MockCluster() override;

  // Upstream::Cluster
  MOCK_METHOD(HealthChecker*, healthChecker, ());
  MOCK_METHOD(ClusterInfoConstSharedPtr, info, (), (const));
  MOCK_METHOD(Outlier::Detector*, outlierDetector, ());
  MOCK_METHOD(const Outlier::Detector*, outlierDetector, (), (const));
  MOCK_METHOD(void, initialize, (std::function<void()> callback));
  MOCK_METHOD(InitializePhase, initializePhase, (), (const));
  MOCK_METHOD(const Network::Address::InstanceConstSharedPtr&, sourceAddress, (), (const));

  std::shared_ptr<MockClusterInfo> info_{new NiceMock<MockClusterInfo>()};
  std::function<void()> initialize_callback_;
  Network::Address::InstanceConstSharedPtr source_address_;
};
}

}
