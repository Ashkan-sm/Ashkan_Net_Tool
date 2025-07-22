//
// Created by dev on 7/22/25.
//

#ifndef ASHKANTOOL_WIFI_AP_SCANNING_TASK_HPP
#define ASHKANTOOL_WIFI_AP_SCANNING_TASK_HPP

#include "task-headers.hpp"
#include "wifi-ap.hpp"
namespace ashk::tasks {
    class WifiApScanningTask:public Task{
    public:
        explicit WifiApScanningTask(pcpp::PcapLiveDevice *dev,
                                    pcpp::IPv4Address iface_ip,
                                    std::vector<WifiAp> &ap_list,
        int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        std::vector<WifiAp> *ap_list;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        int last_task_id;
    };
}

#endif //ASHKANTOOL_WIFI_AP_SCANNING_TASK_HPP
