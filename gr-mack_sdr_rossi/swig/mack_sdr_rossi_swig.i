/* -*- c++ -*- */

#define MACK_SDR_ROSSI_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "mack_sdr_rossi_swig_doc.i"

%{
#include "mack_sdr_rossi/str_to_vec.h"
#include "mack_sdr_rossi/BCH_decoder_ATSC.h"
#include "mack_sdr_rossi/Demapper_ATSC.h"
#include "mack_sdr_rossi/Parity_deinterleaver_ATSC.h"
#include "mack_sdr_rossi/Block_deinterleaver_ATSC.h"
#include "mack_sdr_rossi/Group_deinterleaver_ATSC.h"
#include "mack_sdr_rossi/LDPC_decoder_ATSC.h"
#include "mack_sdr_rossi/LDPC_decoder_hard_ATSC.h"
#include "mack_sdr_rossi/BCH_encoder_ATSC.h"
#include "mack_sdr_rossi/LDPC_encoder_ATSC.h"
#include "mack_sdr_rossi/Block_interleaver_ATSC.h"
#include "mack_sdr_rossi/Group_interleaver_ATSC.h"
#include "mack_sdr_rossi/Parity_interleaver_ATSC.h"
#include "mack_sdr_rossi/Mapper_ATSC.h"
%}


%include "mack_sdr_rossi/str_to_vec.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, str_to_vec);


%include "mack_sdr_rossi/BCH_decoder_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, BCH_decoder_ATSC);

%include "mack_sdr_rossi/Demapper_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Demapper_ATSC);
%include "mack_sdr_rossi/Parity_deinterleaver_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Parity_deinterleaver_ATSC);

%include "mack_sdr_rossi/Block_deinterleaver_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Block_deinterleaver_ATSC);
%include "mack_sdr_rossi/Group_deinterleaver_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Group_deinterleaver_ATSC);
%include "mack_sdr_rossi/LDPC_decoder_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, LDPC_decoder_ATSC);

%include "mack_sdr_rossi/LDPC_decoder_hard_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, LDPC_decoder_hard_ATSC);
%include "mack_sdr_rossi/BCH_encoder_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, BCH_encoder_ATSC);
%include "mack_sdr_rossi/LDPC_encoder_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, LDPC_encoder_ATSC);
%include "mack_sdr_rossi/Block_interleaver_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Block_interleaver_ATSC);
%include "mack_sdr_rossi/Group_interleaver_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Group_interleaver_ATSC);
%include "mack_sdr_rossi/Parity_interleaver_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Parity_interleaver_ATSC);
%include "mack_sdr_rossi/Mapper_ATSC.h"
GR_SWIG_BLOCK_MAGIC2(mack_sdr_rossi, Mapper_ATSC);
