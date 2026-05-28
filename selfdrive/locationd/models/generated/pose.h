#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_387547304249028087);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7237327960985051970);
void pose_H_mod_fun(double *state, double *out_1518150812485221245);
void pose_f_fun(double *state, double dt, double *out_1633491762729632217);
void pose_F_fun(double *state, double dt, double *out_7445322755045531081);
void pose_h_4(double *state, double *unused, double *out_5900540074772401531);
void pose_H_4(double *state, double *unused, double *out_7984231595166509029);
void pose_h_10(double *state, double *unused, double *out_1581049242646868861);
void pose_H_10(double *state, double *unused, double *out_7103662432587704500);
void pose_h_13(double *state, double *unused, double *out_4329138349760988154);
void pose_H_13(double *state, double *unused, double *out_7250238653210709786);
void pose_h_14(double *state, double *unused, double *out_4540324702778368531);
void pose_H_14(double *state, double *unused, double *out_6499271622203558058);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}