#include <iostream>
#include <cmath>
#include "demap.h"

#pragma warning	(disable: 4996)

using namespace std;

void demap::init(int s, int ms, int r, float v)
{
	size = s;
	mod_size = ms;
	rate = r;
	M = log2(mod_size);
	var = v;

	aux_r = new float[mod_size]; //aux real
	aux_i = new float[mod_size]; //aux imag
	aux = new float[mod_size]; //aux dist euclidiana

	tab = new gr_complex[mod_size];

  double y_to_u_1024[32] = {0};//tabela de conversão y_to_u_1024[u] = y 1024QAM
  double u_to_y_1024[32] = {0};//tabela de conversão u_to_y_1024[y] = u 1024QAM

  double y_to_u_4096[64] = {0};//tabela de conversão y_to_u_4096[u+15] = y 4096QAM
  double u_to_y_4096[64] = {0};//tabela de conversão u_to_y_4096[y] = u 4096QAM

  int par = 0, impar = 0, num[12] = {0};

	switch (mod_size) 
  {
    case 4:
      tab[0].real() = 1.0/sqrt(2.0); tab[0].imag() = 1.0/sqrt(2.0);
      break; //QPSK
    case 16:
      switch (rate) 
      {
        case 2:
          tab[0].real() = 0.7062; tab[0].imag() = 0.7075;
          tab[1].real() = 0.7075; tab[1].imag() = 0.7062;
          tab[2].real() = 0.7072; tab[2].imag() = 0.7077;
          tab[3].real() = 0.7077; tab[3].imag() = 0.7072;
          break;
        case 3:
          tab[0].real() = 0.362000; tab[0].imag() = 0.553400;
          tab[1].real() = 0.553400; tab[1].imag() = 0.362000;
          tab[2].real() = 0.594000; tab[2].imag() = 1.100000;
          tab[3].real() = 1.100000; tab[3].imag() = 0.594000;
          break; // rate case 3
        case 4:
          tab[0].real() = 0.3412; tab[0].imag() = 0.5241;
          tab[1].real() = 0.5241; tab[1].imag() = 0.3412;
          tab[2].real() = 0.5797; tab[2].imag() = 1.1282;
          tab[3].real() = 1.1282; tab[3].imag() = 0.5797;
          break;
        case 5:
          tab[0].real() = 0.3192; tab[0].imag() = 0.5011;
          tab[1].real() = 0.5011; tab[1].imag() = 0.3192;
          tab[2].real() = 0.5575; tab[2].imag() = 1.1559;
          tab[3].real() = 1.1559; tab[3].imag() = 0.5575;
          break;
        case 6:
          tab[0].real() = 0.5115; tab[0].imag() = 1.2092;
          tab[1].real() = 1.2092; tab[1].imag() = 0.5115;
          tab[2].real() = 0.2663; tab[2].imag() = 0.4530;
          tab[3].real() = 0.4530; tab[3].imag() = 0.2663;
          break;
        case 7:
          tab[0].real() = 0.2592; tab[0].imag() = 0.4888;
          tab[1].real() = 0.4888; tab[1].imag() = 0.2592;
          tab[2].real() = 0.5072; tab[2].imag() = 1.1980;
          tab[3].real() = 1.1980; tab[3].imag() = 0.5072;
          break;
        case 8:
          tab[0].real() = 0.2535; tab[0].imag() = 0.4923;
          tab[1].real() = 0.4923; tab[1].imag() = 0.2535;
          tab[2].real() = 0.4927; tab[2].imag() = 1.2044;
          tab[3].real() = 1.2044; tab[3].imag() = 0.4927;
          break;
        case 9:
          tab[0].real() = 0.2386; tab[0].imag() = 0.5296;
          tab[1].real() = 0.5296; tab[1].imag() = 0.2386;
          tab[2].real() = 0.4882; tab[2].imag() = 1.1934;
          tab[3].real() = 1.1934; tab[3].imag() = 0.4882;
          break;
        case 10:
          tab[0].real() = 0.4487; tab[0].imag() = 1.1657;
          tab[1].real() = 1.2080; tab[1].imag() = 0.5377;
          tab[2].real() = 0.2213; tab[2].imag() = 0.4416;
          tab[3].real() = 0.6186; tab[3].imag() = 0.2544;
            break; // rate case 10
        case 11:
          tab[0].real() = 0.9342; tab[0].imag() = 0.9847;
          tab[1].real() = 0.9866; tab[1].imag() = 0.2903;
          tab[2].real() = 0.2716; tab[2].imag() = 0.9325;
          tab[3].real() = 0.2901; tab[3].imag() = 0.2695;
          break;
        case 12:
          tab[0].real() = 0.9555; tab[0].imag() = 0.9555;
          tab[1].real() = 0.9555; tab[1].imag() = 0.2949;
          tab[2].real() = 0.2949; tab[2].imag() = 0.9555;
          tab[3].real() = 0.2949; tab[3].imag() = 0.2949;
          break;
        case 13:
          tab[0].real() = 0.9517; tab[0].imag() = 0.9511;
          tab[1].real() = 0.9524; tab[1].imag() = 0.3061;
          tab[2].real() = 0.3067; tab[2].imag() = 0.9524;
          tab[3].real() = 0.3061; tab[3].imag() = 0.3067;
          break;
        default: // está é a de 11/15
          tab[0].real() = 0.9342; tab[0].imag() = 0.9847;
          tab[1].real() = 0.9866; tab[1].imag() = 0.2903;
          tab[2].real() = 0.2716; tab[2].imag() = 0.9325;
          tab[3].real() = 0.2901; tab[3].imag() = 0.2695;
          break; // rate default
        }
      break; // 16-QAM
    case 64:
      switch (rate) 
      {
        case 2:
          tab[0].real() = 0.6474; tab[0].imag() = 0.9831;
          tab[1].real() = 0.6438; tab[1].imag() = 0.9829;
          tab[2].real() = 0.6471; tab[2].imag() = 0.9767;
          tab[3].real() = 0.6444; tab[3].imag() = 0.9762;
          tab[4].real() = 0.9839; tab[4].imag() = 0.6475;
          tab[5].real() = 0.9778; tab[5].imag() = 0.6474;
          tab[6].real() = 0.9835; tab[6].imag() = 0.6434;
          tab[7].real() = 0.9777; tab[7].imag() = 0.6433;
          tab[8].real() = 0.4659; tab[8].imag() = 0.6393;
          tab[9].real() = 0.4643; tab[9].imag() = 0.6386;
          tab[10].real() = 0.4661; tab[10].imag() = 0.6353;
          tab[11].real() = 0.4639; tab[11].imag() = 0.6350;
          tab[12].real() = 0.6378; tab[12].imag() = 0.4671;
          tab[13].real() = 0.6352; tab[13].imag() = 0.4673;
          tab[14].real() = 0.6385; tab[14].imag() = 0.4656;
          tab[15].real() = 0.6353; tab[15].imag() = 0.4653;
          break;
        case 3:
          tab[0].real() = 0.547200; tab[0].imag() = 1.159100;
          tab[1].real() = 0.547300; tab[1].imag() = 1.157300;
          tab[2].real() = 0.546700; tab[2].imag() = 1.159900;
          tab[3].real() = 0.547900; tab[3].imag() = 1.158500;
          tab[4].real() = 1.157800; tab[4].imag() = 0.547800;
          tab[5].real() = 1.157600; tab[5].imag() = 0.547500;
          tab[6].real() = 1.159100; tab[6].imag() = 0.547500;
          tab[7].real() = 1.159100; tab[7].imag() = 0.547500;
          tab[8].real() = 0.316300; tab[8].imag() = 0.507200;
          tab[9].real() = 0.316300; tab[9].imag() = 0.507200;
          tab[10].real() = 0.316300; tab[10].imag() = 0.507200;
          tab[11].real() = 0.316300; tab[11].imag() = 0.507200;
          tab[12].real() = 0.508700; tab[12].imag() = 0.316300;
          tab[13].real() = 0.508700; tab[13].imag() = 0.316300;
          tab[14].real() = 0.508700; tab[14].imag() = 0.316300;
          tab[15].real() = 0.508700; tab[15].imag() = 0.316300;
          break; // rate case 3
        case 4:
          tab[0].real() = 0.5008; tab[0].imag() = 1.2136;
          tab[1].real() = 0.4994; tab[1].imag() = 1.2194;
          tab[2].real() = 0.5313; tab[2].imag() = 1.1715;
          tab[3].real() = 0.5299; tab[3].imag() = 1.1788;
          tab[4].real() = 1.2107; tab[4].imag() = 0.5037;
          tab[5].real() = 1.2209; tab[5].imag() = 0.5008;
          tab[6].real() = 1.1715; tab[6].imag() = 0.5299;
          tab[7].real() = 1.1802; tab[7].imag() = 0.5270;
          tab[8].real() = 0.2744; tab[8].imag() = 0.4762;
          tab[9].real() = 0.2729; tab[9].imag() = 0.4762;
          tab[10].real() = 0.2773; tab[10].imag() = 0.4791;
          tab[11].real() = 0.2773; tab[11].imag() = 0.4791;
          tab[12].real() = 0.4762; tab[12].imag() = 0.2729;
          tab[13].real() = 0.4762; tab[13].imag() = 0.2729;
          tab[14].real() = 0.4791; tab[14].imag() = 0.2773;
          tab[15].real() = 0.4791; tab[15].imag() = 0.2758;
          break;
        case 5:
          tab[0].real() = 1.4327; tab[0].imag() = 0.3305;
          tab[1].real() = 1.0909; tab[1].imag() = 0.2971;
          tab[2].real() = 1.2484; tab[2].imag() = 0.7803;
          tab[3].real() = 0.9762; tab[3].imag() = 0.5715;
          tab[4].real() = 0.3309; tab[4].imag() = 1.4326;
          tab[5].real() = 0.2979; tab[5].imag() = 1.0923;
          tab[6].real() = 0.7829; tab[6].imag() = 1.2477;
          tab[7].real() = 0.5739; tab[7].imag() = 0.9763;
          tab[8].real() = 0.3901; tab[8].imag() = 0.2112;
          tab[9].real() = 0.5317; tab[9].imag() = 0.2475;
          tab[10].real() = 0.3945; tab[10].imag() = 0.2289;
          tab[11].real() = 0.5236; tab[11].imag() = 0.2894;
          tab[12].real() = 0.2108; tab[12].imag() = 0.3911;
          tab[13].real() = 0.2475; tab[13].imag() = 0.5327;
          tab[14].real() = 0.2287; tab[14].imag() = 0.3955;
          tab[15].real() = 0.2898; tab[15].imag() = 0.5246;
          break;
        case 6:
          tab[0].real() = 1.4521; tab[0].imag() = 0.3005;
          tab[1].real() = 1.2657; tab[1].imag() = 0.8178;
          tab[2].real() = 1.0666; tab[2].imag() = 0.2744;
          tab[3].real() = 0.9500; tab[3].imag() = 0.5641;
          tab[4].real() = 0.3011; tab[4].imag() = 1.4529;
          tab[5].real() = 0.8202; tab[5].imag() = 1.2651;
          tab[6].real() = 0.2750; tab[6].imag() = 1.0676;
          tab[7].real() = 0.5656; tab[7].imag() = 0.9499;
          tab[8].real() = 0.3553; tab[8].imag() = 0.1948;
          tab[9].real() = 0.3569; tab[9].imag() = 0.2094;
          tab[10].real() = 0.5596; tab[10].imag() = 0.2431;
          tab[11].real() = 0.5410; tab[11].imag() = 0.3002;
          tab[12].real() = 0.1946; tab[12].imag() = 0.3566;
          tab[13].real() = 0.2094; tab[13].imag() = 0.3579;
          tab[14].real() = 0.2430; tab[14].imag() = 0.5607;
          tab[15].real() = 0.3004; tab[15].imag() = 0.5417;
          break;
        case 7:
          tab[0].real() = 0.1567; tab[0].imag() = 0.3112;
          tab[1].real() = 0.1709; tab[1].imag() = 0.3037;
          tab[2].real() = 0.2093; tab[2].imag() = 0.6562;
          tab[3].real() = 0.3315; tab[3].imag() = 0.6038;
          tab[4].real() = 0.3112; tab[4].imag() = 0.1567;
          tab[5].real() = 0.3037; tab[5].imag() = 0.1709;
          tab[6].real() = 0.6562; tab[6].imag() = 0.2093;
          tab[7].real() = 0.6038; tab[7].imag() = 0.3315;
          tab[8].real() = 0.2959; tab[8].imag() = 1.4877;
          tab[9].real() = 0.8427; tab[9].imag() = 1.2612;
          tab[10].real() = 0.2389; tab[10].imag() = 1.0228;
          tab[11].real() = 0.5559; tab[11].imag() = 0.8912;
          tab[12].real() = 1.4877; tab[12].imag() = 0.2959;
          tab[13].real() = 1.2612; tab[13].imag() = 0.8427;
          tab[14].real() = 1.0228; tab[14].imag() = 0.2389;
          tab[15].real() = 0.8912; tab[15].imag() = 0.5559;
          break;
        case 8:
          tab[0].real() = 1.4827; tab[0].imag() = 0.2920;
          tab[1].real() = 1.2563; tab[1].imag() = 0.8411;
          tab[2].real() = 1.0211; tab[2].imag() = 0.2174;
          tab[3].real() = 0.8798; tab[3].imag() = 0.5702;
          tab[4].real() = 0.2920; tab[4].imag() = 1.4827;
          tab[5].real() = 0.8410; tab[5].imag() = 1.2563;
          tab[6].real() = 0.2174; tab[6].imag() = 1.0211;
          tab[7].real() = 0.5702; tab[7].imag() = 0.8798;
          tab[8].real() = 0.3040; tab[8].imag() = 0.1475;
          tab[9].real() = 0.3028; tab[9].imag() = 0.1691;
          tab[10].real() = 0.6855; tab[10].imag() = 0.1871;
          tab[11].real() = 0.6126; tab[11].imag() = 0.3563;
          tab[12].real() = 0.1475; tab[12].imag() = 0.3040;
          tab[13].real() = 0.1691; tab[13].imag() = 0.3028;
          tab[14].real() = 0.1871; tab[14].imag() = 0.6855;
          tab[15].real() = 0.3563; tab[15].imag() = 0.6126;
          break;
        case 9:
          tab[0].real() = 0.1305; tab[0].imag() = 0.3311;
          tab[1].real() = 0.1633; tab[1].imag() = 0.3162;
          tab[2].real() = 0.1622; tab[2].imag() = 0.7113;
          tab[3].real() = 0.3905; tab[3].imag() = 0.6163;
          tab[4].real() = 0.3311; tab[4].imag() = 0.1305;
          tab[5].real() = 0.3162; tab[5].imag() = 0.1633;
          tab[6].real() = 0.7113; tab[6].imag() = 0.1622;
          tab[7].real() = 0.6163; tab[7].imag() = 0.3905;
          tab[8].real() = 0.2909; tab[8].imag() = 1.4626;
          tab[9].real() = 0.8285; tab[9].imag() = 1.2399;
          tab[10].real() = 0.2062; tab[10].imag() = 1.0367;
          tab[11].real() = 0.5872; tab[11].imag() = 0.8789;
          tab[12].real() = 1.4626; tab[12].imag() = 0.2909;
          tab[13].real() = 1.2399; tab[13].imag() = 0.8285;
          tab[14].real() = 1.0367; tab[14].imag() = 0.2062;
          tab[15].real() = 0.8789; tab[15].imag() = 0.5872;
          break;
        case 10:
          tab[0].real() = 0.1177; tab[0].imag() = 0.1729;
          tab[1].real() = 0.1601; tab[1].imag() = 0.3212;
          tab[2].real() = 0.1352; tab[2].imag() = 0.7279;
          tab[3].real() = 0.3246; tab[3].imag() = 0.6148;
          tab[4].real() = 0.4192; tab[4].imag() = 0.1179;
          tab[5].real() = 0.4033; tab[5].imag() = 0.2421;
          tab[6].real() = 0.7524; tab[6].imag() = 0.1581;
          tab[7].real() = 0.5996; tab[7].imag() = 0.4330;
          tab[8].real() = 0.2902; tab[8].imag() = 1.4611;
          tab[9].real() = 0.8180; tab[9].imag() = 1.2291;
          tab[10].real() = 0.2036; tab[10].imag() = 1.0575;
          tab[11].real() = 0.5641; tab[11].imag() = 0.8965;
          tab[12].real() = 1.4453; tab[12].imag() = 0.2907;
          tab[13].real() = 1.2157; tab[13].imag() = 0.8186;
          tab[14].real() = 1.0447; tab[14].imag() = 0.2242;
          tab[15].real() = 0.8497; tab[15].imag() = 0.6176;
          break; // rate case 10
        case 11:
          tab[0].real() = 1.4443; tab[0].imag() = 0.2683;
          tab[1].real() = 0.7471; tab[1].imag() = 1.2243;
          tab[2].real() = 1.1749; tab[2].imag() = 0.7734;
          tab[3].real() = 0.7138; tab[3].imag() = 0.8201;
          tab[4].real() = 0.1638; tab[4].imag() = 1.0769;
          tab[5].real() = 0.2927; tab[5].imag() = 1.4217;
          tab[6].real() = 0.1462; tab[6].imag() = 0.7457;
          tab[7].real() = 0.4134; tab[7].imag() = 0.7408;
          tab[8].real() = 1.0203; tab[8].imag() = 0.1517;
          tab[9].real() = 0.6653; tab[9].imag() = 0.1357;
          tab[10].real() = 0.9639; tab[10].imag() = 0.4465;
          tab[11].real() = 0.6746; tab[11].imag() = 0.4339;
          tab[12].real() = 0.1271; tab[12].imag() = 0.1428;
          tab[13].real() = 0.3782; tab[13].imag() = 0.1406;
          tab[14].real() = 0.1311; tab[14].imag() = 0.4288;
          tab[15].real() = 0.3919; tab[15].imag() = 0.4276;
          break;
        case 12:
          tab[0].real() = 1.4480; tab[0].imag() = 0.2403;
          tab[1].real() = 0.6406; tab[1].imag() = 1.1995;
          tab[2].real() = 1.0952; tab[2].imag() = 0.9115;
          tab[3].real() = 0.6868; tab[3].imag() = 0.8108;
          tab[4].real() = 1.0500; tab[4].imag() = 0.1642;
          tab[5].real() = 0.7170; tab[5].imag() = 0.1473;
          tab[6].real() = 1.0519; tab[6].imag() = 0.5188;
          tab[7].real() = 0.7146; tab[7].imag() = 0.4532;
          tab[8].real() = 0.1677; tab[8].imag() = 1.0405;
          tab[9].real() = 0.2402; tab[9].imag() = 1.4087;
          tab[10].real() = 0.1369; tab[10].imag() = 0.7073;
          tab[11].real() = 0.4044; tab[11].imag() = 0.7057;
          tab[12].real() = 0.1374; tab[12].imag() = 0.1295;
          tab[13].real() = 0.4185; tab[13].imag() = 0.1357;
          tab[14].real() = 0.1325; tab[14].imag() = 0.3998;
          tab[15].real() = 0.4122; tab[15].imag() = 0.4120;
          break;
        case 13:
          tab[0].real() = 1.4319; tab[0].imag() = 0.2300;
          tab[1].real() = 1.0762; tab[1].imag() = 0.9250;
          tab[2].real() = 0.6290; tab[2].imag() = 1.1820;
          tab[3].real() = 0.6851; tab[3].imag() = 0.8072;
          tab[4].real() = 1.0443; tab[4].imag() = 0.1688;
          tab[5].real() = 1.0635; tab[5].imag() = 0.5305;
          tab[6].real() = 0.7220; tab[6].imag() = 0.1540;
          tab[7].real() = 0.7151; tab[7].imag() = 0.4711;
          tab[8].real() = 0.2099; tab[8].imag() = 1.4205;
          tab[9].real() = 0.1190; tab[9].imag() = 0.6677;
          tab[10].real() = 0.2031; tab[10].imag() = 1.0551;
          tab[11].real() = 0.3722; tab[11].imag() = 0.7548;
          tab[12].real() = 0.1438; tab[12].imag() = 0.1287;
          tab[13].real() = 0.1432; tab[13].imag() = 0.3903;
          tab[14].real() = 0.4298; tab[14].imag() = 0.1384;
          tab[15].real() = 0.4215; tab[15].imag() = 0.4279;
          break;
        default: // está a de 11/15
          tab[0].real() = 1.4443; tab[0].imag() = 0.2683;
          tab[1].real() = 0.7471; tab[1].imag() = 1.2243;
          tab[2].real() = 1.1749; tab[2].imag() = 0.7734;
          tab[3].real() = 0.7138; tab[3].imag() = 0.8201;
          tab[4].real() = 0.1638; tab[4].imag() = 1.0769;
          tab[5].real() = 0.2927; tab[5].imag() = 1.4217;
          tab[6].real() = 0.1462; tab[6].imag() = 0.7457;
          tab[7].real() = 0.4134; tab[7].imag() = 0.7408;
          tab[8].real() = 1.0203; tab[8].imag() = 0.1517;
          tab[9].real() = 0.6653; tab[9].imag() = 0.1357;
          tab[10].real() = 0.9639; tab[10].imag() = 0.4465;
          tab[11].real() = 0.6746; tab[11].imag() = 0.4339;
          tab[12].real() = 0.1271; tab[12].imag() = 0.1428;
          tab[13].real() = 0.3782; tab[13].imag() = 0.1406;
          tab[14].real() = 0.1311; tab[14].imag() = 0.4288;
          tab[15].real() = 0.3919; tab[15].imag() = 0.4276;
          break; // rate default
      }
      break; // 64-QAM
    case 256:
      switch (rate) 
      {
        case 2:
          tab[0].real() = 0.5553; tab[0].imag() = 1.1262;
          tab[1].real() = 0.5673; tab[1].imag() = 1.1336;
          tab[2].real() = 0.5593; tab[2].imag() = 1.1204;
          tab[3].real() = 0.5636; tab[3].imag() = 1.1321;
          tab[4].real() = 0.5525; tab[4].imag() = 1.1249;
          tab[5].real() = 0.5637; tab[5].imag() = 1.1320;
          tab[6].real() = 0.5598; tab[6].imag() = 1.1181;
          tab[7].real() = 0.5659; tab[7].imag() = 1.1274;
          tab[8].real() = 0.5579; tab[8].imag() = 1.1381;
          tab[9].real() = 0.5617; tab[9].imag() = 1.1471;
          tab[10].real() = 0.5593; tab[10].imag() = 1.1346;
          tab[11].real() = 0.5672; tab[11].imag() = 1.1430;
          tab[12].real() = 0.5533; tab[12].imag() = 1.1355;
          tab[13].real() = 0.5632; tab[13].imag() = 1.1421;
          tab[14].real() = 0.5567; tab[14].imag() = 1.1325;
          tab[15].real() = 0.5641; tab[15].imag() = 1.1363;
          tab[16].real() = 1.1309; tab[16].imag() = 0.5597;
          tab[17].real() = 1.1405; tab[17].imag() = 0.5660;
          tab[18].real() = 1.1348; tab[18].imag() = 0.5588;
          tab[19].real() = 1.1491; tab[19].imag() = 0.5638;
          tab[20].real() = 1.1245; tab[20].imag() = 0.5615;
          tab[21].real() = 1.1333; tab[21].imag() = 0.5627;
          tab[22].real() = 1.1284; tab[22].imag() = 0.5578;
          tab[23].real() = 1.1436; tab[23].imag() = 0.5636;
          tab[24].real() = 1.1196; tab[24].imag() = 0.5620;
          tab[25].real() = 1.1347; tab[25].imag() = 0.5665;
          tab[26].real() = 1.1379; tab[26].imag() = 0.5611;
          tab[27].real() = 1.1440; tab[27].imag() = 0.5638;
          tab[28].real() = 1.1221; tab[28].imag() = 0.5594;
          tab[29].real() = 1.1318; tab[29].imag() = 0.5686;
          tab[30].real() = 1.1302; tab[30].imag() = 0.5619;
          tab[31].real() = 1.1386; tab[31].imag() = 0.5662;
          tab[32].real() = 0.3394; tab[32].imag() = 0.5381;
          tab[33].real() = 0.3397; tab[33].imag() = 0.5360;
          tab[34].real() = 0.3387; tab[34].imag() = 0.5324;
          tab[35].real() = 0.3400; tab[35].imag() = 0.5335;
          tab[36].real() = 0.3374; tab[36].imag() = 0.5306;
          tab[37].real() = 0.3405; tab[37].imag() = 0.5343;
          tab[38].real() = 0.3379; tab[38].imag() = 0.5324;
          tab[39].real() = 0.3400; tab[39].imag() = 0.5317;
          tab[40].real() = 0.3397; tab[40].imag() = 0.5370;
          tab[41].real() = 0.3400; tab[41].imag() = 0.5383;
          tab[42].real() = 0.3381; tab[42].imag() = 0.5347;
          tab[43].real() = 0.3382; tab[43].imag() = 0.5347;
          tab[44].real() = 0.3379; tab[44].imag() = 0.5342;
          tab[45].real() = 0.3389; tab[45].imag() = 0.5332;
          tab[46].real() = 0.3402; tab[46].imag() = 0.5347;
          tab[47].real() = 0.3384; tab[47].imag() = 0.5340;
          tab[48].real() = 0.5350; tab[48].imag() = 0.3394;
          tab[49].real() = 0.5363; tab[49].imag() = 0.3397;
          tab[50].real() = 0.5342; tab[50].imag() = 0.3389;
          tab[51].real() = 0.5384; tab[51].imag() = 0.3380;
          tab[52].real() = 0.5329; tab[52].imag() = 0.3363;
          tab[53].real() = 0.5330; tab[53].imag() = 0.3387;
          tab[54].real() = 0.5311; tab[54].imag() = 0.3389;
          tab[55].real() = 0.5332; tab[55].imag() = 0.3380;
          tab[56].real() = 0.5313; tab[56].imag() = 0.3397;
          tab[57].real() = 0.5324; tab[57].imag() = 0.3400;
          tab[58].real() = 0.5339; tab[58].imag() = 0.3402;
          tab[59].real() = 0.5360; tab[59].imag() = 0.3405;
          tab[60].real() = 0.5285; tab[60].imag() = 0.3397;
          tab[61].real() = 0.5317; tab[61].imag() = 0.3379;
          tab[62].real() = 0.5319; tab[62].imag() = 0.3381;
          tab[63].real() = 0.5327; tab[63].imag() = 0.3395;
          break;
        case 3:
          tab[0].real() = 0.522900; tab[0].imag() = 1.181000;
          tab[1].real() = 0.538400; tab[1].imag() = 1.162500;
          tab[2].real() = 0.514800; tab[2].imag() = 1.194300;
          tab[3].real() = 0.528800; tab[3].imag() = 1.175100;
          tab[4].real() = 0.498500; tab[4].imag() = 1.220200;
          tab[5].real() = 0.511100; tab[5].imag() = 1.197300;
          tab[6].real() = 0.488900; tab[6].imag() = 1.235700;
          tab[7].real() = 0.504500; tab[7].imag() = 1.211300;
          tab[8].real() = 0.522200; tab[8].imag() = 1.181700;
          tab[9].real() = 0.537000; tab[9].imag() = 1.164000;
          tab[10].real() = 0.513300; tab[10].imag() = 1.195000;
          tab[11].real() = 0.530300; tab[11].imag() = 1.175100;
          tab[12].real() = 0.497100; tab[12].imag() = 1.221600;
          tab[13].real() = 0.512600; tab[13].imag() = 1.199500;
          tab[14].real() = 0.488200; tab[14].imag() = 1.237100;
          tab[15].real() = 0.504500; tab[15].imag() = 1.212800;
          tab[16].real() = 1.179500; tab[16].imag() = 0.525100;
          tab[17].real() = 1.162500; tab[17].imag() = 0.538400;
          tab[18].real() = 1.191400; tab[18].imag() = 0.513300;
          tab[19].real() = 1.174400; tab[19].imag() = 0.529600;
          tab[20].real() = 1.220900; tab[20].imag() = 0.499300;
          tab[21].real() = 1.200200; tab[21].imag() = 0.514800;
          tab[22].real() = 1.234200; tab[22].imag() = 0.488200;
          tab[23].real() = 1.214200; tab[23].imag() = 0.505200;
          tab[24].real() = 1.180300; tab[24].imag() = 0.522900;
          tab[25].real() = 1.164000; tab[25].imag() = 0.539900;
          tab[26].real() = 1.192100; tab[26].imag() = 0.513300;
          tab[27].real() = 1.175800; tab[27].imag() = 0.530300;
          tab[28].real() = 1.220900; tab[28].imag() = 0.497100;
          tab[29].real() = 1.202400; tab[29].imag() = 0.514800;
          tab[30].real() = 1.234900; tab[30].imag() = 0.488900;
          tab[31].real() = 1.215000; tab[31].imag() = 0.504500;
          tab[32].real() = 0.274000; tab[32].imag() = 0.477100;
          tab[33].real() = 0.276200; tab[33].imag() = 0.480100;
          tab[34].real() = 0.273300; tab[34].imag() = 0.475700;
          tab[35].real() = 0.274800; tab[35].imag() = 0.477900;
          tab[36].real() = 0.270300; tab[36].imag() = 0.474200;
          tab[37].real() = 0.272500; tab[37].imag() = 0.476400;
          tab[38].real() = 0.269600; tab[38].imag() = 0.472700;
          tab[39].real() = 0.271800; tab[39].imag() = 0.474900;
          tab[40].real() = 0.274000; tab[40].imag() = 0.477900;
          tab[41].real() = 0.275500; tab[41].imag() = 0.479300;
          tab[42].real() = 0.272500; tab[42].imag() = 0.475700;
          tab[43].real() = 0.274800; tab[43].imag() = 0.477900;
          tab[44].real() = 0.271100; tab[44].imag() = 0.473400;
          tab[45].real() = 0.272500; tab[45].imag() = 0.476400;
          tab[46].real() = 0.269600; tab[46].imag() = 0.472000;
          tab[47].real() = 0.271100; tab[47].imag() = 0.474200;
          tab[48].real() = 0.477100; tab[48].imag() = 0.274000;
          tab[49].real() = 0.478600; tab[49].imag() = 0.276200;
          tab[50].real() = 0.476400; tab[50].imag() = 0.272500;
          tab[51].real() = 0.477100; tab[51].imag() = 0.274800;
          tab[52].real() = 0.473400; tab[52].imag() = 0.270300;
          tab[53].real() = 0.475700; tab[53].imag() = 0.272500;
          tab[54].real() = 0.473400; tab[54].imag() = 0.269600;
          tab[55].real() = 0.474200; tab[55].imag() = 0.271100;
          tab[56].real() = 0.477100; tab[56].imag() = 0.274000;
          tab[57].real() = 0.477900; tab[57].imag() = 0.276200;
          tab[58].real() = 0.476400; tab[58].imag() = 0.272500;
          tab[59].real() = 0.477100; tab[59].imag() = 0.274800;
          tab[60].real() = 0.474200; tab[60].imag() = 0.270300;
          tab[61].real() = 0.474900; tab[61].imag() = 0.272500;
          tab[62].real() = 0.473400; tab[62].imag() = 0.269600;
          tab[63].real() = 0.474900; tab[63].imag() = 0.271100;
          break; // rate case 3
        case 4:
          tab[0].real() = 0.2975; tab[0].imag() = 1.0564;
          tab[1].real() = 0.5862; tab[1].imag() = 0.9617;
          tab[2].real() = 0.2909; tab[2].imag() = 1.0696;
          tab[3].real() = 0.5796; tab[3].imag() = 0.9689;
          tab[4].real() = 0.2953; tab[4].imag() = 1.3357;
          tab[5].real() = 0.7488; tab[5].imag() = 1.2365;
          tab[6].real() = 0.3004; tab[6].imag() = 1.5114;
          tab[7].real() = 0.8151; tab[7].imag() = 1.3816;
          tab[8].real() = 0.3004; tab[8].imag() = 1.0535;
          tab[9].real() = 0.5847; tab[9].imag() = 0.9631;
          tab[10].real() = 0.2931; tab[10].imag() = 1.0659;
          tab[11].real() = 0.5825; tab[11].imag() = 0.9668;
          tab[12].real() = 0.2953; tab[12].imag() = 1.3189;
          tab[13].real() = 0.7466; tab[13].imag() = 1.2168;
          tab[14].real() = 0.2960; tab[14].imag() = 1.4654;
          tab[15].real() = 0.8297; tab[15].imag() = 1.3539;
          tab[16].real() = 1.0637; tab[16].imag() = 0.2960;
          tab[17].real() = 0.9617; tab[17].imag() = 0.5811;
          tab[18].real() = 1.0732; tab[18].imag() = 0.2931;
          tab[19].real() = 0.9682; tab[19].imag() = 0.5818;
          tab[20].real() = 1.3619; tab[20].imag() = 0.2997;
          tab[21].real() = 1.2249; tab[21].imag() = 0.7546;
          tab[22].real() = 1.5427; tab[22].imag() = 0.3106;
          tab[23].real() = 1.3969; tab[23].imag() = 0.8523;
          tab[24].real() = 1.0615; tab[24].imag() = 0.2945;
          tab[25].real() = 0.9631; tab[25].imag() = 0.5818;
          tab[26].real() = 1.0710; tab[26].imag() = 0.2924;
          tab[27].real() = 0.9675; tab[27].imag() = 0.5825;
          tab[28].real() = 1.3255; tab[28].imag() = 0.2975;
          tab[29].real() = 1.1979; tab[29].imag() = 0.7495;
          tab[30].real() = 1.4560; tab[30].imag() = 0.3040;
          tab[31].real() = 1.3269; tab[31].imag() = 0.8414;
          tab[32].real() = 0.2493; tab[32].imag() = 0.5585;
          tab[33].real() = 0.2960; tab[33].imag() = 0.5344;
          tab[34].real() = 0.2450; tab[34].imag() = 0.5417;
          tab[35].real() = 0.2873; tab[35].imag() = 0.5191;
          tab[36].real() = 0.2049; tab[36].imag() = 0.3922;
          tab[37].real() = 0.2173; tab[37].imag() = 0.3806;
          tab[38].real() = 0.1990; tab[38].imag() = 0.3755;
          tab[39].real() = 0.2107; tab[39].imag() = 0.3645;
          tab[40].real() = 0.2493; tab[40].imag() = 0.5599;
          tab[41].real() = 0.2975; tab[41].imag() = 0.5351;
          tab[42].real() = 0.2450; tab[42].imag() = 0.5439;
          tab[43].real() = 0.2887; tab[43].imag() = 0.5213;
          tab[44].real() = 0.2056; tab[44].imag() = 0.3937;
          tab[45].real() = 0.2187; tab[45].imag() = 0.3820;
          tab[46].real() = 0.1998; tab[46].imag() = 0.3762;
          tab[47].real() = 0.2122; tab[47].imag() = 0.3667;
          tab[48].real() = 0.5607; tab[48].imag() = 0.2486;
          tab[49].real() = 0.5381; tab[49].imag() = 0.2960;
          tab[50].real() = 0.5439; tab[50].imag() = 0.2442;
          tab[51].real() = 0.5220; tab[51].imag() = 0.2865;
          tab[52].real() = 0.3908; tab[52].imag() = 0.2049;
          tab[53].real() = 0.3813; tab[53].imag() = 0.2173;
          tab[54].real() = 0.3740; tab[54].imag() = 0.1998;
          tab[55].real() = 0.3653; tab[55].imag() = 0.2100;
          tab[56].real() = 0.5643; tab[56].imag() = 0.2486;
          tab[57].real() = 0.5410; tab[57].imag() = 0.2967;
          tab[58].real() = 0.5475; tab[58].imag() = 0.2435;
          tab[59].real() = 0.5257; tab[59].imag() = 0.2880;
          tab[60].real() = 0.3937; tab[60].imag() = 0.2049;
          tab[61].real() = 0.3850; tab[61].imag() = 0.2187;
          tab[62].real() = 0.3762; tab[62].imag() = 0.1998;
          tab[63].real() = 0.3689; tab[63].imag() = 0.2114;
          break;
        case 5:
          tab[0].real() = 0.1524; tab[0].imag() = 0.3087;
          tab[1].real() = 0.1525; tab[1].imag() = 0.3087;
          tab[2].real() = 0.1513; tab[2].imag() = 0.3043;
          tab[3].real() = 0.1513; tab[3].imag() = 0.3043;
          tab[4].real() = 0.1682; tab[4].imag() = 0.3004;
          tab[5].real() = 0.1682; tab[5].imag() = 0.3005;
          tab[6].real() = 0.1663; tab[6].imag() = 0.2964;
          tab[7].real() = 0.1663; tab[7].imag() = 0.2964;
          tab[8].real() = 0.1964; tab[8].imag() = 0.6584;
          tab[9].real() = 0.1965; tab[9].imag() = 0.6583;
          tab[10].real() = 0.1967; tab[10].imag() = 0.6652;
          tab[11].real() = 0.1968; tab[11].imag() = 0.6652;
          tab[12].real() = 0.3371; tab[12].imag() = 0.5987;
          tab[13].real() = 0.3370; tab[13].imag() = 0.5987;
          tab[14].real() = 0.3414; tab[14].imag() = 0.6039;
          tab[15].real() = 0.3413; tab[15].imag() = 0.6039;
          tab[16].real() = 0.3087; tab[16].imag() = 0.1524;
          tab[17].real() = 0.3087; tab[17].imag() = 0.1525;
          tab[18].real() = 0.3043; tab[18].imag() = 0.1513;
          tab[19].real() = 0.3043; tab[19].imag() = 0.1513;
          tab[20].real() = 0.3004; tab[20].imag() = 0.1682;
          tab[21].real() = 0.3005; tab[21].imag() = 0.1682;
          tab[22].real() = 0.2964; tab[22].imag() = 0.1663;
          tab[23].real() = 0.2964; tab[23].imag() = 0.1663;
          tab[24].real() = 0.6584; tab[24].imag() = 0.1964;
          tab[25].real() = 0.6583; tab[25].imag() = 0.1965;
          tab[26].real() = 0.6652; tab[26].imag() = 0.1967;
          tab[27].real() = 0.6652; tab[27].imag() = 0.1968;
          tab[28].real() = 0.5987; tab[28].imag() = 0.3371;
          tab[29].real() = 0.5987; tab[29].imag() = 0.3370;
          tab[30].real() = 0.6039; tab[30].imag() = 0.3414;
          tab[31].real() = 0.6039; tab[31].imag() = 0.3413;
          tab[32].real() = 0.3183; tab[32].imag() = 1.5992;
          tab[33].real() = 0.3186; tab[33].imag() = 1.5991;
          tab[34].real() = 0.2756; tab[34].imag() = 1.3848;
          tab[35].real() = 0.2759; tab[35].imag() = 1.3847;
          tab[36].real() = 0.9060; tab[36].imag() = 1.3557;
          tab[37].real() = 0.9058; tab[37].imag() = 1.3559;
          tab[38].real() = 0.7846; tab[38].imag() = 1.1739;
          tab[39].real() = 0.7843; tab[39].imag() = 1.1741;
          tab[40].real() = 0.2257; tab[40].imag() = 0.9956;
          tab[41].real() = 0.2259; tab[41].imag() = 0.9956;
          tab[42].real() = 0.2276; tab[42].imag() = 1.0326;
          tab[43].real() = 0.2278; tab[43].imag() = 1.0326;
          tab[44].real() = 0.5446; tab[44].imag() = 0.8635;
          tab[45].real() = 0.5445; tab[45].imag() = 0.8636;
          tab[46].real() = 0.5694; tab[46].imag() = 0.8910;
          tab[47].real() = 0.5692; tab[47].imag() = 0.8911;
          tab[48].real() = 1.5992; tab[48].imag() = 0.3183;
          tab[49].real() = 1.5991; tab[49].imag() = 0.3186;
          tab[50].real() = 1.3848; tab[50].imag() = 0.2756;
          tab[51].real() = 1.3847; tab[51].imag() = 0.2759;
          tab[52].real() = 1.3557; tab[52].imag() = 0.9060;
          tab[53].real() = 1.3559; tab[53].imag() = 0.9058;
          tab[54].real() = 1.1739; tab[54].imag() = 0.7846;
          tab[55].real() = 1.1741; tab[55].imag() = 0.7843;
          tab[56].real() = 0.9956; tab[56].imag() = 0.2257;
          tab[57].real() = 0.9956; tab[57].imag() = 0.2259;
          tab[58].real() = 1.0326; tab[58].imag() = 0.2276;
          tab[59].real() = 1.0326; tab[59].imag() = 0.2278;
          tab[60].real() = 0.8635; tab[60].imag() = 0.5446;
          tab[61].real() = 0.8636; tab[61].imag() = 0.5445;
          tab[62].real() = 0.8910; tab[62].imag() = 0.5694;
          tab[63].real() = 0.8911; tab[63].imag() = 0.5692;
          break;
        case 6:
          tab[0].real() = 0.1430; tab[0].imag() = 0.3078;
          tab[1].real() = 0.1430; tab[1].imag() = 0.3077;
          tab[2].real() = 0.1413; tab[2].imag() = 0.3003;
          tab[3].real() = 0.1414; tab[3].imag() = 0.3002;
          tab[4].real() = 0.1637; tab[4].imag() = 0.2973;
          tab[5].real() = 0.1636; tab[5].imag() = 0.2973;
          tab[6].real() = 0.1604; tab[6].imag() = 0.2905;
          tab[7].real() = 0.1603; tab[7].imag() = 0.2905;
          tab[8].real() = 0.1768; tab[8].imag() = 0.6686;
          tab[9].real() = 0.1793; tab[9].imag() = 0.6679;
          tab[10].real() = 0.1769; tab[10].imag() = 0.6707;
          tab[11].real() = 0.1793; tab[11].imag() = 0.6700;
          tab[12].real() = 0.3506; tab[12].imag() = 0.5961;
          tab[13].real() = 0.3484; tab[13].imag() = 0.5974;
          tab[14].real() = 0.3523; tab[14].imag() = 0.5975;
          tab[15].real() = 0.3501; tab[15].imag() = 0.5987;
          tab[16].real() = 0.3078; tab[16].imag() = 0.1430;
          tab[17].real() = 0.3077; tab[17].imag() = 0.1430;
          tab[18].real() = 0.3003; tab[18].imag() = 0.1413;
          tab[19].real() = 0.3002; tab[19].imag() = 0.1414;
          tab[20].real() = 0.2973; tab[20].imag() = 0.1637;
          tab[21].real() = 0.2973; tab[21].imag() = 0.1636;
          tab[22].real() = 0.2905; tab[22].imag() = 0.1604;
          tab[23].real() = 0.2905; tab[23].imag() = 0.1603;
          tab[24].real() = 0.6686; tab[24].imag() = 0.1768;
          tab[25].real() = 0.6679; tab[25].imag() = 0.1793;
          tab[26].real() = 0.6707; tab[26].imag() = 0.1769;
          tab[27].real() = 0.6700; tab[27].imag() = 0.1793;
          tab[28].real() = 0.5961; tab[28].imag() = 0.3506;
          tab[29].real() = 0.5974; tab[29].imag() = 0.3484;
          tab[30].real() = 0.5975; tab[30].imag() = 0.3523;
          tab[31].real() = 0.5987; tab[31].imag() = 0.3501;
          tab[32].real() = 0.2071; tab[32].imag() = 1.6690;
          tab[33].real() = 0.4482; tab[33].imag() = 1.6210;
          tab[34].real() = 0.2080; tab[34].imag() = 1.3641;
          tab[35].real() = 0.3307; tab[35].imag() = 1.3397;
          tab[36].real() = 1.0341; tab[36].imag() = 1.3264;
          tab[37].real() = 0.8297; tab[37].imag() = 1.4630;
          tab[38].real() = 0.8178; tab[38].imag() = 1.1114;
          tab[39].real() = 0.7138; tab[39].imag() = 1.1809;
          tab[40].real() = 0.1957; tab[40].imag() = 0.9674;
          tab[41].real() = 0.2170; tab[41].imag() = 0.9629;
          tab[42].real() = 0.1977; tab[42].imag() = 1.0341;
          tab[43].real() = 0.2288; tab[43].imag() = 1.0277;
          tab[44].real() = 0.5458; tab[44].imag() = 0.8224;
          tab[45].real() = 0.5276; tab[45].imag() = 0.8342;
          tab[46].real() = 0.5916; tab[46].imag() = 0.8709;
          tab[47].real() = 0.5651; tab[47].imag() = 0.8883;
          tab[48].real() = 1.6690; tab[48].imag() = 0.2071;
          tab[49].real() = 1.6210; tab[49].imag() = 0.4482;
          tab[50].real() = 1.3641; tab[50].imag() = 0.2080;
          tab[51].real() = 1.3397; tab[51].imag() = 0.3307;
          tab[52].real() = 1.3264; tab[52].imag() = 1.0341;
          tab[53].real() = 1.4630; tab[53].imag() = 0.8297;
          tab[54].real() = 1.1114; tab[54].imag() = 0.8178;
          tab[55].real() = 1.1809; tab[55].imag() = 0.7138;
          tab[56].real() = 0.9674; tab[56].imag() = 0.1957;
          tab[57].real() = 0.9629; tab[57].imag() = 0.2170;
          tab[58].real() = 1.0341; tab[58].imag() = 0.1977;
          tab[59].real() = 1.0277; tab[59].imag() = 0.2288;
          tab[60].real() = 0.8224; tab[60].imag() = 0.5458;
          tab[61].real() = 0.8342; tab[61].imag() = 0.5276;
          tab[62].real() = 0.8709; tab[62].imag() = 0.5916;
          tab[63].real() = 0.8883; tab[63].imag() = 0.5651;
          break;
        case 7:
          tab[0].real() = 0.1170; tab[0].imag() = 0.3003;
          tab[1].real() = 0.1171; tab[1].imag() = 0.3003;
          tab[2].real() = 0.1204; tab[2].imag() = 0.3233;
          tab[3].real() = 0.1204; tab[3].imag() = 0.3233;
          tab[4].real() = 0.1454; tab[4].imag() = 0.2877;
          tab[5].real() = 0.1453; tab[5].imag() = 0.2877;
          tab[6].real() = 0.1566; tab[6].imag() = 0.3074;
          tab[7].real() = 0.1565; tab[7].imag() = 0.3074;
          tab[8].real() = 0.1427; tab[8].imag() = 0.6856;
          tab[9].real() = 0.1562; tab[9].imag() = 0.6826;
          tab[10].real() = 0.1422; tab[10].imag() = 0.6584;
          tab[11].real() = 0.1529; tab[11].imag() = 0.6560;
          tab[12].real() = 0.3840; tab[12].imag() = 0.5856;
          tab[13].real() = 0.3723; tab[13].imag() = 0.5931;
          tab[14].real() = 0.3651; tab[14].imag() = 0.5660;
          tab[15].real() = 0.3559; tab[15].imag() = 0.5718;
          tab[16].real() = 0.3003; tab[16].imag() = 0.1170;
          tab[17].real() = 0.3003; tab[17].imag() = 0.1171;
          tab[18].real() = 0.3233; tab[18].imag() = 0.1204;
          tab[19].real() = 0.3233; tab[19].imag() = 0.1204;
          tab[20].real() = 0.2877; tab[20].imag() = 0.1454;
          tab[21].real() = 0.2877; tab[21].imag() = 0.1453;
          tab[22].real() = 0.3074; tab[22].imag() = 0.1566;
          tab[23].real() = 0.3074; tab[23].imag() = 0.1565;
          tab[24].real() = 0.6856; tab[24].imag() = 0.1427;
          tab[25].real() = 0.6826; tab[25].imag() = 0.1562;
          tab[26].real() = 0.6584; tab[26].imag() = 0.1422;
          tab[27].real() = 0.6560; tab[27].imag() = 0.1529;
          tab[28].real() = 0.5856; tab[28].imag() = 0.3840;
          tab[29].real() = 0.5931; tab[29].imag() = 0.3723;
          tab[30].real() = 0.5660; tab[30].imag() = 0.3651;
          tab[31].real() = 0.5718; tab[31].imag() = 0.3559;
          tab[32].real() = 0.1683; tab[32].imag() = 1.7041;
          tab[33].real() = 0.4972; tab[33].imag() = 1.6386;
          tab[34].real() = 0.1495; tab[34].imag() = 1.3560;
          tab[35].real() = 0.3814; tab[35].imag() = 1.3099;
          tab[36].real() = 1.0862; tab[36].imag() = 1.3238;
          tab[37].real() = 0.8074; tab[37].imag() = 1.5101;
          tab[38].real() = 0.8534; tab[38].imag() = 1.0644;
          tab[39].real() = 0.6568; tab[39].imag() = 1.1958;
          tab[40].real() = 0.1552; tab[40].imag() = 0.9481;
          tab[41].real() = 0.2200; tab[41].imag() = 0.9352;
          tab[42].real() = 0.1577; tab[42].imag() = 1.0449;
          tab[43].real() = 0.2548; tab[43].imag() = 1.0255;
          tab[44].real() = 0.5609; tab[44].imag() = 0.7800;
          tab[45].real() = 0.5060; tab[45].imag() = 0.8167;
          tab[46].real() = 0.6276; tab[46].imag() = 0.8501;
          tab[47].real() = 0.5452; tab[47].imag() = 0.9052;
          tab[48].real() = 1.7041; tab[48].imag() = 0.1683;
          tab[49].real() = 1.6386; tab[49].imag() = 0.4972;
          tab[50].real() = 1.3560; tab[50].imag() = 0.1495;
          tab[51].real() = 1.3099; tab[51].imag() = 0.3814;
          tab[52].real() = 1.3238; tab[52].imag() = 1.0862;
          tab[53].real() = 1.5101; tab[53].imag() = 0.8074;
          tab[54].real() = 1.0644; tab[54].imag() = 0.8534;
          tab[55].real() = 1.1958; tab[55].imag() = 0.6568;
          tab[56].real() = 0.9481; tab[56].imag() = 0.1552;
          tab[57].real() = 0.9352; tab[57].imag() = 0.2200;
          tab[58].real() = 1.0449; tab[58].imag() = 0.1577;
          tab[59].real() = 1.0255; tab[59].imag() = 0.2548;
          tab[60].real() = 0.7800; tab[60].imag() = 0.5609;
          tab[61].real() = 0.8167; tab[61].imag() = 0.5060;
          tab[62].real() = 0.8501; tab[62].imag() = 0.6276;
          tab[63].real() = 0.9052; tab[63].imag() = 0.5452;
          break;
        case 8:
          tab[0].real() = 0.0995; tab[0].imag() = 0.2435;
          tab[1].real() = 0.0996; tab[1].imag() = 0.2434;
          tab[2].real() = 0.1169; tab[2].imag() = 0.3886;
          tab[3].real() = 0.1179; tab[3].imag() = 0.3883;
          tab[4].real() = 0.1192; tab[4].imag() = 0.2345;
          tab[5].real() = 0.1192; tab[5].imag() = 0.2345;
          tab[6].real() = 0.1953; tab[6].imag() = 0.3558;
          tab[7].real() = 0.1944; tab[7].imag() = 0.3563;
          tab[8].real() = 0.1293; tab[8].imag() = 0.7217;
          tab[9].real() = 0.1616; tab[9].imag() = 0.7151;
          tab[10].real() = 0.1287; tab[10].imag() = 0.6355;
          tab[11].real() = 0.1456; tab[11].imag() = 0.6318;
          tab[12].real() = 0.4191; tab[12].imag() = 0.6016;
          tab[13].real() = 0.3916; tab[13].imag() = 0.6198;
          tab[14].real() = 0.3585; tab[14].imag() = 0.5403;
          tab[15].real() = 0.3439; tab[15].imag() = 0.5497;
          tab[16].real() = 0.2435; tab[16].imag() = 0.0995;
          tab[17].real() = 0.2434; tab[17].imag() = 0.0996;
          tab[18].real() = 0.3886; tab[18].imag() = 0.1169;
          tab[19].real() = 0.3883; tab[19].imag() = 0.1179;
          tab[20].real() = 0.2345; tab[20].imag() = 0.1192;
          tab[21].real() = 0.2345; tab[21].imag() = 0.1192;
          tab[22].real() = 0.3558; tab[22].imag() = 0.1953;
          tab[23].real() = 0.3563; tab[23].imag() = 0.1944;
          tab[24].real() = 0.7217; tab[24].imag() = 0.1293;
          tab[25].real() = 0.7151; tab[25].imag() = 0.1616;
          tab[26].real() = 0.6355; tab[26].imag() = 0.1287;
          tab[27].real() = 0.6318; tab[27].imag() = 0.1456;
          tab[28].real() = 0.6016; tab[28].imag() = 0.4191;
          tab[29].real() = 0.6198; tab[29].imag() = 0.3916;
          tab[30].real() = 0.5403; tab[30].imag() = 0.3585;
          tab[31].real() = 0.5497; tab[31].imag() = 0.3439;
          tab[32].real() = 0.1665; tab[32].imag() = 1.6859;
          tab[33].real() = 0.4919; tab[33].imag() = 1.6211;
          tab[34].real() = 0.1360; tab[34].imag() = 1.3498;
          tab[35].real() = 0.3914; tab[35].imag() = 1.2989;
          tab[36].real() = 1.0746; tab[36].imag() = 1.3096;
          tab[37].real() = 0.7987; tab[37].imag() = 1.4940;
          tab[38].real() = 0.8585; tab[38].imag() = 1.0504;
          tab[39].real() = 0.6419; tab[39].imag() = 1.1951;
          tab[40].real() = 0.1334; tab[40].imag() = 0.9483;
          tab[41].real() = 0.2402; tab[41].imag() = 0.9271;
          tab[42].real() = 0.1323; tab[42].imag() = 1.0786;
          tab[43].real() = 0.2910; tab[43].imag() = 1.0470;
          tab[44].real() = 0.5764; tab[44].imag() = 0.7648;
          tab[45].real() = 0.4860; tab[45].imag() = 0.8252;
          tab[46].real() = 0.6693; tab[46].imag() = 0.8561;
          tab[47].real() = 0.5348; tab[47].imag() = 0.9459;
          tab[48].real() = 1.6859; tab[48].imag() = 0.1665;
          tab[49].real() = 1.6211; tab[49].imag() = 0.4919;
          tab[50].real() = 1.3498; tab[50].imag() = 0.1360;
          tab[51].real() = 1.2989; tab[51].imag() = 0.3914;
          tab[52].real() = 1.3096; tab[52].imag() = 1.0746;
          tab[53].real() = 1.4940; tab[53].imag() = 0.7987;
          tab[54].real() = 1.0504; tab[54].imag() = 0.8585;
          tab[55].real() = 1.1951; tab[55].imag() = 0.6419;
          tab[56].real() = 0.9483; tab[56].imag() = 0.1334;
          tab[57].real() = 0.9271; tab[57].imag() = 0.2402;
          tab[58].real() = 1.0786; tab[58].imag() = 0.1323;
          tab[59].real() = 1.0470; tab[59].imag() = 0.2910;
          tab[60].real() = 0.7648; tab[60].imag() = 0.5764;
          tab[61].real() = 0.8252; tab[61].imag() = 0.4860;
          tab[62].real() = 0.8561; tab[62].imag() = 0.6693;
          tab[63].real() = 0.9459; tab[63].imag() = 0.5348;
          break;
        case 9:
          tab[0].real() = 0.0899; tab[0].imag() = 0.1337;
          tab[1].real() = 0.0910; tab[1].imag() = 0.1377;
          tab[2].real() = 0.0873; tab[2].imag() = 0.3862;
          tab[3].real() = 0.0883; tab[3].imag() = 0.3873;
          tab[4].real() = 0.1115; tab[4].imag() = 0.1442;
          tab[5].real() = 0.1135; tab[5].imag() = 0.1472;
          tab[6].real() = 0.2067; tab[6].imag() = 0.3591;
          tab[7].real() = 0.1975; tab[7].imag() = 0.3621;
          tab[8].real() = 0.1048; tab[8].imag() = 0.7533;
          tab[9].real() = 0.1770; tab[9].imag() = 0.7412;
          tab[10].real() = 0.1022; tab[10].imag() = 0.5904;
          tab[11].real() = 0.1191; tab[11].imag() = 0.5890;
          tab[12].real() = 0.4264; tab[12].imag() = 0.6230;
          tab[13].real() = 0.3650; tab[13].imag() = 0.6689;
          tab[14].real() = 0.3254; tab[14].imag() = 0.5153;
          tab[15].real() = 0.2959; tab[15].imag() = 0.5302;
          tab[16].real() = 0.3256; tab[16].imag() = 0.0768;
          tab[17].real() = 0.3266; tab[17].imag() = 0.0870;
          tab[18].real() = 0.4721; tab[18].imag() = 0.0994;
          tab[19].real() = 0.4721; tab[19].imag() = 0.1206;
          tab[20].real() = 0.2927; tab[20].imag() = 0.1267;
          tab[21].real() = 0.2947; tab[21].imag() = 0.1296;
          tab[22].real() = 0.3823; tab[22].imag() = 0.2592;
          tab[23].real() = 0.3944; tab[23].imag() = 0.2521;
          tab[24].real() = 0.7755; tab[24].imag() = 0.1118;
          tab[25].real() = 0.7513; tab[25].imag() = 0.2154;
          tab[26].real() = 0.6591; tab[26].imag() = 0.1033;
          tab[27].real() = 0.6446; tab[27].imag() = 0.1737;
          tab[28].real() = 0.5906; tab[28].imag() = 0.4930;
          tab[29].real() = 0.6538; tab[29].imag() = 0.4155;
          tab[30].real() = 0.4981; tab[30].imag() = 0.3921;
          tab[31].real() = 0.5373; tab[31].imag() = 0.3586;
          tab[32].real() = 0.1630; tab[32].imag() = 1.6621;
          tab[33].real() = 0.4720; tab[33].imag() = 1.5898;
          tab[34].real() = 0.1268; tab[34].imag() = 1.3488;
          tab[35].real() = 0.3752; tab[35].imag() = 1.2961;
          tab[36].real() = 1.0398; tab[36].imag() = 1.2991;
          tab[37].real() = 0.7733; tab[37].imag() = 1.4772;
          tab[38].real() = 0.8380; tab[38].imag() = 1.0552;
          tab[39].real() = 0.6242; tab[39].imag() = 1.2081;
          tab[40].real() = 0.1103; tab[40].imag() = 0.9397;
          tab[41].real() = 0.2415; tab[41].imag() = 0.9155;
          tab[42].real() = 0.1118; tab[42].imag() = 1.1163;
          tab[43].real() = 0.3079; tab[43].imag() = 1.0866;
          tab[44].real() = 0.5647; tab[44].imag() = 0.7638;
          tab[45].real() = 0.4385; tab[45].imag() = 0.8433;
          tab[46].real() = 0.6846; tab[46].imag() = 0.8841;
          tab[47].real() = 0.5165; tab[47].imag() = 1.0034;
          tab[48].real() = 1.6489; tab[48].imag() = 0.1630;
          tab[49].real() = 1.5848; tab[49].imag() = 0.4983;
          tab[50].real() = 1.3437; tab[50].imag() = 0.1389;
          tab[51].real() = 1.2850; tab[51].imag() = 0.4025;
          tab[52].real() = 1.2728; tab[52].imag() = 1.0661;
          tab[53].real() = 1.4509; tab[53].imag() = 0.7925;
          tab[54].real() = 1.0249; tab[54].imag() = 0.8794;
          tab[55].real() = 1.1758; tab[55].imag() = 0.6545;
          tab[56].real() = 0.9629; tab[56].imag() = 0.1113;
          tab[57].real() = 0.9226; tab[57].imag() = 0.2849;
          tab[58].real() = 1.1062; tab[58].imag() = 0.1118;
          tab[59].real() = 1.0674; tab[59].imag() = 0.3393;
          tab[60].real() = 0.7234; tab[60].imag() = 0.6223;
          tab[61].real() = 0.8211; tab[61].imag() = 0.4860;
          tab[62].real() = 0.8457; tab[62].imag() = 0.7260;
          tab[63].real() = 0.9640; tab[63].imag() = 0.5518;
          break;
        case 10:
          tab[0].real() = 0.0754; tab[0].imag() = 0.2310; tab[1].real() = 0.0768; tab[1].imag() = 0.2305; 
          tab[2].real() = 0.0924; tab[2].imag() = 0.4136; tab[3].real() = 0.1043; tab[3].imag() = 0.4125;
          tab[4].real() = 0.0829; tab[4].imag() = 0.1135; tab[5].real() = 0.0836; tab[5].imag() = 0.1149; 
          tab[6].real() = 0.2682; tab[6].imag() = 0.3856; tab[7].real() = 0.2531; tab[7].imag() = 0.3906;
          tab[8].real() = 0.0836; tab[8].imag() = 0.7817; tab[9].real() = 0.2052; tab[9].imag() = 0.7608; 
          tab[10].real() = 0.0838; tab[10].imag() = 0.6034; tab[11].real() = 0.1394; tab[11].imag() = 0.5961;
          tab[12].real() = 0.4861; tab[12].imag() = 0.6331; tab[13].real() = 0.3661; tab[13].imag() = 0.7034; 
          tab[14].real() = 0.3732; tab[14].imag() = 0.5159; tab[15].real() = 0.3095; tab[15].imag() = 0.5511;
          tab[16].real() = 0.3030; tab[16].imag() = 0.0811; tab[17].real() = 0.3017; tab[17].imag() = 0.0853; 
          tab[18].real() = 0.4758; tab[18].imag() = 0.0932; tab[19].real() = 0.4676; tab[19].imag() = 0.1242;
          tab[20].real() = 0.2425; tab[20].imag() = 0.1081; tab[21].real() = 0.2447; tab[21].imag() = 0.1115; 
          tab[22].real() = 0.3837; tab[22].imag() = 0.2813; tab[23].real() = 0.3959; tab[23].imag() = 0.2642;
          tab[24].real() = 0.7929; tab[24].imag() = 0.0859; tab[25].real() = 0.7652; tab[25].imag() = 0.2324; 
          tab[26].real() = 0.6365; tab[26].imag() = 0.0872; tab[27].real() = 0.6207; tab[27].imag() = 0.1757;
          tab[28].real() = 0.6149; tab[28].imag() = 0.5145; tab[29].real() = 0.6987; tab[29].imag() = 0.3934; 
          tab[30].real() = 0.5063; tab[30].imag() = 0.4029; tab[31].real() = 0.5526; tab[31].imag() = 0.3356;
          tab[32].real() = 0.1598; tab[32].imag() = 1.6262; tab[33].real() = 0.4733; tab[33].imag() = 1.5637; 
          tab[34].real() = 0.1307; tab[34].imag() = 1.3502; tab[35].real() = 0.3877; tab[35].imag() = 1.2983;
          tab[36].real() = 1.0328; tab[36].imag() = 1.2617; tab[37].real() = 0.7675; tab[37].imag() = 1.4398; 
          tab[38].real() = 0.8496; tab[38].imag() = 1.0508; tab[39].real() = 0.6297; tab[39].imag() = 1.1967;
          tab[40].real() = 0.0910; tab[40].imag() = 0.9531; tab[41].real() = 0.2649; tab[41].imag() = 0.9198; 
          tab[42].real() = 0.1080; tab[42].imag() = 1.1340; tab[43].real() = 0.3214; tab[43].imag() = 1.0926;
          tab[44].real() = 0.5941; tab[44].imag() = 0.7527; tab[45].real() = 0.4371; tab[45].imag() = 0.8528; 
          tab[46].real() = 0.7093; tab[46].imag() = 0.8880; tab[47].real() = 0.5235; tab[47].imag() = 1.0090;
          tab[48].real() = 1.6180; tab[48].imag() = 0.1602; tab[49].real() = 1.5540; tab[49].imag() = 0.4734; 
          tab[50].real() = 1.3411; tab[50].imag() = 0.1336; tab[51].real() = 1.2883; tab[51].imag() = 0.3955;
          tab[52].real() = 1.2561; tab[52].imag() = 1.0337; tab[53].real() = 1.4311; tab[53].imag() = 0.7676; 
          tab[54].real() = 1.0362; tab[54].imag() = 0.8626; tab[55].real() = 1.1845; tab[55].imag() = 0.6419;
          tab[56].real() = 0.9546; tab[56].imag() = 0.0957; tab[57].real() = 0.9163; tab[57].imag() = 0.2834; 
          tab[58].real() = 1.1282; tab[58].imag() = 0.1128; tab[59].real() = 1.0838; tab[59].imag() = 0.3340;
          tab[60].real() = 0.7329; tab[60].imag() = 0.6204; tab[61].real() = 0.8428; tab[61].imag() = 0.4615; 
          tab[62].real() = 0.8680; tab[62].imag() = 0.7295; tab[63].real() = 0.9959; tab[63].imag() = 0.5426;
          break; // rate case 10
        case 11:
          tab[0].real() = 0.0593; tab[0].imag() = 0.2193;
          tab[1].real() = 0.0690; tab[1].imag() = 0.3047;
          tab[2].real() = 0.0663; tab[2].imag() = 0.4879;
          tab[3].real() = 0.1151; tab[3].imag() = 0.4474;
          tab[4].real() = 0.1689; tab[4].imag() = 0.2163;
          tab[5].real() = 0.1971; tab[5].imag() = 0.2525;
          tab[6].real() = 0.3096; tab[6].imag() = 0.3796;
          tab[7].real() = 0.2489; tab[7].imag() = 0.3933;
          tab[8].real() = 0.0790; tab[8].imag() = 0.7970;
          tab[9].real() = 0.2340; tab[9].imag() = 0.7710;
          tab[10].real() = 0.0723; tab[10].imag() = 0.6395;
          tab[11].real() = 0.1896; tab[11].imag() = 0.6163;
          tab[12].real() = 0.5090; tab[12].imag() = 0.6272;
          tab[13].real() = 0.3787; tab[13].imag() = 0.7126;
          tab[14].real() = 0.4079; tab[14].imag() = 0.5049;
          tab[15].real() = 0.3088; tab[15].imag() = 0.5677;
          tab[16].real() = 0.0675; tab[16].imag() = 0.0626;
          tab[17].real() = 0.3475; tab[17].imag() = 0.0595;
          tab[18].real() = 0.5482; tab[18].imag() = 0.0626;
          tab[19].real() = 0.4784; tab[19].imag() = 0.1124;
          tab[20].real() = 0.1674; tab[20].imag() = 0.0751;
          tab[21].real() = 0.2856; tab[21].imag() = 0.1132;
          tab[22].real() = 0.4134; tab[22].imag() = 0.3028;
          tab[23].real() = 0.4235; tab[23].imag() = 0.2289;
          tab[24].real() = 0.8258; tab[24].imag() = 0.0840;
          tab[25].real() = 0.7936; tab[25].imag() = 0.2483;
          tab[26].real() = 0.6788; tab[26].imag() = 0.0783;
          tab[27].real() = 0.6501; tab[27].imag() = 0.2025;
          tab[28].real() = 0.6246; tab[28].imag() = 0.5211;
          tab[29].real() = 0.7241; tab[29].imag() = 0.3961;
          tab[30].real() = 0.5144; tab[30].imag() = 0.4089;
          tab[31].real() = 0.5918; tab[31].imag() = 0.3146;
          tab[32].real() = 0.1631; tab[32].imag() = 1.5801;
          tab[33].real() = 0.4806; tab[33].imag() = 1.5133;
          tab[34].real() = 0.1260; tab[34].imag() = 1.3365;
          tab[35].real() = 0.3750; tab[35].imag() = 1.2897;
          tab[36].real() = 1.0324; tab[36].imag() = 1.2029;
          tab[37].real() = 0.7737; tab[37].imag() = 1.3837;
          tab[38].real() = 0.8350; tab[38].imag() = 1.0529;
          tab[39].real() = 0.6147; tab[39].imag() = 1.1949;
          tab[40].real() = 0.0929; tab[40].imag() = 0.9596;
          tab[41].real() = 0.2768; tab[41].imag() = 0.9260;
          tab[42].real() = 0.1095; tab[42].imag() = 1.1349;
          tab[43].real() = 0.3250; tab[43].imag() = 1.0941;
          tab[44].real() = 0.6086; tab[44].imag() = 0.7556;
          tab[45].real() = 0.4514; tab[45].imag() = 0.8566;
          tab[46].real() = 0.7161; tab[46].imag() = 0.8933;
          tab[47].real() = 0.5294; tab[47].imag() = 1.0121;
          tab[48].real() = 1.5809; tab[48].imag() = 0.1471;
          tab[49].real() = 1.5253; tab[49].imag() = 0.4385;
          tab[50].real() = 1.3380; tab[50].imag() = 0.1363;
          tab[51].real() = 1.2837; tab[51].imag() = 0.4026;
          tab[52].real() = 1.2476; tab[52].imag() = 0.9785;
          tab[53].real() = 1.4137; tab[53].imag() = 0.7196;
          tab[54].real() = 1.0246; tab[54].imag() = 0.8681;
          tab[55].real() = 1.1771; tab[55].imag() = 0.6494;
          tab[56].real() = 0.9782; tab[56].imag() = 0.0985;
          tab[57].real() = 0.9383; tab[57].imag() = 0.2922;
          tab[58].real() = 1.1455; tab[58].imag() = 0.1158;
          tab[59].real() = 1.0972; tab[59].imag() = 0.3418;
          tab[60].real() = 0.7446; tab[60].imag() = 0.6273;
          tab[61].real() = 0.8573; tab[61].imag() = 0.4721;
          tab[62].real() = 0.8767; tab[62].imag() = 0.7377;
          tab[63].real() = 1.0059; tab[63].imag() = 0.5518;
          break;
        case 12:
          tab[0].real() = 1.1980; tab[0].imag() = 1.1541;
          tab[1].real() = 0.9192; tab[1].imag() = 1.2082;
          tab[2].real() = 1.2778; tab[2].imag() = 0.8523;
          tab[3].real() = 1.0390; tab[3].imag() = 0.9253;
          tab[4].real() = 0.6057; tab[4].imag() = 1.2200;
          tab[5].real() = 0.7371; tab[5].imag() = 1.4217;
          tab[6].real() = 0.6678; tab[6].imag() = 1.0021;
          tab[7].real() = 0.8412; tab[7].imag() = 0.9448;
          tab[8].real() = 1.2128; tab[8].imag() = 0.5373;
          tab[9].real() = 1.0048; tab[9].imag() = 0.5165;
          tab[10].real() = 1.4321; tab[10].imag() = 0.6343;
          tab[11].real() = 1.0245; tab[11].imag() = 0.7152;
          tab[12].real() = 0.6384; tab[12].imag() = 0.6073;
          tab[13].real() = 0.8175; tab[13].imag() = 0.5684;
          tab[14].real() = 0.6568; tab[14].imag() = 0.7801;
          tab[15].real() = 0.8311; tab[15].imag() = 0.7459;
          tab[16].real() = 0.1349; tab[16].imag() = 1.4742;
          tab[17].real() = 0.1105; tab[17].imag() = 1.2309;
          tab[18].real() = 0.0634; tab[18].imag() = 0.9796;
          tab[19].real() = 0.1891; tab[19].imag() = 1.0198;
          tab[20].real() = 0.4142; tab[20].imag() = 1.4461;
          tab[21].real() = 0.3323; tab[21].imag() = 1.2279;
          tab[22].real() = 0.4998; tab[22].imag() = 0.9827;
          tab[23].real() = 0.3467; tab[23].imag() = 1.0202;
          tab[24].real() = 0.0680; tab[24].imag() = 0.6501;
          tab[25].real() = 0.2016; tab[25].imag() = 0.6464;
          tab[26].real() = 0.0719; tab[26].imag() = 0.8075;
          tab[27].real() = 0.2088; tab[27].imag() = 0.8146;
          tab[28].real() = 0.4809; tab[28].imag() = 0.6296;
          tab[29].real() = 0.3374; tab[29].imag() = 0.6412;
          tab[30].real() = 0.4955; tab[30].imag() = 0.8008;
          tab[31].real() = 0.3431; tab[31].imag() = 0.8141;
          tab[32].real() = 1.2731; tab[32].imag() = 0.1108;
          tab[33].real() = 1.0794; tab[33].imag() = 0.0977;
          tab[34].real() = 1.5126; tab[34].imag() = 0.1256;
          tab[35].real() = 0.9029; tab[35].imag() = 0.0853;
          tab[36].real() = 0.5429; tab[36].imag() = 0.0694;
          tab[37].real() = 0.6795; tab[37].imag() = 0.0559;
          tab[38].real() = 0.5628; tab[38].imag() = 0.1945;
          tab[39].real() = 0.7326; tab[39].imag() = 0.1410;
          tab[40].real() = 1.2283; tab[40].imag() = 0.3217;
          tab[41].real() = 1.0269; tab[41].imag() = 0.3261;
          tab[42].real() = 1.4663; tab[42].imag() = 0.3716;
          tab[43].real() = 0.9085; tab[43].imag() = 0.2470;
          tab[44].real() = 0.6160; tab[44].imag() = 0.4549;
          tab[45].real() = 0.7818; tab[45].imag() = 0.4247;
          tab[46].real() = 0.5938; tab[46].imag() = 0.3170;
          tab[47].real() = 0.7600; tab[47].imag() = 0.2850;
          tab[48].real() = 0.0595; tab[48].imag() = 0.0707;
          tab[49].real() = 0.1722; tab[49].imag() = 0.0706;
          tab[50].real() = 0.0599; tab[50].imag() = 0.2119;
          tab[51].real() = 0.1748; tab[51].imag() = 0.2114;
          tab[52].real() = 0.4134; tab[52].imag() = 0.0701;
          tab[53].real() = 0.2935; tab[53].imag() = 0.0705;
          tab[54].real() = 0.4231; tab[54].imag() = 0.2066;
          tab[55].real() = 0.2979; tab[55].imag() = 0.2100;
          tab[56].real() = 0.0638; tab[56].imag() = 0.5002;
          tab[57].real() = 0.1905; tab[57].imag() = 0.4966;
          tab[58].real() = 0.0612; tab[58].imag() = 0.3552;
          tab[59].real() = 0.1810; tab[59].imag() = 0.3533;
          tab[60].real() = 0.4630; tab[60].imag() = 0.4764;
          tab[61].real() = 0.3231; tab[61].imag() = 0.4895;
          tab[62].real() = 0.4416; tab[62].imag() = 0.3397;
          tab[63].real() = 0.3083; tab[63].imag() = 0.3490;
          break;
        case 13:
          tab[0].real() = 1.2412; tab[0].imag() = 1.0688;
          tab[1].real() = 1.2668; tab[1].imag() = 0.8034;
          tab[2].real() = 0.9860; tab[2].imag() = 1.1758;
          tab[3].real() = 1.0365; tab[3].imag() = 0.9065;
          tab[4].real() = 1.2111; tab[4].imag() = 0.5135;
          tab[5].real() = 1.4187; tab[5].imag() = 0.6066;
          tab[6].real() = 1.0103; tab[6].imag() = 0.4879;
          tab[7].real() = 1.0380; tab[7].imag() = 0.6906;
          tab[8].real() = 0.6963; tab[8].imag() = 1.3442;
          tab[9].real() = 0.7089; tab[9].imag() = 1.1122;
          tab[10].real() = 0.1256; tab[10].imag() = 1.4745;
          tab[11].real() = 0.8331; tab[11].imag() = 0.9455;
          tab[12].real() = 0.6615; tab[12].imag() = 0.6012;
          tab[13].real() = 0.6894; tab[13].imag() = 0.7594;
          tab[14].real() = 0.8373; tab[14].imag() = 0.5633;
          tab[15].real() = 0.8552; tab[15].imag() = 0.7410;
          tab[16].real() = 1.2666; tab[16].imag() = 0.1027;
          tab[17].real() = 1.4915; tab[17].imag() = 0.1198;
          tab[18].real() = 1.0766; tab[18].imag() = 0.0945;
          tab[19].real() = 0.9007; tab[19].imag() = 0.0848;
          tab[20].real() = 1.2454; tab[20].imag() = 0.3064;
          tab[21].real() = 1.4646; tab[21].imag() = 0.3600;
          tab[22].real() = 1.0570; tab[22].imag() = 0.2995;
          tab[23].real() = 0.9140; tab[23].imag() = 0.2530;
          tab[24].real() = 0.5461; tab[24].imag() = 0.0679;
          tab[25].real() = 0.5681; tab[25].imag() = 0.1947;
          tab[26].real() = 0.6874; tab[26].imag() = 0.0537;
          tab[27].real() = 0.7375; tab[27].imag() = 0.1492;
          tab[28].real() = 0.6290; tab[28].imag() = 0.4553;
          tab[29].real() = 0.6007; tab[29].imag() = 0.3177;
          tab[30].real() = 0.7885; tab[30].imag() = 0.4231;
          tab[31].real() = 0.7627; tab[31].imag() = 0.2849;
          tab[32].real() = 0.0816; tab[32].imag() = 1.1632;
          tab[33].real() = 0.0830; tab[33].imag() = 0.9813;
          tab[34].real() = 0.2528; tab[34].imag() = 1.2315;
          tab[35].real() = 0.2502; tab[35].imag() = 1.0100;
          tab[36].real() = 0.0732; tab[36].imag() = 0.6827;
          tab[37].real() = 0.0811; tab[37].imag() = 0.8293;
          tab[38].real() = 0.2159; tab[38].imag() = 0.6673;
          tab[39].real() = 0.2359; tab[39].imag() = 0.8283;
          tab[40].real() = 0.4302; tab[40].imag() = 1.4458;
          tab[41].real() = 0.5852; tab[41].imag() = 0.9680;
          tab[42].real() = 0.4528; tab[42].imag() = 1.2074;
          tab[43].real() = 0.4167; tab[43].imag() = 1.0099;
          tab[44].real() = 0.5035; tab[44].imag() = 0.6307;
          tab[45].real() = 0.5359; tab[45].imag() = 0.7954;
          tab[46].real() = 0.3580; tab[46].imag() = 0.6532;
          tab[47].real() = 0.3841; tab[47].imag() = 0.8207;
          tab[48].real() = 0.0576; tab[48].imag() = 0.0745;
          tab[49].real() = 0.0581; tab[49].imag() = 0.2241;
          tab[50].real() = 0.1720; tab[50].imag() = 0.0742;
          tab[51].real() = 0.1753; tab[51].imag() = 0.2222;
          tab[52].real() = 0.0652; tab[52].imag() = 0.5269;
          tab[53].real() = 0.0611; tab[53].imag() = 0.3767;
          tab[54].real() = 0.1972; tab[54].imag() = 0.5178;
          tab[55].real() = 0.1836; tab[55].imag() = 0.3695;
          tab[56].real() = 0.4145; tab[56].imag() = 0.0709;
          tab[57].real() = 0.4266; tab[57].imag() = 0.2100;
          tab[58].real() = 0.2912; tab[58].imag() = 0.0730;
          tab[59].real() = 0.2982; tab[59].imag() = 0.2177;
          tab[60].real() = 0.4766; tab[60].imag() = 0.4821;
          tab[61].real() = 0.4497; tab[61].imag() = 0.3448;
          tab[62].real() = 0.3334; tab[62].imag() = 0.5025;
          tab[63].real() = 0.3125; tab[63].imag() = 0.3601;
          break;
        default: // está a de 11/15
          tab[0].real() = 0.0593; tab[0].imag() = 0.2193;
          tab[1].real() = 0.0690; tab[1].imag() = 0.3047;
          tab[2].real() = 0.0663; tab[2].imag() = 0.4879;
          tab[3].real() = 0.1151; tab[3].imag() = 0.4474;
          tab[4].real() = 0.1689; tab[4].imag() = 0.2163;
          tab[5].real() = 0.1971; tab[5].imag() = 0.2525;
          tab[6].real() = 0.3096; tab[6].imag() = 0.3796;
          tab[7].real() = 0.2489; tab[7].imag() = 0.3933;
          tab[8].real() = 0.0790; tab[8].imag() = 0.7970;
          tab[9].real() = 0.2340; tab[9].imag() = 0.7710;
          tab[10].real() = 0.0723; tab[10].imag() = 0.6395;
          tab[11].real() = 0.1896; tab[11].imag() = 0.6163;
          tab[12].real() = 0.5090; tab[12].imag() = 0.6272;
          tab[13].real() = 0.3787; tab[13].imag() = 0.7126;
          tab[14].real() = 0.4079; tab[14].imag() = 0.5049;
          tab[15].real() = 0.3088; tab[15].imag() = 0.5677;
          tab[16].real() = 0.0675; tab[16].imag() = 0.0626;
          tab[17].real() = 0.3475; tab[17].imag() = 0.0595;
          tab[18].real() = 0.5482; tab[18].imag() = 0.0626;
          tab[19].real() = 0.4784; tab[19].imag() = 0.1124;
          tab[20].real() = 0.1674; tab[20].imag() = 0.0751;
          tab[21].real() = 0.2856; tab[21].imag() = 0.1132;
          tab[22].real() = 0.4134; tab[22].imag() = 0.3028;
          tab[23].real() = 0.4235; tab[23].imag() = 0.2289;
          tab[24].real() = 0.8258; tab[24].imag() = 0.0840;
          tab[25].real() = 0.7936; tab[25].imag() = 0.2483;
          tab[26].real() = 0.6788; tab[26].imag() = 0.0783;
          tab[27].real() = 0.6501; tab[27].imag() = 0.2025;
          tab[28].real() = 0.6246; tab[28].imag() = 0.5211;
          tab[29].real() = 0.7241; tab[29].imag() = 0.3961;
          tab[30].real() = 0.5144; tab[30].imag() = 0.4089;
          tab[31].real() = 0.5918; tab[31].imag() = 0.3146;
          tab[32].real() = 0.1631; tab[32].imag() = 1.5801;
          tab[33].real() = 0.4806; tab[33].imag() = 1.5133;
          tab[34].real() = 0.1260; tab[34].imag() = 1.3365;
          tab[35].real() = 0.3750; tab[35].imag() = 1.2897;
          tab[36].real() = 1.0324; tab[36].imag() = 1.2029;
          tab[37].real() = 0.7737; tab[37].imag() = 1.3837;
          tab[38].real() = 0.8350; tab[38].imag() = 1.0529;
          tab[39].real() = 0.6147; tab[39].imag() = 1.1949;
          tab[40].real() = 0.0929; tab[40].imag() = 0.9596;
          tab[41].real() = 0.2768; tab[41].imag() = 0.9260;
          tab[42].real() = 0.1095; tab[42].imag() = 1.1349;
          tab[43].real() = 0.3250; tab[43].imag() = 1.0941;
          tab[44].real() = 0.6086; tab[44].imag() = 0.7556;
          tab[45].real() = 0.4514; tab[45].imag() = 0.8566;
          tab[46].real() = 0.7161; tab[46].imag() = 0.8933;
          tab[47].real() = 0.5294; tab[47].imag() = 1.0121;
          tab[48].real() = 1.5809; tab[48].imag() = 0.1471;
          tab[49].real() = 1.5253; tab[49].imag() = 0.4385;
          tab[50].real() = 1.3380; tab[50].imag() = 0.1363;
          tab[51].real() = 1.2837; tab[51].imag() = 0.4026;
          tab[52].real() = 1.2476; tab[52].imag() = 0.9785;
          tab[53].real() = 1.4137; tab[53].imag() = 0.7196;
          tab[54].real() = 1.0246; tab[54].imag() = 0.8681;
          tab[55].real() = 1.1771; tab[55].imag() = 0.6494;
          tab[56].real() = 0.9782; tab[56].imag() = 0.0985;
          tab[57].real() = 0.9383; tab[57].imag() = 0.2922;
          tab[58].real() = 1.1455; tab[58].imag() = 0.1158;
          tab[59].real() = 1.0972; tab[59].imag() = 0.3418;
          tab[60].real() = 0.7446; tab[60].imag() = 0.6273;
          tab[61].real() = 0.8573; tab[61].imag() = 0.4721;
          tab[62].real() = 0.8767; tab[62].imag() = 0.7377;
          tab[63].real() = 1.0059; tab[63].imag() = 0.5518;
          break; // rate default
      }
      break; //256-QAM
    case 1024:
     
      for(int i = 0; i < 32; i++)//1024 QAM
      {
        if(i < 16)
          y_to_u_1024[i] += 1;
        if((i >= 8)&&(i < 24))
          y_to_u_1024[i] += 2;
        if((i%16 > 3)&&(i%16 < 12))
          y_to_u_1024[i] += 4;
        if((i%8 > 1)&&(i%8 < 6))
          y_to_u_1024[i] += 8;
        if((i%4 > 0)&&(i%4 < 3))
          y_to_u_1024[i] += 16;

        u_to_y_1024[(int)y_to_u_1024[i]] = i;
        //printf("%i - %.0lf\n", i, y_to_u_1024[i]);
      }

      for(int i = 0; i < 32; i++)
      {
        //printf("%i - %.0lf\n", i, u_to_y_1024[i]);
      }

      for(int i = 0; i < 1024; i++)
      {
        num[9] = i%2;
        num[8] = (i/2)%2;
        num[7] = (i/4)%2;
        num[6] = (i/8)%2;
        num[5] = (i/16)%2;
        num[4] = (i/32)%2;
        num[3] = (i/64)%2;
        num[2] = (i/128)%2;
        num[1] = (i/256)%2;
        num[0] = i/512;

        //if(i == 156)
        //  printf("%i%i%i%i%i%i%i%i%i%i", num[0],num[1],num[2],num[3],num[4],num[5],num[6],num[7],num[8],num[9]);

        par = (int)(num[0]*1+num[2]*2+num[4]*4+num[6]*8+num[8]*16);
        impar = (int)(num[1]*1+num[3]*2+num[5]*4+num[7]*8+num[9]*16);

        tab[i].real() = u_to_y_1024[impar];
        tab[i].imag() = u_to_y_1024[par];

        //printf("i = %i, real = %i, imag = %i\n", i, impar, par);
      }

      float u[4096];

      switch (rate)
      { 
        case 2:
          u[0] = -0.9349;
          u[1] = -0.9394;
          u[2] = -0.9492;
          u[3] = -0.9448;
          u[4] = -0.9471;
          u[5] = -0.9514;
          u[6] = -0.9418;
          u[7] = -0.9369;
          u[8] = -0.3322;
          u[9] = -0.3322;
          u[10] = -0.3328;
          u[11] = -0.3327;
          u[12] = -0.3321;
          u[13] = -0.3322;
          u[14] = -0.3321;
          u[15] = -0.3317;
          u[16] = 0.3317;
          u[17] = 0.3321;
          u[18] = 0.3322;
          u[19] = 0.3321;
          u[20] = 0.3327;
          u[21] = 0.3328;
          u[22] = 0.3322;
          u[23] = 0.3322;
          u[24] = 0.9369;
          u[25] = 0.9418;
          u[26] = 0.9514;
          u[27] = 0.9471;
          u[28] = 0.9448;
          u[29] = 0.9492;
          u[30] = 0.9394;
          u[31] = 0.9349;
          break;
        case 3:
          u[0] = -1.4299;
          u[1] = -0.9459;
          u[2] = -0.8336;
          u[3] = -0.9463;
          u[4] = -0.8348;
          u[5] = -0.781;
          u[6] = -0.8348;
          u[7] = -0.9486;
          u[8] = -0.2558;
          u[9] = -0.2749;
          u[10] = -0.2949;
          u[11] = -0.2748;
          u[12] = -0.2558;
          u[13] = -0.2749;
          u[14] = -0.2556;
          u[15] = -0.2382;
          u[16] = 0.2382;
          u[17] = 0.2556;
          u[18] = 0.2749;
          u[19] = 0.2558;
          u[20] = 0.2748;
          u[21] = 0.2949;
          u[22] = 0.2749;
          u[23] = 0.2558;
          u[24] = 0.9486;
          u[25] = 0.8348;
          u[26] = 0.781;
          u[27] = 0.8348;
          u[28] = 0.9463;
          u[29] = 0.8336;
          u[30] = 0.9459;
          u[31] = 1.4299;
          break;
      case 4:
          u[0] = -1.4761;
          u[1] = -1.1332;
          u[2] = -0.9665;
          u[3] = -0.9667;
          u[4] = -0.7326;
          u[5] = -0.75;
          u[6] = -0.7362;
          u[7] = -0.7167;
          u[8] = -0.2854;
          u[9] = -0.289;
          u[10] = -0.3096;
          u[11] = -0.3056;
          u[12] = -0.205;
          u[13] = -0.207;
          u[14] = -0.194;
          u[15] = -0.1924;
          u[16] = 0.1924;
          u[17] = 0.194;
          u[18] = 0.207;
          u[19] = 0.205;
          u[20] = 0.3056;
          u[21] = 0.3096;
          u[22] = 0.289;
          u[23] = 0.2854;
          u[24] = 0.7167;
          u[25] = 0.7362;
          u[26] = 0.75;
          u[27] = 0.7326;
          u[28] = 0.9667;
          u[29] = 0.9665;
          u[30] = 1.1332;
          u[31] = 1.4761;
          break;
        case 5:
          u[0] = -1.4981;
          u[1] = -1.2021;
          u[2] = -1.0185;
          u[3] = -0.9753;
          u[4] = -0.6903;
          u[5] = -0.6953;
          u[6] = -0.6301;
          u[7] = -0.6295;
          u[8] = -0.3581;
          u[9] = -0.3569;
          u[10] = -0.3504;
          u[11] = -0.3516;
          u[12] = -0.1271;
          u[13] = -0.1269;
          u[14] = -0.1311;
          u[15] = -0.1313;
          u[16] = 0.1313;
          u[17] = 0.1311;
          u[18] = 0.1269;
          u[19] = 0.1271;
          u[20] = 0.3516;
          u[21] = 0.3504;
          u[22] = 0.3569;
          u[23] = 0.3581;
          u[24] = 0.6295;
          u[25] = 0.6301;
          u[26] = 0.6953;
          u[27] = 0.6903;
          u[28] = 0.9753;
          u[29] = 1.0185;
          u[30] = 1.2021;
          u[31] = 1.4981;
          break;
        case 6:
          u[0] = -1.5031;
          u[1] = -1.2286;
          u[2] = -1.0048;
          u[3] = -0.9418;
          u[4] = -0.7196;
          u[5] = -0.7113;
          u[6] = -0.6072;
          u[7] = -0.6097;
          u[8] = -0.3666;
          u[9] = -0.3675;
          u[10] = -0.3431;
          u[11] = -0.3424;
          u[12] = -0.1295;
          u[13] = -0.1294;
          u[14] = -0.1276;
          u[15] = -0.1275;
          u[16] = 0.1275;
          u[17] = 0.1276;
          u[18] = 0.1294;
          u[19] = 0.1295;
          u[20] = 0.3424;
          u[21] = 0.3431;
          u[22] = 0.3675;
          u[23] = 0.3666;
          u[24] = 0.6097;
          u[25] = 0.6072;
          u[26] = 0.7113;
          u[27] = 0.7196;
          u[28] = 0.9418;
          u[29] = 1.0048;
          u[30] = 1.2286;
          u[31] = 1.5031;
          break;
        case 7:
          u[0] = -1.5118;
          u[1] = -1.2349;
          u[2] = -1.0084;
          u[3] = -0.9299;
          u[4] = -0.7456;
          u[5] = -0.7205;
          u[6] = -0.5789;
          u[7] = -0.5786;
          u[8] = -0.3921;
          u[9] = -0.3936;
          u[10] = -0.3174;
          u[11] = -0.317;
          u[12] = -0.1322;
          u[13] = -0.1319;
          u[14] = -0.0949;
          u[15] = -0.0951;
          u[16] = 0.0951;
          u[17] = 0.0949;
          u[18] = 0.1319;
          u[19] = 0.1322;
          u[20] = 0.317;
          u[21] = 0.3174;
          u[22] = 0.3936;
          u[23] = 0.3921;
          u[24] = 0.5786;
          u[25] = 0.5789;
          u[26] = 0.7205;
          u[27] = 0.7456;
          u[28] = 0.9299;
          u[29] = 1.0084;
          u[30] = 1.2349;
          u[31] = 1.5118;
          break;
        case 8:
          u[0] = -1.48;
          u[1] = -1.2281;
          u[2] = -1.0349;
          u[3] = -0.9212;
          u[4] = -0.7604;
          u[5] = -0.7213;
          u[6] = -0.5872;
          u[7] = -0.581;
          u[8] = -0.4163;
          u[9] = -0.4159;
          u[10] = -0.3085;
          u[11] = -0.3086;
          u[12] = -0.1614;
          u[13] = -0.1614;
          u[14] = -0.0773;
          u[15] = -0.0773;
          u[16] = 0.0773;
          u[17] = 0.0773;
          u[18] = 0.1614;
          u[19] = 0.1614;
          u[20] = 0.3086;
          u[21] = 0.3085;
          u[22] = 0.4159;
          u[23] = 0.4163;
          u[24] = 0.581;
          u[25] = 0.5872;
          u[26] = 0.7213;
          u[27] = 0.7604;
          u[28] = 0.9212;
          u[29] = 1.0349;
          u[30] = 1.2281;
          u[31] = 1.48;
          break;
        case 9:
          u[0] = -1.4646;
          u[1] = -1.2234;
          u[2] = -1.0364;
          u[3] = -0.9218;
          u[4] = -0.7705;
          u[5] = -0.7282;
          u[6] = -0.5862;
          u[7] = -0.5765;
          u[8] = -0.4343;
          u[9] = -0.4333;
          u[10] = -0.3067;
          u[11] = -0.3069;
          u[12] = -0.1756;
          u[13] = -0.1757;
          u[14] = -0.0638;
          u[15] = -0.0638;
          u[16] = 0.0638;
          u[17] = 0.0638;
          u[18] = 0.1757;
          u[19] = 0.1756;
          u[20] = 0.3069;
          u[21] = 0.3067;
          u[22] = 0.4333;
          u[23] = 0.4343;
          u[24] = 0.5765;
          u[25] = 0.5862;
          u[26] = 0.7282;
          u[27] = 0.7705;
          u[28] = 0.9218;
          u[29] = 1.0364;
          u[30] = 1.2234;
          u[31] = 1.4646;
          break;
        case 10:
          u[0] = -1.4309;
          u[1] = -1.2285;
          u[2] = -1.0639;
          u[3] = -0.9261;
          u[4] = -0.8043;
          u[5] = -0.7141;
          u[6] = -0.6008;
          u[7] = -0.5561;
          u[8] = -0.4404;
          u[9] = -0.4241;
          u[10] = -0.3041;
          u[11] = -0.2996;
          u[12] = -0.179;
          u[13] = -0.178;
          u[14] = -0.0594;
          u[15] = -0.0592;
          u[16] = 0.0592;
          u[17] = 0.0594;
          u[18] = 0.178;
          u[19] = 0.179;
          u[20] = 0.2996;
          u[21] = 0.3041;
          u[22] = 0.4241;
          u[23] = 0.4404;
          u[24] = 0.5561;
          u[25] = 0.6008;
          u[26] = 0.7141;
          u[27] = 0.8043;
          u[28] = 0.9261;
          u[29] = 1.0639;
          u[30] = 1.2285;
          u[31] = 1.4309;
          break;
        case 11:
          u[0] = -1.3884;
          u[1] = -1.2158;
          u[2] = -1.0704;
          u[3] = -0.9432;
          u[4] = -0.8302;
          u[5] = -0.7293;
          u[6] = -0.6362;
          u[7] = -0.5535;
          u[8] = -0.4686;
          u[9] = -0.404;
          u[10] = -0.3178;
          u[11] = -0.276;
          u[12] = -0.1842;
          u[13] = -0.1615;
          u[14] = -0.0637;
          u[15] = -0.0502;
          u[16] = 0.0502;
          u[17] = 0.0637;
          u[18] = 0.1615;
          u[19] = 0.1842;
          u[20] = 0.276;
          u[21] = 0.3178;
          u[22] = 0.404;
          u[23] = 0.4686;
          u[24] = 0.5535;
          u[25] = 0.6362;
          u[26] = 0.7293;
          u[27] = 0.8302;
          u[28] = 0.9432;
          u[29] = 1.0704;
          u[30] = 1.2158;
          u[31] = 1.3884;
          break;
        case 12:
          u[0] = -1.3675;
          u[1] = -1.1917;
          u[2] = -1.0529;
          u[3] = -0.9386;
          u[4] = -0.8324;
          u[5] = -0.7417;
          u[6] = -0.6531;
          u[7] = -0.5763;
          u[8] = -0.4947;
          u[9] = -0.4264;
          u[10] = -0.353;
          u[11] = -0.291;
          u[12] = -0.2185;
          u[13] = -0.1602;
          u[14] = -0.0921;
          u[15] = -0.0354;
          u[16] = 0.0354;
          u[17] = 0.0921;
          u[18] = 0.1602;
          u[19] = 0.2185;
          u[20] = 0.291;
          u[21] = 0.353;
          u[22] = 0.4264;
          u[23] = 0.4947;
          u[24] = 0.5763;
          u[25] = 0.6531;
          u[26] = 0.7417;
          u[27] = 0.8324;
          u[28] = 0.9386;
          u[29] = 1.0529;
          u[30] = 1.1917;
          u[31] = 1.3675;
          break;
        case 13:
          u[0] = -1.3184;
          u[1] = -1.1795;
          u[2] = -1.0588;
          u[3] = -0.9498;
          u[4] = -0.8497;
          u[5] = -0.7566;
          u[6] = -0.6696;
          u[7] = -0.5878;
          u[8] = -0.51;
          u[9] = -0.4361;
          u[10] = -0.3645;
          u[11] = -0.2957;
          u[12] = -0.228;
          u[13] = -0.1623;
          u[14] = -0.0967;
          u[15] = -0.0325;
          u[16] = 0.0325;
          u[17] = 0.0967;
          u[18] = 0.1623;
          u[19] = 0.228;
          u[20] = 0.2957;
          u[21] = 0.3645;
          u[22] = 0.4361;
          u[23] = 0.51;
          u[24] = 0.5878;
          u[25] = 0.6696;
          u[26] = 0.7566;
          u[27] = 0.8497;
          u[28] = 0.9498;
          u[29] = 1.0588;
          u[30] = 1.1795;
          u[31] = 1.3184;
          break;
      }

      for(int i = 0; i < 1024; i++)
      {
        //if(i == 156)
          //printf("i = %i, tab.real = %.0lf, tab.imag = %.0lf\n", i, tab[i].real(), tab[i].imag());

        tab[i].real() = u[(int)tab[i].real()];
        tab[i].imag() = u[(int)tab[i].imag()];

        //if(i == 156)
          //printf("i = %i, tab.real = %lf, tab.imag = %lf\n", i, tab[i].real(), tab[i].imag());        
      }

      break; //1024-QAM
    case 4096:

      for(int i = 0; i < 64; i++)
      {
        if(i < 32)
          y_to_u_4096[i] += 32;
        if((i >= 16)&&(i < 48))
          y_to_u_4096[i] += 16;
        if((i%32 > 7)&&(i%32 < 24))
          y_to_u_4096[i] += 4;
        if((i%16 > 3)&&(i%16 < 12))
          y_to_u_4096[i] += 4;
        if((i%8 > 1)&&(i%8 < 6))
          y_to_u_4096[i] += 2;
         if((i%4 > 0)&&(i%4 < 3))
          y_to_u_4096[i] += 1;

          u_to_y_4096[(int)y_to_u_4096[i]] = i;
      }

      for(int i = 0; i < 4096; i++)
      {
        num[11] = i%2;
        num[10] = (i/2)%2;
        num[9] = (i/4)%2;
        num[8] = (i/8)%2;
        num[7] = (i/16)%2;
        num[6] = (i/32)%2;
        num[5] = (i/64)%2;
        num[4] = (i/128)%2;
        num[3] = (i/256)%2;
        num[2] = (i/512)%2;
        num[1] = (i/1024)%2;
        num[0] = i/2048;


        par = (int)(num[0]*1+num[2]*2+num[4]*4+num[6]*8+num[8]*16+num[10]*32);
        impar = (int)(num[1]*1+num[3]*2+num[5]*4+num[7]*8+num[9]*16+num[11]*32);

        tab[i].real() = u_to_y_4096[impar];
        tab[i].imag() = u_to_y_4096[par];

        //printf("i = %i, real = %i, imag = %i\n", i, impar, par);
      }

      switch (rate)
      {
        case 2:
          u[0] = -1.466;
          u[1] = -1.0185;
          u[2] = -0.8713;
          u[3] = -0.995;
          u[4] = -0.9302;
          u[5] = -0.8419;
          u[6] = -0.9479;
          u[7] = -1.1657;
          u[8] = -0.9184;
          u[9] = -0.836;
          u[10] = -0.7771;
          u[11] = -0.8242;
          u[12] = -0.8478;
          u[13] = -0.7889;
          u[14] = -0.8596;
          u[15] = -0.9714;
          u[16] = -0.2885;
          u[17] = -0.2944;
          u[18] = -0.3003;
          u[19] = -0.2944;
          u[20] = -0.3003;
          u[21] = -0.3003;
          u[22] = -0.3003;
          u[23] = -0.2944;
          u[24] = -0.2885;
          u[25] = -0.2944;
          u[26] = -0.3003;
          u[27] = -0.2944;
          u[28] = -0.2885;
          u[29] = -0.2944;
          u[30] = -0.2885;
          u[31] = -0.2826;
          u[32] = 0.2826;
          u[33] = 0.2885;
          u[34] = 0.2944;
          u[35] = 0.2885;
          u[36] = 0.2944;
          u[37] = 0.3003;
          u[38] = 0.2944;
          u[39] = 0.2885;
          u[40] = 0.2944;
          u[41] = 0.3003;
          u[42] = 0.3003;
          u[43] = 0.3003;
          u[44] = 0.2944;
          u[45] = 0.3003;
          u[46] = 0.2944;
          u[47] = 0.2885;
          u[48] = 0.9714;
          u[49] = 0.8596;
          u[50] = 0.7889;
          u[51] = 0.8478;
          u[52] = 0.8242;
          u[53] = 0.7771;
          u[54] = 0.836;
          u[55] = 0.9184;
          u[56] = 1.1657;
          u[57] = 0.9479;
          u[58] = 0.8419;
          u[59] = 0.9302;
          u[60] = 0.995;
          u[61] = 0.8713;
          u[62] = 1.0185;
          u[63] = 1.466;
          break;
        case 3:
          u[0] = -1.6424;
          u[1] = -1.0658;
          u[2] = -0.961;
          u[3] = -0.9901;
          u[4] = -1.0134;
          u[5] = -0.9785;
          u[6] = -1.0833;
          u[7] = -1.3046;
          u[8] = -0.7339;
          u[9] = -0.7455;
          u[10] = -0.7513;
          u[11] = -0.7397;
          u[12] = -0.7339;
          u[13] = -0.7455;
          u[14] = -0.7397;
          u[15] = -0.7222;
          u[16] = -0.2796;
          u[17] = -0.2796;
          u[18] = -0.3029;
          u[19] = -0.297;
          u[20] = -0.297;
          u[21] = -0.3029;
          u[22] = -0.2912;
          u[23] = -0.2796;
          u[24] = -0.2038;
          u[25] = -0.2097;
          u[26] = -0.2155;
          u[27] = -0.2155;
          u[28] = -0.2155;
          u[29] = -0.2155;
          u[30] = -0.2038;
          u[31] = -0.2038;
          u[32] = 0.2038;
          u[33] = 0.2038;
          u[34] = 0.2155;
          u[35] = 0.2155;
          u[36] = 0.2155;
          u[37] = 0.2155;
          u[38] = 0.2097;
          u[39] = 0.2038;
          u[40] = 0.2796;
          u[41] = 0.2912;
          u[42] = 0.3029;
          u[43] = 0.297;
          u[44] = 0.297;
          u[45] = 0.3029;
          u[46] = 0.2796;
          u[47] = 0.2796;
          u[48] = 0.7222;
          u[49] = 0.7397;
          u[50] = 0.7455;
          u[51] = 0.7339;
          u[52] = 0.7397;
          u[53] = 0.7513;
          u[54] = 0.7455;
          u[55] = 0.7339;
          u[56] = 1.3046;
          u[57] = 1.0833;
          u[58] = 0.9785;
          u[59] = 1.0134;
          u[60] = 0.9901;
          u[61] = 0.961;
          u[62] = 1.0658;
          u[63] = 1.6424;
          break;
        case 4:
          u[0] = 	-1.6391;
          u[1] = -1.1683;
          u[2] = -0.9967;
          u[3] = -0.9689;
          u[4] = -0.9857;
          u[5] = -1.0117;
          u[6] = -1.1931;
          u[7] = -1.3549;
          u[8] = -0.6465;
          u[9] = -0.6575;
          u[10] = -0.7124;
          u[11] = -0.6974;
          u[12] = -0.6979;
          u[13] = -0.7101;
          u[14] = -0.6569;
          u[15] = -0.6448;
          u[16] = -0.3374;
          u[17] = -0.334;
          u[18] = -0.3357;
          u[19] = -0.3386;
          u[20] = -0.3363;
          u[21] = -0.3334;
          u[22] = -0.3368;
          u[23] = -0.3368;
          u[24] = -0.1508;
          u[25] = -0.1491;
          u[26] = -0.1444;
          u[27] = -0.1491;
          u[28] = -0.1479;
          u[29] = -0.1456;
          u[30] = -0.1468;
          u[31] = -0.1508;
          u[32] = 0.1508;
          u[33] = 0.1468;
          u[34] = 0.1456;
          u[35] = 0.1479;
          u[36] = 0.1491;
          u[37] = 0.1444;
          u[38] = 0.1491;
          u[39] = 0.1508;
          u[40] = 0.3368;
          u[41] = 0.3368;
          u[42] = 0.3334;
          u[43] = 0.3363;
          u[44] = 0.3386;
          u[45] = 0.3357;
          u[46] = 0.334;
          u[47] = 0.3374;
          u[48] = 0.6448;
          u[49] = 0.6569;
          u[50] = 0.7101;
          u[51] = 0.6979;
          u[52] = 0.6974;
          u[53] = 0.7124;
          u[54] = 0.6575;
          u[55] = 0.6465;
          u[56] = 1.3549;
          u[57] = 1.1931;
          u[58] = 1.0117;
          u[59] = 0.9857;
          u[60] = 0.9689;
          u[61] = 0.9967;
          u[62] = 1.1683;
          u[63] = 1.6391;
          break;
        case 5:
          u[0] = -1.6566;
          u[1] = -1.1882;
          u[2] = -0.9939;
          u[3] = -0.9425;
          u[4] = -0.9482;
          u[5] = -1.0054;
          u[6] = -1.2281;
          u[7] = -1.4052;
          u[8] = -0.6112;
          u[9] = -0.6112;
          u[10] = -0.6969;
          u[11] = -0.6969;
          u[12] = -0.7026;
          u[13] = -0.6969;
          u[14] = -0.6112;
          u[15] = -0.6112;
          u[16] = -0.3599;
          u[17] = -0.3599;
          u[18] = -0.3484;
          u[19] = -0.3484;
          u[20] = -0.3484;
          u[21] = -0.3484;
          u[22] = -0.3599;
          u[23] = -0.3599;
          u[24] = -0.1257;
          u[25] = -0.1257;
          u[26] = -0.1257;
          u[27] = -0.1257;
          u[28] = -0.1257;
          u[29] = -0.1257;
          u[30] = -0.1257;
          u[31] = -0.1257;
          u[32] = 0.1257;
          u[33] = 0.1257;
          u[34] = 0.1257;
          u[35] = 0.1257;
          u[36] = 0.1257;
          u[37] = 0.1257;
          u[38] = 0.1257;
          u[39] = 0.1257;
          u[40] = 0.3599;
          u[41] = 0.3599;
          u[42] = 0.3484;
          u[43] = 0.3484;
          u[44] = 0.3484;
          u[45] = 0.3484;
          u[46] = 0.3599;
          u[47] = 0.3599;
          u[48] = 0.6112;
          u[49] = 0.6112;
          u[50] = 0.6969;
          u[51] = 0.7026;
          u[52] = 0.6969;
          u[53] = 0.6969;
          u[54] = 0.6112;
          u[55] = 0.6112;
          u[56] = 1.4052;
          u[57] = 1.2281;
          u[58] = 1.0054;
          u[59] = 0.9482;
          u[60] = 0.9425;
          u[61] = 0.9939;
          u[62] = 1.1882;
          u[63] = 1.6566;
          break;
        case 6:
          u[0] = -1.7274;
          u[1] = -1.4707;
          u[2] = -1.2411;
          u[3] = -1.1892;
          u[4] = -0.9842;
          u[5] = -0.978;
          u[6] = -0.9102;
          u[7] = -0.9102;
          u[8] = -0.7018;
          u[9] = -0.6968;
          u[10] = -0.6651;
          u[11] = -0.6648;
          u[12] = -0.5877;
          u[13] = -0.5876;
          u[14] = -0.5876;
          u[15] = -0.5875;
          u[16] = -0.3657;
          u[17] = -0.3657;
          u[18] = -0.3657;
          u[19] = -0.3657;
          u[20] = -0.3348;
          u[21] = -0.3348;
          u[22] = -0.3319;
          u[23] = -0.3319;
          u[24] = -0.1109;
          u[25] = -0.1094;
          u[26] = -0.1094;
          u[27] = -0.1094;
          u[28] = -0.1089;
          u[29] = -0.1087;
          u[30] = -0.1041;
          u[31] = -0.1041;
          u[32] = 0.1041;
          u[33] = 0.1041;
          u[34] = 0.1087;
          u[35] = 0.1089;
          u[36] = 0.1094;
          u[37] = 0.1094;
          u[38] = 0.1094;
          u[39] = 0.1109;
          u[40] = 0.3319;
          u[41] = 0.3319;
          u[42] = 0.3348;
          u[43] = 0.3348;
          u[44] = 0.3657;
          u[45] = 0.3657;
          u[46] = 0.3657;
          u[47] = 0.3657;
          u[48] = 0.5875;
          u[49] = 0.5876;
          u[50] = 0.5876;
          u[51] = 0.5877;
          u[52] = 0.6648;
          u[53] = 0.6651;
          u[54] = 0.6968;
          u[55] = 0.7018;
          u[56] = 0.9102;
          u[57] = 0.9102;
          u[58] = 0.978;
          u[59] = 0.9842;
          u[60] = 1.1892;
          u[61] = 1.2411;
          u[62] = 1.4707;
          u[63] = 1.7274;
          break;
        case 7:
          u[0] = -1.6851;
          u[1] = -1.4381;
          u[2] = -1.2355;
          u[3] = -1.1766;
          u[4] = -1.0012;
          u[5] = -0.9771;
          u[6] = -0.9089;
          u[7] = -0.9163;
          u[8] = -0.7385;
          u[9] = -0.7425;
          u[10] = -0.7186;
          u[11] = -0.7155;
          u[12] = -0.5704;
          u[13] = -0.57;
          u[14] = -0.5682;
          u[15] = -0.5684;
          u[16] = -0.4036;
          u[17] = -0.4036;
          u[18] = -0.4042;
          u[19] = -0.4043;
          u[20] = -0.3056;
          u[21] = -0.3056;
          u[22] = -0.306;
          u[23] = -0.3059;
          u[24] = -0.1456;
          u[25] = -0.1456;
          u[26] = -0.1457;
          u[27] = -0.1456;
          u[28] = -0.081;
          u[29] = -0.0807;
          u[30] = -0.0808;
          u[31] = -0.081;
          u[32] = 0.081;
          u[33] = 0.0808;
          u[34] = 0.0807;
          u[35] = 0.081;
          u[36] = 0.1456;
          u[37] = 0.1457;
          u[38] = 0.1456;
          u[39] = 0.1456;
          u[40] = 0.3059;
          u[41] = 0.306;
          u[42] = 0.3056;
          u[43] = 0.3056;
          u[44] = 0.4043;
          u[45] = 0.4042;
          u[46] = 0.4036;
          u[47] = 0.4036;
          u[48] = 0.5684;
          u[49] = 0.5682;
          u[50] = 0.57;
          u[51] = 0.5704;
          u[52] = 0.7155;
          u[53] = 0.7186;
          u[54] = 0.7425;
          u[55] = 0.7385;
          u[56] = 0.9163;
          u[57] = 0.9089;
          u[58] = 0.9771;
          u[59] = 1.0012;
          u[60] = 1.1766;
          u[61] = 1.2355;
          u[62] = 1.4381;
          u[63] = 1.6851;
          break;
        case 8:
          u[0] = -1.6336;
          u[1] = -1.4232;
          u[2] = -1.2459;
          u[3] = -1.1817;
          u[4] = -1.0393;
          u[5] = -1.0135;
          u[6] = -0.8979;
          u[7] = -0.8966;
          u[8] = -0.764;
          u[9] = -0.761;
          u[10] =	-0.709;
          u[11] =	-0.7078;
          u[12] =	-0.5729;
          u[13] =	-0.5679;
          u[14] =	-0.559;
          u[15] =	-0.5584;
          u[16] =	-0.4248;
          u[17] =	-0.4248;
          u[18] =	-0.424;
          u[19] =	-0.4234;
          u[20] =	-0.2968;
          u[21] =	-0.2963;
          u[22] =	-0.2963;
          u[23] =	-0.2963;
          u[24] =	-0.1718;
          u[25] =	-0.1687;
          u[26] =	-0.1687;
          u[27] =	-0.1677;
          u[28] =	-0.0562;
          u[29] =	-0.0562;
          u[30] =	-0.0553;
          u[31] =	-0.0501;
          u[32] =	0.0501;
          u[33] =	0.0553;
          u[34] =	0.0562;
          u[35] =	0.0562;
          u[36] =	0.1677;
          u[37] =	0.1687;
          u[38] =	0.1687;
          u[39] =	0.1718;
          u[40] =	0.2963;
          u[41] =	0.2963;
          u[42] =	0.2963;
          u[43] =	0.2968;
          u[44] =	0.4234;
          u[45] =	0.424;
          u[46] =	0.4248;
          u[47] =	0.4248;
          u[48] =	0.5584;
          u[49] =	0.559;
          u[50] =	0.5679;
          u[51] =	0.5729;
          u[52] =	0.7078;
          u[53] =	0.709;
          u[54] =	0.761;
          u[55] =	0.764;
          u[56] =	0.8966;
          u[57] =	0.8979;
          u[58] =	1.0135;
          u[59] =	1.0393;
          u[60] =	1.1817;
          u[61] =	1.2459;
          u[62] =	1.4232;
          u[63] =	1.6336;
          break;
        case 9:
          u[0] = -1.6223;
          u[1] = -1.4381;
          u[2] = -1.2898;
          u[3] = -1.1797;
          u[4] = -1.0619;
          u[5] = -1.005;
          u[6] = -0.9039;
          u[7] = -0.8808;
          u[8] = -0.7838;
          u[9] = -0.7694;
          u[10] =	-0.6848;
          u[11] =	-0.6848;
          u[12] =	-0.5683;
          u[13] =	-0.5673;
          u[14] =	-0.537;
          u[15] =	-0.5352;
          u[16] =	-0.4204;
          u[17] =	-0.4204;
          u[18] =	-0.4178;
          u[19] =	-0.4144;
          u[20] =	-0.2877;
          u[21] =	-0.2877;
          u[22] =	-0.2863;
          u[23] =	-0.2861;
          u[24] =	-0.1663;
          u[25] =	-0.1663;
          u[26] =	-0.1663;
          u[27] =	-0.1656;
          u[28] =	-0.0592;
          u[29] =	-0.0592;
          u[30] =	-0.0478;
          u[31] =	-0.0415;
          u[32] =	0.0415;
          u[33] =	0.0478;
          u[34] =	0.0592;
          u[35] =	0.0592;
          u[36] =	0.1656;
          u[37] =	0.1663;
          u[38] =	0.1663;
          u[39] =	0.1663;
          u[40] =	0.2861;
          u[41] =	0.2863;
          u[42] =	0.2877;
          u[43] =	0.2877;
          u[44] =	0.4144;
          u[45] =	0.4178;
          u[46] =	0.4204;
          u[47] =	0.4204;
          u[48] =	0.5352;
          u[49] =	0.537;
          u[50] =	0.5673;
          u[51] =	0.5683;
          u[52] =	0.6848;
          u[53] =	0.6848;
          u[54] =	0.7694;
          u[55] =	0.7838;
          u[56] =	0.8808;
          u[57] =	0.9039;
          u[58] =	1.005;
          u[59] =	1.0619;
          u[60] =	1.1797;
          u[61] =	1.2898;
          u[62] =	1.4381;
          u[63] =	1.6223;
          break;
        case 10:
          u[0] = -1.5629;
          u[1] = -1.4122;
          u[2] = -1.2894;
          u[3] = -1.187;
          u[4] = -1.0861;
          u[5] = -1.0037;
          u[6] = -0.9248;
          u[7] = -0.8802;
          u[8] = -0.8012;
          u[9] = -0.7787;
          u[10] =	-0.6969;
          u[11] =	-0.6911;
          u[12] =	-0.6081;
          u[13] =	-0.6069;
          u[14] =	-0.5302;
          u[15] =	-0.529;
          u[16] =	-0.4549;
          u[17] =	-0.4549;
          u[18] =	-0.3872;
          u[19] =	-0.3872;
          u[20] =	-0.3128;
          u[21] =	-0.3128;
          u[22] =	-0.2591;
          u[23] =	-0.2591;
          u[24] =	-0.1826;
          u[25] =	-0.1819;
          u[26] =	-0.1453;
          u[27] =	-0.1443;
          u[28] =	-0.0659;
          u[29] =	-0.0659;
          u[30] =	-0.0397;
          u[31] =	-0.0397;
          u[32] =	0.0397;
          u[33] =	0.0397;
          u[34] =	0.0659;
          u[35] =	0.0659;
          u[36] =	0.1443;
          u[37] =	0.1453;
          u[38] =	0.1819;
          u[39] =	0.1826;
          u[40] =	0.2591;
          u[41] =	0.2591;
          u[42] =	0.3128;
          u[43] =	0.3128;
          u[44] =	0.3872;
          u[45] =	0.3872;
          u[46] =	0.4549;
          u[47] =	0.4549;
          u[48] =	0.529;
          u[49] =	0.5302;
          u[50] =	0.6069;
          u[51] =	0.6081;
          u[52] =	0.6911;
          u[53] =	0.6969;
          u[54] =	0.7787;
          u[55] =	0.8012;
          u[56] =	0.8802;
          u[57] =	0.9248;
          u[58] =	1.0037;
          u[59] =	1.0861;
          u[60] =	1.187;
          u[61] =	1.2894;
          u[62] =	1.4122;
          u[63] =	1.5629;
          break;
        case 11:
          u[0] = -1.5162;
          u[1] = -1.3852;
          u[2] = -1.2766;
          u[3] = -1.1787;
          u[4] = -1.0904;
          u[5] = -1.0131;
          u[6] = -0.9425;
          u[7] = -0.8791;
          u[8] = -0.8174;
          u[9] = -0.7734;
          u[10] =	-0.7107;
          u[11] =	-0.6857;
          u[12] =	-0.6209;
          u[13] =	-0.6118;
          u[14] =	-0.5446;
          u[15] =	-0.5417;
          u[16] =	-0.4742;
          u[17] =	-0.4742;
          u[18] =	-0.4052;
          u[19] =	-0.4051;
          u[20] =	-0.336;
          u[21] =	-0.336;
          u[22] =	-0.2708;
          u[23] =	-0.2708;
          u[24] =	-0.2078;
          u[25] =	-0.2078;
          u[26] =	-0.146;
          u[27] =	-0.146;
          u[28] =	-0.0848;
          u[29] =	-0.0844;
          u[30] =	-0.0285;
          u[31] =	-0.0253;
          u[32] =	0.0253;
          u[33] =	0.0285;
          u[34] =	0.0844;
          u[35] =	0.0848;
          u[36] =	0.146;
          u[37] =	0.146;
          u[38] =	0.2078;
          u[39] =	0.2078;
          u[40] =	0.2708;
          u[41] =	0.2708;
          u[42] =	0.336;
          u[43] =	0.336;
          u[44] =	0.4051;
          u[45] =	0.4052;
          u[46] =	0.4742;
          u[47] =	0.4742;
          u[48] =	0.5417;
          u[49] =	0.5446;
          u[50] =	0.6118;
          u[51] =	0.6209;
          u[52] =	0.6857;
          u[53] =	0.7107;
          u[54] =	0.7734;
          u[55] =	0.8174;
          u[56] =	0.8791;
          u[57] =	0.9425;
          u[58] =	1.0131;
          u[59] =	1.0904;
          u[60] =	1.1787;
          u[61] =	1.2766;
          u[62] =	1.3852;
          u[63] =	1.5162;
          break;
        case 12:
          u[0] = -1.4431;
          u[1] = -1.3405;
          u[2] = -1.2541;
          u[3] = -1.1756;
          u[4] = -1.1017;
          u[5] = -1.0325;
          u[6] = -0.9718;
          u[7] = -0.9152;
          u[8] = -0.8624;
          u[9] = -0.8043;
          u[10] =	-0.7544;
          u[11] =	-0.706;
          u[12] =	-0.6586;
          u[13] =	-0.6136;
          u[14] =	-0.5712;
          u[15] =	-0.5296;
          u[16] =	-0.4897;
          u[17] =	-0.4506;
          u[18] =	-0.4118;
          u[19] =	-0.3796;
          u[20] =	-0.3393;
          u[21] =	-0.3096;
          u[22] =	-0.2675;
          u[23] =	-0.2466;
          u[24] =	-0.2018;
          u[25] =	-0.1887;
          u[26] =	-0.1389;
          u[27] =	-0.1337;
          u[28] =	-0.0842;
          u[29] =	-0.0828;
          u[30] =	-0.0262;
          u[31] =	-0.0262;
          u[32] =	0.0262;
          u[33] =	0.0262;
          u[34] =	0.0828;
          u[35] =	0.0842;
          u[36] =	0.1337;
          u[37] =	0.1389;
          u[38] =	0.1887;
          u[39] =	0.2018;
          u[40] =	0.2466;
          u[41] =	0.2675;
          u[42] =	0.3096;
          u[43] =	0.3393;
          u[44] =	0.3796;
          u[45] =	0.4118;
          u[46] =	0.4506;
          u[47] =	0.4897;
          u[48] =	0.5296;
          u[49] = 0.5712;
          u[50] =	0.6136;
          u[51] = 0.6586;
          u[52] = 0.706;
          u[53] = 0.7544;
          u[54] = 0.8043;
          u[55] = 0.8624;
          u[56] = 0.9152;
          u[57] = 0.9718;
          u[58] = 1.0325;
          u[59] = 1.1017;
          u[60] = 1.1756;
          u[61] = 1.2541;
          u[62] = 1.3405;
          u[63] = 1.4431;
          break;
        case 13:
          u[0] = -1.3644;
          u[1] = -1.2835;
          u[2] = -1.2121;
          u[3] = -1.1474;
          u[4] = -1.087;
          u[5] = -1.0276;
          u[6] = -0.9749;
          u[7] = -0.9254;
          u[8] = -0.8776;
          u[9] = -0.8255;
          u[10] = -0.779;
          u[11] = -0.7336;
          u[12] = -0.6885;
          u[13] = -0.6469;
          u[14] = -0.6051;
          u[15] = -0.5643;
          u[16] = -0.526;
          u[17] = -0.4893;
          u[18] = -0.4522;
          u[19] = -0.4156;
          u[20] = -0.3754;
          u[21] = -0.3412;
          u[22] = -0.3076;
          u[23] = -0.272;
          u[24] = -0.2378;
          u[25] = -0.2053;
          u[26] = -0.1713;
          u[27] = -0.1399;
          u[28] = -0.108;
          u[29] = -0.0781;
          u[30] = -0.0487;
          u[31] = -0.0176;
          u[32] = 0.0176;
          u[33] = 0.0487;
          u[34] = 0.0781;
          u[35] = 0.108;
          u[36] = 0.1399;
          u[37] = 0.1713;
          u[38] = 0.2053;
          u[39] = 0.2378;
          u[40] = 0.272;
          u[41] = 0.3076;
          u[42] = 0.3412;
          u[43] = 0.3754;
          u[44] = 0.4156;
          u[45] = 0.4522;
          u[46] = 0.4893;
          u[47] = 0.526;
          u[48] = 0.5643;
          u[49] = 0.6051;
          u[50] = 0.6469;
          u[51] = 0.6885;
          u[52] = 0.7336;
          u[53] = 0.779;
          u[54] = 0.8255;
          u[55] = 0.8776;
          u[56] = 0.9254;
          u[57] = 0.9749;
          u[58] = 1.0276;
          u[59] = 1.087;
          u[60] = 1.1474;
          u[61] = 1.2121;
          u[62] = 1.2835;
          u[63] = 1.3644;
          break;
      }

      for(int i = 0; i < 4096; i++)
      {
        //if(i == 156)
          //printf("i = %i, tab.real = %.0lf, tab.imag = %.0lf\n", i, tab[i].real(), tab[i].imag());

        tab[i].real() = u[(int)tab[i].real()];
        tab[i].imag() = u[(int)tab[i].imag()];

        //if(i == 156)
          //printf("i = %i, tab.real = %lf, tab.imag = %lf\n", i, tab[i].real(), tab[i].imag());        
      }

      break; //4096-QAM
    default:
      tab[0].real() = 1.0/sqrt(2.0); tab[0].imag() = 1.0/sqrt(2.0);
      break; // QPSK default
  } // switch mod_size
  
	for(int i = 0; i < mod_size/4; i++)
	{
		//tab[i].real() = t[i].real();
		//tab[i].imag() = t[i].imag();
		//printf("%i - tab.real = %lf, tab.imag = %lf\n", i, tab[i].real(), tab[i].imag());
	}

  if(mod_size < 1024)
  {
    for(int i = 1; i < 4; i++) //quadrantes
    {
      for(int j = 0; j < mod_size/4; j++) //pontos
      {
        if(i == 1)
        {
          tab[j+(mod_size/4)].real() = -tab[j].real();
          tab[j+(mod_size/4)].imag() = tab[j].imag();
        }
        else if(i == 2)
        {
          tab[j+2*(mod_size/4)].real() = tab[j].real();
          tab[j+2*(mod_size/4)].imag() = -tab[j].imag();
        }
        else if(i == 3)
        {
          tab[j+3*(mod_size/4)].real() = -tab[j].real();
          tab[j+3*(mod_size/4)].imag() = -tab[j].imag();
        }
        //printf("%i - tab.real = %lf, tab.imag = %lf\n", j+i*(mod_size/4), tab[j+i*(mod_size/4)].real(), tab[j+i*(mod_size/4)].imag());
      }
    }
  }

	for(int i = 0; i < mod_size; i++)
	{
		tabela[i] = tab[i];
		//printf("%i - tabela.real = %lf, tabela.imag = %lf\n", i, tabela[i].real(), tabela[i].imag());
	}

	delete []tab;
}

