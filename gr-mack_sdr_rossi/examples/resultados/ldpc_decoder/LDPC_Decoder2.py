#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Ldpc Decoder2
# Generated: Fri Oct 26 19:01:06 2018
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
from demapper_atsc import demapper_atsc  # grc-generated hier_block
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.qtgui import Range, RangeWidget
from grc_gnuradio import blks2 as grc_blks2
from ldpc_dec_soft import ldpc_dec_soft  # grc-generated hier_block
from ldpc_enc import ldpc_enc  # grc-generated hier_block
from mapper_atsc import mapper_atsc  # grc-generated hier_block
from optparse import OptionParser
import math
import sip


class LDPC_Decoder2(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Ldpc Decoder2")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Ldpc Decoder2")
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

        self.settings = Qt.QSettings("GNU Radio", "LDPC_Decoder2")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.r = r = 10
        self.n = n = 64800
        self.EsN0_dB = EsN0_dB = 2

        ##################################################
        # Blocks
        ##################################################
        self._EsN0_dB_range = Range(-50, 50, 1, 2, 200)
        self._EsN0_dB_win = RangeWidget(self._EsN0_dB_range, self.set_EsN0_dB, "EsN0_dB", "counter_slider", float)
        self.top_layout.addWidget(self._EsN0_dB_win)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title("")
        
        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        units = ['', '', '', '', '',
                 '', '', '', '', '']
        colors = [("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
                  ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        for i in xrange(1):
            self.qtgui_number_sink_0.set_min(i, -1)
            self.qtgui_number_sink_0.set_max(i, 1)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])
        
        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_number_sink_0_win)
        self.mapper_atsc_0 = mapper_atsc(
            m=4,
            n=2,
            r=r,
        )
        self.ldpc_enc_0 = ldpc_enc(
            n=n,
            r=r,
        )
        self.ldpc_dec_soft_0 = ldpc_dec_soft(
            n=64800,
            r=10,
        )
        self.demapper_atsc_0 = demapper_atsc(
            m=4,
            r=r,
            size_in=1,
        )
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(8)
        self.blocks_pack_k_bits_bb_0 = blocks.pack_k_bits_bb(8)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, '/home/rossi/PN.ts', False)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, 'ldpc_decoder_soft.bin', False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.blks2_error_rate_0 = grc_blks2.error_rate(
        	type='BER',
        	win_size=1000000000,
        	bits_per_symbol=8,
        )
        self.analog_noise_source_x_0_0 = analog.noise_source_c(analog.GR_GAUSSIAN, math.sqrt(1/math.pow(10.0,(EsN0_dB/10.0))), 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0_0, 0), (self.blocks_add_xx_0, 0))    
        self.connect((self.blks2_error_rate_0, 0), (self.qtgui_number_sink_0, 0))    
        self.connect((self.blocks_add_xx_0, 0), (self.demapper_atsc_0, 0))    
        self.connect((self.blocks_file_source_0, 0), (self.blks2_error_rate_0, 0))    
        self.connect((self.blocks_file_source_0, 0), (self.blocks_unpack_k_bits_bb_0, 0))    
        self.connect((self.blocks_pack_k_bits_bb_0, 0), (self.blks2_error_rate_0, 1))    
        self.connect((self.blocks_pack_k_bits_bb_0, 0), (self.blocks_file_sink_0, 0))    
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.ldpc_enc_0, 0))    
        self.connect((self.demapper_atsc_0, 0), (self.ldpc_dec_soft_0, 0))    
        self.connect((self.ldpc_dec_soft_0, 0), (self.blocks_pack_k_bits_bb_0, 0))    
        self.connect((self.ldpc_enc_0, 0), (self.mapper_atsc_0, 0))    
        self.connect((self.mapper_atsc_0, 0), (self.blocks_add_xx_0, 1))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "LDPC_Decoder2")
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
        self.mapper_atsc_0.set_r(self.r)
        self.ldpc_enc_0.set_r(self.r)
        self.demapper_atsc_0.set_r(self.r)

    def get_n(self):
        return self.n

    def set_n(self, n):
        self.n = n
        self.ldpc_enc_0.set_n(self.n)

    def get_EsN0_dB(self):
        return self.EsN0_dB

    def set_EsN0_dB(self, EsN0_dB):
        self.EsN0_dB = EsN0_dB
        self.analog_noise_source_x_0_0.set_amplitude(math.sqrt(1/math.pow(10.0,(self.EsN0_dB/10.0))))


def main(top_block_cls=LDPC_Decoder2, options=None):

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
