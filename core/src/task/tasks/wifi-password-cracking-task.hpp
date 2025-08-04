//
// Created by dev on 8/4/25.
//

#ifndef ASHKANTOOL_WIFI_PASSWORD_CRACKING_TASK_HPP
#define ASHKANTOOL_WIFI_PASSWORD_CRACKING_TASK_HPP
#include "task-headers.hpp"
#include <openssl/hmac.h>
#include <openssl/cmac.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

namespace ashk::tasks {
    class WifiPasswordCrackingTask :public Task{
    public:
        explicit WifiPasswordCrackingTask(pcpp::PcapLiveDevice *dev,
                                          std::string iface_name_or_ip, std::shared_ptr<HandShakeData> handshake_data,
                                          int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        std::string iface_name_or_ip;
        std::shared_ptr<HandShakeData> handshake_data;

    };
}


#endif //ASHKANTOOL_WIFI_PASSWORD_CRACKING_TASK_HPP
