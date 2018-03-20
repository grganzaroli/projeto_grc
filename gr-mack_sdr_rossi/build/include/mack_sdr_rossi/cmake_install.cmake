# Install script for directory: /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mack_sdr_rossi" TYPE FILE FILES
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/api.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/str_to_vec.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/BCH_decoder_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Demapper_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Parity_deinterleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Block_deinterleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Group_deinterleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/LDPC_decoder_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/LDPC_decoder_hard_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/BCH_encoder_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/LDPC_encoder_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Block_interleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Group_interleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Parity_interleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Mapper_ATSC.h"
    )
endif()

