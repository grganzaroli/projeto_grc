#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: BICM ATSC 3.0 
# Author: Guilherme Rossi Ganzaroli
# Generated: Sun Dec 10 10:39:12 2017
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt4 import Qt
from bch_dec import bch_dec  # grc-generated hier_block
from bch_enc import bch_enc  # grc-generated hier_block
from block_deinter import block_deinter  # grc-generated hier_block
from block_inter import block_inter  # grc-generated hier_block
from demapper_atsc import demapper_atsc  # grc-generated hier_block
from gnuradio import blocks
from gnuradio import channels
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gw_deinter import gw_deinter  # grc-generated hier_block
from gw_inter import gw_inter  # grc-generated hier_block
from ldpc_dec import ldpc_dec  # grc-generated hier_block
from ldpc_enc import ldpc_enc  # grc-generated hier_block
from mapper_atsc import mapper_atsc  # grc-generated hier_block
from optparse import OptionParser
from parity_deinter import parity_deinter  # grc-generated hier_block
from parity_inter import parity_inter  # grc-generated hier_block
import mapper


class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "BICM ATSC 3.0 ")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("BICM ATSC 3.0 ")
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.r = r = 10
        self.n_ldpc = n_ldpc = 16200
        self.n_bch = n_bch = 10800

        ##################################################
        # Blocks
        ##################################################
        self.parity_inter_0 = parity_inter(
            n=n_ldpc,
        )
        self.parity_deinter_0 = parity_deinter(
            n=n_ldpc,
        )
        self.mapper_prbs_source_b_0 = mapper.prbs_source_b("PRBS7", 162000)
        self.mapper_prbs_sink_b_0 = mapper.prbs_sink_b("PRBS7", 162000)
        self.mapper_atsc_0 = mapper_atsc(
            m=6,
            n=n_ldpc,
            r=10,
        )
        self.ldpc_enc_0 = ldpc_enc(
            n=n_ldpc,
            r=r,
        )
        self.ldpc_dec_0 = ldpc_dec(
            n=16200,
            r=10,
        )
        self.gw_inter_0 = gw_inter(
            n=n_ldpc,
        )
        self.gw_deinter_0 = gw_deinter(
            n=n_ldpc,
        )
        self.demapper_atsc_0 = demapper_atsc(
            m=6,
            n=n_ldpc,
            r=10,
        )
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=0.15,
        	frequency_offset=0.0,
        	epsilon=1.0,
        	taps=(1.0 + 1.0j, ),
        	noise_seed=0,
        	block_tags=False
        )
        self.blocks_threshold_ff_0 = blocks.threshold_ff(0.5, 0.5, 0)
        self.blocks_float_to_char_0 = blocks.float_to_char(1, 1)
        self.block_inter_0 = block_inter(
            n=n_ldpc,
        )
        self.block_deinter_0 = block_deinter(
            n=n_ldpc,
        )
        self.bch_enc_0 = bch_enc(
            n=n_bch,
        )
        self.bch_dec_0 = bch_dec(
            n=10800,
        )

        ##################################################
        # Connections
        ##################################################
        self.connect((self.bch_dec_0, 0), (self.mapper_prbs_sink_b_0, 0))    
        self.connect((self.bch_enc_0, 0), (self.ldpc_enc_0, 0))    
        self.connect((self.block_deinter_0, 0), (self.gw_deinter_0, 0))    
        self.connect((self.block_inter_0, 0), (self.mapper_atsc_0, 0))    
        self.connect((self.blocks_float_to_char_0, 0), (self.ldpc_dec_0, 0))    
        self.connect((self.blocks_threshold_ff_0, 0), (self.blocks_float_to_char_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.demapper_atsc_0, 0))    
        self.connect((self.demapper_atsc_0, 0), (self.block_deinter_0, 0))    
        self.connect((self.gw_deinter_0, 0), (self.parity_deinter_0, 0))    
        self.connect((self.gw_inter_0, 0), (self.block_inter_0, 0))    
        self.connect((self.ldpc_dec_0, 0), (self.bch_dec_0, 0))    
        self.connect((self.ldpc_enc_0, 0), (self.parity_inter_0, 0))    
        self.connect((self.mapper_atsc_0, 0), (self.channels_channel_model_0, 0))    
        self.connect((self.mapper_prbs_source_b_0, 0), (self.bch_enc_0, 0))    
        self.connect((self.parity_deinter_0, 0), (self.blocks_threshold_ff_0, 0))    
        self.connect((self.parity_inter_0, 0), (self.gw_inter_0, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_r(self):
        return self.r

    def set_r(self, r):
        self.r = r
        self.ldpc_enc_0.set_r(self.r)

    def get_n_ldpc(self):
        return self.n_ldpc

    def set_n_ldpc(self, n_ldpc):
        self.n_ldpc = n_ldpc
        self.parity_inter_0.set_n(self.n_ldpc)
        self.parity_deinter_0.set_n(self.n_ldpc)
        self.mapper_atsc_0.set_n(self.n_ldpc)
        self.ldpc_enc_0.set_n(self.n_ldpc)
        self.gw_inter_0.set_n(self.n_ldpc)
        self.gw_deinter_0.set_n(self.n_ldpc)
        self.demapper_atsc_0.set_n(self.n_ldpc)
        self.block_inter_0.set_n(self.n_ldpc)
        self.block_deinter_0.set_n(self.n_ldpc)

    def get_n_bch(self):
        return self.n_bch

    def set_n_bch(self, n_bch):
        self.n_bch = n_bch
        self.bch_enc_0.set_n(self.n_bch)


def main(top_block_cls=top_block, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
