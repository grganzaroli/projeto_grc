# Install script for directory: /home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_str_to_vec.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_BCH_decoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Demapper_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Parity_deinterleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Block_deinterleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Group_deinterleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_LDPC_decoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_LDPC_decoder_hard_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_BCH_encoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_LDPC_encoder_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Block_interleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Group_interleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Parity_interleaver_ATSC.xml;/usr/local/share/gnuradio/grc/blocks/mack_sdr_rossi_Mapper_ATSC.xml")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_str_to_vec.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_BCH_decoder_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Demapper_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Parity_deinterleaver_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Block_deinterleaver_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Group_deinterleaver_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_LDPC_decoder_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_LDPC_decoder_hard_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_BCH_encoder_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_LDPC_encoder_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Block_interleaver_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Group_interleaver_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Parity_interleaver_ATSC.xml"
    "/home/aluno/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/grc/mack_sdr_rossi_Mapper_ATSC.xml"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

