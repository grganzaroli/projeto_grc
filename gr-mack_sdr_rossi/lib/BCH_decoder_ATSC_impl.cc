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

#define m 14
#define n 10800 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir 16383 amostras
#define k 10632	
#define n_extension 5583  //numero de zeroas a acrescntar em n
#define t 12
int pol_gerador[n-k+1] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,1,
0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,
1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(norma)
int pol_primitivo[m+1] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1};

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade
/*
#define m 16
#define n 43200 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir 65535 amostras
#define k 43008	
#define n_extension 22335  //numero de zeroas a acrescntar em n
#define t 12
int pol_gerador[n-k+1] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1}; //(norma)
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1}; // NAO RECONHECEU
int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1}; // NAO RECONHECEU (MATLAB)
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
*/

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
              gr::io_signature::make(1, 1, sizeof(unsigned char)*(10632)))
        {
          N_size = N;
          //ESSA PARTE RODA SÓ UMA VEZ

          decoder.init(n, k, t, m);
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
	void BCH_decoder_ATSC_impl::decoder_BCH(const char *in, char *out)
	{	
    int n_err;
    unsigned char r[n];
    for(int i = 0; i < n; i++)
      r[i] = in[i];
    bool decoding_ok = decoder.decode(r, n_err);
    for(int i = 0; i < n; i++)
      out[i] = r[i];
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
      in += n;
      out += k;
    }
	  
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

