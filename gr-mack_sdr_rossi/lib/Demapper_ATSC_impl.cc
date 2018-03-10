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
#include <stdio.h>
#endif

#include <gnuradio/io_signature.h>
#include "Demapper_ATSC_impl.h"
#include "stdio.h"

#pragma warning	(disable: 4996)

namespace gr {
  namespace mack_sdr_rossi {

    Demapper_ATSC::sptr
    Demapper_ATSC::make(int size_in, int size_out, int rate, int mod_size, float var)
    {
      return gnuradio::get_initial_sptr
        (new Demapper_ATSC_impl(size_in, size_out, rate, mod_size, var));
    }

    /*
     * The private constructor
     */
    Demapper_ATSC_impl::Demapper_ATSC_impl(int size_in, int size_out, int rate, int mod_size, float var)
      : gr::block("Demapper_ATSC",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*size_in),
              gr::io_signature::make(1, 1, sizeof(float)*size_out))
    {

      s_in = size_in;
      s_out = size_out;

      //printf("mod_size = %i, rate = %i/15\n", mod_size, rate);

      demapper.init(size_in, mod_size, rate, var);
    }

    /*
     * Our virtual destructor.
     */
    Demapper_ATSC_impl::~Demapper_ATSC_impl()
    {
    }

    void
    Demapper_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    void Demapper_ATSC_impl::DEMAP(const gr_complex *in, float *out)
    {
      demapper.demapper_soft(in, out);
    }

    int
    Demapper_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        DEMAP(in, &*out);
        
        //Incremento dos ponteiros para o GRC
        in += s_in;
        out += s_out;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

