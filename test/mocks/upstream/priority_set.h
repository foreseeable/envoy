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

#include "host_set.h"
namespace Envoy {
namespace Upstream {
class MockPrioritySet : public PrioritySet {
public:
  MockPrioritySet();
  ~MockPrioritySet() override;

  HostSet& getHostSet(uint32_t priority);
  void runUpdateCallbacks(uint32_t priority, const HostVector& hosts_added,
                          const HostVector& hosts_removed);

  MOCK_METHOD(Common::CallbackHandle*, addMemberUpdateCb, (MemberUpdateCb callback), (const));
  MOCK_METHOD(Common::CallbackHandle*, addPriorityUpdateCb, (PriorityUpdateCb callback), (const));
  MOCK_METHOD(const std::vector<HostSetPtr>&, hostSetsPerPriority, (), (const));
  MOCK_METHOD(std::vector<HostSetPtr>&, hostSetsPerPriority, ());
  MOCK_METHOD(void, updateHosts,
              (uint32_t priority, UpdateHostsParams&& update_hosts_params,
               LocalityWeightsConstSharedPtr locality_weights, const HostVector& hosts_added,
               const HostVector& hosts_removed, absl::optional<uint32_t> overprovisioning_factor));
  MOCK_METHOD(void, batchHostUpdate, (BatchUpdateCb&));

  MockHostSet* getMockHostSet(uint32_t priority) {
    getHostSet(priority); // Ensure the host set exists.
    return reinterpret_cast<MockHostSet*>(host_sets_[priority].get());
  }

  std::vector<HostSetPtr> host_sets_;
  Common::CallbackManager<const HostVector&, const HostVector&> member_update_cb_helper_;
  Common::CallbackManager<uint32_t, const HostVector&, const HostVector&>
      priority_update_cb_helper_;
};
}

}
