//
// Created by dev on 6/5/25.
//

#include "capture-wrapper.hpp"

namespace ashk {

CaptureWrapper &CaptureWrapper::getInstance() {
    static CaptureWrapper capture_rapper;
    return capture_rapper;
}

CaptureWrapper::CaptureWrapper() = default;

bool CaptureWrapper::start_capture(pcpp::PcapLiveDevice *dev, pcpp::OnPacketArrivesCallback onPacketArrives,
                                   void *onPacketArrivesUserCookie, int id) {
    m_is_capturing.lock();
    if (!is_capturing) {
        dev->startCapture(std::move(onPacketArrives), onPacketArrivesUserCookie);
        capturing_thread_id = id;
        is_capturing = true;
        m_is_capturing.unlock();
        return true;
    } else {
        logger.log("capture is busy by thread : " + std::to_string(capturing_thread_id) + ".\n");
        m_is_capturing.unlock();
        return false;
    }

}

void CaptureWrapper::stop_capture(pcpp::PcapLiveDevice *dev) {
    dev->stopCapture();
    m_is_capturing.lock();
    is_capturing = false;
    m_is_capturing.unlock();
}


}