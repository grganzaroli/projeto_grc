# Copyright 2011 Free Software Foundation, Inc.
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
install(FILES
    mack_sdr_rossi_str_to_vec.xml
    mack_sdr_rossi_BCH_decoder_ATSC.xml
    mack_sdr_rossi_Demapper_ATSC.xml
    mack_sdr_rossi_Parity_deinterleaver_ATSC.xml
    mack_sdr_rossi_Block_deinterleaver_ATSC.xml
    mack_sdr_rossi_Group_deinterleaver_ATSC.xml
    mack_sdr_rossi_LDPC_decoder_ATSC.xml
    mack_sdr_rossi_LDPC_decoder_hard_ATSC.xml
    mack_sdr_rossi_BCH_encoder_ATSC.xml
    mack_sdr_rossi_LDPC_encoder_ATSC.xml
    mack_sdr_rossi_Block_interleaver_ATSC.xml
    mack_sdr_rossi_Group_interleaver_ATSC.xml
    mack_sdr_rossi_Parity_interleaver_ATSC.xml
    mack_sdr_rossi_Mapper_ATSC.xml
    mack_sdr_rossi_Bit_interleaver_ATSC.xml
    mack_sdr_rossi_Bit_deinterleaver_ATSC.xml DESTINATION /usr/local/share/gnuradio/grc/blocks
)
