# Install script for directory: /media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/cmake-build-debug/Common++/libCommon++.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pcapplusplus" TYPE FILE FILES
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/DeprecationUtils.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/GeneralUtils.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/IpAddress.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/IpAddressUtils.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/IpUtils.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/Logger.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/LRUList.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/MacAddress.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/ObjectPool.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/OUILookup.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/PcapPlusPlusVersion.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/PointerVector.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/SystemUtils.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/TablePrinter.h"
    "/media/dev/H/projects/pcap/PcapPlusPlus-25.05/Common++/header/TimespecTimeval.h"
    )
endif()

