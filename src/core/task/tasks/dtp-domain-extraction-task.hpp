//
// Created by dev on 7/10/25.
//

#ifndef ASHKANTOOL_DTP_DOMAIN_EXTRACTION_TASK_HPP
#define ASHKANTOOL_DTP_DOMAIN_EXTRACTION_TASK_HPP
#include "task-headers.hpp"
namespace ashk::tasks {
    class DtpDomainExtraction : public Task {
    public:
        explicit DtpDomainExtraction(pcpp::PcapLiveDevice *dev,
            pcpp::IPv4Address iface_ip,char buffer[32],
            int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        pcpp::IPv4Address iface_ip;
        char *buffer;

    };
}

#endif //ASHKANTOOL_DTP_DOMAIN_EXTRACTION_TASK_HPP
