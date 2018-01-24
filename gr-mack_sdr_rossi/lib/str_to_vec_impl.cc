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
#include "str_to_vec_impl.h"
#include "stdio.h"

namespace gr {
  namespace mack_sdr_rossi {

    str_to_vec::sptr
    str_to_vec::make(size_t N)
    {
      return gnuradio::get_initial_sptr
        (new str_to_vec_impl());
    }

    /*
     * The private constructor
     */
    str_to_vec_impl::str_to_vec_impl()
      : gr::block("str_to_vec",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)*8192))
    {

      //ESSA PARTE RODA SÓ A PRIMEIRA VEZ


      count = 0;
      op = 0;
      n_out = 0;
      c = 0;
      C = 0;
      buf_size = 0;
      p_pass = true;
      aux_buf = 0;

      for(int i = 0; i < 100; i++)
      {
        buf[i] = 0;
      }


    }

    /*
     * Our virtual destructor.
     */
    str_to_vec_impl::~str_to_vec_impl()
    {
    }

    void
    str_to_vec_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    //ESCREVER FUNÇÃO AQUI
	void str_to_vec_impl::str_to_vector(const char *in, char *out)
	{	


  }


    int
    str_to_vec_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];

      // Do <+signal processing+>

      //FUNÇÃO RODA AQUI (criar uma função principal e chamar ela aqui)

      if(count == 0)
        op = 6075;
      else if(count == 1)
        op = 6432;
      else if(count > 1)
        op = 6807;

      if(count == 20)
        count = 0;

        C = c; //contador na passagem anterior
        c += noutput_items; //contador de entrada

        if(c <= op) //até completar o tamanho desejado
        {
          if(buf_size =! 0) //primeira passagem, copiar o que sobrou na passagem anterior
          {
            for(int i = 0; i < buf_size; i++) //copiar buffer para saída
            {
              out[i] = buf[i];
            }
            aux_buf = buf_size; 
            buf_size = 0; // já usei o buffer, zerar a variável
          }
          for(int i = 0; i < noutput_items; i++) //copiar entrada com o offset baseado na passagem anterior
          {
            out[i+C] = in[i];
          }
          //out += noutput_items+aux_buf; //incrementar saída
          out += 0; // NÃO incrementar saída
          aux_buf = 0; // após usar as amostras extras, zerar a variável
        }
        else if(c > op) //após completar o tamanho desejado
        {
          for(int i = op; i < 8192; i++) // zerar o resto do vetor
          {
            out[i] = 0;
          }
          //out += 8192-op; //incrementar saída
          out += 8192; //incrementar saída
          c -= op; //"resetar" variável que conta as entradas
          buf_size = c; //se não for o tamanho exato, descobrir quantas amostras a mais foram lidas 
          for(int i = noutput_items-buf_size; i < noutput_items; i++) // gravar amostras extras em um buffer
          {
            buf[i] = in[i];
          }
          //printf("%i %i %i %i %i %i\n", noutput_items, buf_size, op, out[op-1], out[op], out[op+1]);
          count++;
        }
      
        in += noutput_items; // incrementar entrada 

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

