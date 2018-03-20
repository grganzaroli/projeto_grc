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
#include "Parity_interleaver_ATSC_impl.h"

namespace gr {
  namespace mack_sdr_rossi {

    Parity_interleaver_ATSC::sptr
    Parity_interleaver_ATSC::make(size_t Size, int Rate)
    {
      return gnuradio::get_initial_sptr
        (new Parity_interleaver_ATSC_impl(Size, Rate));
    }

    /*
     * The private constructor
     */
    Parity_interleaver_ATSC_impl::Parity_interleaver_ATSC_impl(size_t Size, int Rate)
      : gr::block("Parity_interleaver_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)*Size),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*Size))
    {
      nldpc = Size;
      rate = Rate;

      interleaver.set(nldpc, rate, 16); //mod_size nao importa
    }

    /*
     * Our virtual destructor.
     */
    Parity_interleaver_ATSC_impl::~Parity_interleaver_ATSC_impl()
    {
    }

    void
    Parity_interleaver_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    void Parity_interleaver_ATSC_impl::PI (const unsigned char *in, unsigned char *out)
    {
      if((rate >= 8)||(rate == 6)||((rate == 7)&&(nldpc == 16200)))
        interleaver.parity_inter(in, out); // APENAS LDPC TIPO B
      else
        for(int i = 0; i < nldpc; i++)
          out[i] = in[i];
    }

    int
    Parity_interleaver_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        PI(in, out);
        
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

