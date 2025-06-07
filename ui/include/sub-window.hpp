//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_SUB_WINDOW_HPP
#define ASHKANTOOL_SUB_WINDOW_HPP
#include "imgui-headers.hpp"
#include "config.h"
#include "../../core/interface.hpp"

class ISubWindow {
public:
    explicit ISubWindow(ashk::ModelInterface *core);
    virtual void draw() = 0;
protected:
    ashk::ModelInterface *core_;
    void draw_base(const std::string &name);
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
#endif //ASHKANTOOL_SUB_WINDOW_HPP
