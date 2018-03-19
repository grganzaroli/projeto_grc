# Install script for directory: /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_str_to_vec.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_BCH_decoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Demapper_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Parity_deinterleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Block_deinterleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Group_deinterleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_LDPC_decoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_LDPC_decoder_hard_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_BCH_encoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_LDPC_encoder_ATSC.xml")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_str_to_vec.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_BCH_decoder_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Demapper_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Parity_deinterleaver_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Block_deinterleaver_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Group_deinterleaver_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_LDPC_decoder_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_LDPC_decoder_hard_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_BCH_encoder_ATSC.xml"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_LDPC_encoder_ATSC.xml"
    )
endif()

