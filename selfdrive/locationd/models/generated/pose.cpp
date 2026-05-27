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
void err_fun(double *nom_x, double *delta_x, double *out_1678677657067247278) {
   out_1678677657067247278[0] = delta_x[0] + nom_x[0];
   out_1678677657067247278[1] = delta_x[1] + nom_x[1];
   out_1678677657067247278[2] = delta_x[2] + nom_x[2];
   out_1678677657067247278[3] = delta_x[3] + nom_x[3];
   out_1678677657067247278[4] = delta_x[4] + nom_x[4];
   out_1678677657067247278[5] = delta_x[5] + nom_x[5];
   out_1678677657067247278[6] = delta_x[6] + nom_x[6];
   out_1678677657067247278[7] = delta_x[7] + nom_x[7];
   out_1678677657067247278[8] = delta_x[8] + nom_x[8];
   out_1678677657067247278[9] = delta_x[9] + nom_x[9];
   out_1678677657067247278[10] = delta_x[10] + nom_x[10];
   out_1678677657067247278[11] = delta_x[11] + nom_x[11];
   out_1678677657067247278[12] = delta_x[12] + nom_x[12];
   out_1678677657067247278[13] = delta_x[13] + nom_x[13];
   out_1678677657067247278[14] = delta_x[14] + nom_x[14];
   out_1678677657067247278[15] = delta_x[15] + nom_x[15];
   out_1678677657067247278[16] = delta_x[16] + nom_x[16];
   out_1678677657067247278[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1406774922343404125) {
   out_1406774922343404125[0] = -nom_x[0] + true_x[0];
   out_1406774922343404125[1] = -nom_x[1] + true_x[1];
   out_1406774922343404125[2] = -nom_x[2] + true_x[2];
   out_1406774922343404125[3] = -nom_x[3] + true_x[3];
   out_1406774922343404125[4] = -nom_x[4] + true_x[4];
   out_1406774922343404125[5] = -nom_x[5] + true_x[5];
   out_1406774922343404125[6] = -nom_x[6] + true_x[6];
   out_1406774922343404125[7] = -nom_x[7] + true_x[7];
   out_1406774922343404125[8] = -nom_x[8] + true_x[8];
   out_1406774922343404125[9] = -nom_x[9] + true_x[9];
   out_1406774922343404125[10] = -nom_x[10] + true_x[10];
   out_1406774922343404125[11] = -nom_x[11] + true_x[11];
   out_1406774922343404125[12] = -nom_x[12] + true_x[12];
   out_1406774922343404125[13] = -nom_x[13] + true_x[13];
   out_1406774922343404125[14] = -nom_x[14] + true_x[14];
   out_1406774922343404125[15] = -nom_x[15] + true_x[15];
   out_1406774922343404125[16] = -nom_x[16] + true_x[16];
   out_1406774922343404125[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8585248171069107514) {
   out_8585248171069107514[0] = 1.0;
   out_8585248171069107514[1] = 0.0;
   out_8585248171069107514[2] = 0.0;
   out_8585248171069107514[3] = 0.0;
   out_8585248171069107514[4] = 0.0;
   out_8585248171069107514[5] = 0.0;
   out_8585248171069107514[6] = 0.0;
   out_8585248171069107514[7] = 0.0;
   out_8585248171069107514[8] = 0.0;
   out_8585248171069107514[9] = 0.0;
   out_8585248171069107514[10] = 0.0;
   out_8585248171069107514[11] = 0.0;
   out_8585248171069107514[12] = 0.0;
   out_8585248171069107514[13] = 0.0;
   out_8585248171069107514[14] = 0.0;
   out_8585248171069107514[15] = 0.0;
   out_8585248171069107514[16] = 0.0;
   out_8585248171069107514[17] = 0.0;
   out_8585248171069107514[18] = 0.0;
   out_8585248171069107514[19] = 1.0;
   out_8585248171069107514[20] = 0.0;
   out_8585248171069107514[21] = 0.0;
   out_8585248171069107514[22] = 0.0;
   out_8585248171069107514[23] = 0.0;
   out_8585248171069107514[24] = 0.0;
   out_8585248171069107514[25] = 0.0;
   out_8585248171069107514[26] = 0.0;
   out_8585248171069107514[27] = 0.0;
   out_8585248171069107514[28] = 0.0;
   out_8585248171069107514[29] = 0.0;
   out_8585248171069107514[30] = 0.0;
   out_8585248171069107514[31] = 0.0;
   out_8585248171069107514[32] = 0.0;
   out_8585248171069107514[33] = 0.0;
   out_8585248171069107514[34] = 0.0;
   out_8585248171069107514[35] = 0.0;
   out_8585248171069107514[36] = 0.0;
   out_8585248171069107514[37] = 0.0;
   out_8585248171069107514[38] = 1.0;
   out_8585248171069107514[39] = 0.0;
   out_8585248171069107514[40] = 0.0;
   out_8585248171069107514[41] = 0.0;
   out_8585248171069107514[42] = 0.0;
   out_8585248171069107514[43] = 0.0;
   out_8585248171069107514[44] = 0.0;
   out_8585248171069107514[45] = 0.0;
   out_8585248171069107514[46] = 0.0;
   out_8585248171069107514[47] = 0.0;
   out_8585248171069107514[48] = 0.0;
   out_8585248171069107514[49] = 0.0;
   out_8585248171069107514[50] = 0.0;
   out_8585248171069107514[51] = 0.0;
   out_8585248171069107514[52] = 0.0;
   out_8585248171069107514[53] = 0.0;
   out_8585248171069107514[54] = 0.0;
   out_8585248171069107514[55] = 0.0;
   out_8585248171069107514[56] = 0.0;
   out_8585248171069107514[57] = 1.0;
   out_8585248171069107514[58] = 0.0;
   out_8585248171069107514[59] = 0.0;
   out_8585248171069107514[60] = 0.0;
   out_8585248171069107514[61] = 0.0;
   out_8585248171069107514[62] = 0.0;
   out_8585248171069107514[63] = 0.0;
   out_8585248171069107514[64] = 0.0;
   out_8585248171069107514[65] = 0.0;
   out_8585248171069107514[66] = 0.0;
   out_8585248171069107514[67] = 0.0;
   out_8585248171069107514[68] = 0.0;
   out_8585248171069107514[69] = 0.0;
   out_8585248171069107514[70] = 0.0;
   out_8585248171069107514[71] = 0.0;
   out_8585248171069107514[72] = 0.0;
   out_8585248171069107514[73] = 0.0;
   out_8585248171069107514[74] = 0.0;
   out_8585248171069107514[75] = 0.0;
   out_8585248171069107514[76] = 1.0;
   out_8585248171069107514[77] = 0.0;
   out_8585248171069107514[78] = 0.0;
   out_8585248171069107514[79] = 0.0;
   out_8585248171069107514[80] = 0.0;
   out_8585248171069107514[81] = 0.0;
   out_8585248171069107514[82] = 0.0;
   out_8585248171069107514[83] = 0.0;
   out_8585248171069107514[84] = 0.0;
   out_8585248171069107514[85] = 0.0;
   out_8585248171069107514[86] = 0.0;
   out_8585248171069107514[87] = 0.0;
   out_8585248171069107514[88] = 0.0;
   out_8585248171069107514[89] = 0.0;
   out_8585248171069107514[90] = 0.0;
   out_8585248171069107514[91] = 0.0;
   out_8585248171069107514[92] = 0.0;
   out_8585248171069107514[93] = 0.0;
   out_8585248171069107514[94] = 0.0;
   out_8585248171069107514[95] = 1.0;
   out_8585248171069107514[96] = 0.0;
   out_8585248171069107514[97] = 0.0;
   out_8585248171069107514[98] = 0.0;
   out_8585248171069107514[99] = 0.0;
   out_8585248171069107514[100] = 0.0;
   out_8585248171069107514[101] = 0.0;
   out_8585248171069107514[102] = 0.0;
   out_8585248171069107514[103] = 0.0;
   out_8585248171069107514[104] = 0.0;
   out_8585248171069107514[105] = 0.0;
   out_8585248171069107514[106] = 0.0;
   out_8585248171069107514[107] = 0.0;
   out_8585248171069107514[108] = 0.0;
   out_8585248171069107514[109] = 0.0;
   out_8585248171069107514[110] = 0.0;
   out_8585248171069107514[111] = 0.0;
   out_8585248171069107514[112] = 0.0;
   out_8585248171069107514[113] = 0.0;
   out_8585248171069107514[114] = 1.0;
   out_8585248171069107514[115] = 0.0;
   out_8585248171069107514[116] = 0.0;
   out_8585248171069107514[117] = 0.0;
   out_8585248171069107514[118] = 0.0;
   out_8585248171069107514[119] = 0.0;
   out_8585248171069107514[120] = 0.0;
   out_8585248171069107514[121] = 0.0;
   out_8585248171069107514[122] = 0.0;
   out_8585248171069107514[123] = 0.0;
   out_8585248171069107514[124] = 0.0;
   out_8585248171069107514[125] = 0.0;
   out_8585248171069107514[126] = 0.0;
   out_8585248171069107514[127] = 0.0;
   out_8585248171069107514[128] = 0.0;
   out_8585248171069107514[129] = 0.0;
   out_8585248171069107514[130] = 0.0;
   out_8585248171069107514[131] = 0.0;
   out_8585248171069107514[132] = 0.0;
   out_8585248171069107514[133] = 1.0;
   out_8585248171069107514[134] = 0.0;
   out_8585248171069107514[135] = 0.0;
   out_8585248171069107514[136] = 0.0;
   out_8585248171069107514[137] = 0.0;
   out_8585248171069107514[138] = 0.0;
   out_8585248171069107514[139] = 0.0;
   out_8585248171069107514[140] = 0.0;
   out_8585248171069107514[141] = 0.0;
   out_8585248171069107514[142] = 0.0;
   out_8585248171069107514[143] = 0.0;
   out_8585248171069107514[144] = 0.0;
   out_8585248171069107514[145] = 0.0;
   out_8585248171069107514[146] = 0.0;
   out_8585248171069107514[147] = 0.0;
   out_8585248171069107514[148] = 0.0;
   out_8585248171069107514[149] = 0.0;
   out_8585248171069107514[150] = 0.0;
   out_8585248171069107514[151] = 0.0;
   out_8585248171069107514[152] = 1.0;
   out_8585248171069107514[153] = 0.0;
   out_8585248171069107514[154] = 0.0;
   out_8585248171069107514[155] = 0.0;
   out_8585248171069107514[156] = 0.0;
   out_8585248171069107514[157] = 0.0;
   out_8585248171069107514[158] = 0.0;
   out_8585248171069107514[159] = 0.0;
   out_8585248171069107514[160] = 0.0;
   out_8585248171069107514[161] = 0.0;
   out_8585248171069107514[162] = 0.0;
   out_8585248171069107514[163] = 0.0;
   out_8585248171069107514[164] = 0.0;
   out_8585248171069107514[165] = 0.0;
   out_8585248171069107514[166] = 0.0;
   out_8585248171069107514[167] = 0.0;
   out_8585248171069107514[168] = 0.0;
   out_8585248171069107514[169] = 0.0;
   out_8585248171069107514[170] = 0.0;
   out_8585248171069107514[171] = 1.0;
   out_8585248171069107514[172] = 0.0;
   out_8585248171069107514[173] = 0.0;
   out_8585248171069107514[174] = 0.0;
   out_8585248171069107514[175] = 0.0;
   out_8585248171069107514[176] = 0.0;
   out_8585248171069107514[177] = 0.0;
   out_8585248171069107514[178] = 0.0;
   out_8585248171069107514[179] = 0.0;
   out_8585248171069107514[180] = 0.0;
   out_8585248171069107514[181] = 0.0;
   out_8585248171069107514[182] = 0.0;
   out_8585248171069107514[183] = 0.0;
   out_8585248171069107514[184] = 0.0;
   out_8585248171069107514[185] = 0.0;
   out_8585248171069107514[186] = 0.0;
   out_8585248171069107514[187] = 0.0;
   out_8585248171069107514[188] = 0.0;
   out_8585248171069107514[189] = 0.0;
   out_8585248171069107514[190] = 1.0;
   out_8585248171069107514[191] = 0.0;
   out_8585248171069107514[192] = 0.0;
   out_8585248171069107514[193] = 0.0;
   out_8585248171069107514[194] = 0.0;
   out_8585248171069107514[195] = 0.0;
   out_8585248171069107514[196] = 0.0;
   out_8585248171069107514[197] = 0.0;
   out_8585248171069107514[198] = 0.0;
   out_8585248171069107514[199] = 0.0;
   out_8585248171069107514[200] = 0.0;
   out_8585248171069107514[201] = 0.0;
   out_8585248171069107514[202] = 0.0;
   out_8585248171069107514[203] = 0.0;
   out_8585248171069107514[204] = 0.0;
   out_8585248171069107514[205] = 0.0;
   out_8585248171069107514[206] = 0.0;
   out_8585248171069107514[207] = 0.0;
   out_8585248171069107514[208] = 0.0;
   out_8585248171069107514[209] = 1.0;
   out_8585248171069107514[210] = 0.0;
   out_8585248171069107514[211] = 0.0;
   out_8585248171069107514[212] = 0.0;
   out_8585248171069107514[213] = 0.0;
   out_8585248171069107514[214] = 0.0;
   out_8585248171069107514[215] = 0.0;
   out_8585248171069107514[216] = 0.0;
   out_8585248171069107514[217] = 0.0;
   out_8585248171069107514[218] = 0.0;
   out_8585248171069107514[219] = 0.0;
   out_8585248171069107514[220] = 0.0;
   out_8585248171069107514[221] = 0.0;
   out_8585248171069107514[222] = 0.0;
   out_8585248171069107514[223] = 0.0;
   out_8585248171069107514[224] = 0.0;
   out_8585248171069107514[225] = 0.0;
   out_8585248171069107514[226] = 0.0;
   out_8585248171069107514[227] = 0.0;
   out_8585248171069107514[228] = 1.0;
   out_8585248171069107514[229] = 0.0;
   out_8585248171069107514[230] = 0.0;
   out_8585248171069107514[231] = 0.0;
   out_8585248171069107514[232] = 0.0;
   out_8585248171069107514[233] = 0.0;
   out_8585248171069107514[234] = 0.0;
   out_8585248171069107514[235] = 0.0;
   out_8585248171069107514[236] = 0.0;
   out_8585248171069107514[237] = 0.0;
   out_8585248171069107514[238] = 0.0;
   out_8585248171069107514[239] = 0.0;
   out_8585248171069107514[240] = 0.0;
   out_8585248171069107514[241] = 0.0;
   out_8585248171069107514[242] = 0.0;
   out_8585248171069107514[243] = 0.0;
   out_8585248171069107514[244] = 0.0;
   out_8585248171069107514[245] = 0.0;
   out_8585248171069107514[246] = 0.0;
   out_8585248171069107514[247] = 1.0;
   out_8585248171069107514[248] = 0.0;
   out_8585248171069107514[249] = 0.0;
   out_8585248171069107514[250] = 0.0;
   out_8585248171069107514[251] = 0.0;
   out_8585248171069107514[252] = 0.0;
   out_8585248171069107514[253] = 0.0;
   out_8585248171069107514[254] = 0.0;
   out_8585248171069107514[255] = 0.0;
   out_8585248171069107514[256] = 0.0;
   out_8585248171069107514[257] = 0.0;
   out_8585248171069107514[258] = 0.0;
   out_8585248171069107514[259] = 0.0;
   out_8585248171069107514[260] = 0.0;
   out_8585248171069107514[261] = 0.0;
   out_8585248171069107514[262] = 0.0;
   out_8585248171069107514[263] = 0.0;
   out_8585248171069107514[264] = 0.0;
   out_8585248171069107514[265] = 0.0;
   out_8585248171069107514[266] = 1.0;
   out_8585248171069107514[267] = 0.0;
   out_8585248171069107514[268] = 0.0;
   out_8585248171069107514[269] = 0.0;
   out_8585248171069107514[270] = 0.0;
   out_8585248171069107514[271] = 0.0;
   out_8585248171069107514[272] = 0.0;
   out_8585248171069107514[273] = 0.0;
   out_8585248171069107514[274] = 0.0;
   out_8585248171069107514[275] = 0.0;
   out_8585248171069107514[276] = 0.0;
   out_8585248171069107514[277] = 0.0;
   out_8585248171069107514[278] = 0.0;
   out_8585248171069107514[279] = 0.0;
   out_8585248171069107514[280] = 0.0;
   out_8585248171069107514[281] = 0.0;
   out_8585248171069107514[282] = 0.0;
   out_8585248171069107514[283] = 0.0;
   out_8585248171069107514[284] = 0.0;
   out_8585248171069107514[285] = 1.0;
   out_8585248171069107514[286] = 0.0;
   out_8585248171069107514[287] = 0.0;
   out_8585248171069107514[288] = 0.0;
   out_8585248171069107514[289] = 0.0;
   out_8585248171069107514[290] = 0.0;
   out_8585248171069107514[291] = 0.0;
   out_8585248171069107514[292] = 0.0;
   out_8585248171069107514[293] = 0.0;
   out_8585248171069107514[294] = 0.0;
   out_8585248171069107514[295] = 0.0;
   out_8585248171069107514[296] = 0.0;
   out_8585248171069107514[297] = 0.0;
   out_8585248171069107514[298] = 0.0;
   out_8585248171069107514[299] = 0.0;
   out_8585248171069107514[300] = 0.0;
   out_8585248171069107514[301] = 0.0;
   out_8585248171069107514[302] = 0.0;
   out_8585248171069107514[303] = 0.0;
   out_8585248171069107514[304] = 1.0;
   out_8585248171069107514[305] = 0.0;
   out_8585248171069107514[306] = 0.0;
   out_8585248171069107514[307] = 0.0;
   out_8585248171069107514[308] = 0.0;
   out_8585248171069107514[309] = 0.0;
   out_8585248171069107514[310] = 0.0;
   out_8585248171069107514[311] = 0.0;
   out_8585248171069107514[312] = 0.0;
   out_8585248171069107514[313] = 0.0;
   out_8585248171069107514[314] = 0.0;
   out_8585248171069107514[315] = 0.0;
   out_8585248171069107514[316] = 0.0;
   out_8585248171069107514[317] = 0.0;
   out_8585248171069107514[318] = 0.0;
   out_8585248171069107514[319] = 0.0;
   out_8585248171069107514[320] = 0.0;
   out_8585248171069107514[321] = 0.0;
   out_8585248171069107514[322] = 0.0;
   out_8585248171069107514[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7025233619786589722) {
   out_7025233619786589722[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7025233619786589722[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7025233619786589722[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7025233619786589722[3] = dt*state[12] + state[3];
   out_7025233619786589722[4] = dt*state[13] + state[4];
   out_7025233619786589722[5] = dt*state[14] + state[5];
   out_7025233619786589722[6] = state[6];
   out_7025233619786589722[7] = state[7];
   out_7025233619786589722[8] = state[8];
   out_7025233619786589722[9] = state[9];
   out_7025233619786589722[10] = state[10];
   out_7025233619786589722[11] = state[11];
   out_7025233619786589722[12] = state[12];
   out_7025233619786589722[13] = state[13];
   out_7025233619786589722[14] = state[14];
   out_7025233619786589722[15] = state[15];
   out_7025233619786589722[16] = state[16];
   out_7025233619786589722[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5989987150238344461) {
   out_5989987150238344461[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5989987150238344461[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5989987150238344461[2] = 0;
   out_5989987150238344461[3] = 0;
   out_5989987150238344461[4] = 0;
   out_5989987150238344461[5] = 0;
   out_5989987150238344461[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5989987150238344461[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5989987150238344461[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5989987150238344461[9] = 0;
   out_5989987150238344461[10] = 0;
   out_5989987150238344461[11] = 0;
   out_5989987150238344461[12] = 0;
   out_5989987150238344461[13] = 0;
   out_5989987150238344461[14] = 0;
   out_5989987150238344461[15] = 0;
   out_5989987150238344461[16] = 0;
   out_5989987150238344461[17] = 0;
   out_5989987150238344461[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5989987150238344461[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5989987150238344461[20] = 0;
   out_5989987150238344461[21] = 0;
   out_5989987150238344461[22] = 0;
   out_5989987150238344461[23] = 0;
   out_5989987150238344461[24] = 0;
   out_5989987150238344461[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5989987150238344461[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5989987150238344461[27] = 0;
   out_5989987150238344461[28] = 0;
   out_5989987150238344461[29] = 0;
   out_5989987150238344461[30] = 0;
   out_5989987150238344461[31] = 0;
   out_5989987150238344461[32] = 0;
   out_5989987150238344461[33] = 0;
   out_5989987150238344461[34] = 0;
   out_5989987150238344461[35] = 0;
   out_5989987150238344461[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5989987150238344461[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5989987150238344461[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5989987150238344461[39] = 0;
   out_5989987150238344461[40] = 0;
   out_5989987150238344461[41] = 0;
   out_5989987150238344461[42] = 0;
   out_5989987150238344461[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5989987150238344461[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5989987150238344461[45] = 0;
   out_5989987150238344461[46] = 0;
   out_5989987150238344461[47] = 0;
   out_5989987150238344461[48] = 0;
   out_5989987150238344461[49] = 0;
   out_5989987150238344461[50] = 0;
   out_5989987150238344461[51] = 0;
   out_5989987150238344461[52] = 0;
   out_5989987150238344461[53] = 0;
   out_5989987150238344461[54] = 0;
   out_5989987150238344461[55] = 0;
   out_5989987150238344461[56] = 0;
   out_5989987150238344461[57] = 1;
   out_5989987150238344461[58] = 0;
   out_5989987150238344461[59] = 0;
   out_5989987150238344461[60] = 0;
   out_5989987150238344461[61] = 0;
   out_5989987150238344461[62] = 0;
   out_5989987150238344461[63] = 0;
   out_5989987150238344461[64] = 0;
   out_5989987150238344461[65] = 0;
   out_5989987150238344461[66] = dt;
   out_5989987150238344461[67] = 0;
   out_5989987150238344461[68] = 0;
   out_5989987150238344461[69] = 0;
   out_5989987150238344461[70] = 0;
   out_5989987150238344461[71] = 0;
   out_5989987150238344461[72] = 0;
   out_5989987150238344461[73] = 0;
   out_5989987150238344461[74] = 0;
   out_5989987150238344461[75] = 0;
   out_5989987150238344461[76] = 1;
   out_5989987150238344461[77] = 0;
   out_5989987150238344461[78] = 0;
   out_5989987150238344461[79] = 0;
   out_5989987150238344461[80] = 0;
   out_5989987150238344461[81] = 0;
   out_5989987150238344461[82] = 0;
   out_5989987150238344461[83] = 0;
   out_5989987150238344461[84] = 0;
   out_5989987150238344461[85] = dt;
   out_5989987150238344461[86] = 0;
   out_5989987150238344461[87] = 0;
   out_5989987150238344461[88] = 0;
   out_5989987150238344461[89] = 0;
   out_5989987150238344461[90] = 0;
   out_5989987150238344461[91] = 0;
   out_5989987150238344461[92] = 0;
   out_5989987150238344461[93] = 0;
   out_5989987150238344461[94] = 0;
   out_5989987150238344461[95] = 1;
   out_5989987150238344461[96] = 0;
   out_5989987150238344461[97] = 0;
   out_5989987150238344461[98] = 0;
   out_5989987150238344461[99] = 0;
   out_5989987150238344461[100] = 0;
   out_5989987150238344461[101] = 0;
   out_5989987150238344461[102] = 0;
   out_5989987150238344461[103] = 0;
   out_5989987150238344461[104] = dt;
   out_5989987150238344461[105] = 0;
   out_5989987150238344461[106] = 0;
   out_5989987150238344461[107] = 0;
   out_5989987150238344461[108] = 0;
   out_5989987150238344461[109] = 0;
   out_5989987150238344461[110] = 0;
   out_5989987150238344461[111] = 0;
   out_5989987150238344461[112] = 0;
   out_5989987150238344461[113] = 0;
   out_5989987150238344461[114] = 1;
   out_5989987150238344461[115] = 0;
   out_5989987150238344461[116] = 0;
   out_5989987150238344461[117] = 0;
   out_5989987150238344461[118] = 0;
   out_5989987150238344461[119] = 0;
   out_5989987150238344461[120] = 0;
   out_5989987150238344461[121] = 0;
   out_5989987150238344461[122] = 0;
   out_5989987150238344461[123] = 0;
   out_5989987150238344461[124] = 0;
   out_5989987150238344461[125] = 0;
   out_5989987150238344461[126] = 0;
   out_5989987150238344461[127] = 0;
   out_5989987150238344461[128] = 0;
   out_5989987150238344461[129] = 0;
   out_5989987150238344461[130] = 0;
   out_5989987150238344461[131] = 0;
   out_5989987150238344461[132] = 0;
   out_5989987150238344461[133] = 1;
   out_5989987150238344461[134] = 0;
   out_5989987150238344461[135] = 0;
   out_5989987150238344461[136] = 0;
   out_5989987150238344461[137] = 0;
   out_5989987150238344461[138] = 0;
   out_5989987150238344461[139] = 0;
   out_5989987150238344461[140] = 0;
   out_5989987150238344461[141] = 0;
   out_5989987150238344461[142] = 0;
   out_5989987150238344461[143] = 0;
   out_5989987150238344461[144] = 0;
   out_5989987150238344461[145] = 0;
   out_5989987150238344461[146] = 0;
   out_5989987150238344461[147] = 0;
   out_5989987150238344461[148] = 0;
   out_5989987150238344461[149] = 0;
   out_5989987150238344461[150] = 0;
   out_5989987150238344461[151] = 0;
   out_5989987150238344461[152] = 1;
   out_5989987150238344461[153] = 0;
   out_5989987150238344461[154] = 0;
   out_5989987150238344461[155] = 0;
   out_5989987150238344461[156] = 0;
   out_5989987150238344461[157] = 0;
   out_5989987150238344461[158] = 0;
   out_5989987150238344461[159] = 0;
   out_5989987150238344461[160] = 0;
   out_5989987150238344461[161] = 0;
   out_5989987150238344461[162] = 0;
   out_5989987150238344461[163] = 0;
   out_5989987150238344461[164] = 0;
   out_5989987150238344461[165] = 0;
   out_5989987150238344461[166] = 0;
   out_5989987150238344461[167] = 0;
   out_5989987150238344461[168] = 0;
   out_5989987150238344461[169] = 0;
   out_5989987150238344461[170] = 0;
   out_5989987150238344461[171] = 1;
   out_5989987150238344461[172] = 0;
   out_5989987150238344461[173] = 0;
   out_5989987150238344461[174] = 0;
   out_5989987150238344461[175] = 0;
   out_5989987150238344461[176] = 0;
   out_5989987150238344461[177] = 0;
   out_5989987150238344461[178] = 0;
   out_5989987150238344461[179] = 0;
   out_5989987150238344461[180] = 0;
   out_5989987150238344461[181] = 0;
   out_5989987150238344461[182] = 0;
   out_5989987150238344461[183] = 0;
   out_5989987150238344461[184] = 0;
   out_5989987150238344461[185] = 0;
   out_5989987150238344461[186] = 0;
   out_5989987150238344461[187] = 0;
   out_5989987150238344461[188] = 0;
   out_5989987150238344461[189] = 0;
   out_5989987150238344461[190] = 1;
   out_5989987150238344461[191] = 0;
   out_5989987150238344461[192] = 0;
   out_5989987150238344461[193] = 0;
   out_5989987150238344461[194] = 0;
   out_5989987150238344461[195] = 0;
   out_5989987150238344461[196] = 0;
   out_5989987150238344461[197] = 0;
   out_5989987150238344461[198] = 0;
   out_5989987150238344461[199] = 0;
   out_5989987150238344461[200] = 0;
   out_5989987150238344461[201] = 0;
   out_5989987150238344461[202] = 0;
   out_5989987150238344461[203] = 0;
   out_5989987150238344461[204] = 0;
   out_5989987150238344461[205] = 0;
   out_5989987150238344461[206] = 0;
   out_5989987150238344461[207] = 0;
   out_5989987150238344461[208] = 0;
   out_5989987150238344461[209] = 1;
   out_5989987150238344461[210] = 0;
   out_5989987150238344461[211] = 0;
   out_5989987150238344461[212] = 0;
   out_5989987150238344461[213] = 0;
   out_5989987150238344461[214] = 0;
   out_5989987150238344461[215] = 0;
   out_5989987150238344461[216] = 0;
   out_5989987150238344461[217] = 0;
   out_5989987150238344461[218] = 0;
   out_5989987150238344461[219] = 0;
   out_5989987150238344461[220] = 0;
   out_5989987150238344461[221] = 0;
   out_5989987150238344461[222] = 0;
   out_5989987150238344461[223] = 0;
   out_5989987150238344461[224] = 0;
   out_5989987150238344461[225] = 0;
   out_5989987150238344461[226] = 0;
   out_5989987150238344461[227] = 0;
   out_5989987150238344461[228] = 1;
   out_5989987150238344461[229] = 0;
   out_5989987150238344461[230] = 0;
   out_5989987150238344461[231] = 0;
   out_5989987150238344461[232] = 0;
   out_5989987150238344461[233] = 0;
   out_5989987150238344461[234] = 0;
   out_5989987150238344461[235] = 0;
   out_5989987150238344461[236] = 0;
   out_5989987150238344461[237] = 0;
   out_5989987150238344461[238] = 0;
   out_5989987150238344461[239] = 0;
   out_5989987150238344461[240] = 0;
   out_5989987150238344461[241] = 0;
   out_5989987150238344461[242] = 0;
   out_5989987150238344461[243] = 0;
   out_5989987150238344461[244] = 0;
   out_5989987150238344461[245] = 0;
   out_5989987150238344461[246] = 0;
   out_5989987150238344461[247] = 1;
   out_5989987150238344461[248] = 0;
   out_5989987150238344461[249] = 0;
   out_5989987150238344461[250] = 0;
   out_5989987150238344461[251] = 0;
   out_5989987150238344461[252] = 0;
   out_5989987150238344461[253] = 0;
   out_5989987150238344461[254] = 0;
   out_5989987150238344461[255] = 0;
   out_5989987150238344461[256] = 0;
   out_5989987150238344461[257] = 0;
   out_5989987150238344461[258] = 0;
   out_5989987150238344461[259] = 0;
   out_5989987150238344461[260] = 0;
   out_5989987150238344461[261] = 0;
   out_5989987150238344461[262] = 0;
   out_5989987150238344461[263] = 0;
   out_5989987150238344461[264] = 0;
   out_5989987150238344461[265] = 0;
   out_5989987150238344461[266] = 1;
   out_5989987150238344461[267] = 0;
   out_5989987150238344461[268] = 0;
   out_5989987150238344461[269] = 0;
   out_5989987150238344461[270] = 0;
   out_5989987150238344461[271] = 0;
   out_5989987150238344461[272] = 0;
   out_5989987150238344461[273] = 0;
   out_5989987150238344461[274] = 0;
   out_5989987150238344461[275] = 0;
   out_5989987150238344461[276] = 0;
   out_5989987150238344461[277] = 0;
   out_5989987150238344461[278] = 0;
   out_5989987150238344461[279] = 0;
   out_5989987150238344461[280] = 0;
   out_5989987150238344461[281] = 0;
   out_5989987150238344461[282] = 0;
   out_5989987150238344461[283] = 0;
   out_5989987150238344461[284] = 0;
   out_5989987150238344461[285] = 1;
   out_5989987150238344461[286] = 0;
   out_5989987150238344461[287] = 0;
   out_5989987150238344461[288] = 0;
   out_5989987150238344461[289] = 0;
   out_5989987150238344461[290] = 0;
   out_5989987150238344461[291] = 0;
   out_5989987150238344461[292] = 0;
   out_5989987150238344461[293] = 0;
   out_5989987150238344461[294] = 0;
   out_5989987150238344461[295] = 0;
   out_5989987150238344461[296] = 0;
   out_5989987150238344461[297] = 0;
   out_5989987150238344461[298] = 0;
   out_5989987150238344461[299] = 0;
   out_5989987150238344461[300] = 0;
   out_5989987150238344461[301] = 0;
   out_5989987150238344461[302] = 0;
   out_5989987150238344461[303] = 0;
   out_5989987150238344461[304] = 1;
   out_5989987150238344461[305] = 0;
   out_5989987150238344461[306] = 0;
   out_5989987150238344461[307] = 0;
   out_5989987150238344461[308] = 0;
   out_5989987150238344461[309] = 0;
   out_5989987150238344461[310] = 0;
   out_5989987150238344461[311] = 0;
   out_5989987150238344461[312] = 0;
   out_5989987150238344461[313] = 0;
   out_5989987150238344461[314] = 0;
   out_5989987150238344461[315] = 0;
   out_5989987150238344461[316] = 0;
   out_5989987150238344461[317] = 0;
   out_5989987150238344461[318] = 0;
   out_5989987150238344461[319] = 0;
   out_5989987150238344461[320] = 0;
   out_5989987150238344461[321] = 0;
   out_5989987150238344461[322] = 0;
   out_5989987150238344461[323] = 1;
}
void h_4(double *state, double *unused, double *out_5416308601503649612) {
   out_5416308601503649612[0] = state[6] + state[9];
   out_5416308601503649612[1] = state[7] + state[10];
   out_5416308601503649612[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6661086001538974078) {
   out_6661086001538974078[0] = 0;
   out_6661086001538974078[1] = 0;
   out_6661086001538974078[2] = 0;
   out_6661086001538974078[3] = 0;
   out_6661086001538974078[4] = 0;
   out_6661086001538974078[5] = 0;
   out_6661086001538974078[6] = 1;
   out_6661086001538974078[7] = 0;
   out_6661086001538974078[8] = 0;
   out_6661086001538974078[9] = 1;
   out_6661086001538974078[10] = 0;
   out_6661086001538974078[11] = 0;
   out_6661086001538974078[12] = 0;
   out_6661086001538974078[13] = 0;
   out_6661086001538974078[14] = 0;
   out_6661086001538974078[15] = 0;
   out_6661086001538974078[16] = 0;
   out_6661086001538974078[17] = 0;
   out_6661086001538974078[18] = 0;
   out_6661086001538974078[19] = 0;
   out_6661086001538974078[20] = 0;
   out_6661086001538974078[21] = 0;
   out_6661086001538974078[22] = 0;
   out_6661086001538974078[23] = 0;
   out_6661086001538974078[24] = 0;
   out_6661086001538974078[25] = 1;
   out_6661086001538974078[26] = 0;
   out_6661086001538974078[27] = 0;
   out_6661086001538974078[28] = 1;
   out_6661086001538974078[29] = 0;
   out_6661086001538974078[30] = 0;
   out_6661086001538974078[31] = 0;
   out_6661086001538974078[32] = 0;
   out_6661086001538974078[33] = 0;
   out_6661086001538974078[34] = 0;
   out_6661086001538974078[35] = 0;
   out_6661086001538974078[36] = 0;
   out_6661086001538974078[37] = 0;
   out_6661086001538974078[38] = 0;
   out_6661086001538974078[39] = 0;
   out_6661086001538974078[40] = 0;
   out_6661086001538974078[41] = 0;
   out_6661086001538974078[42] = 0;
   out_6661086001538974078[43] = 0;
   out_6661086001538974078[44] = 1;
   out_6661086001538974078[45] = 0;
   out_6661086001538974078[46] = 0;
   out_6661086001538974078[47] = 1;
   out_6661086001538974078[48] = 0;
   out_6661086001538974078[49] = 0;
   out_6661086001538974078[50] = 0;
   out_6661086001538974078[51] = 0;
   out_6661086001538974078[52] = 0;
   out_6661086001538974078[53] = 0;
}
void h_10(double *state, double *unused, double *out_5402550001453747401) {
   out_5402550001453747401[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5402550001453747401[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5402550001453747401[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1285395886965427856) {
   out_1285395886965427856[0] = 0;
   out_1285395886965427856[1] = 9.8100000000000005*cos(state[1]);
   out_1285395886965427856[2] = 0;
   out_1285395886965427856[3] = 0;
   out_1285395886965427856[4] = -state[8];
   out_1285395886965427856[5] = state[7];
   out_1285395886965427856[6] = 0;
   out_1285395886965427856[7] = state[5];
   out_1285395886965427856[8] = -state[4];
   out_1285395886965427856[9] = 0;
   out_1285395886965427856[10] = 0;
   out_1285395886965427856[11] = 0;
   out_1285395886965427856[12] = 1;
   out_1285395886965427856[13] = 0;
   out_1285395886965427856[14] = 0;
   out_1285395886965427856[15] = 1;
   out_1285395886965427856[16] = 0;
   out_1285395886965427856[17] = 0;
   out_1285395886965427856[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1285395886965427856[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1285395886965427856[20] = 0;
   out_1285395886965427856[21] = state[8];
   out_1285395886965427856[22] = 0;
   out_1285395886965427856[23] = -state[6];
   out_1285395886965427856[24] = -state[5];
   out_1285395886965427856[25] = 0;
   out_1285395886965427856[26] = state[3];
   out_1285395886965427856[27] = 0;
   out_1285395886965427856[28] = 0;
   out_1285395886965427856[29] = 0;
   out_1285395886965427856[30] = 0;
   out_1285395886965427856[31] = 1;
   out_1285395886965427856[32] = 0;
   out_1285395886965427856[33] = 0;
   out_1285395886965427856[34] = 1;
   out_1285395886965427856[35] = 0;
   out_1285395886965427856[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1285395886965427856[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1285395886965427856[38] = 0;
   out_1285395886965427856[39] = -state[7];
   out_1285395886965427856[40] = state[6];
   out_1285395886965427856[41] = 0;
   out_1285395886965427856[42] = state[4];
   out_1285395886965427856[43] = -state[3];
   out_1285395886965427856[44] = 0;
   out_1285395886965427856[45] = 0;
   out_1285395886965427856[46] = 0;
   out_1285395886965427856[47] = 0;
   out_1285395886965427856[48] = 0;
   out_1285395886965427856[49] = 0;
   out_1285395886965427856[50] = 1;
   out_1285395886965427856[51] = 0;
   out_1285395886965427856[52] = 0;
   out_1285395886965427856[53] = 1;
}
void h_13(double *state, double *unused, double *out_4433163398587339817) {
   out_4433163398587339817[0] = state[3];
   out_4433163398587339817[1] = state[4];
   out_4433163398587339817[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4175026863853876609) {
   out_4175026863853876609[0] = 0;
   out_4175026863853876609[1] = 0;
   out_4175026863853876609[2] = 0;
   out_4175026863853876609[3] = 1;
   out_4175026863853876609[4] = 0;
   out_4175026863853876609[5] = 0;
   out_4175026863853876609[6] = 0;
   out_4175026863853876609[7] = 0;
   out_4175026863853876609[8] = 0;
   out_4175026863853876609[9] = 0;
   out_4175026863853876609[10] = 0;
   out_4175026863853876609[11] = 0;
   out_4175026863853876609[12] = 0;
   out_4175026863853876609[13] = 0;
   out_4175026863853876609[14] = 0;
   out_4175026863853876609[15] = 0;
   out_4175026863853876609[16] = 0;
   out_4175026863853876609[17] = 0;
   out_4175026863853876609[18] = 0;
   out_4175026863853876609[19] = 0;
   out_4175026863853876609[20] = 0;
   out_4175026863853876609[21] = 0;
   out_4175026863853876609[22] = 1;
   out_4175026863853876609[23] = 0;
   out_4175026863853876609[24] = 0;
   out_4175026863853876609[25] = 0;
   out_4175026863853876609[26] = 0;
   out_4175026863853876609[27] = 0;
   out_4175026863853876609[28] = 0;
   out_4175026863853876609[29] = 0;
   out_4175026863853876609[30] = 0;
   out_4175026863853876609[31] = 0;
   out_4175026863853876609[32] = 0;
   out_4175026863853876609[33] = 0;
   out_4175026863853876609[34] = 0;
   out_4175026863853876609[35] = 0;
   out_4175026863853876609[36] = 0;
   out_4175026863853876609[37] = 0;
   out_4175026863853876609[38] = 0;
   out_4175026863853876609[39] = 0;
   out_4175026863853876609[40] = 0;
   out_4175026863853876609[41] = 1;
   out_4175026863853876609[42] = 0;
   out_4175026863853876609[43] = 0;
   out_4175026863853876609[44] = 0;
   out_4175026863853876609[45] = 0;
   out_4175026863853876609[46] = 0;
   out_4175026863853876609[47] = 0;
   out_4175026863853876609[48] = 0;
   out_4175026863853876609[49] = 0;
   out_4175026863853876609[50] = 0;
   out_4175026863853876609[51] = 0;
   out_4175026863853876609[52] = 0;
   out_4175026863853876609[53] = 0;
}
void h_14(double *state, double *unused, double *out_9196456217182301585) {
   out_9196456217182301585[0] = state[6];
   out_9196456217182301585[1] = state[7];
   out_9196456217182301585[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3578297569243601782) {
   out_3578297569243601782[0] = 0;
   out_3578297569243601782[1] = 0;
   out_3578297569243601782[2] = 0;
   out_3578297569243601782[3] = 0;
   out_3578297569243601782[4] = 0;
   out_3578297569243601782[5] = 0;
   out_3578297569243601782[6] = 1;
   out_3578297569243601782[7] = 0;
   out_3578297569243601782[8] = 0;
   out_3578297569243601782[9] = 0;
   out_3578297569243601782[10] = 0;
   out_3578297569243601782[11] = 0;
   out_3578297569243601782[12] = 0;
   out_3578297569243601782[13] = 0;
   out_3578297569243601782[14] = 0;
   out_3578297569243601782[15] = 0;
   out_3578297569243601782[16] = 0;
   out_3578297569243601782[17] = 0;
   out_3578297569243601782[18] = 0;
   out_3578297569243601782[19] = 0;
   out_3578297569243601782[20] = 0;
   out_3578297569243601782[21] = 0;
   out_3578297569243601782[22] = 0;
   out_3578297569243601782[23] = 0;
   out_3578297569243601782[24] = 0;
   out_3578297569243601782[25] = 1;
   out_3578297569243601782[26] = 0;
   out_3578297569243601782[27] = 0;
   out_3578297569243601782[28] = 0;
   out_3578297569243601782[29] = 0;
   out_3578297569243601782[30] = 0;
   out_3578297569243601782[31] = 0;
   out_3578297569243601782[32] = 0;
   out_3578297569243601782[33] = 0;
   out_3578297569243601782[34] = 0;
   out_3578297569243601782[35] = 0;
   out_3578297569243601782[36] = 0;
   out_3578297569243601782[37] = 0;
   out_3578297569243601782[38] = 0;
   out_3578297569243601782[39] = 0;
   out_3578297569243601782[40] = 0;
   out_3578297569243601782[41] = 0;
   out_3578297569243601782[42] = 0;
   out_3578297569243601782[43] = 0;
   out_3578297569243601782[44] = 1;
   out_3578297569243601782[45] = 0;
   out_3578297569243601782[46] = 0;
   out_3578297569243601782[47] = 0;
   out_3578297569243601782[48] = 0;
   out_3578297569243601782[49] = 0;
   out_3578297569243601782[50] = 0;
   out_3578297569243601782[51] = 0;
   out_3578297569243601782[52] = 0;
   out_3578297569243601782[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1678677657067247278) {
  err_fun(nom_x, delta_x, out_1678677657067247278);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1406774922343404125) {
  inv_err_fun(nom_x, true_x, out_1406774922343404125);
}
void pose_H_mod_fun(double *state, double *out_8585248171069107514) {
  H_mod_fun(state, out_8585248171069107514);
}
void pose_f_fun(double *state, double dt, double *out_7025233619786589722) {
  f_fun(state,  dt, out_7025233619786589722);
}
void pose_F_fun(double *state, double dt, double *out_5989987150238344461) {
  F_fun(state,  dt, out_5989987150238344461);
}
void pose_h_4(double *state, double *unused, double *out_5416308601503649612) {
  h_4(state, unused, out_5416308601503649612);
}
void pose_H_4(double *state, double *unused, double *out_6661086001538974078) {
  H_4(state, unused, out_6661086001538974078);
}
void pose_h_10(double *state, double *unused, double *out_5402550001453747401) {
  h_10(state, unused, out_5402550001453747401);
}
void pose_H_10(double *state, double *unused, double *out_1285395886965427856) {
  H_10(state, unused, out_1285395886965427856);
}
void pose_h_13(double *state, double *unused, double *out_4433163398587339817) {
  h_13(state, unused, out_4433163398587339817);
}
void pose_H_13(double *state, double *unused, double *out_4175026863853876609) {
  H_13(state, unused, out_4175026863853876609);
}
void pose_h_14(double *state, double *unused, double *out_9196456217182301585) {
  h_14(state, unused, out_9196456217182301585);
}
void pose_H_14(double *state, double *unused, double *out_3578297569243601782) {
  H_14(state, unused, out_3578297569243601782);
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
