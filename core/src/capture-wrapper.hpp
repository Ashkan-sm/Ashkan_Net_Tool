//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_CAPTURE_WRAPPER_HPP
#define ASHKANTOOL_CAPTURE_WRAPPER_HPP

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
#include <mutex>
#include "../../utils/logger.hpp"
namespace ashk {

class CaptureWrapper {
public:
    static CaptureWrapper &getInstance();

    bool start_capture(pcpp::PcapLiveDevice *dev, pcpp::OnPacketArrivesCallback onPacketArrives,
                       void *onPacketArrivesUserCookie, int id);

    void stop_capture(pcpp::PcapLiveDevice *dev);

private:
    CaptureWrapper();

    CaptureWrapper(const CaptureWrapper &) = delete;

    CaptureWrapper &operator=(const CaptureWrapper &) = default;

    std::mutex m_is_capturing;
    bool is_capturing = false;
    int capturing_thread_id = 0;
    utils::Logger &logger = utils::Logger::getInstance();

};

}
#endif //ASHKANTOOL_CAPTURE_WRAPPER_HPP
