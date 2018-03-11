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
#include "LDPC_decoder_ATSC_impl.h"
#include <cmath>
#include <stdio.h>

namespace gr {
  namespace mack_sdr_rossi {

    LDPC_decoder_ATSC::sptr
    LDPC_decoder_ATSC::make(int N_in, int N_out)
    {
      return gnuradio::get_initial_sptr
        (new LDPC_decoder_ATSC_impl(N_in, N_out));
    }

    /*
     * The private constructor
     */
    LDPC_decoder_ATSC_impl::LDPC_decoder_ATSC_impl(int N_in, int N_out)
      : gr::block("LDPC_decoder_ATSC",
              gr::io_signature::make(1, 1, sizeof(float)*N_in),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*N_out))
    	{
		      N = N_in;
          K = N_out;
          printf("\nSTART LDPC SOFT\n");

          decoder.init(N, K);
          printf("INIT LDPC SOFT OK\n");

          decoder.alocar_soft();
          printf("ALOC LDPC SOFT OK\n");
	    }

    /*
     * Our virtual destructor.
     */
    LDPC_decoder_ATSC_impl::~LDPC_decoder_ATSC_impl()
    {
      decoder.free_soft();
      printf("FREE LDPC SOFT OK\n");
    }

    void
    LDPC_decoder_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }


    //ESCREVER FUNÇÃO AQUI
    void LDPC_decoder_ATSC_impl::decoder_LDPC(const float *in, unsigned char *out)
    {	
      decoder.decode_soft(in, out);
    }

    int
    LDPC_decoder_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];



      // Do <+signal processing+>

      //FUNÇÃO RODA AQUI (criar uma função principal e chamar ela aqui)

      for ( int nnn = 0; nnn < noutput_items; nnn++ )
      {
            
        /*
        FILE *F = fopen("vetor_IN.txt", "w");
        for (int j = 0; j < n; j++)
        {
            fprintf(F, "%.2lf,\t", in[j]);
        }
        fprintf(F, "\n");
        fclose(F);
        printf("vetor_IN OK\n");
        */

        decoder_LDPC(in, &*out);

        /*
        printf("%lu ", sizeof(in));
        printf("%lu ", sizeof(ninput_items));
        printf("%i\n", noutput_items);
        FILE *f = fopen("vetor_OUT.txt", "w");
        for (int j = 0; j < k; j++)
        {
            fprintf(f, "%i", out[j]);
        }
        fprintf(f, "\n");
        fclose(f);
        printf("vetor_OUT OK\n");
        */

        
        //Incremento dos ponteiros para o GRC
        in += N;
        out += K;

      }




      /*
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (sizeof(ninput_items));
      */

      //CÓDIGO ORIGINAL
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);
      


      // Tell runtime system how many output items we produced.
      return noutput_items;
      
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */