//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_CAPTURE_WRAPPER_HPP
#define ASHKANTOOL_CAPTURE_WRAPPER_HPP

#include <iostream>
#include <mutex>

#include "PcapLiveDevice.h"

#include "utils/logger.hpp"

namespace ashk {

class CaptureWrapper {
public:
    static CaptureWrapper &getInstance();
    CaptureWrapper(const CaptureWrapper &) = delete;
    CaptureWrapper &operator=(const CaptureWrapper &) = delete;

    bool start_capture(pcpp::PcapLiveDevice *dev, pcpp::OnPacketArrivesCallback onPacketArrives,
                       void *onPacketArrivesUserCookie, int id);

    void stop_capture(pcpp::PcapLiveDevice *dev);

private:
    CaptureWrapper();

    std::mutex m_is_capturing;
    bool is_capturing = false;
    int capturing_thread_id = 0;
    utils::Logger &logger = utils::Logger::getInstance();

};

}
#endif //ASHKANTOOL_CAPTURE_WRAPPER_HPP
