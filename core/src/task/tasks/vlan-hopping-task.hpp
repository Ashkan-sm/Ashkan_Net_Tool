//
// Created by dev on 6/10/25.
//

#ifndef ASHKANTOOL_VLAN_HOPPING_TASK_HPP
#define ASHKANTOOL_VLAN_HOPPING_TASK_HPP

#include "task-headers.hpp"

namespace ashk::tasks{
class VlanHoppingTask : public Task {
public:
    explicit VlanHoppingTask(pcpp::PcapLiveDevice *dev,
                             pcpp::IPv4Address iface_ip,
                             int outer_id,
                             int inner_id,
                             int last_task_id);
    std::string get_data(tasks_data_id data_id) override;
private:
    void exec() override;
    pcpp::PcapLiveDevice *dev_ = nullptr;
    pcpp::IPv4Address iface_ip;
    CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
    int outer_id;
    int inner_id;
    int last_task_id;
};

}

#endif //ASHKANTOOL_VLAN_HOPPING_TASK_HPP
