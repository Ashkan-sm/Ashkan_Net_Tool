//
// Created by dev on 10/16/25.
//

#ifndef ASHKANTOOL_WIRELESS_HPP
#define ASHKANTOOL_WIRELESS_HPP

#include <string>
namespace ashk::ui {
struct WifiAp {
  std::string mac;
  std::string name;
};
struct WifiHost {
  std::string mac;
  std::string name;
};
}  // namespace ashk::ui
#endif  //ASHKANTOOL_WIRELESS_HPP
