//
// Created by dev on 7/22/25.
//

#ifndef ASHKANTOOL_WIFI_HPP
#define ASHKANTOOL_WIFI_HPP

#include <getopt.h>

#include "MacAddress.h"
#include "IpAddress.h"
#include "Logger.h"
#include "PcapPlusPlusVersion.h"
#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"
#include "NetworkUtils.h"
#include "SystemUtils.h"
#include "EthLayer.h"
#include "Packet.h"

#include "core/task/task.hpp"
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
struct HandShakeData{
    WifiAp *selected_ap;
    pcpp::MacAddress station_mac=pcpp::MacAddress::Zero;
    bool got_msg_1=false;
    uint8_t ANonce[32];
    uint8_t SNonce[32];
    bool got_msg_2= false;
    uint8_t MIC[16];
    std::uint8_t eapol[256];
    long eapol_size=0;

};
#endif //ASHKANTOOL_WIFI_HPP
