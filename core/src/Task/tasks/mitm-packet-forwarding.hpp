//
// Created by dev on 6/28/25.
//

#ifndef ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
#define ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
#include "../task.hpp"
#include <iostream>
#include "MacAddress.h"
#include "IpAddress.h"
#include "Logger.h"
#include "PcapPlusPlusVersion.h"
#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"
#include "NetworkUtils.h"
#include <getopt.h>
#include "SystemUtils.h"
#include "EthLayer.h"
#include "Packet.h"
#include "VlanLayer.h"
#include <map>
#include "../../../../utils/net-utils.hpp"
#include "../../packet-receiver.hpp"
#include "../../capture-wrapper.hpp"
#include "RawPacket.h"
#include <EthDot3Layer.h>
namespace ashk::tasks {
    class MITMPacketForwarding : public Task{
    public:
        explicit MITMPacketForwarding(pcpp::IPv4Address iface_ip,
            pcpp::IPv4Address victim,
            pcpp::IPv4Address gateway,
            int last_task_id);
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        pcpp::IPv4Address victim;
        pcpp::IPv4Address gateway;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        int last_task_id;

    };
}

#endif //ASHKANTOOL_MITM_PACKET_FORWARDING_HPP
