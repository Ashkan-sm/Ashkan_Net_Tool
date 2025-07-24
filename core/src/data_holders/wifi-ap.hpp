//
// Created by dev on 7/22/25.
//

#ifndef ASHKANTOOL_WIFI_AP_HPP
#define ASHKANTOOL_WIFI_AP_HPP
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

struct WifiAp{
    std::string e_ssid;
    pcpp::MacAddress b_ssid;
    int pwr;
    std::string enc;

    bool operator==(const WifiAp &b){
        return e_ssid==b.e_ssid && b_ssid==b.b_ssid && enc==b.enc;
    }
};

struct WifiHost{
    pcpp::MacAddress mac;
    bool is_selected=false;

};
#endif //ASHKANTOOL_WIFI_AP_HPP
