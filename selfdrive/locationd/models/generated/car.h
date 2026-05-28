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
void car_err_fun(double *nom_x, double *delta_x, double *out_47249178359766282);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4179118128779086698);
void car_H_mod_fun(double *state, double *out_5939580081522663454);
void car_f_fun(double *state, double dt, double *out_2085324948004346152);
void car_F_fun(double *state, double dt, double *out_5950927418780674832);
void car_h_25(double *state, double *unused, double *out_2205567022592625878);
void car_H_25(double *state, double *unused, double *out_157328285083711162);
void car_h_24(double *state, double *unused, double *out_349567140287956942);
void car_H_24(double *state, double *unused, double *out_3400597313718611974);
void car_h_30(double *state, double *unused, double *out_5843016550846648228);
void car_H_30(double *state, double *unused, double *out_2361004673423537465);
void car_h_26(double *state, double *unused, double *out_5239700666170170711);
void car_H_26(double *state, double *unused, double *out_3147197684677089439);
void car_h_27(double *state, double *unused, double *out_831219028851706807);
void car_H_27(double *state, double *unused, double *out_4584598744607480682);
void car_h_29(double *state, double *unused, double *out_7602054255202057743);
void car_H_29(double *state, double *unused, double *out_2871236017737929649);
void car_h_28(double *state, double *unused, double *out_1774728881753369242);
void car_H_28(double *state, double *unused, double *out_2211162999331600925);
void car_h_31(double *state, double *unused, double *out_4382260903883669285);
void car_H_31(double *state, double *unused, double *out_6919346965428106091);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}