void demap::demapper_soft(const gr_complex *i, float *o)
{
	for(int ii = 0; ii < size; ii++) //cada simbolo recebido
	{
		int a;

		//dist. real e imag
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
		{
			aux_r[j] = i[ii].real() - tabela[j].real();
			aux_i[j] = i[ii].imag() - tabela[j].imag();
		}

		//dist. euclidiana ao quadrado
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
			aux[j] = aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]; 
      //aux[j] = sqrt(aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]);

		//printf("\nreal = %lf, imag = %lf\n", i[ii].real(), i[ii].imag());

		//for(int III = 0; III < mod_size; III++)
		//	printf("aux[%i] = %lf\n", III, aux[III]);

		for(int j = 1; j <= M; j++) //cada bit do simbolo
		{
			D[0] = 999;
			D[1] = 999;

			for(int k = 0; k < mod_size; k++) //cada simbolo possivel
			{

				if(j == 1)
					a = k%(int)(pow(2,j));//isolar bit
				else
					a = (k%(int)(pow(2,j)))/(pow(2,(j-1))); //isolar bit

				if(a == 0)//bit 0
				{
					if(aux[k] < D[0])
						D[0] = aux[k];
				}
				else if(a == 1)//bit 1
				{
					if(aux[k] < D[1])
						D[1] = aux[k];
				}
			}

			o[ii*M+M-j] = -(1/var)*(D[1]-D[0]); //saida LLR do bit

			//printf("%lf\n", o[ii*M+M-j]);
		}
	}
}

