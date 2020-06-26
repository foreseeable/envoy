#include "priority_set.h"

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
MockPrioritySet::MockPrioritySet() {
  getHostSet(0);
  ON_CALL(*this, hostSetsPerPriority()).WillByDefault(ReturnRef(host_sets_));
  ON_CALL(testing::Const(*this), hostSetsPerPriority()).WillByDefault(ReturnRef(host_sets_));
  ON_CALL(*this, addMemberUpdateCb(_))
      .WillByDefault(Invoke([this](PrioritySet::MemberUpdateCb cb) -> Common::CallbackHandle* {
        return member_update_cb_helper_.add(cb);
      }));
  ON_CALL(*this, addPriorityUpdateCb(_))
      .WillByDefault(Invoke([this](PrioritySet::PriorityUpdateCb cb) -> Common::CallbackHandle* {
        return priority_update_cb_helper_.add(cb);
      }));
}


MockPrioritySet::~MockPrioritySet() = default;


HostSet& MockPrioritySet::getHostSet(uint32_t priority) {
  if (host_sets_.size() < priority + 1) {
    for (size_t i = host_sets_.size(); i <= priority; ++i) {
      auto host_set = new NiceMock<MockHostSet>(i);
      host_sets_.push_back(HostSetPtr{host_set});
      host_set->addMemberUpdateCb([this](uint32_t priority, const HostVector& hosts_added,
                                         const HostVector& hosts_removed) {
        runUpdateCallbacks(priority, hosts_added, hosts_removed);
      });
    }
  }
  return *host_sets_[priority];
}

void MockPrioritySet::runUpdateCallbacks(uint32_t priority, const HostVector& hosts_added,
                                         const HostVector& hosts_removed) {
  member_update_cb_helper_.runCallbacks(hosts_added, hosts_removed);
  priority_update_cb_helper_.runCallbacks(priority, hosts_added, hosts_removed);
}



}

}
