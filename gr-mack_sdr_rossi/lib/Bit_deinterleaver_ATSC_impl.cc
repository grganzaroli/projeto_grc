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
#include "Bit_deinterleaver_ATSC_impl.h"
#include "stdio.h"

namespace gr {
  namespace mack_sdr_rossi {

    Bit_deinterleaver_ATSC::sptr
    Bit_deinterleaver_ATSC::make(size_t ldpc_size, int rate, int mod)
    {
      return gnuradio::get_initial_sptr
        (new Bit_deinterleaver_ATSC_impl(ldpc_size, rate, mod));
    }

    /*
     * The private constructor
     */
    Bit_deinterleaver_ATSC_impl::Bit_deinterleaver_ATSC_impl(size_t ldpc_size, int rate, int mod)
      : gr::block("Bit_deinterleaver_ATSC",
              gr::io_signature::make(1, 1, sizeof(float)*ldpc_size),
              gr::io_signature::make(1, 1, sizeof(float)*ldpc_size))
    {
      Nldpc = ldpc_size;
      Rate = rate;
      Mod_size = mod;

      deinterleaver.set(Nldpc, Rate, Mod_size);

      float t_in[64800];

      for(int i = 0; i < Nldpc; i++)
      {
        t_in[i] = i;
        tab[i] = i;
      }
      
      if((Rate >= 8)||(Rate == 6)||((Rate == 7)&&(Nldpc == 16200)))
        deinterleaver.parity_inter(t_in, tab); // APENAS LDPC TIPO B
      else
        for(int i = 0; i < Nldpc; i++)
          tab[i] = t_in[i];
      deinterleaver.group_inter(tab, t_in);
      deinterleaver.block_inter(t_in, tab);
    }

    /*
     * Our virtual destructor.
     */
    Bit_deinterleaver_ATSC_impl::~Bit_deinterleaver_ATSC_impl()
    {
    }

    void
    Bit_deinterleaver_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    void Bit_deinterleaver_ATSC_impl::Bit_deinterleaver (const float *in, float *out)
    {
      for(int i = 0; i < Nldpc; i++)
        out[(int)tab[i]] = in[i];
    }

    int
    Bit_deinterleaver_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        Bit_deinterleaver(in, &*out);
        
        //Incremento dos ponteiros para o GRC
        in += Nldpc;
        out += Nldpc;
      }
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

