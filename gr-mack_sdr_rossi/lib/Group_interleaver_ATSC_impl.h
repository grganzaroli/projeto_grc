/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_MACK_SDR_ROSSI_GROUP_INTERLEAVER_ATSC_IMPL_H
#define INCLUDED_MACK_SDR_ROSSI_GROUP_INTERLEAVER_ATSC_IMPL_H

#include <mack_sdr_rossi/Group_interleaver_ATSC.h>
#include "atsc_interleaver.h"

namespace gr {
  namespace mack_sdr_rossi {

    class Group_interleaver_ATSC_impl : public Group_interleaver_ATSC
    {
     private:
      // Nothing to declare in this block.

     public:
      Group_interleaver_ATSC_impl(size_t Size, int Rate, int Mod);
      ~Group_interleaver_ATSC_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      int nldpc, rate, mod_size;

      atsc_interleaver interleaver;

      void GWI(const unsigned char *in, unsigned char *out);
    };

  } // namespace mack_sdr_rossi
} // namespace gr

#endif /* INCLUDED_MACK_SDR_ROSSI_GROUP_INTERLEAVER_ATSC_IMPL_H */

