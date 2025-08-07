//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_NET_UTILS_HPP
#define ASHKANTOOL_NET_UTILS_HPP

#include <iostream>
#include <map>

#include "IpAddress.h"
#include "MacAddress.h"
#include "NetworkUtils.h"

#include "logger.hpp"

namespace ashk {
class NetUtils {
 public:
  static pcpp::MacAddress Arp(pcpp::IPv4Address ip, pcpp::PcapLiveDevice *dev);
};
}

#endif //ASHKANTOOL_NET_UTILS_HPP
