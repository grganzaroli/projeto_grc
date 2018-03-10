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
#include "LDPC_decoder_hard_ATSC_impl.h"
#include <cmath>
#include <stdio.h>

//Teste para LDPC(7, 4)
/*
#define n 7
#define k 4
#define el_C 4 // numero de 1s por check node
#define max_it 50 // m�ximo de itera��es
int INDX_hard[n-k] = {4,4,4};
int C_hard[n-k][el_C] = {{0, 1, 3, 4},{0, 2, 3, 5},{1, 2, 3, 6}}; // matriz de check nodes
double in[n] =  {4.2, 3.05, -1.2, 2.2, -3.3, 2.8, 1.2}; // palavra-código recebida
//double in[n] =  {4.2, 3.05, -1.2, -2.2, -3.3, 2.8, 1.2}; // palavra-código recebida certa de primeira
*/
//LDPC 2/3 (64800, 43200) DVBT2
/*
#define n 64800
#define k 43200
#define el_C 8 // numero maximo de 1s por check node
#define max_it 50 // m�ximo de itera��es
#define Q_ldpc 60 //constante que vem da norma
int **C_i_hard; // matriz de troca de bits, que será calculada
int *INDX_i_hard; // indices para calcular a matriz C_i_hard, numero de troca de bits por linha
int **C_hard; // matriz de check nodes, que será calculada
int *INDX_hard; // indices para calcular a matriz C_hard, numero de 1s por linha
int *aux_indx_hard; // indice auxiliar para calcular C_hard
*/

//LDPC 2/3 (16200, 10800) DVBT2

#define n 16200
#define k 10800
#define el_C 8 // numero maximo de troca de bits por check node
#define max_it 50 // m�ximo de itera��es
#define Q_ldpc 15 //constante que vem da norma
int **C_i_hard; // matriz de troca de bits, que será calculada
int *INDX_i_hard; // indices para calcular a matriz C_i_hard, numero de troca de bits por linha
int **C_hard; // matriz de check nodes, que será calculada
int *INDX_hard; // indices para calcular a matriz C_hard, numero de 1s por linha
int *aux_indx_hard; // indice auxiliar para calcular C_hard


int **err_hard; //contagem de erros
int *r_aux_hard; //in para eu manipular
int *SIN_hard; //sindrome

namespace gr {
  namespace mack_sdr_rossi {

    LDPC_decoder_hard_ATSC::sptr
    LDPC_decoder_hard_ATSC::make(size_t N)
    {
      return gnuradio::get_initial_sptr
        (new LDPC_decoder_hard_ATSC_impl(N));
    }

