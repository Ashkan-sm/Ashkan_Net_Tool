
#include "core/packet-receiver/packet-receiver.hpp"
struct TagData {
    uint8_t* data;
    uint8_t length;
};
void ashk::PacketReceiver::onPacketArrivesWifiApScanning(pcpp::RawPacket *raw_pcap_packet, pcpp::PcapLiveDevice *dev, void *cookie) {
    auto *data = static_cast<WifiApScanningCookie *>(cookie);
//    data->ap_list->push_back({"yoo"});
    const uint8_t* raw_packet=raw_pcap_packet->getRawData();

    const uint8_t* wifi_layer;
    if(htonl(*reinterpret_cast<const uint32_t *>(raw_packet))==0x44000000){//parism header
        uint32_t prism_header_length= *reinterpret_cast<const uint32_t *>(raw_packet+4);
        wifi_layer=raw_packet+prism_header_length;
    }
    else if(raw_packet[0]==0x00){//readio header
        uint16_t radio_header_length= *reinterpret_cast<const uint16_t *>(raw_packet+2);
        wifi_layer=raw_packet+radio_header_length;
    }
    else{
        return;
    }



    uint16_t wifi_layer_type= htons(*reinterpret_cast<const uint16_t *>(wifi_layer));
    if (wifi_layer_type!=0x8000 && wifi_layer_type!=0x5000)//beacon packet or probe respounce
        return;
    uint8_t ap_mac_adr[6];
    memcpy(ap_mac_adr,wifi_layer+16,6);

    const uint8_t* fixed_params=wifi_layer+24;
    const uint8_t*  variable_tags=fixed_params+12;
    std::map<uint8_t,TagData> tags;
    int i=0;
    while(variable_tags+i< raw_packet + raw_pcap_packet->getRawDataLen()){
        uint8_t id=variable_tags[i];
        i++;
        uint8_t length=variable_tags[i];
        i++;
        tags[id].data=new uint8_t[length];
        tags[id].length=length;
        memcpy(tags[id].data,variable_tags+i,length);
        i+=length;
    }
    WifiAp out(std::string(reinterpret_cast<char*>(tags[0].data), tags[0].length));
    out.b_ssid=pcpp::MacAddress(ap_mac_adr);
    if(out.b_ssid==pcpp::MacAddress::Zero)
        return;
    if(std::find(data->ap_list->begin(), data->ap_list->end(),out)==data->ap_list->end())
        data->ap_list->push_back(out);

}