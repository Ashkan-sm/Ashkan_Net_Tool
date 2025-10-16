//
// Created by dev on 10/12/25.
//

#ifndef ASHKANTOOL_SERVICES_HPP
#define ASHKANTOOL_SERVICES_HPP

#include "ui-services.grpc.pb.h"
#include "core/interface.hpp"
#include "utils/signal-vector.hpp"

class Services final : public UiServie::Service {
 public:
  explicit Services(std::shared_ptr<ashk::ModelInterface> core);
  grpc::Status ReadLogs(
      ::grpc::ServerContext* context, const ::ReadLogsRequestType* request,
      ::grpc::ServerWriter<::ReadLogsResponseType>* writer) override;
  grpc::Status Arp(::grpc::ServerContext* context,
                   const ::ArpRequestType* request,
                   ::ArpResponseType* response) override;
  grpc::Status GetInterfaces(::grpc::ServerContext* context,
                             const ::GetInterfacesRequestType* request,
                             ::GetInterfacesResponseType* response) override;

  grpc::Status SendArpReq(::grpc::ServerContext* context,
                          const ::SendArpReqRequestType* request,
                          ::SendArpReqResponseType* response) override;

  grpc::Status StartArpPoison(::grpc::ServerContext* context,
                              const ::StartArpPoisonRequestType* request,
                              ::StartArpPoisonResponseType* response) override;
  grpc::Status StartVlanHopping(
      ::grpc::ServerContext* context,
      const ::StartVlanHoppingRequestType* request,
      ::StartVlanHoppingResponseType* response) override;
  grpc::Status StartDtpDomainExtraction(
      ::grpc::ServerContext* context,
      const ::StartDtpDomainExtractionRequestType* request,
      ::StartDtpDomainExtractionResponseType* response) override;
  grpc::Status StartDtpNegotiation(
      ::grpc::ServerContext* context,
      const ::StartDtpNegotiationRequestType* request,
      ::StartDtpNegotiationResponseType* response) override;
  grpc::Status StartWpa2HandshakeCapturing(
      ::grpc::ServerContext* context,
      const ::StartWpa2HandshakeCapturingRequestType* request,
      ::StartWpa2HandshakeCapturingResponseType* response) override;
  grpc::Status EndTask(::grpc::ServerContext* context,
                       const ::EndTaskRequestType* request,
                       ::EndTaskResponseType* response) override;
  grpc::Status StartDetectingWifiHosts(
      ::grpc::ServerContext* context,
      const ::StartDetectingWifiHostsRequestType* request,
      ::grpc::ServerWriter<::StartDetectingWifiHostsResponseType>* writer)
      override;
  grpc::Status GetRunningTasks(
      ::grpc::ServerContext* context,
      const ::GetRunningTasksRequestType* request,
      ::grpc::ServerWriter<::GetRunningTasksResponseType>* writer) override;
  grpc::Status StartDetectingWifiAps(
      ::grpc::ServerContext* context,
      const ::StartDetectingWifiApsRequestType* request,
      ::grpc::ServerWriter<::StartDetectingWifiApsResponseType>* writer)
      override;
  grpc::Status StartPasswordCracking(
      ::grpc::ServerContext* context,
      const ::StartPasswordCrackingRequestType* request,
      ::StartPasswordCrackingResponseType* response) override;
  grpc::Status StartSendingDeauthPackets(
      ::grpc::ServerContext* context,
      const ::StartSendingDeauthPacketsRequestType* request,
      ::StartSendingDeauthPacketsResponseType* response) override;
  grpc::Status StartMitmForwarding(
      ::grpc::ServerContext* context,
      const ::StartMitmForwardingRequestType* request,
      ::StartMitmForwardingResponseType* response) override;
  grpc::Status StartArpPoisonDetection(
      ::grpc::ServerContext* context,
      const ::StartArpPoisonDetectionRequestType* request,
      ::StartArpPoisonDetectionResponseType* response) override;

 private:
  std::shared_ptr<ashk::ModelInterface> core_;


};

#endif  //ASHKANTOOL_SERVICES_HPP
