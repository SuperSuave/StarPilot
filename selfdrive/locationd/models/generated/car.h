#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_4626521360668525331);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4353911889365054107);
void car_H_mod_fun(double *state, double *out_6528496846179259150);
void car_f_fun(double *state, double dt, double *out_7526004771255385533);
void car_F_fun(double *state, double dt, double *out_8955470585899740962);
void car_h_25(double *state, double *unused, double *out_5894972468097248859);
void car_H_25(double *state, double *unused, double *out_3434478573386862642);
void car_h_24(double *state, double *unused, double *out_1154048763614280866);
void car_H_24(double *state, double *unused, double *out_5607128172392362208);
void car_h_30(double *state, double *unused, double *out_390148965807262188);
void car_H_30(double *state, double *unused, double *out_916145614879614015);
void car_h_26(double *state, double *unused, double *out_2080596800542943148);
void car_H_26(double *state, double *unused, double *out_7175981892260918866);
void car_h_27(double *state, double *unused, double *out_4847425094158536933);
void car_H_27(double *state, double *unused, double *out_1307448456304329202);
void car_h_29(double *state, double *unused, double *out_5391822233468107833);
void car_H_29(double *state, double *unused, double *out_405914270565221831);
void car_h_28(double *state, double *unused, double *out_4173118318281939509);
void car_H_28(double *state, double *unused, double *out_5488313287634752405);
void car_h_31(double *state, double *unused, double *out_3522494624731266051);
void car_H_31(double *state, double *unused, double *out_3403832611509902214);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}