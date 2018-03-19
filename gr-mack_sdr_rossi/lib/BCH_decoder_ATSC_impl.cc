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
#include "BCH_decoder_ATSC_impl.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <volk/volk.h>
#pragma warning	(disable: 4996)

//BCH 10/15 short_frame (10800,10632,12) - 168 bits de paridade

#define m_s 14
#define n_s 10800 //acrescentar n_extension zeros no comeco do vetor recebido ate atingir 16383 amostras
#define k_s 10632	
#define t_s 12
unsigned char pol_gerador_s[169] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,1,
0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,1,1,
0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(norma, dvbt2 encoder grc)

unsigned char pol_primitivo_s[m_s+1] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1}; // MATLAB

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade

#define m_n 16
#define n_n 43200 //acrescentar n_extension zeros no comeco do vetor recebido ate atingir 65535 amostras
#define k_n 43008	
#define t_n 12

unsigned char pol_gerador_n[193] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1}; //(meu calculo - matlab, victor)

unsigned char pol_primitivo_n[m_n+1] = {1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1};

namespace gr {
  namespace mack_sdr_rossi {

    BCH_decoder_ATSC::sptr
    BCH_decoder_ATSC::make(size_t N, size_t K)
    {
      return gnuradio::get_initial_sptr
        (new BCH_decoder_ATSC_impl(N, K));
    }

    /*
     * The private constructor
     */
    BCH_decoder_ATSC_impl::BCH_decoder_ATSC_impl(size_t N, size_t K)
      : gr::block("BCH_decoder_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)*N),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*K))
    {
      N_size = N;
      K_size = K;

      int parity_size = N-K;
      int M;

      if(parity_size == 168)
      {
        M = 14;
        decoder.set_pol_prim(pol_primitivo_s);
         }
      else if(parity_size == 192)
      {
        M = 16;
        decoder.set_pol_prim(pol_primitivo_n);
      }

      decoder.init(N, K, 12, M);
      decoder.calc_gf();
      decoder.calc_tab_inv();

    }

    /*
     * Our virtual destructor.
     */
    BCH_decoder_ATSC_impl::~BCH_decoder_ATSC_impl()
    {
      
    }

    void
    BCH_decoder_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    //ESCREVER FUNÇÃO AQUI
    void BCH_decoder_ATSC_impl::decoder_BCH(const unsigned char *in, unsigned char *out)
    {	
      int n_err;
      unsigned char r[N_size];
      for(int i = 0; i < N_size; i++)
        r[N_size-1-i] = in[i];
      bool decoding_ok = decoder.decode(r, n_err);
      for(int i = 0; i < N_size; i++)
        out[N_size-1-i] = r[i];

    }

    int
    BCH_decoder_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>
      //FUNÇÃO RODA AQUI
    

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        decoder_BCH(in, &*out);
        
        //Incremento dos ponteiros para o GRC
        in += N_size;
        out += K_size;
      }
	  
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

