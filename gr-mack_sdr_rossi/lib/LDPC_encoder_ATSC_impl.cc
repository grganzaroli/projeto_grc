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
#include "LDPC_encoder_ATSC_impl.h"
#include <stdio.h>

namespace gr {
  namespace mack_sdr_rossi {

    LDPC_encoder_ATSC::sptr
    LDPC_encoder_ATSC::make(size_t K_ldpc, size_t N_ldpc, int rate)
    {
      return gnuradio::get_initial_sptr
        (new LDPC_encoder_ATSC_impl(K_ldpc, N_ldpc, rate));
    }

    /*
     * The private constructor
     */
    LDPC_encoder_ATSC_impl::LDPC_encoder_ATSC_impl(size_t K_ldpc, size_t N_ldpc, int rate)
      : gr::block("LDPC_encoder_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)*K_ldpc),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*N_ldpc))
    {
      N = N_ldpc;
      K = K_ldpc;

      printf("\nSTART LDPC ENCODER\n");

      encoder.init(N, K);
      printf("INIT LDPC ENCODER OK\n");

    }

    /*
     * Our virtual destructor.
     */
    LDPC_encoder_ATSC_impl::~LDPC_encoder_ATSC_impl()
    {
    }

    void
    LDPC_encoder_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    //ESCREVER FUNÇÃO AQUI
    void LDPC_encoder_ATSC_impl::encoder_LDPC(const unsigned char *in, unsigned char *out)
    {	
      encoder.encode(in, out);
    }

    int
    LDPC_encoder_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>

      for ( int nnn = 0; nnn < noutput_items; nnn++ )
      {

        encoder_LDPC(in, &*out);

        //Incremento dos ponteiros para o GRC
        in += K;
        out += N;

      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

