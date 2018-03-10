#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: BICM ATSC 3.0 
# Author: Guilherme Rossi Ganzaroli
# Generated: Fri Mar  9 14:00:37 2018
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
from block_deinter import block_deinter  # grc-generated hier_block
from demapper_atsc import demapper_atsc  # grc-generated hier_block
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from group_deinter import group_deinter  # grc-generated hier_block
from ldpc_dec import ldpc_dec  # grc-generated hier_block
from optparse import OptionParser
from parity_deinter import parity_deinter  # grc-generated hier_block
import math
import sip


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
        self.r = r = 10
        self.n_ldpc = n_ldpc = 64800
        self.samp_rate = samp_rate = 32000
        self.n_bch = n_bch = n_ldpc*r/15
        self.mod_size = mod_size = 64

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
        	1024, #size
        	samp_rate, #samp_rate
        	'OUT', #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-0.1, 1.1)
        
        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")
        
        self.qtgui_time_sink_x_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(True)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_0.disable_legend()
        
        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_win)
        self.parity_deinter_0 = parity_deinter(
            n=n_ldpc,
            r=r,
        )
        self.ldpc_dec_0 = ldpc_dec(
            n=n_ldpc,
            r=r,
        )
        self.group_deinter_0 = group_deinter(
            mod=mod_size,
            n=n_ldpc,
            r=r,
        )
        self.demapper_atsc_0 = demapper_atsc(
            m=mod_size,
            r=r,
            size_in=1,
        )
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_gr_complex*1, 'mapper.bin', True)
        self.blocks_char_to_float_0_0 = blocks.char_to_float(1, 1)
        self.block_deinter_0 = block_deinter(
            mod=mod_size,
            n=n_ldpc,
            r=r,
        )
        self.bch_dec_0 = bch_dec(
            fec=10,
            size=64800,
        )

        ##################################################
        # Connections
        ##################################################
        self.connect((self.bch_dec_0, 0), (self.blocks_char_to_float_0_0, 0))    
        self.connect((self.block_deinter_0, 0), (self.group_deinter_0, 0))    
        self.connect((self.blocks_char_to_float_0_0, 0), (self.qtgui_time_sink_x_0, 0))    
        self.connect((self.blocks_file_source_0, 0), (self.blocks_throttle_0, 0))    
        self.connect((self.blocks_throttle_0, 0), (self.demapper_atsc_0, 0))    
        self.connect((self.demapper_atsc_0, 0), (self.block_deinter_0, 0))    
        self.connect((self.group_deinter_0, 0), (self.parity_deinter_0, 0))    
        self.connect((self.ldpc_dec_0, 0), (self.bch_dec_0, 0))    
        self.connect((self.parity_deinter_0, 0), (self.ldpc_dec_0, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_r(self):
        return self.r

    def set_r(self, r):
        self.r = r
        self.parity_deinter_0.set_r(self.r)
        self.set_n_bch(self.n_ldpc*self.r/15)
        self.ldpc_dec_0.set_r(self.r)
        self.group_deinter_0.set_r(self.r)
        self.demapper_atsc_0.set_r(self.r)
        self.block_deinter_0.set_r(self.r)

    def get_n_ldpc(self):
        return self.n_ldpc

    def set_n_ldpc(self, n_ldpc):
        self.n_ldpc = n_ldpc
        self.parity_deinter_0.set_n(self.n_ldpc)
        self.set_n_bch(self.n_ldpc*self.r/15)
        self.ldpc_dec_0.set_n(self.n_ldpc)
        self.group_deinter_0.set_n(self.n_ldpc)
        self.block_deinter_0.set_n(self.n_ldpc)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_n_bch(self):
        return self.n_bch

    def set_n_bch(self, n_bch):
        self.n_bch = n_bch

    def get_mod_size(self):
        return self.mod_size

    def set_mod_size(self, mod_size):
        self.mod_size = mod_size
        self.group_deinter_0.set_mod(self.mod_size)
        self.demapper_atsc_0.set_m(self.mod_size)
        self.block_deinter_0.set_mod(self.mod_size)


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
