//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_ARP_POISONING_TASK_HPP
#define ASHKANTOOL_ARP_POISONING_TASK_HPP

#include "core/task/task.hpp"
#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"
#include "utils/net-utils.hpp"

namespace ashk::tasks {
    class ArpPoisoningTask : public Task {
    public:
        explicit ArpPoisoningTask(pcpp::PcapLiveDevice *dev,
                                  pcpp::IPv4Address vic_src_ip,
                                  pcpp::IPv4Address vic_dst_ip,
                                  pcpp::IPv4Address forward_to_ip,
                                  pcpp::IPv4Address iface_ip,
                                  int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address vic_src_ip;
        pcpp::IPv4Address vic_dst_ip;
        pcpp::IPv4Address forward_to_ip;
        pcpp::IPv4Address iface_ip;
        pcpp::MacAddress vic_dst_mac;
        pcpp::MacAddress vic_src_mac;

        std::set<tasks_data_id> extractable_data{
                VICTIM_DST_MAC,
                VICTIM_SRC_MAC
        };
    };
}


#endif //ASHKANTOOL_ARP_POISONING_TASK_HPP
