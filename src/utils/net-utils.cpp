//
// Created by dev on 6/9/25.
//

#include "net-utils.hpp"

pcpp::MacAddress ashk::NetUtils::Arp(pcpp::IPv4Address ip, pcpp::PcapLiveDevice *dev) {
  double arpResponseTimeMS;
  int arpTimeOut = 2;
  return pcpp::NetworkUtils::getInstance().getMacAddress(ip, dev, arpResponseTimeMS,
                                                         dev->getMacAddress(), dev->getIPv4Address(), arpTimeOut);
}
