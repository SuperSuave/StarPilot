#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4626521360668525331) {
   out_4626521360668525331[0] = delta_x[0] + nom_x[0];
   out_4626521360668525331[1] = delta_x[1] + nom_x[1];
   out_4626521360668525331[2] = delta_x[2] + nom_x[2];
   out_4626521360668525331[3] = delta_x[3] + nom_x[3];
   out_4626521360668525331[4] = delta_x[4] + nom_x[4];
   out_4626521360668525331[5] = delta_x[5] + nom_x[5];
   out_4626521360668525331[6] = delta_x[6] + nom_x[6];
   out_4626521360668525331[7] = delta_x[7] + nom_x[7];
   out_4626521360668525331[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4353911889365054107) {
   out_4353911889365054107[0] = -nom_x[0] + true_x[0];
   out_4353911889365054107[1] = -nom_x[1] + true_x[1];
   out_4353911889365054107[2] = -nom_x[2] + true_x[2];
   out_4353911889365054107[3] = -nom_x[3] + true_x[3];
   out_4353911889365054107[4] = -nom_x[4] + true_x[4];
   out_4353911889365054107[5] = -nom_x[5] + true_x[5];
   out_4353911889365054107[6] = -nom_x[6] + true_x[6];
   out_4353911889365054107[7] = -nom_x[7] + true_x[7];
   out_4353911889365054107[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6528496846179259150) {
   out_6528496846179259150[0] = 1.0;
   out_6528496846179259150[1] = 0.0;
   out_6528496846179259150[2] = 0.0;
   out_6528496846179259150[3] = 0.0;
   out_6528496846179259150[4] = 0.0;
   out_6528496846179259150[5] = 0.0;
   out_6528496846179259150[6] = 0.0;
   out_6528496846179259150[7] = 0.0;
   out_6528496846179259150[8] = 0.0;
   out_6528496846179259150[9] = 0.0;
   out_6528496846179259150[10] = 1.0;
   out_6528496846179259150[11] = 0.0;
   out_6528496846179259150[12] = 0.0;
   out_6528496846179259150[13] = 0.0;
   out_6528496846179259150[14] = 0.0;
   out_6528496846179259150[15] = 0.0;
   out_6528496846179259150[16] = 0.0;
   out_6528496846179259150[17] = 0.0;
   out_6528496846179259150[18] = 0.0;
   out_6528496846179259150[19] = 0.0;
   out_6528496846179259150[20] = 1.0;
   out_6528496846179259150[21] = 0.0;
   out_6528496846179259150[22] = 0.0;
   out_6528496846179259150[23] = 0.0;
   out_6528496846179259150[24] = 0.0;
   out_6528496846179259150[25] = 0.0;
   out_6528496846179259150[26] = 0.0;
   out_6528496846179259150[27] = 0.0;
   out_6528496846179259150[28] = 0.0;
   out_6528496846179259150[29] = 0.0;
   out_6528496846179259150[30] = 1.0;
   out_6528496846179259150[31] = 0.0;
   out_6528496846179259150[32] = 0.0;
   out_6528496846179259150[33] = 0.0;
   out_6528496846179259150[34] = 0.0;
   out_6528496846179259150[35] = 0.0;
   out_6528496846179259150[36] = 0.0;
   out_6528496846179259150[37] = 0.0;
   out_6528496846179259150[38] = 0.0;
   out_6528496846179259150[39] = 0.0;
   out_6528496846179259150[40] = 1.0;
   out_6528496846179259150[41] = 0.0;
   out_6528496846179259150[42] = 0.0;
   out_6528496846179259150[43] = 0.0;
   out_6528496846179259150[44] = 0.0;
   out_6528496846179259150[45] = 0.0;
   out_6528496846179259150[46] = 0.0;
   out_6528496846179259150[47] = 0.0;
   out_6528496846179259150[48] = 0.0;
   out_6528496846179259150[49] = 0.0;
   out_6528496846179259150[50] = 1.0;
   out_6528496846179259150[51] = 0.0;
   out_6528496846179259150[52] = 0.0;
   out_6528496846179259150[53] = 0.0;
   out_6528496846179259150[54] = 0.0;
   out_6528496846179259150[55] = 0.0;
   out_6528496846179259150[56] = 0.0;
   out_6528496846179259150[57] = 0.0;
   out_6528496846179259150[58] = 0.0;
   out_6528496846179259150[59] = 0.0;
   out_6528496846179259150[60] = 1.0;
   out_6528496846179259150[61] = 0.0;
   out_6528496846179259150[62] = 0.0;
   out_6528496846179259150[63] = 0.0;
   out_6528496846179259150[64] = 0.0;
   out_6528496846179259150[65] = 0.0;
   out_6528496846179259150[66] = 0.0;
   out_6528496846179259150[67] = 0.0;
   out_6528496846179259150[68] = 0.0;
   out_6528496846179259150[69] = 0.0;
   out_6528496846179259150[70] = 1.0;
   out_6528496846179259150[71] = 0.0;
   out_6528496846179259150[72] = 0.0;
   out_6528496846179259150[73] = 0.0;
   out_6528496846179259150[74] = 0.0;
   out_6528496846179259150[75] = 0.0;
   out_6528496846179259150[76] = 0.0;
   out_6528496846179259150[77] = 0.0;
   out_6528496846179259150[78] = 0.0;
   out_6528496846179259150[79] = 0.0;
   out_6528496846179259150[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7526004771255385533) {
   out_7526004771255385533[0] = state[0];
   out_7526004771255385533[1] = state[1];
   out_7526004771255385533[2] = state[2];
   out_7526004771255385533[3] = state[3];
   out_7526004771255385533[4] = state[4];
   out_7526004771255385533[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7526004771255385533[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7526004771255385533[7] = state[7];
   out_7526004771255385533[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8955470585899740962) {
   out_8955470585899740962[0] = 1;
   out_8955470585899740962[1] = 0;
   out_8955470585899740962[2] = 0;
   out_8955470585899740962[3] = 0;
   out_8955470585899740962[4] = 0;
   out_8955470585899740962[5] = 0;
   out_8955470585899740962[6] = 0;
   out_8955470585899740962[7] = 0;
   out_8955470585899740962[8] = 0;
   out_8955470585899740962[9] = 0;
   out_8955470585899740962[10] = 1;
   out_8955470585899740962[11] = 0;
   out_8955470585899740962[12] = 0;
   out_8955470585899740962[13] = 0;
   out_8955470585899740962[14] = 0;
   out_8955470585899740962[15] = 0;
   out_8955470585899740962[16] = 0;
   out_8955470585899740962[17] = 0;
   out_8955470585899740962[18] = 0;
   out_8955470585899740962[19] = 0;
   out_8955470585899740962[20] = 1;
   out_8955470585899740962[21] = 0;
   out_8955470585899740962[22] = 0;
   out_8955470585899740962[23] = 0;
   out_8955470585899740962[24] = 0;
   out_8955470585899740962[25] = 0;
   out_8955470585899740962[26] = 0;
   out_8955470585899740962[27] = 0;
   out_8955470585899740962[28] = 0;
   out_8955470585899740962[29] = 0;
   out_8955470585899740962[30] = 1;
   out_8955470585899740962[31] = 0;
   out_8955470585899740962[32] = 0;
   out_8955470585899740962[33] = 0;
   out_8955470585899740962[34] = 0;
   out_8955470585899740962[35] = 0;
   out_8955470585899740962[36] = 0;
   out_8955470585899740962[37] = 0;
   out_8955470585899740962[38] = 0;
   out_8955470585899740962[39] = 0;
   out_8955470585899740962[40] = 1;
   out_8955470585899740962[41] = 0;
   out_8955470585899740962[42] = 0;
   out_8955470585899740962[43] = 0;
   out_8955470585899740962[44] = 0;
   out_8955470585899740962[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8955470585899740962[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8955470585899740962[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8955470585899740962[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8955470585899740962[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8955470585899740962[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8955470585899740962[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8955470585899740962[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8955470585899740962[53] = -9.8100000000000005*dt;
   out_8955470585899740962[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8955470585899740962[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8955470585899740962[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8955470585899740962[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8955470585899740962[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8955470585899740962[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8955470585899740962[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8955470585899740962[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8955470585899740962[62] = 0;
   out_8955470585899740962[63] = 0;
   out_8955470585899740962[64] = 0;
   out_8955470585899740962[65] = 0;
   out_8955470585899740962[66] = 0;
   out_8955470585899740962[67] = 0;
   out_8955470585899740962[68] = 0;
   out_8955470585899740962[69] = 0;
   out_8955470585899740962[70] = 1;
   out_8955470585899740962[71] = 0;
   out_8955470585899740962[72] = 0;
   out_8955470585899740962[73] = 0;
   out_8955470585899740962[74] = 0;
   out_8955470585899740962[75] = 0;
   out_8955470585899740962[76] = 0;
   out_8955470585899740962[77] = 0;
   out_8955470585899740962[78] = 0;
   out_8955470585899740962[79] = 0;
   out_8955470585899740962[80] = 1;
}
void h_25(double *state, double *unused, double *out_5894972468097248859) {
   out_5894972468097248859[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3434478573386862642) {
   out_3434478573386862642[0] = 0;
   out_3434478573386862642[1] = 0;
   out_3434478573386862642[2] = 0;
   out_3434478573386862642[3] = 0;
   out_3434478573386862642[4] = 0;
   out_3434478573386862642[5] = 0;
   out_3434478573386862642[6] = 1;
   out_3434478573386862642[7] = 0;
   out_3434478573386862642[8] = 0;
}
void h_24(double *state, double *unused, double *out_1154048763614280866) {
   out_1154048763614280866[0] = state[4];
   out_1154048763614280866[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5607128172392362208) {
   out_5607128172392362208[0] = 0;
   out_5607128172392362208[1] = 0;
   out_5607128172392362208[2] = 0;
   out_5607128172392362208[3] = 0;
   out_5607128172392362208[4] = 1;
   out_5607128172392362208[5] = 0;
   out_5607128172392362208[6] = 0;
   out_5607128172392362208[7] = 0;
   out_5607128172392362208[8] = 0;
   out_5607128172392362208[9] = 0;
   out_5607128172392362208[10] = 0;
   out_5607128172392362208[11] = 0;
   out_5607128172392362208[12] = 0;
   out_5607128172392362208[13] = 0;
   out_5607128172392362208[14] = 1;
   out_5607128172392362208[15] = 0;
   out_5607128172392362208[16] = 0;
   out_5607128172392362208[17] = 0;
}
void h_30(double *state, double *unused, double *out_390148965807262188) {
   out_390148965807262188[0] = state[4];
}
void H_30(double *state, double *unused, double *out_916145614879614015) {
   out_916145614879614015[0] = 0;
   out_916145614879614015[1] = 0;
   out_916145614879614015[2] = 0;
   out_916145614879614015[3] = 0;
   out_916145614879614015[4] = 1;
   out_916145614879614015[5] = 0;
   out_916145614879614015[6] = 0;
   out_916145614879614015[7] = 0;
   out_916145614879614015[8] = 0;
}
void h_26(double *state, double *unused, double *out_2080596800542943148) {
   out_2080596800542943148[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7175981892260918866) {
   out_7175981892260918866[0] = 0;
   out_7175981892260918866[1] = 0;
   out_7175981892260918866[2] = 0;
   out_7175981892260918866[3] = 0;
   out_7175981892260918866[4] = 0;
   out_7175981892260918866[5] = 0;
   out_7175981892260918866[6] = 0;
   out_7175981892260918866[7] = 1;
   out_7175981892260918866[8] = 0;
}
void h_27(double *state, double *unused, double *out_4847425094158536933) {
   out_4847425094158536933[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1307448456304329202) {
   out_1307448456304329202[0] = 0;
   out_1307448456304329202[1] = 0;
   out_1307448456304329202[2] = 0;
   out_1307448456304329202[3] = 1;
   out_1307448456304329202[4] = 0;
   out_1307448456304329202[5] = 0;
   out_1307448456304329202[6] = 0;
   out_1307448456304329202[7] = 0;
   out_1307448456304329202[8] = 0;
}
void h_29(double *state, double *unused, double *out_5391822233468107833) {
   out_5391822233468107833[0] = state[1];
}
void H_29(double *state, double *unused, double *out_405914270565221831) {
   out_405914270565221831[0] = 0;
   out_405914270565221831[1] = 1;
   out_405914270565221831[2] = 0;
   out_405914270565221831[3] = 0;
   out_405914270565221831[4] = 0;
   out_405914270565221831[5] = 0;
   out_405914270565221831[6] = 0;
   out_405914270565221831[7] = 0;
   out_405914270565221831[8] = 0;
}
void h_28(double *state, double *unused, double *out_4173118318281939509) {
   out_4173118318281939509[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5488313287634752405) {
   out_5488313287634752405[0] = 1;
   out_5488313287634752405[1] = 0;
   out_5488313287634752405[2] = 0;
   out_5488313287634752405[3] = 0;
   out_5488313287634752405[4] = 0;
   out_5488313287634752405[5] = 0;
   out_5488313287634752405[6] = 0;
   out_5488313287634752405[7] = 0;
   out_5488313287634752405[8] = 0;
}
void h_31(double *state, double *unused, double *out_3522494624731266051) {
   out_3522494624731266051[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3403832611509902214) {
   out_3403832611509902214[0] = 0;
   out_3403832611509902214[1] = 0;
   out_3403832611509902214[2] = 0;
   out_3403832611509902214[3] = 0;
   out_3403832611509902214[4] = 0;
   out_3403832611509902214[5] = 0;
   out_3403832611509902214[6] = 0;
   out_3403832611509902214[7] = 0;
   out_3403832611509902214[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4626521360668525331) {
  err_fun(nom_x, delta_x, out_4626521360668525331);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4353911889365054107) {
  inv_err_fun(nom_x, true_x, out_4353911889365054107);
}
void car_H_mod_fun(double *state, double *out_6528496846179259150) {
  H_mod_fun(state, out_6528496846179259150);
}
void car_f_fun(double *state, double dt, double *out_7526004771255385533) {
  f_fun(state,  dt, out_7526004771255385533);
}
void car_F_fun(double *state, double dt, double *out_8955470585899740962) {
  F_fun(state,  dt, out_8955470585899740962);
}
void car_h_25(double *state, double *unused, double *out_5894972468097248859) {
  h_25(state, unused, out_5894972468097248859);
}
void car_H_25(double *state, double *unused, double *out_3434478573386862642) {
  H_25(state, unused, out_3434478573386862642);
}
void car_h_24(double *state, double *unused, double *out_1154048763614280866) {
  h_24(state, unused, out_1154048763614280866);
}
void car_H_24(double *state, double *unused, double *out_5607128172392362208) {
  H_24(state, unused, out_5607128172392362208);
}
void car_h_30(double *state, double *unused, double *out_390148965807262188) {
  h_30(state, unused, out_390148965807262188);
}
void car_H_30(double *state, double *unused, double *out_916145614879614015) {
  H_30(state, unused, out_916145614879614015);
}
void car_h_26(double *state, double *unused, double *out_2080596800542943148) {
  h_26(state, unused, out_2080596800542943148);
}
void car_H_26(double *state, double *unused, double *out_7175981892260918866) {
  H_26(state, unused, out_7175981892260918866);
}
void car_h_27(double *state, double *unused, double *out_4847425094158536933) {
  h_27(state, unused, out_4847425094158536933);
}
void car_H_27(double *state, double *unused, double *out_1307448456304329202) {
  H_27(state, unused, out_1307448456304329202);
}
void car_h_29(double *state, double *unused, double *out_5391822233468107833) {
  h_29(state, unused, out_5391822233468107833);
}
void car_H_29(double *state, double *unused, double *out_405914270565221831) {
  H_29(state, unused, out_405914270565221831);
}
void car_h_28(double *state, double *unused, double *out_4173118318281939509) {
  h_28(state, unused, out_4173118318281939509);
}
void car_H_28(double *state, double *unused, double *out_5488313287634752405) {
  H_28(state, unused, out_5488313287634752405);
}
void car_h_31(double *state, double *unused, double *out_3522494624731266051) {
  h_31(state, unused, out_3522494624731266051);
}
void car_H_31(double *state, double *unused, double *out_3403832611509902214) {
  H_31(state, unused, out_3403832611509902214);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
