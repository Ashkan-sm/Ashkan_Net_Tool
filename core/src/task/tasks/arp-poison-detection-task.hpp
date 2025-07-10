//
// Created by dev on 6/9/25.
//

#ifndef ASHKANTOOL_ARP_POISON_DETECTION_TASK_HPP
#define ASHKANTOOL_ARP_POISON_DETECTION_TASK_HPP

#include "task-headers.hpp"

namespace ashk::tasks {
    class ArpPoisonDetectionTask : public Task {
    public:
        explicit ArpPoisonDetectionTask(pcpp::IPv4Address iface_ip,int last_task_id);
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        int last_task_id;
    };
}

#endif //ASHKANTOOL_ARP_POISON_DETECTION_TASK_HPP
