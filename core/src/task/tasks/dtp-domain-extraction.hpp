//
// Created by dev on 7/10/25.
//

#ifndef ASHKANTOOL_DTP_DOMAIN_EXTRACTION_HPP
#define ASHKANTOOL_DTP_DOMAIN_EXTRACTION_HPP
#include "task-headers.hpp"
namespace ashk::tasks {
    class DtpDomainExtraction : public Task {
    public:
        explicit DtpDomainExtraction(pcpp::PcapLiveDevice *dev,
        pcpp::IPv4Address iface_ip,
        int last_task_id);
    private:
        void exec() override;
        pcpp::PcapLiveDevice *dev_ = nullptr;
        pcpp::IPv4Address iface_ip;
        int last_task_id;
    };
}

#endif //ASHKANTOOL_DTP_DOMAIN_EXTRACTION_HPP
