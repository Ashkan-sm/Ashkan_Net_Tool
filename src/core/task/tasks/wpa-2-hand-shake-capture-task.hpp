//
// Created by dev on 8/3/25.
//

#ifndef ASHKANTOOL_WPA_2_HAND_SHAKE_CAPTURE_TASK_HPP
#define ASHKANTOOL_WPA_2_HAND_SHAKE_CAPTURE_TASK_HPP
#include "task-headers.hpp"

namespace ashk::tasks {

    class WPA2HandShakeCaptureTask : public Task {
    public:
        explicit WPA2HandShakeCaptureTask(pcpp::PcapLiveDevice *dev,
                                          std::string iface_name_or_ip,std::shared_ptr<HandShakeData> data,
                                     int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        std::string iface_name_or_ip;
        std::shared_ptr<HandShakeData> data;
        
    };
}

#endif //ASHKANTOOL_WPA_2_HAND_SHAKE_CAPTURE_TASK_HPP
