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
#include "BCH_encoder_ATSC_impl.h"
#include "bch.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <volk/volk.h>
#pragma warning	(disable: 4996)

//BCH 10/15 short_frame (10800,10632,12) - 168 bits de paridade

#define m__s 14
#define n__s 10800 //acrescentar n_extension zeros no comeco do vetor recebido ate atingir 16383 amostras
#define k__s 10632	
#define t__s 12
unsigned char p_gerador_s[169] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,
1,0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,
1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(norma, dvbt2 encoder grc)

unsigned char p_primitivo_s[m__s+1] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1}; // MATLAB

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade

#define m__n 16
#define n__n 43200 //acrescentar n_extension zeros no comeco do vetor recebido ate atingir 65535 amostras
#define k__n 43008	
#define t__n 12

unsigned char p_gerador_n[193] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1}; //(meu calculo - matlab, victor)

unsigned char p_primitivo_n[m__n+1] = {1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1};

namespace gr {
  namespace mack_sdr_rossi {

    BCH_encoder_ATSC::sptr
    BCH_encoder_ATSC::make(size_t K, size_t N)
    {
      return gnuradio::get_initial_sptr
        (new BCH_encoder_ATSC_impl(K, N));
    }

    /*
     * The private constructor
     */
    BCH_encoder_ATSC_impl::BCH_encoder_ATSC_impl(size_t K, size_t N)
      : gr::block("BCH_encoder_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)*K),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*N))
    {
      n_bch = N;
      k_bch = K;

      int parity_size = N-K;
      int M;

      if(parity_size == 168)
      {
        M = 14;
        encoder.set_pol_prim(p_primitivo_s);
        encoder.set_pol_ger(p_gerador_s);
      }
      else if(parity_size == 192)
      {
        M = 16;
        encoder.set_pol_prim(p_primitivo_n);
        encoder.set_pol_ger(p_gerador_n);
      }

      encoder.init(N, K, 12, M);
      //encoder.calc_gf();
      //encoder.calc_tab_inv();

      //printf("n = %i\n", n_bch);
      //printf("k = %i\n", k_bch);
      //printf("M = %i\n", M);
    }

    /*
     * Our virtual destructor.
     */
    BCH_encoder_ATSC_impl::~BCH_encoder_ATSC_impl()
    {
    }

    void
    BCH_encoder_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    //ESCREVER FUNÇÃO AQUI
    void BCH_encoder_ATSC_impl::encoder_BCH(const unsigned char *in, unsigned char *out)
    {	
      encoder.encode(in, out);
    }

    int
    BCH_encoder_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        encoder_BCH(in, &*out);
        
        //Incremento dos ponteiros para o GRC
        in += k_bch;
        out += n_bch;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

