//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_CAPTURE_WRAPPER_H
#define ASHKANTOOL_CAPTURE_WRAPPER_H

#include <iostream>
#include <MacAddress.h>
#include <IpAddress.h>
#include <Logger.h>
#include <PcapPlusPlusVersion.h>
#include <PcapLiveDeviceList.h>
#include <PcapLiveDevice.h>
#include <NetworkUtils.h>
#include <getopt.h>
#include <SystemUtils.h>
#include <EthLayer.h>
#include <Packet.h>
#include <mutex>
#include "logger.h"
class CaptureWrapper {
public:
    static CaptureWrapper& getInstance();
    bool start_capture(pcpp::PcapLiveDevice* dev,pcpp::OnPacketArrivesCallback onPacketArrives, void* onPacketArrivesUserCookie,int id);
    void stop_capture(pcpp::PcapLiveDevice* dev);
private:
    CaptureWrapper();
    CaptureWrapper(const CaptureWrapper&)=delete;
    CaptureWrapper& operator=(const CaptureWrapper&)=default;

    std::mutex m_is_capturing;
    bool is_capturing=false;
    int capturing_thread_id=0;
    Logger &logger=Logger::getInstance();

};


#endif //ASHKANTOOL_CAPTURE_WRAPPER_H
