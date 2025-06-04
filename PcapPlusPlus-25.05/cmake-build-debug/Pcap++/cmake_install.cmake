# Install script for directory: /media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/cmake-build-debug/Pcap++/libPcap++.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pcapplusplus" TYPE FILE FILES
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/Device.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/DeviceListBase.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/NetworkUtils.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/PcapDevice.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/PcapFileDevice.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/PcapFilter.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/PcapLiveDevice.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/PcapLiveDeviceList.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/RawSocketDevice.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Pcap++/header/LinuxNicInformationSocket.h"
    )
endif()

