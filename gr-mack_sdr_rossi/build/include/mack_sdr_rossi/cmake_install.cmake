# Install script for directory: /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mack_sdr_rossi" TYPE FILE FILES
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/api.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/LDPC_decoder_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/str_to_vec.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/LDPC_decoder_hard_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/BCH_decoder_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Demapper_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Parity_deinterleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Block_deinterleaver_ATSC.h"
    "/home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/include/mack_sdr_rossi/Group_deinterleaver_ATSC.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

