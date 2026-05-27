#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1678677657067247278);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1406774922343404125);
void pose_H_mod_fun(double *state, double *out_8585248171069107514);
void pose_f_fun(double *state, double dt, double *out_7025233619786589722);
void pose_F_fun(double *state, double dt, double *out_5989987150238344461);
void pose_h_4(double *state, double *unused, double *out_5416308601503649612);
void pose_H_4(double *state, double *unused, double *out_6661086001538974078);
void pose_h_10(double *state, double *unused, double *out_5402550001453747401);
void pose_H_10(double *state, double *unused, double *out_1285395886965427856);
void pose_h_13(double *state, double *unused, double *out_4433163398587339817);
void pose_H_13(double *state, double *unused, double *out_4175026863853876609);
void pose_h_14(double *state, double *unused, double *out_9196456217182301585);
void pose_H_14(double *state, double *unused, double *out_3578297569243601782);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}