#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_387547304249028087) {
   out_387547304249028087[0] = delta_x[0] + nom_x[0];
   out_387547304249028087[1] = delta_x[1] + nom_x[1];
   out_387547304249028087[2] = delta_x[2] + nom_x[2];
   out_387547304249028087[3] = delta_x[3] + nom_x[3];
   out_387547304249028087[4] = delta_x[4] + nom_x[4];
   out_387547304249028087[5] = delta_x[5] + nom_x[5];
   out_387547304249028087[6] = delta_x[6] + nom_x[6];
   out_387547304249028087[7] = delta_x[7] + nom_x[7];
   out_387547304249028087[8] = delta_x[8] + nom_x[8];
   out_387547304249028087[9] = delta_x[9] + nom_x[9];
   out_387547304249028087[10] = delta_x[10] + nom_x[10];
   out_387547304249028087[11] = delta_x[11] + nom_x[11];
   out_387547304249028087[12] = delta_x[12] + nom_x[12];
   out_387547304249028087[13] = delta_x[13] + nom_x[13];
   out_387547304249028087[14] = delta_x[14] + nom_x[14];
   out_387547304249028087[15] = delta_x[15] + nom_x[15];
   out_387547304249028087[16] = delta_x[16] + nom_x[16];
   out_387547304249028087[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7237327960985051970) {
   out_7237327960985051970[0] = -nom_x[0] + true_x[0];
   out_7237327960985051970[1] = -nom_x[1] + true_x[1];
   out_7237327960985051970[2] = -nom_x[2] + true_x[2];
   out_7237327960985051970[3] = -nom_x[3] + true_x[3];
   out_7237327960985051970[4] = -nom_x[4] + true_x[4];
   out_7237327960985051970[5] = -nom_x[5] + true_x[5];
   out_7237327960985051970[6] = -nom_x[6] + true_x[6];
   out_7237327960985051970[7] = -nom_x[7] + true_x[7];
   out_7237327960985051970[8] = -nom_x[8] + true_x[8];
   out_7237327960985051970[9] = -nom_x[9] + true_x[9];
   out_7237327960985051970[10] = -nom_x[10] + true_x[10];
   out_7237327960985051970[11] = -nom_x[11] + true_x[11];
   out_7237327960985051970[12] = -nom_x[12] + true_x[12];
   out_7237327960985051970[13] = -nom_x[13] + true_x[13];
   out_7237327960985051970[14] = -nom_x[14] + true_x[14];
   out_7237327960985051970[15] = -nom_x[15] + true_x[15];
   out_7237327960985051970[16] = -nom_x[16] + true_x[16];
   out_7237327960985051970[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1518150812485221245) {
   out_1518150812485221245[0] = 1.0;
   out_1518150812485221245[1] = 0.0;
   out_1518150812485221245[2] = 0.0;
   out_1518150812485221245[3] = 0.0;
   out_1518150812485221245[4] = 0.0;
   out_1518150812485221245[5] = 0.0;
   out_1518150812485221245[6] = 0.0;
   out_1518150812485221245[7] = 0.0;
   out_1518150812485221245[8] = 0.0;
   out_1518150812485221245[9] = 0.0;
   out_1518150812485221245[10] = 0.0;
   out_1518150812485221245[11] = 0.0;
   out_1518150812485221245[12] = 0.0;
   out_1518150812485221245[13] = 0.0;
   out_1518150812485221245[14] = 0.0;
   out_1518150812485221245[15] = 0.0;
   out_1518150812485221245[16] = 0.0;
   out_1518150812485221245[17] = 0.0;
   out_1518150812485221245[18] = 0.0;
   out_1518150812485221245[19] = 1.0;
   out_1518150812485221245[20] = 0.0;
   out_1518150812485221245[21] = 0.0;
   out_1518150812485221245[22] = 0.0;
   out_1518150812485221245[23] = 0.0;
   out_1518150812485221245[24] = 0.0;
   out_1518150812485221245[25] = 0.0;
   out_1518150812485221245[26] = 0.0;
   out_1518150812485221245[27] = 0.0;
   out_1518150812485221245[28] = 0.0;
   out_1518150812485221245[29] = 0.0;
   out_1518150812485221245[30] = 0.0;
   out_1518150812485221245[31] = 0.0;
   out_1518150812485221245[32] = 0.0;
   out_1518150812485221245[33] = 0.0;
   out_1518150812485221245[34] = 0.0;
   out_1518150812485221245[35] = 0.0;
   out_1518150812485221245[36] = 0.0;
   out_1518150812485221245[37] = 0.0;
   out_1518150812485221245[38] = 1.0;
   out_1518150812485221245[39] = 0.0;
   out_1518150812485221245[40] = 0.0;
   out_1518150812485221245[41] = 0.0;
   out_1518150812485221245[42] = 0.0;
   out_1518150812485221245[43] = 0.0;
   out_1518150812485221245[44] = 0.0;
   out_1518150812485221245[45] = 0.0;
   out_1518150812485221245[46] = 0.0;
   out_1518150812485221245[47] = 0.0;
   out_1518150812485221245[48] = 0.0;
   out_1518150812485221245[49] = 0.0;
   out_1518150812485221245[50] = 0.0;
   out_1518150812485221245[51] = 0.0;
   out_1518150812485221245[52] = 0.0;
   out_1518150812485221245[53] = 0.0;
   out_1518150812485221245[54] = 0.0;
   out_1518150812485221245[55] = 0.0;
   out_1518150812485221245[56] = 0.0;
   out_1518150812485221245[57] = 1.0;
   out_1518150812485221245[58] = 0.0;
   out_1518150812485221245[59] = 0.0;
   out_1518150812485221245[60] = 0.0;
   out_1518150812485221245[61] = 0.0;
   out_1518150812485221245[62] = 0.0;
   out_1518150812485221245[63] = 0.0;
   out_1518150812485221245[64] = 0.0;
   out_1518150812485221245[65] = 0.0;
   out_1518150812485221245[66] = 0.0;
   out_1518150812485221245[67] = 0.0;
   out_1518150812485221245[68] = 0.0;
   out_1518150812485221245[69] = 0.0;
   out_1518150812485221245[70] = 0.0;
   out_1518150812485221245[71] = 0.0;
   out_1518150812485221245[72] = 0.0;
   out_1518150812485221245[73] = 0.0;
   out_1518150812485221245[74] = 0.0;
   out_1518150812485221245[75] = 0.0;
   out_1518150812485221245[76] = 1.0;
   out_1518150812485221245[77] = 0.0;
   out_1518150812485221245[78] = 0.0;
   out_1518150812485221245[79] = 0.0;
   out_1518150812485221245[80] = 0.0;
   out_1518150812485221245[81] = 0.0;
   out_1518150812485221245[82] = 0.0;
   out_1518150812485221245[83] = 0.0;
   out_1518150812485221245[84] = 0.0;
   out_1518150812485221245[85] = 0.0;
   out_1518150812485221245[86] = 0.0;
   out_1518150812485221245[87] = 0.0;
   out_1518150812485221245[88] = 0.0;
   out_1518150812485221245[89] = 0.0;
   out_1518150812485221245[90] = 0.0;
   out_1518150812485221245[91] = 0.0;
   out_1518150812485221245[92] = 0.0;
   out_1518150812485221245[93] = 0.0;
   out_1518150812485221245[94] = 0.0;
   out_1518150812485221245[95] = 1.0;
   out_1518150812485221245[96] = 0.0;
   out_1518150812485221245[97] = 0.0;
   out_1518150812485221245[98] = 0.0;
   out_1518150812485221245[99] = 0.0;
   out_1518150812485221245[100] = 0.0;
   out_1518150812485221245[101] = 0.0;
   out_1518150812485221245[102] = 0.0;
   out_1518150812485221245[103] = 0.0;
   out_1518150812485221245[104] = 0.0;
   out_1518150812485221245[105] = 0.0;
   out_1518150812485221245[106] = 0.0;
   out_1518150812485221245[107] = 0.0;
   out_1518150812485221245[108] = 0.0;
   out_1518150812485221245[109] = 0.0;
   out_1518150812485221245[110] = 0.0;
   out_1518150812485221245[111] = 0.0;
   out_1518150812485221245[112] = 0.0;
   out_1518150812485221245[113] = 0.0;
   out_1518150812485221245[114] = 1.0;
   out_1518150812485221245[115] = 0.0;
   out_1518150812485221245[116] = 0.0;
   out_1518150812485221245[117] = 0.0;
   out_1518150812485221245[118] = 0.0;
   out_1518150812485221245[119] = 0.0;
   out_1518150812485221245[120] = 0.0;
   out_1518150812485221245[121] = 0.0;
   out_1518150812485221245[122] = 0.0;
   out_1518150812485221245[123] = 0.0;
   out_1518150812485221245[124] = 0.0;
   out_1518150812485221245[125] = 0.0;
   out_1518150812485221245[126] = 0.0;
   out_1518150812485221245[127] = 0.0;
   out_1518150812485221245[128] = 0.0;
   out_1518150812485221245[129] = 0.0;
   out_1518150812485221245[130] = 0.0;
   out_1518150812485221245[131] = 0.0;
   out_1518150812485221245[132] = 0.0;
   out_1518150812485221245[133] = 1.0;
   out_1518150812485221245[134] = 0.0;
   out_1518150812485221245[135] = 0.0;
   out_1518150812485221245[136] = 0.0;
   out_1518150812485221245[137] = 0.0;
   out_1518150812485221245[138] = 0.0;
   out_1518150812485221245[139] = 0.0;
   out_1518150812485221245[140] = 0.0;
   out_1518150812485221245[141] = 0.0;
   out_1518150812485221245[142] = 0.0;
   out_1518150812485221245[143] = 0.0;
   out_1518150812485221245[144] = 0.0;
   out_1518150812485221245[145] = 0.0;
   out_1518150812485221245[146] = 0.0;
   out_1518150812485221245[147] = 0.0;
   out_1518150812485221245[148] = 0.0;
   out_1518150812485221245[149] = 0.0;
   out_1518150812485221245[150] = 0.0;
   out_1518150812485221245[151] = 0.0;
   out_1518150812485221245[152] = 1.0;
   out_1518150812485221245[153] = 0.0;
   out_1518150812485221245[154] = 0.0;
   out_1518150812485221245[155] = 0.0;
   out_1518150812485221245[156] = 0.0;
   out_1518150812485221245[157] = 0.0;
   out_1518150812485221245[158] = 0.0;
   out_1518150812485221245[159] = 0.0;
   out_1518150812485221245[160] = 0.0;
   out_1518150812485221245[161] = 0.0;
   out_1518150812485221245[162] = 0.0;
   out_1518150812485221245[163] = 0.0;
   out_1518150812485221245[164] = 0.0;
   out_1518150812485221245[165] = 0.0;
   out_1518150812485221245[166] = 0.0;
   out_1518150812485221245[167] = 0.0;
   out_1518150812485221245[168] = 0.0;
   out_1518150812485221245[169] = 0.0;
   out_1518150812485221245[170] = 0.0;
   out_1518150812485221245[171] = 1.0;
   out_1518150812485221245[172] = 0.0;
   out_1518150812485221245[173] = 0.0;
   out_1518150812485221245[174] = 0.0;
   out_1518150812485221245[175] = 0.0;
   out_1518150812485221245[176] = 0.0;
   out_1518150812485221245[177] = 0.0;
   out_1518150812485221245[178] = 0.0;
   out_1518150812485221245[179] = 0.0;
   out_1518150812485221245[180] = 0.0;
   out_1518150812485221245[181] = 0.0;
   out_1518150812485221245[182] = 0.0;
   out_1518150812485221245[183] = 0.0;
   out_1518150812485221245[184] = 0.0;
   out_1518150812485221245[185] = 0.0;
   out_1518150812485221245[186] = 0.0;
   out_1518150812485221245[187] = 0.0;
   out_1518150812485221245[188] = 0.0;
   out_1518150812485221245[189] = 0.0;
   out_1518150812485221245[190] = 1.0;
   out_1518150812485221245[191] = 0.0;
   out_1518150812485221245[192] = 0.0;
   out_1518150812485221245[193] = 0.0;
   out_1518150812485221245[194] = 0.0;
   out_1518150812485221245[195] = 0.0;
   out_1518150812485221245[196] = 0.0;
   out_1518150812485221245[197] = 0.0;
   out_1518150812485221245[198] = 0.0;
   out_1518150812485221245[199] = 0.0;
   out_1518150812485221245[200] = 0.0;
   out_1518150812485221245[201] = 0.0;
   out_1518150812485221245[202] = 0.0;
   out_1518150812485221245[203] = 0.0;
   out_1518150812485221245[204] = 0.0;
   out_1518150812485221245[205] = 0.0;
   out_1518150812485221245[206] = 0.0;
   out_1518150812485221245[207] = 0.0;
   out_1518150812485221245[208] = 0.0;
   out_1518150812485221245[209] = 1.0;
   out_1518150812485221245[210] = 0.0;
   out_1518150812485221245[211] = 0.0;
   out_1518150812485221245[212] = 0.0;
   out_1518150812485221245[213] = 0.0;
   out_1518150812485221245[214] = 0.0;
   out_1518150812485221245[215] = 0.0;
   out_1518150812485221245[216] = 0.0;
   out_1518150812485221245[217] = 0.0;
   out_1518150812485221245[218] = 0.0;
   out_1518150812485221245[219] = 0.0;
   out_1518150812485221245[220] = 0.0;
   out_1518150812485221245[221] = 0.0;
   out_1518150812485221245[222] = 0.0;
   out_1518150812485221245[223] = 0.0;
   out_1518150812485221245[224] = 0.0;
   out_1518150812485221245[225] = 0.0;
   out_1518150812485221245[226] = 0.0;
   out_1518150812485221245[227] = 0.0;
   out_1518150812485221245[228] = 1.0;
   out_1518150812485221245[229] = 0.0;
   out_1518150812485221245[230] = 0.0;
   out_1518150812485221245[231] = 0.0;
   out_1518150812485221245[232] = 0.0;
   out_1518150812485221245[233] = 0.0;
   out_1518150812485221245[234] = 0.0;
   out_1518150812485221245[235] = 0.0;
   out_1518150812485221245[236] = 0.0;
   out_1518150812485221245[237] = 0.0;
   out_1518150812485221245[238] = 0.0;
   out_1518150812485221245[239] = 0.0;
   out_1518150812485221245[240] = 0.0;
   out_1518150812485221245[241] = 0.0;
   out_1518150812485221245[242] = 0.0;
   out_1518150812485221245[243] = 0.0;
   out_1518150812485221245[244] = 0.0;
   out_1518150812485221245[245] = 0.0;
   out_1518150812485221245[246] = 0.0;
   out_1518150812485221245[247] = 1.0;
   out_1518150812485221245[248] = 0.0;
   out_1518150812485221245[249] = 0.0;
   out_1518150812485221245[250] = 0.0;
   out_1518150812485221245[251] = 0.0;
   out_1518150812485221245[252] = 0.0;
   out_1518150812485221245[253] = 0.0;
   out_1518150812485221245[254] = 0.0;
   out_1518150812485221245[255] = 0.0;
   out_1518150812485221245[256] = 0.0;
   out_1518150812485221245[257] = 0.0;
   out_1518150812485221245[258] = 0.0;
   out_1518150812485221245[259] = 0.0;
   out_1518150812485221245[260] = 0.0;
   out_1518150812485221245[261] = 0.0;
   out_1518150812485221245[262] = 0.0;
   out_1518150812485221245[263] = 0.0;
   out_1518150812485221245[264] = 0.0;
   out_1518150812485221245[265] = 0.0;
   out_1518150812485221245[266] = 1.0;
   out_1518150812485221245[267] = 0.0;
   out_1518150812485221245[268] = 0.0;
   out_1518150812485221245[269] = 0.0;
   out_1518150812485221245[270] = 0.0;
   out_1518150812485221245[271] = 0.0;
   out_1518150812485221245[272] = 0.0;
   out_1518150812485221245[273] = 0.0;
   out_1518150812485221245[274] = 0.0;
   out_1518150812485221245[275] = 0.0;
   out_1518150812485221245[276] = 0.0;
   out_1518150812485221245[277] = 0.0;
   out_1518150812485221245[278] = 0.0;
   out_1518150812485221245[279] = 0.0;
   out_1518150812485221245[280] = 0.0;
   out_1518150812485221245[281] = 0.0;
   out_1518150812485221245[282] = 0.0;
   out_1518150812485221245[283] = 0.0;
   out_1518150812485221245[284] = 0.0;
   out_1518150812485221245[285] = 1.0;
   out_1518150812485221245[286] = 0.0;
   out_1518150812485221245[287] = 0.0;
   out_1518150812485221245[288] = 0.0;
   out_1518150812485221245[289] = 0.0;
   out_1518150812485221245[290] = 0.0;
   out_1518150812485221245[291] = 0.0;
   out_1518150812485221245[292] = 0.0;
   out_1518150812485221245[293] = 0.0;
   out_1518150812485221245[294] = 0.0;
   out_1518150812485221245[295] = 0.0;
   out_1518150812485221245[296] = 0.0;
   out_1518150812485221245[297] = 0.0;
   out_1518150812485221245[298] = 0.0;
   out_1518150812485221245[299] = 0.0;
   out_1518150812485221245[300] = 0.0;
   out_1518150812485221245[301] = 0.0;
   out_1518150812485221245[302] = 0.0;
   out_1518150812485221245[303] = 0.0;
   out_1518150812485221245[304] = 1.0;
   out_1518150812485221245[305] = 0.0;
   out_1518150812485221245[306] = 0.0;
   out_1518150812485221245[307] = 0.0;
   out_1518150812485221245[308] = 0.0;
   out_1518150812485221245[309] = 0.0;
   out_1518150812485221245[310] = 0.0;
   out_1518150812485221245[311] = 0.0;
   out_1518150812485221245[312] = 0.0;
   out_1518150812485221245[313] = 0.0;
   out_1518150812485221245[314] = 0.0;
   out_1518150812485221245[315] = 0.0;
   out_1518150812485221245[316] = 0.0;
   out_1518150812485221245[317] = 0.0;
   out_1518150812485221245[318] = 0.0;
   out_1518150812485221245[319] = 0.0;
   out_1518150812485221245[320] = 0.0;
   out_1518150812485221245[321] = 0.0;
   out_1518150812485221245[322] = 0.0;
   out_1518150812485221245[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1633491762729632217) {
   out_1633491762729632217[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1633491762729632217[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1633491762729632217[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1633491762729632217[3] = dt*state[12] + state[3];
   out_1633491762729632217[4] = dt*state[13] + state[4];
   out_1633491762729632217[5] = dt*state[14] + state[5];
   out_1633491762729632217[6] = state[6];
   out_1633491762729632217[7] = state[7];
   out_1633491762729632217[8] = state[8];
   out_1633491762729632217[9] = state[9];
   out_1633491762729632217[10] = state[10];
   out_1633491762729632217[11] = state[11];
   out_1633491762729632217[12] = state[12];
   out_1633491762729632217[13] = state[13];
   out_1633491762729632217[14] = state[14];
   out_1633491762729632217[15] = state[15];
   out_1633491762729632217[16] = state[16];
   out_1633491762729632217[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7445322755045531081) {
   out_7445322755045531081[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7445322755045531081[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7445322755045531081[2] = 0;
   out_7445322755045531081[3] = 0;
   out_7445322755045531081[4] = 0;
   out_7445322755045531081[5] = 0;
   out_7445322755045531081[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7445322755045531081[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7445322755045531081[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7445322755045531081[9] = 0;
   out_7445322755045531081[10] = 0;
   out_7445322755045531081[11] = 0;
   out_7445322755045531081[12] = 0;
   out_7445322755045531081[13] = 0;
   out_7445322755045531081[14] = 0;
   out_7445322755045531081[15] = 0;
   out_7445322755045531081[16] = 0;
   out_7445322755045531081[17] = 0;
   out_7445322755045531081[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7445322755045531081[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7445322755045531081[20] = 0;
   out_7445322755045531081[21] = 0;
   out_7445322755045531081[22] = 0;
   out_7445322755045531081[23] = 0;
   out_7445322755045531081[24] = 0;
   out_7445322755045531081[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7445322755045531081[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7445322755045531081[27] = 0;
   out_7445322755045531081[28] = 0;
   out_7445322755045531081[29] = 0;
   out_7445322755045531081[30] = 0;
   out_7445322755045531081[31] = 0;
   out_7445322755045531081[32] = 0;
   out_7445322755045531081[33] = 0;
   out_7445322755045531081[34] = 0;
   out_7445322755045531081[35] = 0;
   out_7445322755045531081[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7445322755045531081[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7445322755045531081[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7445322755045531081[39] = 0;
   out_7445322755045531081[40] = 0;
   out_7445322755045531081[41] = 0;
   out_7445322755045531081[42] = 0;
   out_7445322755045531081[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7445322755045531081[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7445322755045531081[45] = 0;
   out_7445322755045531081[46] = 0;
   out_7445322755045531081[47] = 0;
   out_7445322755045531081[48] = 0;
   out_7445322755045531081[49] = 0;
   out_7445322755045531081[50] = 0;
   out_7445322755045531081[51] = 0;
   out_7445322755045531081[52] = 0;
   out_7445322755045531081[53] = 0;
   out_7445322755045531081[54] = 0;
   out_7445322755045531081[55] = 0;
   out_7445322755045531081[56] = 0;
   out_7445322755045531081[57] = 1;
   out_7445322755045531081[58] = 0;
   out_7445322755045531081[59] = 0;
   out_7445322755045531081[60] = 0;
   out_7445322755045531081[61] = 0;
   out_7445322755045531081[62] = 0;
   out_7445322755045531081[63] = 0;
   out_7445322755045531081[64] = 0;
   out_7445322755045531081[65] = 0;
   out_7445322755045531081[66] = dt;
   out_7445322755045531081[67] = 0;
   out_7445322755045531081[68] = 0;
   out_7445322755045531081[69] = 0;
   out_7445322755045531081[70] = 0;
   out_7445322755045531081[71] = 0;
   out_7445322755045531081[72] = 0;
   out_7445322755045531081[73] = 0;
   out_7445322755045531081[74] = 0;
   out_7445322755045531081[75] = 0;
   out_7445322755045531081[76] = 1;
   out_7445322755045531081[77] = 0;
   out_7445322755045531081[78] = 0;
   out_7445322755045531081[79] = 0;
   out_7445322755045531081[80] = 0;
   out_7445322755045531081[81] = 0;
   out_7445322755045531081[82] = 0;
   out_7445322755045531081[83] = 0;
   out_7445322755045531081[84] = 0;
   out_7445322755045531081[85] = dt;
   out_7445322755045531081[86] = 0;
   out_7445322755045531081[87] = 0;
   out_7445322755045531081[88] = 0;
   out_7445322755045531081[89] = 0;
   out_7445322755045531081[90] = 0;
   out_7445322755045531081[91] = 0;
   out_7445322755045531081[92] = 0;
   out_7445322755045531081[93] = 0;
   out_7445322755045531081[94] = 0;
   out_7445322755045531081[95] = 1;
   out_7445322755045531081[96] = 0;
   out_7445322755045531081[97] = 0;
   out_7445322755045531081[98] = 0;
   out_7445322755045531081[99] = 0;
   out_7445322755045531081[100] = 0;
   out_7445322755045531081[101] = 0;
   out_7445322755045531081[102] = 0;
   out_7445322755045531081[103] = 0;
   out_7445322755045531081[104] = dt;
   out_7445322755045531081[105] = 0;
   out_7445322755045531081[106] = 0;
   out_7445322755045531081[107] = 0;
   out_7445322755045531081[108] = 0;
   out_7445322755045531081[109] = 0;
   out_7445322755045531081[110] = 0;
   out_7445322755045531081[111] = 0;
   out_7445322755045531081[112] = 0;
   out_7445322755045531081[113] = 0;
   out_7445322755045531081[114] = 1;
   out_7445322755045531081[115] = 0;
   out_7445322755045531081[116] = 0;
   out_7445322755045531081[117] = 0;
   out_7445322755045531081[118] = 0;
   out_7445322755045531081[119] = 0;
   out_7445322755045531081[120] = 0;
   out_7445322755045531081[121] = 0;
   out_7445322755045531081[122] = 0;
   out_7445322755045531081[123] = 0;
   out_7445322755045531081[124] = 0;
   out_7445322755045531081[125] = 0;
   out_7445322755045531081[126] = 0;
   out_7445322755045531081[127] = 0;
   out_7445322755045531081[128] = 0;
   out_7445322755045531081[129] = 0;
   out_7445322755045531081[130] = 0;
   out_7445322755045531081[131] = 0;
   out_7445322755045531081[132] = 0;
   out_7445322755045531081[133] = 1;
   out_7445322755045531081[134] = 0;
   out_7445322755045531081[135] = 0;
   out_7445322755045531081[136] = 0;
   out_7445322755045531081[137] = 0;
   out_7445322755045531081[138] = 0;
   out_7445322755045531081[139] = 0;
   out_7445322755045531081[140] = 0;
   out_7445322755045531081[141] = 0;
   out_7445322755045531081[142] = 0;
   out_7445322755045531081[143] = 0;
   out_7445322755045531081[144] = 0;
   out_7445322755045531081[145] = 0;
   out_7445322755045531081[146] = 0;
   out_7445322755045531081[147] = 0;
   out_7445322755045531081[148] = 0;
   out_7445322755045531081[149] = 0;
   out_7445322755045531081[150] = 0;
   out_7445322755045531081[151] = 0;
   out_7445322755045531081[152] = 1;
   out_7445322755045531081[153] = 0;
   out_7445322755045531081[154] = 0;
   out_7445322755045531081[155] = 0;
   out_7445322755045531081[156] = 0;
   out_7445322755045531081[157] = 0;
   out_7445322755045531081[158] = 0;
   out_7445322755045531081[159] = 0;
   out_7445322755045531081[160] = 0;
   out_7445322755045531081[161] = 0;
   out_7445322755045531081[162] = 0;
   out_7445322755045531081[163] = 0;
   out_7445322755045531081[164] = 0;
   out_7445322755045531081[165] = 0;
   out_7445322755045531081[166] = 0;
   out_7445322755045531081[167] = 0;
   out_7445322755045531081[168] = 0;
   out_7445322755045531081[169] = 0;
   out_7445322755045531081[170] = 0;
   out_7445322755045531081[171] = 1;
   out_7445322755045531081[172] = 0;
   out_7445322755045531081[173] = 0;
   out_7445322755045531081[174] = 0;
   out_7445322755045531081[175] = 0;
   out_7445322755045531081[176] = 0;
   out_7445322755045531081[177] = 0;
   out_7445322755045531081[178] = 0;
   out_7445322755045531081[179] = 0;
   out_7445322755045531081[180] = 0;
   out_7445322755045531081[181] = 0;
   out_7445322755045531081[182] = 0;
   out_7445322755045531081[183] = 0;
   out_7445322755045531081[184] = 0;
   out_7445322755045531081[185] = 0;
   out_7445322755045531081[186] = 0;
   out_7445322755045531081[187] = 0;
   out_7445322755045531081[188] = 0;
   out_7445322755045531081[189] = 0;
   out_7445322755045531081[190] = 1;
   out_7445322755045531081[191] = 0;
   out_7445322755045531081[192] = 0;
   out_7445322755045531081[193] = 0;
   out_7445322755045531081[194] = 0;
   out_7445322755045531081[195] = 0;
   out_7445322755045531081[196] = 0;
   out_7445322755045531081[197] = 0;
   out_7445322755045531081[198] = 0;
   out_7445322755045531081[199] = 0;
   out_7445322755045531081[200] = 0;
   out_7445322755045531081[201] = 0;
   out_7445322755045531081[202] = 0;
   out_7445322755045531081[203] = 0;
   out_7445322755045531081[204] = 0;
   out_7445322755045531081[205] = 0;
   out_7445322755045531081[206] = 0;
   out_7445322755045531081[207] = 0;
   out_7445322755045531081[208] = 0;
   out_7445322755045531081[209] = 1;
   out_7445322755045531081[210] = 0;
   out_7445322755045531081[211] = 0;
   out_7445322755045531081[212] = 0;
   out_7445322755045531081[213] = 0;
   out_7445322755045531081[214] = 0;
   out_7445322755045531081[215] = 0;
   out_7445322755045531081[216] = 0;
   out_7445322755045531081[217] = 0;
   out_7445322755045531081[218] = 0;
   out_7445322755045531081[219] = 0;
   out_7445322755045531081[220] = 0;
   out_7445322755045531081[221] = 0;
   out_7445322755045531081[222] = 0;
   out_7445322755045531081[223] = 0;
   out_7445322755045531081[224] = 0;
   out_7445322755045531081[225] = 0;
   out_7445322755045531081[226] = 0;
   out_7445322755045531081[227] = 0;
   out_7445322755045531081[228] = 1;
   out_7445322755045531081[229] = 0;
   out_7445322755045531081[230] = 0;
   out_7445322755045531081[231] = 0;
   out_7445322755045531081[232] = 0;
   out_7445322755045531081[233] = 0;
   out_7445322755045531081[234] = 0;
   out_7445322755045531081[235] = 0;
   out_7445322755045531081[236] = 0;
   out_7445322755045531081[237] = 0;
   out_7445322755045531081[238] = 0;
   out_7445322755045531081[239] = 0;
   out_7445322755045531081[240] = 0;
   out_7445322755045531081[241] = 0;
   out_7445322755045531081[242] = 0;
   out_7445322755045531081[243] = 0;
   out_7445322755045531081[244] = 0;
   out_7445322755045531081[245] = 0;
   out_7445322755045531081[246] = 0;
   out_7445322755045531081[247] = 1;
   out_7445322755045531081[248] = 0;
   out_7445322755045531081[249] = 0;
   out_7445322755045531081[250] = 0;
   out_7445322755045531081[251] = 0;
   out_7445322755045531081[252] = 0;
   out_7445322755045531081[253] = 0;
   out_7445322755045531081[254] = 0;
   out_7445322755045531081[255] = 0;
   out_7445322755045531081[256] = 0;
   out_7445322755045531081[257] = 0;
   out_7445322755045531081[258] = 0;
   out_7445322755045531081[259] = 0;
   out_7445322755045531081[260] = 0;
   out_7445322755045531081[261] = 0;
   out_7445322755045531081[262] = 0;
   out_7445322755045531081[263] = 0;
   out_7445322755045531081[264] = 0;
   out_7445322755045531081[265] = 0;
   out_7445322755045531081[266] = 1;
   out_7445322755045531081[267] = 0;
   out_7445322755045531081[268] = 0;
   out_7445322755045531081[269] = 0;
   out_7445322755045531081[270] = 0;
   out_7445322755045531081[271] = 0;
   out_7445322755045531081[272] = 0;
   out_7445322755045531081[273] = 0;
   out_7445322755045531081[274] = 0;
   out_7445322755045531081[275] = 0;
   out_7445322755045531081[276] = 0;
   out_7445322755045531081[277] = 0;
   out_7445322755045531081[278] = 0;
   out_7445322755045531081[279] = 0;
   out_7445322755045531081[280] = 0;
   out_7445322755045531081[281] = 0;
   out_7445322755045531081[282] = 0;
   out_7445322755045531081[283] = 0;
   out_7445322755045531081[284] = 0;
   out_7445322755045531081[285] = 1;
   out_7445322755045531081[286] = 0;
   out_7445322755045531081[287] = 0;
   out_7445322755045531081[288] = 0;
   out_7445322755045531081[289] = 0;
   out_7445322755045531081[290] = 0;
   out_7445322755045531081[291] = 0;
   out_7445322755045531081[292] = 0;
   out_7445322755045531081[293] = 0;
   out_7445322755045531081[294] = 0;
   out_7445322755045531081[295] = 0;
   out_7445322755045531081[296] = 0;
   out_7445322755045531081[297] = 0;
   out_7445322755045531081[298] = 0;
   out_7445322755045531081[299] = 0;
   out_7445322755045531081[300] = 0;
   out_7445322755045531081[301] = 0;
   out_7445322755045531081[302] = 0;
   out_7445322755045531081[303] = 0;
   out_7445322755045531081[304] = 1;
   out_7445322755045531081[305] = 0;
   out_7445322755045531081[306] = 0;
   out_7445322755045531081[307] = 0;
   out_7445322755045531081[308] = 0;
   out_7445322755045531081[309] = 0;
   out_7445322755045531081[310] = 0;
   out_7445322755045531081[311] = 0;
   out_7445322755045531081[312] = 0;
   out_7445322755045531081[313] = 0;
   out_7445322755045531081[314] = 0;
   out_7445322755045531081[315] = 0;
   out_7445322755045531081[316] = 0;
   out_7445322755045531081[317] = 0;
   out_7445322755045531081[318] = 0;
   out_7445322755045531081[319] = 0;
   out_7445322755045531081[320] = 0;
   out_7445322755045531081[321] = 0;
   out_7445322755045531081[322] = 0;
   out_7445322755045531081[323] = 1;
}
void h_4(double *state, double *unused, double *out_5900540074772401531) {
   out_5900540074772401531[0] = state[6] + state[9];
   out_5900540074772401531[1] = state[7] + state[10];
   out_5900540074772401531[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7984231595166509029) {
   out_7984231595166509029[0] = 0;
   out_7984231595166509029[1] = 0;
   out_7984231595166509029[2] = 0;
   out_7984231595166509029[3] = 0;
   out_7984231595166509029[4] = 0;
   out_7984231595166509029[5] = 0;
   out_7984231595166509029[6] = 1;
   out_7984231595166509029[7] = 0;
   out_7984231595166509029[8] = 0;
   out_7984231595166509029[9] = 1;
   out_7984231595166509029[10] = 0;
   out_7984231595166509029[11] = 0;
   out_7984231595166509029[12] = 0;
   out_7984231595166509029[13] = 0;
   out_7984231595166509029[14] = 0;
   out_7984231595166509029[15] = 0;
   out_7984231595166509029[16] = 0;
   out_7984231595166509029[17] = 0;
   out_7984231595166509029[18] = 0;
   out_7984231595166509029[19] = 0;
   out_7984231595166509029[20] = 0;
   out_7984231595166509029[21] = 0;
   out_7984231595166509029[22] = 0;
   out_7984231595166509029[23] = 0;
   out_7984231595166509029[24] = 0;
   out_7984231595166509029[25] = 1;
   out_7984231595166509029[26] = 0;
   out_7984231595166509029[27] = 0;
   out_7984231595166509029[28] = 1;
   out_7984231595166509029[29] = 0;
   out_7984231595166509029[30] = 0;
   out_7984231595166509029[31] = 0;
   out_7984231595166509029[32] = 0;
   out_7984231595166509029[33] = 0;
   out_7984231595166509029[34] = 0;
   out_7984231595166509029[35] = 0;
   out_7984231595166509029[36] = 0;
   out_7984231595166509029[37] = 0;
   out_7984231595166509029[38] = 0;
   out_7984231595166509029[39] = 0;
   out_7984231595166509029[40] = 0;
   out_7984231595166509029[41] = 0;
   out_7984231595166509029[42] = 0;
   out_7984231595166509029[43] = 0;
   out_7984231595166509029[44] = 1;
   out_7984231595166509029[45] = 0;
   out_7984231595166509029[46] = 0;
   out_7984231595166509029[47] = 1;
   out_7984231595166509029[48] = 0;
   out_7984231595166509029[49] = 0;
   out_7984231595166509029[50] = 0;
   out_7984231595166509029[51] = 0;
   out_7984231595166509029[52] = 0;
   out_7984231595166509029[53] = 0;
}
void h_10(double *state, double *unused, double *out_1581049242646868861) {
   out_1581049242646868861[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1581049242646868861[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1581049242646868861[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7103662432587704500) {
   out_7103662432587704500[0] = 0;
   out_7103662432587704500[1] = 9.8100000000000005*cos(state[1]);
   out_7103662432587704500[2] = 0;
   out_7103662432587704500[3] = 0;
   out_7103662432587704500[4] = -state[8];
   out_7103662432587704500[5] = state[7];
   out_7103662432587704500[6] = 0;
   out_7103662432587704500[7] = state[5];
   out_7103662432587704500[8] = -state[4];
   out_7103662432587704500[9] = 0;
   out_7103662432587704500[10] = 0;
   out_7103662432587704500[11] = 0;
   out_7103662432587704500[12] = 1;
   out_7103662432587704500[13] = 0;
   out_7103662432587704500[14] = 0;
   out_7103662432587704500[15] = 1;
   out_7103662432587704500[16] = 0;
   out_7103662432587704500[17] = 0;
   out_7103662432587704500[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7103662432587704500[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7103662432587704500[20] = 0;
   out_7103662432587704500[21] = state[8];
   out_7103662432587704500[22] = 0;
   out_7103662432587704500[23] = -state[6];
   out_7103662432587704500[24] = -state[5];
   out_7103662432587704500[25] = 0;
   out_7103662432587704500[26] = state[3];
   out_7103662432587704500[27] = 0;
   out_7103662432587704500[28] = 0;
   out_7103662432587704500[29] = 0;
   out_7103662432587704500[30] = 0;
   out_7103662432587704500[31] = 1;
   out_7103662432587704500[32] = 0;
   out_7103662432587704500[33] = 0;
   out_7103662432587704500[34] = 1;
   out_7103662432587704500[35] = 0;
   out_7103662432587704500[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7103662432587704500[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7103662432587704500[38] = 0;
   out_7103662432587704500[39] = -state[7];
   out_7103662432587704500[40] = state[6];
   out_7103662432587704500[41] = 0;
   out_7103662432587704500[42] = state[4];
   out_7103662432587704500[43] = -state[3];
   out_7103662432587704500[44] = 0;
   out_7103662432587704500[45] = 0;
   out_7103662432587704500[46] = 0;
   out_7103662432587704500[47] = 0;
   out_7103662432587704500[48] = 0;
   out_7103662432587704500[49] = 0;
   out_7103662432587704500[50] = 1;
   out_7103662432587704500[51] = 0;
   out_7103662432587704500[52] = 0;
   out_7103662432587704500[53] = 1;
}
void h_13(double *state, double *unused, double *out_4329138349760988154) {
   out_4329138349760988154[0] = state[3];
   out_4329138349760988154[1] = state[4];
   out_4329138349760988154[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7250238653210709786) {
   out_7250238653210709786[0] = 0;
   out_7250238653210709786[1] = 0;
   out_7250238653210709786[2] = 0;
   out_7250238653210709786[3] = 1;
   out_7250238653210709786[4] = 0;
   out_7250238653210709786[5] = 0;
   out_7250238653210709786[6] = 0;
   out_7250238653210709786[7] = 0;
   out_7250238653210709786[8] = 0;
   out_7250238653210709786[9] = 0;
   out_7250238653210709786[10] = 0;
   out_7250238653210709786[11] = 0;
   out_7250238653210709786[12] = 0;
   out_7250238653210709786[13] = 0;
   out_7250238653210709786[14] = 0;
   out_7250238653210709786[15] = 0;
   out_7250238653210709786[16] = 0;
   out_7250238653210709786[17] = 0;
   out_7250238653210709786[18] = 0;
   out_7250238653210709786[19] = 0;
   out_7250238653210709786[20] = 0;
   out_7250238653210709786[21] = 0;
   out_7250238653210709786[22] = 1;
   out_7250238653210709786[23] = 0;
   out_7250238653210709786[24] = 0;
   out_7250238653210709786[25] = 0;
   out_7250238653210709786[26] = 0;
   out_7250238653210709786[27] = 0;
   out_7250238653210709786[28] = 0;
   out_7250238653210709786[29] = 0;
   out_7250238653210709786[30] = 0;
   out_7250238653210709786[31] = 0;
   out_7250238653210709786[32] = 0;
   out_7250238653210709786[33] = 0;
   out_7250238653210709786[34] = 0;
   out_7250238653210709786[35] = 0;
   out_7250238653210709786[36] = 0;
   out_7250238653210709786[37] = 0;
   out_7250238653210709786[38] = 0;
   out_7250238653210709786[39] = 0;
   out_7250238653210709786[40] = 0;
   out_7250238653210709786[41] = 1;
   out_7250238653210709786[42] = 0;
   out_7250238653210709786[43] = 0;
   out_7250238653210709786[44] = 0;
   out_7250238653210709786[45] = 0;
   out_7250238653210709786[46] = 0;
   out_7250238653210709786[47] = 0;
   out_7250238653210709786[48] = 0;
   out_7250238653210709786[49] = 0;
   out_7250238653210709786[50] = 0;
   out_7250238653210709786[51] = 0;
   out_7250238653210709786[52] = 0;
   out_7250238653210709786[53] = 0;
}
void h_14(double *state, double *unused, double *out_4540324702778368531) {
   out_4540324702778368531[0] = state[6];
   out_4540324702778368531[1] = state[7];
   out_4540324702778368531[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6499271622203558058) {
   out_6499271622203558058[0] = 0;
   out_6499271622203558058[1] = 0;
   out_6499271622203558058[2] = 0;
   out_6499271622203558058[3] = 0;
   out_6499271622203558058[4] = 0;
   out_6499271622203558058[5] = 0;
   out_6499271622203558058[6] = 1;
   out_6499271622203558058[7] = 0;
   out_6499271622203558058[8] = 0;
   out_6499271622203558058[9] = 0;
   out_6499271622203558058[10] = 0;
   out_6499271622203558058[11] = 0;
   out_6499271622203558058[12] = 0;
   out_6499271622203558058[13] = 0;
   out_6499271622203558058[14] = 0;
   out_6499271622203558058[15] = 0;
   out_6499271622203558058[16] = 0;
   out_6499271622203558058[17] = 0;
   out_6499271622203558058[18] = 0;
   out_6499271622203558058[19] = 0;
   out_6499271622203558058[20] = 0;
   out_6499271622203558058[21] = 0;
   out_6499271622203558058[22] = 0;
   out_6499271622203558058[23] = 0;
   out_6499271622203558058[24] = 0;
   out_6499271622203558058[25] = 1;
   out_6499271622203558058[26] = 0;
   out_6499271622203558058[27] = 0;
   out_6499271622203558058[28] = 0;
   out_6499271622203558058[29] = 0;
   out_6499271622203558058[30] = 0;
   out_6499271622203558058[31] = 0;
   out_6499271622203558058[32] = 0;
   out_6499271622203558058[33] = 0;
   out_6499271622203558058[34] = 0;
   out_6499271622203558058[35] = 0;
   out_6499271622203558058[36] = 0;
   out_6499271622203558058[37] = 0;
   out_6499271622203558058[38] = 0;
   out_6499271622203558058[39] = 0;
   out_6499271622203558058[40] = 0;
   out_6499271622203558058[41] = 0;
   out_6499271622203558058[42] = 0;
   out_6499271622203558058[43] = 0;
   out_6499271622203558058[44] = 1;
   out_6499271622203558058[45] = 0;
   out_6499271622203558058[46] = 0;
   out_6499271622203558058[47] = 0;
   out_6499271622203558058[48] = 0;
   out_6499271622203558058[49] = 0;
   out_6499271622203558058[50] = 0;
   out_6499271622203558058[51] = 0;
   out_6499271622203558058[52] = 0;
   out_6499271622203558058[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_387547304249028087) {
  err_fun(nom_x, delta_x, out_387547304249028087);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7237327960985051970) {
  inv_err_fun(nom_x, true_x, out_7237327960985051970);
}
void pose_H_mod_fun(double *state, double *out_1518150812485221245) {
  H_mod_fun(state, out_1518150812485221245);
}
void pose_f_fun(double *state, double dt, double *out_1633491762729632217) {
  f_fun(state,  dt, out_1633491762729632217);
}
void pose_F_fun(double *state, double dt, double *out_7445322755045531081) {
  F_fun(state,  dt, out_7445322755045531081);
}
void pose_h_4(double *state, double *unused, double *out_5900540074772401531) {
  h_4(state, unused, out_5900540074772401531);
}
void pose_H_4(double *state, double *unused, double *out_7984231595166509029) {
  H_4(state, unused, out_7984231595166509029);
}
void pose_h_10(double *state, double *unused, double *out_1581049242646868861) {
  h_10(state, unused, out_1581049242646868861);
}
void pose_H_10(double *state, double *unused, double *out_7103662432587704500) {
  H_10(state, unused, out_7103662432587704500);
}
void pose_h_13(double *state, double *unused, double *out_4329138349760988154) {
  h_13(state, unused, out_4329138349760988154);
}
void pose_H_13(double *state, double *unused, double *out_7250238653210709786) {
  H_13(state, unused, out_7250238653210709786);
}
void pose_h_14(double *state, double *unused, double *out_4540324702778368531) {
  h_14(state, unused, out_4540324702778368531);
}
void pose_H_14(double *state, double *unused, double *out_6499271622203558058) {
  H_14(state, unused, out_6499271622203558058);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
