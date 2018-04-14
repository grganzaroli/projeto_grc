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


#ifndef INCLUDED_MACK_SDR_ROSSI_BIT_INTERLEAVER_ATSC_H
#define INCLUDED_MACK_SDR_ROSSI_BIT_INTERLEAVER_ATSC_H

#include <mack_sdr_rossi/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace mack_sdr_rossi {

    /*!
     * \brief <+description of block+>
     * \ingroup mack_sdr_rossi
     *
     */
    class MACK_SDR_ROSSI_API Bit_interleaver_ATSC : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<Bit_interleaver_ATSC> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of mack_sdr_rossi::Bit_interleaver_ATSC.
       *
       * To avoid accidental use of raw pointers, mack_sdr_rossi::Bit_interleaver_ATSC's
       * constructor is in a private implementation
       * class. mack_sdr_rossi::Bit_interleaver_ATSC::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t ldpc_size, int rate, int mod);
    };

  } // namespace mack_sdr_rossi
} // namespace gr

#endif /* INCLUDED_MACK_SDR_ROSSI_BIT_INTERLEAVER_ATSC_H */

