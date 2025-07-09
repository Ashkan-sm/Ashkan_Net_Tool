//
// Created by dev on 6/10/25.
//

#ifndef ASHKANTOOL_VLAN_HOPPING_TASK_HPP
#define ASHKANTOOL_VLAN_HOPPING_TASK_HPP

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

namespace ashk::tasks{
class VlanHoppingTask : public Task {
public:
    explicit VlanHoppingTask(pcpp::PcapLiveDevice *dev,
                             pcpp::IPv4Address iface_ip,
                             int outer_id,
                             int inner_id,
                             int last_task_id);
private:
    void exec() override;
    pcpp::PcapLiveDevice *dev_ = nullptr;
    pcpp::IPv4Address iface_ip;
    CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
    int outer_id;
    int inner_id;
    int last_task_id;
};

}

#endif //ASHKANTOOL_VLAN_HOPPING_TASK_HPP
