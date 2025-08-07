//
// Created by dev on 6/28/25.
//

#ifndef ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
#define ASHKANTOOL_MITM_PACKET_FORWARDING_HPP

#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"

#include "core/task/task.hpp"
#include "core/packet-receiver/packet-receiver.hpp"
#include "core/capture-wrapper.hpp"

namespace ashk::tasks {
    class MITMPacketForwarding : public Task{
    public:
        explicit MITMPacketForwarding(pcpp::IPv4Address iface_ip,
                                      pcpp::IPv4Address victim_ip,
                                    pcpp::IPv4Address gateway_ip,
                                    pcpp::MacAddress victim_mac,
                                    pcpp::MacAddress gateway_mac,
            int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        pcpp::IPv4Address victim_ip;
        pcpp::IPv4Address gateway_ip;
        pcpp::MacAddress victim_mac;
        pcpp::MacAddress gateway_mac;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();

    };
}

#endif //ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
