# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND mack_sdr_rossi_sources
    str_to_vec_impl.cc
    bch.cpp
	ldpc.cpp
	demap.cpp
	atsc_interleaver.cpp
    BCH_decoder_ATSC_impl.cc
    Demapper_ATSC_impl.cc
    Parity_deinterleaver_ATSC_impl.cc
    Block_deinterleaver_ATSC_impl.cc
    Group_deinterleaver_ATSC_impl.cc
    LDPC_decoder_ATSC_impl.cc
    LDPC_decoder_hard_ATSC_impl.cc )

set(mack_sdr_rossi_sources "${mack_sdr_rossi_sources}" PARENT_SCOPE)
if(NOT mack_sdr_rossi_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT mack_sdr_rossi_sources)

add_library(gnuradio-mack_sdr_rossi SHARED ${mack_sdr_rossi_sources})
target_link_libraries(gnuradio-mack_sdr_rossi ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-mack_sdr_rossi PROPERTIES DEFINE_SYMBOL "gnuradio_mack_sdr_rossi_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-mack_sdr_rossi PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-mack_sdr_rossi RUNTIME_COMPONENT "mack_sdr_rossi_runtime" DEVEL_COMPONENT "mack_sdr_rossi_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_mack_sdr_rossi_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_mack_sdr_rossi.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_mack_sdr_rossi.cc
)

add_executable(test-mack_sdr_rossi ${test_mack_sdr_rossi_sources})

target_link_libraries(
  test-mack_sdr_rossi
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-mack_sdr_rossi
)

GR_ADD_TEST(test_mack_sdr_rossi test-mack_sdr_rossi)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

