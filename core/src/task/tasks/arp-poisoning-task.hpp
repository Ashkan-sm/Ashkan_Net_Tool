//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_ARP_POISONING_TASK_HPP
#define ASHKANTOOL_ARP_POISONING_TASK_HPP

#include "task-headers.hpp"
namespace ashk::tasks {
    class ArpPoisoningTask : public Task {
    public:
        explicit ArpPoisoningTask(pcpp::PcapLiveDevice *dev,
                                  pcpp::IPv4Address vic_src_ip,
                                  pcpp::IPv4Address vic_dst_ip,
                                  pcpp::IPv4Address forward_to_ip,
                                  pcpp::IPv4Address iface_ip);
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address vic_src_ip;
        pcpp::IPv4Address vic_dst_ip;
        pcpp::IPv4Address forward_to_ip;
        pcpp::IPv4Address iface_ip;


    };
}


#endif //ASHKANTOOL_ARP_POISONING_TASK_HPP
