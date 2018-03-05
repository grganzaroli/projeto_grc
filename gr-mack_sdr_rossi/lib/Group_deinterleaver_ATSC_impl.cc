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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "Group_deinterleaver_ATSC_impl.h"

namespace gr {
  namespace mack_sdr_rossi {

    Group_deinterleaver_ATSC::sptr
    Group_deinterleaver_ATSC::make(int Nldpc, int Rate, int Mod_size)
    {
      return gnuradio::get_initial_sptr
        (new Group_deinterleaver_ATSC_impl(Nldpc, Rate, Mod_size));
    }

    /*
     * The private constructor
     */
    Group_deinterleaver_ATSC_impl::Group_deinterleaver_ATSC_impl(int Nldpc, int Rate, int Mod_size)
      : gr::block("Group_deinterleaver_ATSC",
              gr::io_signature::make(1, 1, sizeof(float)*Nldpc),
              gr::io_signature::make(1, 1, sizeof(float)*Nldpc))
    {
      nldpc = Nldpc;
      rate = Rate;
      mod_size = Mod_size;

      deinterleaver.set(nldpc, rate, mod_size);
    }

    /*
     * Our virtual destructor.
     */
    Group_deinterleaver_ATSC_impl::~Group_deinterleaver_ATSC_impl()
    {
    }

    void
    Group_deinterleaver_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    void Group_deinterleaver_ATSC_impl::GWDI (const float *in, float *out)
    {
      deinterleaver.group_deinter(in, out);
    }

    int
    Group_deinterleaver_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        GWDI(in, &*out);
        
        //Incremento dos ponteiros para o GRC
        in += nldpc;
        out += nldpc;
      }
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

