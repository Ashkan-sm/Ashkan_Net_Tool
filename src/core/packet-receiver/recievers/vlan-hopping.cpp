//
// Created by dev on 7/10/25.
//

#include "core/packet-receiver/packet-receiver.hpp"

void ashk::PacketReceiver::onPacketArrivesVlanHopping(pcpp::RawPacket *rawPacket,
                                                      pcpp::PcapLiveDevice *dev,
                                                      void *cookie) {

  auto *data = static_cast<VlanHoppingCookie *>(cookie);

  // Parse the original packet
  pcpp::Packet originalPacket(rawPacket);

  auto *ethLayer = originalPacket.getLayerOfType<pcpp::EthLayer>();
  if (ethLayer == nullptr) {
//        std::cerr << "No Ethernet layer found!" << std::endl;
    return;
  }

  pcpp::MacAddress srcMac = ethLayer->getSourceMac();
  pcpp::MacAddress dstMac = ethLayer->getDestMac();
  if (srcMac != dev->getMacAddress()) {
    return;
  }
  auto *vlan_layer = originalPacket.getLayerOfType<pcpp::VlanLayer>();
  if (vlan_layer != nullptr) {
    return;
  }
  pcpp::Packet new_packet(rawPacket->getRawDataLen() + 100);
  pcpp::EthLayer new_ethlayer(srcMac, dstMac, PCPP_ETHERTYPE_VLAN);
  new_packet.addLayer(&new_ethlayer);
  int id = data->outer_id | data->inner_id;
  pcpp::VlanLayer Vlan(id,    // VLAN ID
                       false,      // Priority
                       0,      // DEI
                       ntohs(ethLayer->getEthHeader()->etherType));
  pcpp::VlanLayer outerVlan(data->outer_id,    // VLAN ID
                            false,      // Priority
                            0,      // DEI
                            PCPP_ETHERTYPE_VLAN);
  pcpp::VlanLayer innerVlan(data->inner_id,    // Target VLAN ID
                            false,      // Priority
                            0,      // DEI
                            ntohs(ethLayer->getEthHeader()->etherType));
  if (data->outer_id == 0 | data->inner_id == 0) {
    new_packet.addLayer(&Vlan);
  } else {
    new_packet.addLayer(&outerVlan);
    new_packet.addLayer(&innerVlan);
  }

  pcpp::Layer *layer = ethLayer->getNextLayer();
  uint8_t lArr[layer->getDataLen()];
  layer->copyData(lArr);
  auto *new_layer = new pcpp::PayloadLayer(lArr, sizeof(lArr));
  new_packet.addLayer(new_layer);

  new_packet.computeCalculateFields();
  dev->sendPacket(&new_packet);
}


