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
class MockHostSet : public HostSet {
public:
  MockHostSet(uint32_t priority = 0,
              uint32_t overprovisioning_factor = kDefaultOverProvisioningFactor);
  ~MockHostSet() override;

  void runCallbacks(const HostVector added, const HostVector removed) {
    member_update_cb_helper_.runCallbacks(priority(), added, removed);
  }

  Common::CallbackHandle* addMemberUpdateCb(PrioritySet::PriorityUpdateCb callback) {
    return member_update_cb_helper_.add(callback);
  }

  // Upstream::HostSet
  MOCK_METHOD(const HostVector&, hosts, (), (const));
  MOCK_METHOD(HostVectorConstSharedPtr, hostsPtr, (), (const));
  MOCK_METHOD(const HostVector&, healthyHosts, (), (const));
  MOCK_METHOD(HealthyHostVectorConstSharedPtr, healthyHostsPtr, (), (const));
  MOCK_METHOD(const HostVector&, degradedHosts, (), (const));
  MOCK_METHOD(DegradedHostVectorConstSharedPtr, degradedHostsPtr, (), (const));
  MOCK_METHOD(const HostVector&, excludedHosts, (), (const));
  MOCK_METHOD(ExcludedHostVectorConstSharedPtr, excludedHostsPtr, (), (const));
  MOCK_METHOD(const HostsPerLocality&, hostsPerLocality, (), (const));
  MOCK_METHOD(HostsPerLocalityConstSharedPtr, hostsPerLocalityPtr, (), (const));
  MOCK_METHOD(const HostsPerLocality&, healthyHostsPerLocality, (), (const));
  MOCK_METHOD(HostsPerLocalityConstSharedPtr, healthyHostsPerLocalityPtr, (), (const));
  MOCK_METHOD(const HostsPerLocality&, degradedHostsPerLocality, (), (const));
  MOCK_METHOD(HostsPerLocalityConstSharedPtr, degradedHostsPerLocalityPtr, (), (const));
  MOCK_METHOD(const HostsPerLocality&, excludedHostsPerLocality, (), (const));
  MOCK_METHOD(HostsPerLocalityConstSharedPtr, excludedHostsPerLocalityPtr, (), (const));
  MOCK_METHOD(LocalityWeightsConstSharedPtr, localityWeights, (), (const));
  MOCK_METHOD(absl::optional<uint32_t>, chooseHealthyLocality, ());
  MOCK_METHOD(absl::optional<uint32_t>, chooseDegradedLocality, ());
  MOCK_METHOD(uint32_t, priority, (), (const));
  uint32_t overprovisioningFactor() const override { return overprovisioning_factor_; }
  void setOverprovisioningFactor(const uint32_t overprovisioning_factor) {
    overprovisioning_factor_ = overprovisioning_factor;
  }

  HostVector hosts_;
  HostVector healthy_hosts_;
  HostVector degraded_hosts_;
  HostVector excluded_hosts_;
  HostsPerLocalitySharedPtr hosts_per_locality_{new HostsPerLocalityImpl()};
  HostsPerLocalitySharedPtr healthy_hosts_per_locality_{new HostsPerLocalityImpl()};
  HostsPerLocalitySharedPtr degraded_hosts_per_locality_{new HostsPerLocalityImpl()};
  HostsPerLocalitySharedPtr excluded_hosts_per_locality_{new HostsPerLocalityImpl()};
  LocalityWeightsConstSharedPtr locality_weights_{{}};
  Common::CallbackManager<uint32_t, const HostVector&, const HostVector&> member_update_cb_helper_;
  uint32_t priority_{};
  uint32_t overprovisioning_factor_{};
  bool run_in_panic_mode_ = false;
};
}

}
