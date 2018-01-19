#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/rossi/Desktop/Git_Hub/projeto_grc/gr-mack_sdr_rossi/lib
export PATH=/home/rossi/Desktop/Git_Hub/projeto_grc/gr-mack_sdr_rossi/build/lib:$PATH
export LD_LIBRARY_PATH=/home/rossi/Desktop/Git_Hub/projeto_grc/gr-mack_sdr_rossi/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-mack_sdr_rossi 
