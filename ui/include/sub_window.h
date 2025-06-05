//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_SUB_WINDOW_H
#define ASHKANTOOL_SUB_WINDOW_H
#include "imgui_headers.h"
#include "config.h"
#include "../../model/interface.h"

class ISubWindow {
public:
    ISubWindow(ModelInterface *core);
    virtual void draw() = 0;
protected:
    ModelInterface *core_;
    void draw_base(const std::string &name);
private:
};
class DefaultWindow :public ISubWindow{
public:
    DefaultWindow(ModelInterface *core);
    void draw() override;
};

class ArpSpoofWindow :public ISubWindow{
public:
    ArpSpoofWindow(ModelInterface *core);
    void draw() override;
};

class ArpPoisonDetectionWindow :public ISubWindow{
public:
    ArpPoisonDetectionWindow(ModelInterface *core);
    void draw() override;
};

#endif //ASHKANTOOL_SUB_WINDOW_H