void demap::demapper_hard(const gr_complex *i, unsigned char *o)
{

	for(int ii = 0; ii < size; ii++) //cada simbolo recebido
	{
		int out_hard = 0;

		//dist. real e imag
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
		{
			aux_r[j] = i[ii].real() - tabela[j].real();
			aux_i[j] = i[ii].imag() - tabela[j].imag();
		}

		//dist. euclidiana
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
			aux[j] = sqrt(aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]);

		for(int j = 1; j < mod_size; j++) //cada simbolo possivel
		{
			if(aux[j] < aux[out_hard])
				out_hard = j; //(falta separar os bits)
		}

		for(int j = 1; j <= M; j++) //cada bit do simbolo
		{
			if(j == 1)
				o[ii*M+M-j] = out_hard%(int)(pow(2,j));//isolar bit
			else
				o[ii*M+M-j] = (out_hard%(int)(pow(2,j)))/(pow(2,(j-1))); //isolar bit
		}
	}
}

void demap::mapper(const unsigned char *i, gr_complex *o)
{
  for(int ii = 0; ii < 1; ii++) //cada simbolo recebido
	{
    o[ii].real() = tabela[(int)i[ii]].real();
    o[ii].imag() = tabela[(int)i[ii]].imag();
    //printf("%i\n", (int)i[ii]);
  }
}

void demap::pack_bits(const unsigned char *pack_in, unsigned char *pack_out, int n_bits)
{
  int index_pack_out = 0, aux_index = 0, aux = 0;
  for(int i = 0; i < size; i++) //cada simbolo recebido
	{
    aux_index = i%n_bits;
    aux = aux + pack_in[i]*pow(2, aux_index);
    if(aux_index == n_bits-1)
    {
      pack_out[index_pack_out] = aux;
      aux = 0;
      index_pack_out++;
      printf("%i\n",pack_out[index_pack_out]);
    }
  }
}