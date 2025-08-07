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
#include "core/interface.hpp"
#include "core/data-holders/wifi.hpp"
#include "utils/logger.hpp"

class ISubWindow {
public:
    explicit ISubWindow(ashk::ModelInterface *core);
    virtual void draw() = 0;
protected:
    ashk::ModelInterface *core_;
    void draw_base(const std::string &name);
    pcpp::PcapLiveDevice * draw_interface_widget();
private:
};
class DefaultWindow :public ISubWindow{
public:
    explicit DefaultWindow(ashk::ModelInterface *core);
    void draw() override;
};

class ArpSpoofWindow :public ISubWindow{
public:
    explicit ArpSpoofWindow(ashk::ModelInterface *core);
    void draw() override;
};

class ArpPoisonDetectionWindow :public ISubWindow{
public:
    explicit ArpPoisonDetectionWindow(ashk::ModelInterface *core);
    void draw() override;
};
class SendArpRequestWindow :public ISubWindow{
public:
    explicit SendArpRequestWindow(ashk::ModelInterface *core);
    void draw() override;
};
class VlanHoppingWindow  :public ISubWindow{
public:
    explicit VlanHoppingWindow(ashk::ModelInterface *core);
    void draw() override;
};
class MITMWindow  :public ISubWindow{
public:
    explicit MITMWindow(ashk::ModelInterface *core);
    void draw() override;
};
class WIFIAttackWindow  : public ISubWindow{
public:
    explicit WIFIAttackWindow(ashk::ModelInterface *core);
    void draw() override;
};

#endif //ASHKANTOOL_SUB_WINDOW_HPP
