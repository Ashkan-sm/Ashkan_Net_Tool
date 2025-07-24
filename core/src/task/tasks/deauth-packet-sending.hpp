
#ifndef ASHKANTOOL_DEAUTH_PACKET_SENDING_HPP
#define ASHKANTOOL_DEAUTH_PACKET_SENDING_HPP
#include "task-headers.hpp"
namespace ashk::tasks {
    class DeauthPacketSendingTask : public Task {
    public:
        explicit DeauthPacketSendingTask(pcpp::PcapLiveDevice *dev,
                                         std::string iface_name_or_ip,
                                         WifiAp &wifi_ap,
                                         std::vector<std::shared_ptr<WifiHost>> &host_list,
                                         int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        std::string iface_name_or_ip;
        WifiAp* wifi_ap;
        std::vector<std::shared_ptr<WifiHost>> *host_list;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        int last_task_id;
    };
}

#endif //ASHKANTOOL_DEAUTH_PACKET_SENDING_HPP
