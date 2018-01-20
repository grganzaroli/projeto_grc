/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include "bch.h"
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
unsigned char pol_gerador_s[n_s-k_s+1] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,1,
0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,
1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(norma, dvbt2 encoder grc)

unsigned char pol_primitivo_s[m_s+1] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1}; // MATLAB

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade

#define m_n 16
#define n_n 43200 //acrescentar n_extension zeros no comeco do vetor recebido ate atingir 65535 amostras
#define k_n 43008	
#define t_n 12
/*unsigned char pol_gerador_n[n_n-k_n+1] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1};*/ //(meu calculo - matlab)
unsigned char pol_gerador_n[n_n-k_n+1] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,
1,1,0,1,1,1,0,1,0,1,1,0,0,1,0,0,0,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,0,
0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,1,
1,1,1,1,1,0,1}; //(dvbt2 encoder grc)
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1}; // NAO RECONHECEU
unsigned char pol_primitivo_n[m_n+1] = {1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1}; // NAO RECONHECEU (MATLAB)
//int pol_primitivo[m+1] = {1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,1,1,0,1,1,0,1,1,0,0,0,0,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1};	// NAO RECONHECEU	
//int pol_primitivo[m+1] = {1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1};	// NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,1,1,0,1,1,1,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1}; // NAO RECONHECEU

#if N == 10800
  #define parity 168
#else
  #define parity 192
#endif

bch decoder;

namespace gr {
  namespace mack_sdr_rossi {

    BCH_decoder_ATSC::sptr
    BCH_decoder_ATSC::make(size_t N)
    {
      return gnuradio::get_initial_sptr
        (new BCH_decoder_ATSC_impl(N));
    }

    /*
     * The private constructor
     */
    BCH_decoder_ATSC_impl::BCH_decoder_ATSC_impl(size_t N)
      : gr::block("BCH_decoder_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)*N),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*(43008)))
        {
          N_size = N;
          
          //ESSA PARTE RODA SÓ UMA VEZ
          if(N_size == 10800)
          {
            decoder.init(n_s, k_s, t_s, m_s);
            decoder.set_pol_prim(pol_primitivo_s);
            decoder.calc_gf();
            decoder.calc_tab_inv();
          }
          else if(N_size == 43200)
          {
            decoder.init(n_n, k_n, t_n, m_n);
            decoder.set_pol_prim(pol_primitivo_n);
            decoder.calc_gf();
            decoder.calc_tab_inv();
          }
          else
            printf("Tamanho do frame invalido. Este deve ser 10800 (short) ou 43200 (normal).\n");
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
	void BCH_decoder_ATSC_impl::decoder_BCH(const char *in, char *out)
	{	
    if(N_size == 10800)
    {
      int n_err;
      unsigned char r[n_s];
      for(int i = 0; i < n_s; i++)
        r[n_s-1-i] = in[i];
      bool decoding_ok = decoder.decode(r, n_err);
      for(int i = 0; i < n_s; i++)
        out[n_s-1-i] = r[i];
    }
    else if(N_size == 43200)
    {
      int n_err;
      unsigned char r[n_n];
      for(int i = 0; i < n_n; i++)
        r[n_n-1-i] = in[i];
      bool decoding_ok = decoder.decode(r, n_err);
      for(int i = 0; i < n_n; i++)
        out[n_n-1-i] = r[i];
    }
	}


  int
  BCH_decoder_ATSC_impl::general_work (int noutput_items,
                      gr_vector_int &ninput_items,
                      gr_vector_const_void_star &input_items,
                      gr_vector_void_star &output_items)
  {
    const char *in = (const char *) input_items[0];
    char *out = (char *) output_items[0];

    // Do <+signal processing+>

    //FUNÇÃO RODA AQUI
    

    for (int nnn = 0; nnn < noutput_items; nnn++ )
    {
      decoder_BCH(in, &*out);
      
      //Incremento dos ponteiros para o GRC
      if(N_size == 10800)
      {
        in += n_n;
        out += k_s;
      }
      else if(N_size == 43200)
      {
        in += n_n;
        out += k_n;
      }
    }
	  
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

