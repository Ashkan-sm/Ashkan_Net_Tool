//
// Created by dev on 6/5/25.
//

#include "../include/capture_wrapper.h"

CaptureWrapper &CaptureWrapper::getInstance() {
    static CaptureWrapper capture_rapper;
    return capture_rapper;
}

CaptureWrapper::CaptureWrapper() {

}

bool CaptureWrapper::start_capture(pcpp::PcapLiveDevice *dev, pcpp::OnPacketArrivesCallback onPacketArrives,
                                   void *onPacketArrivesUserCookie,int id) {
    m_is_capturing.lock();
    if(is_capturing== false) {
        dev->startCapture(onPacketArrives, onPacketArrivesUserCookie);
        capturing_thread_id=id;
        is_capturing = true;
        m_is_capturing.unlock();
        return 1;
    }
    else{
        logger.log("capture is busy by thread : "+std::to_string(capturing_thread_id)+".\n");
        m_is_capturing.unlock();
        return 0;
    }

}

void CaptureWrapper::stop_capture(pcpp::PcapLiveDevice* dev) {
    dev->stopCapture();
    m_is_capturing.lock();
    is_capturing=false;
    m_is_capturing.unlock();
}
