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
#include "Mapper_ATSC_impl.h"

namespace gr {
  namespace mack_sdr_rossi {

    Mapper_ATSC::sptr
    Mapper_ATSC::make(size_t N_ldpc, int Rate, int Mod_size)
    {
      return gnuradio::get_initial_sptr
        (new Mapper_ATSC_impl(N_ldpc, Rate, Mod_size));
    }

    /*
     * The private constructor
     */
    Mapper_ATSC_impl::Mapper_ATSC_impl(size_t N_ldpc, int Rate, int Mod_size)
      : gr::block("Mapper_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      s_in = N_ldpc;
      m_size = Mod_size;
      mapper.init(s_in, Mod_size, Rate, 0.1);
      printf("MAPPER INIT\n");
    }

    /*
     * Our virtual destructor.
     */
    Mapper_ATSC_impl::~Mapper_ATSC_impl()
    {
    }

    void
    Mapper_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    void Mapper_ATSC_impl::MAP(const unsigned char *in, gr_complex *out)
    {
      mapper.mapper(in, out);
    }

    int
    Mapper_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>

      for (int nnn = 0; nnn < noutput_items; nnn++ )
      {
        MAP(in, &*out);
        
        //Incremento dos ponteiros para o GRC
        in += 1;
        out += 1;
      }
      
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

