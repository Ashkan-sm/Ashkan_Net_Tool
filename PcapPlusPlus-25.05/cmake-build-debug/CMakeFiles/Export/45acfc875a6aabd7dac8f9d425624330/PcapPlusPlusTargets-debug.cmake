#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "PcapPlusPlus::Common++" for configuration "Debug"
set_property(TARGET PcapPlusPlus::Common++ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::Common++ PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libCommon++.a"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::Common++ )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::Common++ "${_IMPORT_PREFIX}/lib/libCommon++.a" )

# Import target "PcapPlusPlus::Packet++" for configuration "Debug"
set_property(TARGET PcapPlusPlus::Packet++ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::Packet++ PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libPacket++.a"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::Packet++ )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::Packet++ "${_IMPORT_PREFIX}/lib/libPacket++.a" )

# Import target "PcapPlusPlus::Pcap++" for configuration "Debug"
set_property(TARGET PcapPlusPlus::Pcap++ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::Pcap++ PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libPcap++.a"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::Pcap++ )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::Pcap++ "${_IMPORT_PREFIX}/lib/libPcap++.a" )

# Import target "PcapPlusPlus::Arping" for configuration "Debug"
set_property(TARGET PcapPlusPlus::Arping APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::Arping PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/Arping"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::Arping )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::Arping "${_IMPORT_PREFIX}/bin/Arping" )

# Import target "PcapPlusPlus::ArpSpoofing" for configuration "Debug"
set_property(TARGET PcapPlusPlus::ArpSpoofing APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::ArpSpoofing PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/ArpSpoofing"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::ArpSpoofing )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::ArpSpoofing "${_IMPORT_PREFIX}/bin/ArpSpoofing" )

# Import target "PcapPlusPlus::DNSResolver" for configuration "Debug"
set_property(TARGET PcapPlusPlus::DNSResolver APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::DNSResolver PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/DNSResolver"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::DNSResolver )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::DNSResolver "${_IMPORT_PREFIX}/bin/DNSResolver" )

# Import target "PcapPlusPlus::DnsSpoofing" for configuration "Debug"
set_property(TARGET PcapPlusPlus::DnsSpoofing APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::DnsSpoofing PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/DnsSpoofing"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::DnsSpoofing )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::DnsSpoofing "${_IMPORT_PREFIX}/bin/DnsSpoofing" )

# Import target "PcapPlusPlus::HttpAnalyzer" for configuration "Debug"
set_property(TARGET PcapPlusPlus::HttpAnalyzer APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::HttpAnalyzer PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/HttpAnalyzer"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::HttpAnalyzer )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::HttpAnalyzer "${_IMPORT_PREFIX}/bin/HttpAnalyzer" )

# Import target "PcapPlusPlus::IcmpFileTransfer-catcher" for configuration "Debug"
set_property(TARGET PcapPlusPlus::IcmpFileTransfer-catcher APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::IcmpFileTransfer-catcher PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/IcmpFileTransfer-catcher"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::IcmpFileTransfer-catcher )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::IcmpFileTransfer-catcher "${_IMPORT_PREFIX}/bin/IcmpFileTransfer-catcher" )

# Import target "PcapPlusPlus::IcmpFileTransfer-pitcher" for configuration "Debug"
set_property(TARGET PcapPlusPlus::IcmpFileTransfer-pitcher APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::IcmpFileTransfer-pitcher PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/IcmpFileTransfer-pitcher"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::IcmpFileTransfer-pitcher )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::IcmpFileTransfer-pitcher "${_IMPORT_PREFIX}/bin/IcmpFileTransfer-pitcher" )

# Import target "PcapPlusPlus::IPDefragUtil" for configuration "Debug"
set_property(TARGET PcapPlusPlus::IPDefragUtil APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::IPDefragUtil PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/IPDefragUtil"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::IPDefragUtil )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::IPDefragUtil "${_IMPORT_PREFIX}/bin/IPDefragUtil" )

# Import target "PcapPlusPlus::IPFragUtil" for configuration "Debug"
set_property(TARGET PcapPlusPlus::IPFragUtil APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::IPFragUtil PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/IPFragUtil"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::IPFragUtil )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::IPFragUtil "${_IMPORT_PREFIX}/bin/IPFragUtil" )

# Import target "PcapPlusPlus::BenchmarkExample" for configuration "Debug"
set_property(TARGET PcapPlusPlus::BenchmarkExample APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::BenchmarkExample PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/BenchmarkExample"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::BenchmarkExample )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::BenchmarkExample "${_IMPORT_PREFIX}/bin/BenchmarkExample" )

# Import target "PcapPlusPlus::BenchmarkExampleGoogle" for configuration "Debug"
set_property(TARGET PcapPlusPlus::BenchmarkExampleGoogle APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::BenchmarkExampleGoogle PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/BenchmarkExampleGoogle"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::BenchmarkExampleGoogle )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::BenchmarkExampleGoogle "${_IMPORT_PREFIX}/bin/BenchmarkExampleGoogle" )

# Import target "PcapPlusPlus::PcapPrinter" for configuration "Debug"
set_property(TARGET PcapPlusPlus::PcapPrinter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::PcapPrinter PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/PcapPrinter"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::PcapPrinter )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::PcapPrinter "${_IMPORT_PREFIX}/bin/PcapPrinter" )

# Import target "PcapPlusPlus::PcapSearch" for configuration "Debug"
set_property(TARGET PcapPlusPlus::PcapSearch APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::PcapSearch PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/PcapSearch"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::PcapSearch )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::PcapSearch "${_IMPORT_PREFIX}/bin/PcapSearch" )

# Import target "PcapPlusPlus::PcapSplitter" for configuration "Debug"
set_property(TARGET PcapPlusPlus::PcapSplitter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::PcapSplitter PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/PcapSplitter"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::PcapSplitter )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::PcapSplitter "${_IMPORT_PREFIX}/bin/PcapSplitter" )

# Import target "PcapPlusPlus::SSLAnalyzer" for configuration "Debug"
set_property(TARGET PcapPlusPlus::SSLAnalyzer APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::SSLAnalyzer PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/SSLAnalyzer"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::SSLAnalyzer )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::SSLAnalyzer "${_IMPORT_PREFIX}/bin/SSLAnalyzer" )

# Import target "PcapPlusPlus::TcpReassembly" for configuration "Debug"
set_property(TARGET PcapPlusPlus::TcpReassembly APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::TcpReassembly PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/TcpReassembly"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::TcpReassembly )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::TcpReassembly "${_IMPORT_PREFIX}/bin/TcpReassembly" )

# Import target "PcapPlusPlus::TLSFingerprinting" for configuration "Debug"
set_property(TARGET PcapPlusPlus::TLSFingerprinting APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PcapPlusPlus::TLSFingerprinting PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/TLSFingerprinting"
  )

list(APPEND _cmake_import_check_targets PcapPlusPlus::TLSFingerprinting )
list(APPEND _cmake_import_check_files_for_PcapPlusPlus::TLSFingerprinting "${_IMPORT_PREFIX}/bin/TLSFingerprinting" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
