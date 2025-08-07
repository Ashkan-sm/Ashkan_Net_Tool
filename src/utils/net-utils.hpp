//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_NET_UTILS_HPP
#define ASHKANTOOL_NET_UTILS_HPP

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
#include "logger.hpp"
#include <map>

namespace ashk {
    class NetUtils {
    public:
        static pcpp::MacAddress arp(pcpp::IPv4Address ip, pcpp::PcapLiveDevice *dev);
    };
}


#endif //ASHKANTOOL_NET_UTILS_HPP
