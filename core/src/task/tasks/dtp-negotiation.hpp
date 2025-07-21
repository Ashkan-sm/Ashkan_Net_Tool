//
// Created by dev on 7/9/25.
//

#ifndef ASHKANTOOL_DTP_NEGOTIATION_HPP
#define ASHKANTOOL_DTP_NEGOTIATION_HPP
#include "task-headers.hpp"

namespace ashk::tasks{
    class DTPNegotiation : public Task {
    public:
        explicit DTPNegotiation(pcpp::PcapLiveDevice *dev,
                                pcpp::IPv4Address iface_ip,
                                std::string domain_name,
                                int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        std::string domain_name;
        int last_task_id;
    };

}

#endif //ASHKANTOOL_DTP_NEGOTIATION_HPP
