//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_SUB_WINDOW_HPP
#define ASHKANTOOL_SUB_WINDOW_HPP

#include "EthDot3Layer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "config.h"
#include "utils/logger.hpp"
#include "grpc-interface/client-interface.hpp"

#include "ui/data-holders/wireless.hpp"

class ISubWindow {
public:
    explicit ISubWindow(ClientInterface *core);
    virtual void Draw() = 0;
protected:
    ClientInterface *core_;
    void DrawBase(const std::string &name);
    std::string DrawInterfaceWidget();
private:
};
class DefaultWindow :public ISubWindow{
public:
    explicit DefaultWindow(ClientInterface *core);
    void Draw() override;
};

class ArpSpoofWindow :public ISubWindow{
public:
    explicit ArpSpoofWindow(ClientInterface *core);
    void Draw() override;
};

class ArpPoisonDetectionWindow :public ISubWindow{
public:
    explicit ArpPoisonDetectionWindow(ClientInterface *core);
    void Draw() override;
};
class SendArpRequestWindow :public ISubWindow{
public:
    explicit SendArpRequestWindow(ClientInterface *core);
    void Draw() override;
};
class VlanHoppingWindow  :public ISubWindow{
public:
    explicit VlanHoppingWindow(ClientInterface *core);
    void Draw() override;
};
class MITMWindow  :public ISubWindow{
public:
    explicit MITMWindow(ClientInterface *core);
    void Draw() override;
};
class WIFIAttackWindow  : public ISubWindow{
 public:
  explicit WIFIAttackWindow(ClientInterface *core);
  void Draw() override;
 private:
  std::vector<ashk::ui::WifiAp> wifi_ap_list;
  std::vector<ashk::ui::WifiHost> wifi_host_list;
};

#endif //ASHKANTOOL_SUB_WINDOW_HPP
