//
// Created by dev on 7/9/25.
//

#ifndef ASHKANTOOL_DTP_NEGOTIATION_HPP
#define ASHKANTOOL_DTP_NEGOTIATION_HPP
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
#include <arpa/inet.h>

namespace ashk::tasks{
    class DTPNegotiation : public Task {
    public:
        explicit DTPNegotiation(pcpp::PcapLiveDevice *dev,
                                 pcpp::IPv4Address iface_ip,
                                 std::string domain_name,
                                 int last_task_id);
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        std::string domain_name;
        int last_task_id;
    };

}

#endif //ASHKANTOOL_DTP_NEGOTIATION_HPP