    /*
     * The private constructor
     */
    LDPC_decoder_hard_ATSC_impl::LDPC_decoder_hard_ATSC_impl(size_t N)
      : gr::block("LDPC_decoder_hard_ATSC",
              gr::io_signature::make(1, 1, sizeof(char)*N),
              gr::io_signature::make(1, 1, sizeof(char)*10800))
    {
      N_size = N;
      

      //ESSA PARTE RODA SÓ A PRIMEIRA VEZ

      //TABELA DA NORMA 

      //10/15 64800 ATSC - 3.0
      /*
      int T[120][14] = {{316, 1271, 3692, 9495, 12147, 12849, 14928, 16671, 16938, 17864, 19108, 20502, 21097, 21115},
      {2341, 2559, 2643, 2816, 2865, 5137, 5331, 7000, 7523, 8023, 10439, 10797, 13208, 15041},
      {5556, 6858, 7677, 10162, 10207, 11349, 12321, 12398, 14787, 15743, 15859, 15952, 19313, 20879},
      {349, 573, 910, 2702, 3654, 6214, 9246, 9353, 10638, 11772, 14447, 14953, 16620, 19888},
      {204, 1390, 2887, 3835, 6230, 6533, 7443, 7876, 9299, 10291, 10896, 13960, 18287, 20086},
      {541, 2429, 2838, 7144, 8523, 8637, 10490, 10585, 11074, 12074, 15762, 16812, 17900, 18548},
      {733, 1659, 3838, 5323, 5805, 7882, 9429, 10682, 13697, 16909, 18846, 19587, 19592, 20904},
      {1134, 2136, 4631, 4653, 4718, 5197, 10410, 11666, 14996, 15305, 16048, 17417, 18960, 20303},
      {734, 1001, 1283, 4959, 10016, 10176, 10973, 11578, 12051, 15550, 15915, 19022, 19430, 20121},
      {745, 4057, 5855, 9885, 10594, 10989, 13156, 13219, 13351, 13631, 13685, 14577, 17713, 20386},
      {968, 1446, 2130, 2502, 3092, 3787, 5323, 8104, 8418, 9998, 11681, 13972, 17747, 17929},
      {3020, 3857, 5275, 5786, 6319, 8608, 11943, 14062, 17144, 17752, 18001, 18453, 19311, 21414},
      {709, 747, 1038, 2181, 5320, 8292, 10584, 10859, 13964, 15009, 15277, 16953, 20675, 21509},
      {1663, 3247, 5003, 5760, 7186, 7360, 10346, 14211, 14717, 14792, 15155, 16128, 17355, 17970},
      {516, 578, 1914, 6147, 9419, 11148, 11434, 13289, 13325, 13332, 19106, 19257, 20962, 21556},
      {5009, 5632, 6531, 9430, 9886, 10621, 11765, 13969, 16178, 16413, 18110, 18249, 20616, 20759},
      {457, 2686, 3318, 4608, 5620, 5858, 6480, 7430, 9602, 12691, 14664, 18777, 20152, 20848},
      {33, 2877, 5334, 6851, 7907, 8654, 10688, 15401, 16123, 17942, 17969, 18747, 18931, 20224},
      {87, 897, 7636, 8663, 11425, 12288, 12672, 14199, 16435, 17615, 17950, 18953, 19667, 20281},
      {1042, 1832, 2545, 2719, 2947, 3672, 3700, 6249, 6398, 6833, 11114, 14283, 17694, 20477},
      {326, 488, 2662, 2880, 3009, 5357, 6587, 8882, 11604, 14374, 18781, 19051, 19057, 20508},
      {854, 1294, 2436, 2852, 4903, 6466, 7761, 9072, 9564, 10321, 13638, 15658, 16946, 19119},
      {194, 899, 1711, 2408, 2786, 5391, 7108, 8079, 8716, 11453, 17303, 19484, 20989, 21389},
      {1631, 3121, 3994, 5005, 7810, 8850, 10315, 10589, 13407, 17162, 18624, 18758, 19311, 20301},
      {736, 2424, 4792, 5600, 6370, 10061, 16053, 16775, 18600, -1, -1, -1, -1, -1},
      {1254, 8163, 8876, 9157, 12141, 14587, 16545, 17175, 18191, -1, -1, -1, -1, -1},
      {388, 6641, 8974, 10607, 10716, 14477, 16825, 17191, 18400, -1, -1, -1, -1, -1},
      {5578, 6082, 6824, 7360, 7745, 8655, 11402, 11665, 12428, -1, -1, -1, -1, -1},
      {3603, 8729, 13463, 14698, 15210, 19112, 19550, 20727, 21052, -1, -1, -1, -1, -1},
      {48, 1732, 3805, 5158, 15442, 16909, 19854, 21071, 21579, -1, -1, -1, -1, -1},
      {11707, 14014, 21531, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1542, 4133, 4925, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {10083, 13505, 21198, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {14300, 15765, 16752, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {778, 1237, 11215, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1325, 3199, 14534, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2007, 14510, 20599, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1996, 5881, 16429, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5111, 15018, 15980, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4989, 10681, 12810, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3763, 10715, 16515, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2259, 10080, 15642, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9032, 11319, 21305, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3915, 15213, 20884, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {11150, 15022, 20201, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1147, 6749, 19625, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {12139, 12939, 18870, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3840, 4634, 10244, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1018, 10231, 17720, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2708, 13056, 13393, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5781, 11588, 18888, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1345, 2036, 5252, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5908, 8143, 15141, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1804, 13693, 18640, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {10433, 13965, 16950, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9568, 10122, 15945, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {547, 6722, 14015, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {321, 12844, 14095, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2632, 10513, 14936, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {6369, 11995, 20321, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9920, 19136, 21529, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1990, 2726, 10183, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5763, 12118, 15467, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {503, 10006, 19564, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9839, 11942, 19472, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {11205, 13552, 15389, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {8841, 13797, 19697, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {124, 6053, 18224, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {6477, 14406, 21146, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1224, 8027, 16011, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3046, 4422, 17717, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {739, 12308, 17760, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4014, 4130, 7835, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2266, 5652, 11981, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2711, 7970, 18317, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2196, 15229, 17217, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {8636, 13302, 16764, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5612, 15010, 16657, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {615, 1249, 4639, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3821, 12073, 18506, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1066, 16522, 21536, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {11307, 18363, 19740, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3240, 8560, 10391, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3124, 11424, 20779, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1604, 8861, 17394, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2083, 7400, 8093, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3218, 7454, 9155, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9855, 15998, 20533, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {316, 2850, 20652, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5583, 9768, 10333, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {7147, 7713, 18339, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {12607, 17428, 21418, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {14216, 16954, 18164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {8477, 15970, 18488, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1632, 8032, 9751, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4573, 9080, 13507, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {11747, 12441, 13876, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1183, 15605, 16675, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4408, 10264, 17109, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5495, 7882, 12150, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1010, 3763, 5065, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9828, 18054, 21599, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {6342, 7353, 15358, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {6362, 9462, 19999, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {7184, 13693, 17622, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4343, 4654, 10995, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {7099, 8466, 18520, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {11505, 14395, 15138, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {6779, 16691, 18726, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {7146, 12644, 20196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {5865, 16728, 19634, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4657, 8714, 21246, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4580, 5279, 18750, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3767, 6620, 18905, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9209, 13093, 17575, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {12486, 15875, 19791, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {8046, 14636, 17491, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2120, 4643, 13206, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {6186, 9675, 12601, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {784, 5770, 21585, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
      */

      //10/15 16200 - ATSC 3.0

      int T[30][25] = {{352, 747, 894, 1437, 1688, 1807, 1883, 2119, 2159, 3321, 3400, 3543, 3588, 3770, 3821, 4384, 4470, 4884, 5012, 5036, 5084, 5101, 5271, 5281, 5353},
      {505, 915, 1156, 1269, 1518, 1650, 2153, 2256, 2344, 2465, 2509, 2867, 2875, 3007, 3254, 3519, 3687, 4331, 4439, 4532, 4940, 5011, 5076, 5113, 5367},
      {268, 346, 650, 919, 1260, 4389, 4653, 4721, 4838, 5054, 5157, 5162, 5275, 5362, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {220, 236, 828, 1590, 1792, 3259, 3647, 4276, 4281, 4325, 4963, 4974, 5003, 5037, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {381, 737, 1099, 1409, 2364, 2955, 3228, 3341, 3473, 3985, 4257, 4730, 5173, 5242, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {88, 771, 1640, 1737, 1803, 2408, 2575, 2974, 3167, 3464, 3780, 4501, 4901, 5047, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {749, 1502, 2201, 3189, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2873, 3245, 3427, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2158, 2605, 3165, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1, 3438, 3606, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {10, 3019, 5221, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {371, 2901, 2923, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {9, 3935, 4683, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1937, 3502, 3735, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {507, 3128, 4994, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {25, 3854, 4550, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1178, 4737, 5366, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2, 223, 5304, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1146, 5175, 5197, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1816, 2313, 3649, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {740, 1951, 3844, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1320, 3703, 4791, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1754, 2905, 4058, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {7, 917, 5277, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {3048, 3954, 5396, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {4804, 4824, 5105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2812, 3895, 5226, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {0, 5318, 5358, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {1483, 2324, 4826, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
      {2266, 4752, 5387, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

      C_hard = new int*[n-k]; //matriz C_hard
      for(int i = 0; i < (n-k); i++)
        C_hard[i] = new int[k+1];
    
      C_i_hard = new int*[n-k]; //matriz C_i_hard
      for(int i = 0; i < (n-k); i++)
        C_i_hard[i] = new int[el_C];
    
      INDX_hard = new int[n-k]; //vetor INDX_hard
      INDX_i_hard = new int[n-k]; //vetor INDX_i_hard
      aux_indx_hard = new int[n-k]; //vetor aux_indx_hard
    
      int count = 0;
    
      //inicializar C_hard e INDX_hard
      /*
      memset(C_i_hard, -1, sizeof(C_i_hard[0][0]) * (n-k) * el_C);
      memset(C_hard, -1, sizeof(C_hard[0][0]) * (n-k) * (k+1));
      memset (INDX_i_hard, 0, sizeof(INDX_i_hard));
      memset (INDX_hard, 0, sizeof(INDX_i_hard));
      memset (aux_indx_hard, 0, sizeof(INDX_i_hard));
      */
      
      for (int j = 0; j < (n-k); j++)
      {
        for (int i = 0; i < el_C; i++)
        {
          C_i_hard[j][i] = -1;
        }
        for (int i = 0; i < (k+1); i++)
        {
          C_hard[j][i] = -1;
        }
        INDX_i_hard[j] = 0;
        INDX_hard[j] = 0;
        aux_indx_hard[j] = 0;
      }
      
    
      //for (int j = 0; j < 120; j++) //numero de linhas, LDPC 64800
      for (int j = 0; j < 30; j++) //numero de linhas, LDPC 16200
      {
        for (int kkk = 0; kkk < 360; kkk++) //elementos
        {
          //for (int i = 0; i < 14; i++) //elementos em uma linha, LDPC 64800
          for (int i = 0; i < 25; i++) //elementos em uma linha, LDPC 16200
          {
            if(T[j][i] != -1)
            {
              C_i_hard[(T[j][i]+kkk*Q_ldpc)%(n-k)][INDX_i_hard[(T[j][i]+kkk*Q_ldpc)%(n-k)]] = count;
    
              INDX_i_hard[(T[j][i]+kkk*Q_ldpc)%(n-k)] += 1;
            }
          }
          count++;
        }
      }
    
      int bit; //se inverteu para 0 ou 1
    
      for(int i = 0; i < k; i++) // para cada i
      {
        bit = 0;
        for(int j = 0; j < (n-k); j++) //para cada p
        {
          if(C_i_hard[j][aux_indx_hard[j]] == i)
          {
            bit = bit^1;
            aux_indx_hard[j]++;
          }
    
          if(bit == 1)
          {
            C_hard[j][INDX_hard[j]] = i;
            INDX_hard[j]++;
          }
        }
      }
    
      for (int i = 0; i < (n-k); i++)
      {
        C_hard[i][INDX_hard[i]] = i+k;
        INDX_hard[i]++;
      }
    
      
      //alocação das variáveis do loop principal

      r_aux_hard = new int[n]; 
      SIN_hard = new int[n-k]; 

      err_hard = new int*[n]; //matriz C_i_hard
      for(int i = 0; i < n; i++)
        err_hard[i] = new int[2];
    
    
      /*
      FILE *F = fopen("matriz_C_i.txt", "w");
      for (int j = 0; j < (n-k); j++)
      {
        for (int i = 0; i < el_C; i++)
        {
          fprintf(F, "%i,", C_i_hard[j][i]);
        }
        fprintf(F, "\n");
      }
      fclose(F);
      printf("OK matriz_C_i\n");
      */
      /*
      FILE *G = fopen("vetor_INDX_i.txt", "w");
      for (int j = 0; j < (n-k); j++)
      {
        fprintf(G, "%i,", INDX_i_hard[j]);
      }
      fclose(G);
      printf("OK vetor_INDX_i\n");
      */
      /*
      FILE *f = fopen("matriz_C.txt", "w");
      for (int j = 0; j < (n-k); j++)
      {
        for (int i = 0; i < (n-k); i++)
        {
          fprintf(f, "%i,", C_hard[j][i]);
        }
        fprintf(f, "\n");
      }
      fclose(f);
      printf("OK matriz_C\n");
      */
      /*
      FILE *g = fopen("vetor_INDX.txt", "w");
      for (int j = 0; j < (n-k); j++)
      {
        fprintf(g, "%i,", INDX_hard[j]);
      }
      fclose(g);
      printf("OK vetor_INDX\n");
      */
    
    }

    /*
     * Our virtual destructor.
     */
    LDPC_decoder_hard_ATSC_impl::~LDPC_decoder_hard_ATSC_impl()
    {
    }

    void
    LDPC_decoder_hard_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    //ESCREVER FUNÇÃO AQUI
    void LDPC_decoder_hard_ATSC_impl::decoder_LDPC_hard(const char *in, char *out)
    {	
      //FUNÇÃO PRINCIPAL que será chamada no main 

      int I = 0; //numero de iteraçoes
      int aux_S = 0; //auxiliar para saber se a sindrome é zero
      int c_node = 0; // bit que o check node acredita estar correto
    
      //copiar entrada
      for(int i = 0; i < n; i++)
      {
        r_aux_hard[i] = in[i];
      }

      //buscar e corrigir o erro
      while(I < 50)
      {
        aux_S = 0;
    
        //zerar sindrome
        for(int i = 0; i < (n-k); i++)
        {
          SIN_hard[i] = 0;
        }
    
        //calculo da sindrome
        for(int i = 0; i < (n-k); i++)
        {
          for(int j = 0; j < INDX_hard[i]; j++)
          {
            SIN_hard[i] = SIN_hard[i] ^ r_aux_hard[C_hard[i][j]];
          }
        }
    
        //checar se sindrome � zero
        for(int i = 0; i < (n-k); i++)
        {
          aux_S = aux_S + SIN_hard[i];    
        }
    
        // mensagem ok
        if(aux_S == 0) 
        {
          printf("MENSAGEM OK. ITERACOES = %i\n", I);
          goto end;
        }
        else
        {
            I++;
            
            printf("ITERACAO %i\n", I);
      
            //zerar err_hard
            for(int i = 0; i < n; i++)
            {
              err_hard[i][0] = 0;
              err_hard[i][1] = 0;
            }

            for(int i = 0; i < (n-k); i++) // cada fi (check node)
            {
              for(int j = 0; j < INDX_hard[i]; j++) //cada cj (entrada ligada ao check node)
              {
                c_node = 0;
                for(int K = 0; K < INDX_hard[i]; K++) //cada cK (entrada ligada ao check node, exceto cj)
                {
                  if(K != j)
                  {
                    c_node = c_node^r_aux_hard[C_hard[i][K]];
                  }
                }
      
                //contar 0s e 1s sugeridos
                if(c_node == 0)
                  err_hard[C_hard[i][j]][0]++;
                else if(c_node == 1)
                  err_hard[C_hard[i][j]][1]++;
      
              }
              if(i%100 == 0)
                printf("f%i, INDX[i] = %i\n", i, INDX_hard[i]);
            }
      
            for(int i = 0; i < n; i++)
            {
              //contar 0s e 1s na palavra codigo
      
              if(r_aux_hard[i] == 0)
                err_hard[i][0]++;
              else if(r_aux_hard[i] == 1)
                err_hard[i][1]++;
      
      
              //corrigir a palavra codigo
      
              if(err_hard[i][0] > err_hard[i][1])
              {
                if(r_aux_hard[i] == 1)
                  printf("%i INVERTEU DE 1 PARA 0 | 0 = %i | 1 = %i\n", i, err_hard[i][0], err_hard[i][1]);
                r_aux_hard[i] = 0;
              }
              else if(err_hard[i][0] < err_hard[i][1])
              {
                if(r_aux_hard[i] == 0)
                  printf("%i INVERTEU DE 0 PARA 1 | 0 = %i | 1 = %i\n", i, err_hard[i][0], err_hard[i][1]);
                r_aux_hard[i] = 1;
              }
            }
        }
    
        if(I == 50) //sair do loop se chegar ao max de iteracoes ou chegar em um "deadlock" 
        {
          printf("MENSAGEM NAO CORRIGIDA. ITERACOES = %i\n", I);
          goto end;
        }
      }
    
    end:
    
      //printf("ITERACOES = %i\n ", I);
    
    
      //r_aux_hard é a mensagem corrigida, out é a saída, sem os bits de paridade
      for(int i = 0; i < k; i++)
      {
        out[i] = r_aux_hard[i];
      }
    
    
      /*
      delete [] LLR;
      delete [] LLR_aux;
      delete [] r_aux_hard;
      delete [] SIN_hard;
    
      for (int i = 0; i < n-k; ++i)
        delete [] R[i];
      delete [] R;
    
      for (int i = 0; i < n-k; ++i)
        delete [] Q[i];
      delete [] Q;
      */

    }

    int
    LDPC_decoder_hard_ATSC_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];

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

        decoder_LDPC_hard(in, &*out);

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

