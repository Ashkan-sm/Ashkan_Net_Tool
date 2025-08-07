// Created by dev on 6/5/25.
//

#include "capture-wrapper.hpp"

namespace ashk {

CaptureWrapper &CaptureWrapper::getInstance() {
    static CaptureWrapper capture_rapper;
    return capture_rapper;
}

CaptureWrapper::CaptureWrapper() = default;

bool CaptureWrapper::StartCapture(pcpp::PcapLiveDevice *dev, pcpp::OnPacketArrivesCallback onPacketArrives,
                                  void *onPacketArrivesUserCookie, int id) {
    m_is_capturing_.lock();
    if (!is_capturing_) {
        dev->startCapture(std::move(onPacketArrives), onPacketArrivesUserCookie);
      capturing_thread_id_ = id;
      is_capturing_ = true;
        m_is_capturing_.unlock();
        return true;
    } else {
      logger_.Log("capture is busy by thread : " + std::to_string(capturing_thread_id_) + ".\n");
        m_is_capturing_.unlock();
        return false;
    }

}

void CaptureWrapper::StopCapture(pcpp::PcapLiveDevice *dev) {
    dev->stopCapture();
    m_is_capturing_.lock();
  is_capturing_ = false;
    m_is_capturing_.unlock();
}


}