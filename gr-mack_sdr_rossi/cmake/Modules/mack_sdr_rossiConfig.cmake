INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MACK_SDR_ROSSI mack_sdr_rossi)

FIND_PATH(
    MACK_SDR_ROSSI_INCLUDE_DIRS
    NAMES mack_sdr_rossi/api.h
    HINTS $ENV{MACK_SDR_ROSSI_DIR}/include
        ${PC_MACK_SDR_ROSSI_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MACK_SDR_ROSSI_LIBRARIES
    NAMES gnuradio-mack_sdr_rossi
    HINTS $ENV{MACK_SDR_ROSSI_DIR}/lib
        ${PC_MACK_SDR_ROSSI_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MACK_SDR_ROSSI DEFAULT_MSG MACK_SDR_ROSSI_LIBRARIES MACK_SDR_ROSSI_INCLUDE_DIRS)
MARK_AS_ADVANCED(MACK_SDR_ROSSI_LIBRARIES MACK_SDR_ROSSI_INCLUDE_DIRS)

