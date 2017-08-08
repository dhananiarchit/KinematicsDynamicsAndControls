/*****************************************************************************/
/*
  data.c: save data from simulation
*/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../useful/mrdplot/mrdplot.h"

#include "main.h"
#include "main2.h"

/*****************************************************************************/

extern SIM sim;

/*****************************************************************************/

enum channels {
MRDPLOT_TIME=0,
MRDPLOT_ALIEN_X,
MRDPLOT_ALIEN_Y,
MRDPLOT_ALIEN_Z,
MRDPLOT_ALIEN_Q0,
MRDPLOT_ALIEN_Q1,
MRDPLOT_ALIEN_Q2,
MRDPLOT_ALIEN_Q3,
MRDPLOT_ALIEN_Q_NORM,
MRDPLOT_ALIEN_XD,
MRDPLOT_ALIEN_YD,
MRDPLOT_ALIEN_ZD,
MRDPLOT_ALIEN_WX,
MRDPLOT_ALIEN_WY,
MRDPLOT_ALIEN_WZ,
MRDPLOT_LANDER_X,
MRDPLOT_LANDER_Y,
MRDPLOT_LANDER_Z,
MRDPLOT_LANDER_Q0,
MRDPLOT_LANDER_Q1,
MRDPLOT_LANDER_Q2,
MRDPLOT_LANDER_Q3,
MRDPLOT_LANDER_Q_NORM,
MRDPLOT_LANDER_XD,
MRDPLOT_LANDER_YD,
MRDPLOT_LANDER_ZD,
MRDPLOT_LANDER_WX,
MRDPLOT_LANDER_WY,
MRDPLOT_LANDER_WZ,
MRDPLOT_LANDER_TRQ_X,
MRDPLOT_LANDER_TRQ_Y,
MRDPLOT_LANDER_TRQ_Z,
MRDPLOT_LANDER_ROTVEC_X,
MRDPLOT_LANDER_ROTVEC_Y,
MRDPLOT_LANDER_ROTVEC_Z,
MRDPLOT_A_R00,
MRDPLOT_A_R01,
MRDPLOT_A_R02,
MRDPLOT_A_R10,
MRDPLOT_A_R11,
MRDPLOT_A_R12,
MRDPLOT_A_R20,
MRDPLOT_A_R21,
MRDPLOT_A_R22,
MRDPLOT_L_R00,
MRDPLOT_L_R01,
MRDPLOT_L_R02,
MRDPLOT_L_R10,
MRDPLOT_L_R11,
MRDPLOT_L_R12,
MRDPLOT_L_R20,
MRDPLOT_L_R21,
MRDPLOT_L_R22,
MRDPLOT_MZX,
MRDPLOT_MZY,
MRDPLOT_MZZ,
MRDPLOT_M0X,
MRDPLOT_M0Y,
MRDPLOT_M0Z,
MRDPLOT_M1X,
MRDPLOT_M1Y,
MRDPLOT_M1Z,
MRDPLOT_M2X,
MRDPLOT_M2Y,
MRDPLOT_M2Z,
MRDPLOT_M3X,
MRDPLOT_M3Y,
MRDPLOT_M3Z,
MRDPLOT_M4X,
MRDPLOT_M4Y,
MRDPLOT_M4Z,
MRDPLOT_M5X,
MRDPLOT_M5Y,
MRDPLOT_M5Z,
MRDPLOT_M6X,
MRDPLOT_M6Y,
MRDPLOT_M6Z,
MRDPLOT_M7X,
MRDPLOT_M7Y,
MRDPLOT_M7Z,
MRDPLOT_ML0X,
MRDPLOT_ML0Y,
MRDPLOT_ML0Z,
MRDPLOT_ML1X,
MRDPLOT_ML1Y,
MRDPLOT_ML1Z,
MRDPLOT_ML2X,
MRDPLOT_ML2Y,
MRDPLOT_ML2Z,
MRDPLOT_ML3X,
MRDPLOT_ML3Y,
MRDPLOT_ML3Z,
MRDPLOT_ML4X,
MRDPLOT_ML4Y,
MRDPLOT_ML4Z,
MRDPLOT_ML5X,
MRDPLOT_ML5Y,
MRDPLOT_ML5Z,
MRDPLOT_ML6X,
MRDPLOT_ML6Y,
MRDPLOT_ML6Z,
MRDPLOT_ML7X,
MRDPLOT_ML7Y,
MRDPLOT_ML7Z,
MRDPLOT_MN0X,
MRDPLOT_MN0Y,
MRDPLOT_MN0Z,
MRDPLOT_MN1X,
MRDPLOT_MN1Y,
MRDPLOT_MN1Z,
MRDPLOT_MN2X,
MRDPLOT_MN2Y,
MRDPLOT_MN2Z,
MRDPLOT_MN3X,
MRDPLOT_MN3Y,
MRDPLOT_MN3Z,
MRDPLOT_MN4X,
MRDPLOT_MN4Y,
MRDPLOT_MN4Z,
MRDPLOT_MN5X,
MRDPLOT_MN5Y,
MRDPLOT_MN5Z,
MRDPLOT_MN6X,
MRDPLOT_MN6Y,
MRDPLOT_MN6Z,
MRDPLOT_MN7X,
MRDPLOT_MN7Y,
MRDPLOT_MN7Z,
N_CHANNELS
};

#define MAX_N_POINTS 100000

int n_points = 0;
float data[MAX_N_POINTS*N_CHANNELS];

char *names[N_CHANNELS];
char *units[N_CHANNELS];

/*****************************************************************************/

void init_data( SIM *s )
{
  int i;

  /*
  printf( "N_CHANNELS: %d; MRDPLOT_L_HIP: %d; last: %d\n", N_CHANNELS,
	  MRDPLOT_L_HIP, MRDPLOT_L_ANKLE_COMMAND );
  */

  for( i = 0; i < N_CHANNELS; i++ )
    {
      names[i] = "xxx";
      units[i] = "xxx";
    }

  names[MRDPLOT_TIME] = "time";
  names[MRDPLOT_ALIEN_X] = "a_x";
  names[MRDPLOT_ALIEN_Y] = "a_y";
  names[MRDPLOT_ALIEN_Z] = "a_z";
  names[MRDPLOT_ALIEN_Q0] = "a_q0";
  names[MRDPLOT_ALIEN_Q1] = "a_q1";
  names[MRDPLOT_ALIEN_Q2] = "a_q2";
  names[MRDPLOT_ALIEN_Q3] = "a_q3";
  names[MRDPLOT_ALIEN_Q_NORM] = "a_q_n";
  names[MRDPLOT_ALIEN_XD] = "a_xd";
  names[MRDPLOT_ALIEN_YD] = "a_yd";
  names[MRDPLOT_ALIEN_ZD] = "a_zd";
  names[MRDPLOT_ALIEN_WX] = "a_wx";
  names[MRDPLOT_ALIEN_WY] = "a_wy";
  names[MRDPLOT_ALIEN_WZ] = "a_wz";
  names[MRDPLOT_LANDER_X] = "l_x";
  names[MRDPLOT_LANDER_Y] = "l_y";
  names[MRDPLOT_LANDER_Z] = "l_z";
  names[MRDPLOT_LANDER_Q0] = "l_q0";
  names[MRDPLOT_LANDER_Q1] = "l_q1";
  names[MRDPLOT_LANDER_Q2] = "l_q2";
  names[MRDPLOT_LANDER_Q3] = "l_q3";
  names[MRDPLOT_LANDER_Q_NORM] = "l_q_n";
  names[MRDPLOT_LANDER_XD] = "l_xd";
  names[MRDPLOT_LANDER_YD] = "l_yd";
  names[MRDPLOT_LANDER_ZD] = "l_zd";
  names[MRDPLOT_LANDER_WX] = "l_wx";
  names[MRDPLOT_LANDER_WY] = "l_wy";
  names[MRDPLOT_LANDER_WZ] = "l_wz";
  names[MRDPLOT_LANDER_TRQ_X] = "l_trq_x";
  names[MRDPLOT_LANDER_TRQ_Y] = "l_trq_y";
  names[MRDPLOT_LANDER_TRQ_Z] = "l_trq_z";
  names[MRDPLOT_LANDER_ROTVEC_X] = "l_rotvec_x";
  names[MRDPLOT_LANDER_ROTVEC_Y] = "l_rotvec_y";
  names[MRDPLOT_LANDER_ROTVEC_Z] = "l_rotvec_z";
  names[MRDPLOT_A_R00] = "a_r00";
  names[MRDPLOT_A_R01] = "a_r01";
  names[MRDPLOT_A_R02] = "a_r02";
  names[MRDPLOT_A_R10] = "a_r10";
  names[MRDPLOT_A_R11] = "a_r11";
  names[MRDPLOT_A_R12] = "a_r12";
  names[MRDPLOT_A_R20] = "a_r20";
  names[MRDPLOT_A_R21] = "a_r21";
  names[MRDPLOT_A_R22] = "a_r22";
  names[MRDPLOT_L_R00] = "l_r00";
  names[MRDPLOT_L_R01] = "l_r01";
  names[MRDPLOT_L_R02] = "l_r02";
  names[MRDPLOT_L_R10] = "l_r10";
  names[MRDPLOT_L_R11] = "l_r11";
  names[MRDPLOT_L_R12] = "l_r12";
  names[MRDPLOT_L_R20] = "l_r20";
  names[MRDPLOT_L_R21] = "l_r21";
  names[MRDPLOT_L_R22] = "l_r22";
  names[MRDPLOT_MZX] = "mzx";
  names[MRDPLOT_MZY] = "mzy";
  names[MRDPLOT_MZZ] = "mzz";
  names[MRDPLOT_M0X] = "m0x";
  names[MRDPLOT_M0Y] = "m0y";
  names[MRDPLOT_M0Z] = "m0z";
  names[MRDPLOT_M1X] = "m1x";
  names[MRDPLOT_M1Y] = "m1y";
  names[MRDPLOT_M1Z] = "m1z";
  names[MRDPLOT_M2X] = "m2x";
  names[MRDPLOT_M2Y] = "m2y";
  names[MRDPLOT_M2Z] = "m2z";
  names[MRDPLOT_M3X] = "m3x";
  names[MRDPLOT_M3Y] = "m3y";
  names[MRDPLOT_M3Z] = "m3z";
  names[MRDPLOT_M4X] = "m4x";
  names[MRDPLOT_M4Y] = "m4y";
  names[MRDPLOT_M4Z] = "m4z";
  names[MRDPLOT_M5X] = "m5x";
  names[MRDPLOT_M5Y] = "m5y";
  names[MRDPLOT_M5Z] = "m5z";
  names[MRDPLOT_M6X] = "m6x";
  names[MRDPLOT_M6Y] = "m6y";
  names[MRDPLOT_M6Z] = "m6z";
  names[MRDPLOT_M7X] = "m7x";
  names[MRDPLOT_M7Y] = "m7y";
  names[MRDPLOT_M7Z] = "m7z";
  names[MRDPLOT_ML0X] = "ml0x";
  names[MRDPLOT_ML0Y] = "ml0y";
  names[MRDPLOT_ML0Z] = "ml0z";
  names[MRDPLOT_ML1X] = "ml1x";
  names[MRDPLOT_ML1Y] = "ml1y";
  names[MRDPLOT_ML1Z] = "ml1z";
  names[MRDPLOT_ML2X] = "ml2x";
  names[MRDPLOT_ML2Y] = "ml2y";
  names[MRDPLOT_ML2Z] = "ml2z";
  names[MRDPLOT_ML3X] = "ml3x";
  names[MRDPLOT_ML3Y] = "ml3y";
  names[MRDPLOT_ML3Z] = "ml3z";
  names[MRDPLOT_ML4X] = "ml4x";
  names[MRDPLOT_ML4Y] = "ml4y";
  names[MRDPLOT_ML4Z] = "ml4z";
  names[MRDPLOT_ML5X] = "ml5x";
  names[MRDPLOT_ML5Y] = "ml5y";
  names[MRDPLOT_ML5Z] = "ml5z";
  names[MRDPLOT_ML6X] = "ml6x";
  names[MRDPLOT_ML6Y] = "ml6y";
  names[MRDPLOT_ML6Z] = "ml6z";
  names[MRDPLOT_ML7X] = "ml7x";
  names[MRDPLOT_ML7Y] = "ml7y";
  names[MRDPLOT_ML7Z] = "ml7z";
  names[MRDPLOT_MN0X] = "mn0x";
  names[MRDPLOT_MN0Y] = "mn0y";
  names[MRDPLOT_MN0Z] = "mn0z";
  names[MRDPLOT_MN1X] = "mn1x";
  names[MRDPLOT_MN1Y] = "mn1y";
  names[MRDPLOT_MN1Z] = "mn1z";
  names[MRDPLOT_MN2X] = "mn2x";
  names[MRDPLOT_MN2Y] = "mn2y";
  names[MRDPLOT_MN2Z] = "mn2z";
  names[MRDPLOT_MN3X] = "mn3x";
  names[MRDPLOT_MN3Y] = "mn3y";
  names[MRDPLOT_MN3Z] = "mn3z";
  names[MRDPLOT_MN4X] = "mn4x";
  names[MRDPLOT_MN4Y] = "mn4y";
  names[MRDPLOT_MN4Z] = "mn4z";
  names[MRDPLOT_MN5X] = "mn5x";
  names[MRDPLOT_MN5Y] = "mn5y";
  names[MRDPLOT_MN5Z] = "mn5z";
  names[MRDPLOT_MN6X] = "mn6x";
  names[MRDPLOT_MN6Y] = "mn6y";
  names[MRDPLOT_MN6Z] = "mn6z";
  names[MRDPLOT_MN7X] = "mn7x";
  names[MRDPLOT_MN7Y] = "mn7y";
  names[MRDPLOT_MN7Z] = "mn7z";

  units[MRDPLOT_TIME] = "s";
  units[MRDPLOT_ALIEN_X] = "m";
  units[MRDPLOT_ALIEN_Y] = "m";
  units[MRDPLOT_ALIEN_Z] = "m";
  units[MRDPLOT_ALIEN_Q0] = "-";
  units[MRDPLOT_ALIEN_Q1] = "-";
  units[MRDPLOT_ALIEN_Q2] = "-";
  units[MRDPLOT_ALIEN_Q3] = "-";
  units[MRDPLOT_ALIEN_Q_NORM] = "-";
  units[MRDPLOT_ALIEN_XD] = "m/s";
  units[MRDPLOT_ALIEN_YD] = "m/s";
  units[MRDPLOT_ALIEN_ZD] = "m/s";
  units[MRDPLOT_ALIEN_WX] = "r/s";
  units[MRDPLOT_ALIEN_WY] = "r/s";
  units[MRDPLOT_ALIEN_WZ] = "r/sz";
  units[MRDPLOT_LANDER_X] = "m";
  units[MRDPLOT_LANDER_Y] = "m";
  units[MRDPLOT_LANDER_Z] = "m";
  units[MRDPLOT_LANDER_Q0] = "-";
  units[MRDPLOT_LANDER_Q1] = "-";
  units[MRDPLOT_LANDER_Q2] = "-";
  units[MRDPLOT_LANDER_Q3] = "-";
  units[MRDPLOT_LANDER_Q_NORM] = "-";
  units[MRDPLOT_LANDER_XD] = "m/s";
  units[MRDPLOT_LANDER_YD] = "m/s";
  units[MRDPLOT_LANDER_ZD] = "m/s";
  units[MRDPLOT_LANDER_WX] = "r/s";
  units[MRDPLOT_LANDER_WY] = "r/s";
  units[MRDPLOT_LANDER_WZ] = "r/sz";
  units[MRDPLOT_LANDER_TRQ_X] = "Nm";
  units[MRDPLOT_LANDER_TRQ_Y] = "Nm";
  units[MRDPLOT_LANDER_TRQ_Z] = "Nm";
  units[MRDPLOT_LANDER_ROTVEC_X] = "r";
  units[MRDPLOT_LANDER_ROTVEC_Y] = "r";
  units[MRDPLOT_LANDER_ROTVEC_Z] = "r";
  units[MRDPLOT_A_R00] = "-";
  units[MRDPLOT_A_R01] = "-";
  units[MRDPLOT_A_R02] = "-";
  units[MRDPLOT_A_R10] = "-";
  units[MRDPLOT_A_R11] = "-";
  units[MRDPLOT_A_R12] = "-";
  units[MRDPLOT_A_R20] = "-";
  units[MRDPLOT_A_R21] = "-";
  units[MRDPLOT_A_R22] = "-";
  units[MRDPLOT_L_R00] = "-";
  units[MRDPLOT_L_R01] = "-";
  units[MRDPLOT_L_R02] = "-";
  units[MRDPLOT_L_R10] = "-";
  units[MRDPLOT_L_R11] = "-";
  units[MRDPLOT_L_R12] = "-";
  units[MRDPLOT_L_R20] = "-";
  units[MRDPLOT_L_R21] = "-";
  units[MRDPLOT_L_R22] = "-";
  units[MRDPLOT_MZX] = "m";
  units[MRDPLOT_MZY] = "m";
  units[MRDPLOT_MZZ] = "m";
  units[MRDPLOT_M0X] = "m";
  units[MRDPLOT_M0Y] = "m";
  units[MRDPLOT_M0Z] = "m";
  units[MRDPLOT_M1X] = "m";
  units[MRDPLOT_M1Y] = "m";
  units[MRDPLOT_M1Z] = "m";
  units[MRDPLOT_M2X] = "m";
  units[MRDPLOT_M2Y] = "m";
  units[MRDPLOT_M2Z] = "m";
  units[MRDPLOT_M3X] = "m";
  units[MRDPLOT_M3Y] = "m";
  units[MRDPLOT_M3Z] = "m";
  units[MRDPLOT_M4X] = "m";
  units[MRDPLOT_M4Y] = "m";
  units[MRDPLOT_M4Z] = "m";
  units[MRDPLOT_M5X] = "m";
  units[MRDPLOT_M5Y] = "m";
  units[MRDPLOT_M5Z] = "m";
  units[MRDPLOT_M6X] = "m";
  units[MRDPLOT_M6Y] = "m";
  units[MRDPLOT_M6Z] = "m";
  units[MRDPLOT_M7X] = "m";
  units[MRDPLOT_M7Y] = "m";
  units[MRDPLOT_M7Z] = "m";
  units[MRDPLOT_ML0X] = "m";
  units[MRDPLOT_ML0Y] = "m";
  units[MRDPLOT_ML0Z] = "m";
  units[MRDPLOT_ML1X] = "m";
  units[MRDPLOT_ML1Y] = "m";
  units[MRDPLOT_ML1Z] = "m";
  units[MRDPLOT_ML2X] = "m";
  units[MRDPLOT_ML2Y] = "m";
  units[MRDPLOT_ML2Z] = "m";
  units[MRDPLOT_ML3X] = "m";
  units[MRDPLOT_ML3Y] = "m";
  units[MRDPLOT_ML3Z] = "m";
  units[MRDPLOT_ML4X] = "m";
  units[MRDPLOT_ML4Y] = "m";
  units[MRDPLOT_ML4Z] = "m";
  units[MRDPLOT_ML5X] = "m";
  units[MRDPLOT_ML5Y] = "m";
  units[MRDPLOT_ML5Z] = "m";
  units[MRDPLOT_ML6X] = "m";
  units[MRDPLOT_ML6Y] = "m";
  units[MRDPLOT_ML6Z] = "m";
  units[MRDPLOT_ML7X] = "m";
  units[MRDPLOT_ML7Y] = "m";
  units[MRDPLOT_ML7Z] = "m";
  units[MRDPLOT_MN0X] = "m";
  units[MRDPLOT_MN0Y] = "m";
  units[MRDPLOT_MN0Z] = "m";
  units[MRDPLOT_MN1X] = "m";
  units[MRDPLOT_MN1Y] = "m";
  units[MRDPLOT_MN1Z] = "m";
  units[MRDPLOT_MN2X] = "m";
  units[MRDPLOT_MN2Y] = "m";
  units[MRDPLOT_MN2Z] = "m";
  units[MRDPLOT_MN3X] = "m";
  units[MRDPLOT_MN3Y] = "m";
  units[MRDPLOT_MN3Z] = "m";
  units[MRDPLOT_MN4X] = "m";
  units[MRDPLOT_MN4Y] = "m";
  units[MRDPLOT_MN4Z] = "m";
  units[MRDPLOT_MN5X] = "m";
  units[MRDPLOT_MN5Y] = "m";
  units[MRDPLOT_MN5Z] = "m";
  units[MRDPLOT_MN6X] = "m";
  units[MRDPLOT_MN6Y] = "m";
  units[MRDPLOT_MN6Z] = "m";
  units[MRDPLOT_MN7X] = "m";
  units[MRDPLOT_MN7Y] = "m";
  units[MRDPLOT_MN7Z] = "m";

  /*
  for( i = 0; i < N_CHANNELS; i++ )
    {
      printf( "%d %s %s\n", i, names[i], units[i] );
    }
  */
}

/*****************************************************************************/

int save_data( SIM *s )
{
  static int myindex = 0;

  if ( n_points >= MAX_N_POINTS )
    return 0;

  data[myindex + MRDPLOT_TIME] = s->time;
  data[myindex + MRDPLOT_ALIEN_X] = s->alien_x[XX];
  data[myindex + MRDPLOT_ALIEN_Y] = s->alien_x[YY];
  data[myindex + MRDPLOT_ALIEN_Z] = s->alien_x[ZZ];
  data[myindex + MRDPLOT_ALIEN_Q0] = s->alien_q[0];
  data[myindex + MRDPLOT_ALIEN_Q1] = s->alien_q[1];
  data[myindex + MRDPLOT_ALIEN_Q2] = s->alien_q[2];
  data[myindex + MRDPLOT_ALIEN_Q3] = s->alien_q[3];
  data[myindex + MRDPLOT_ALIEN_Q_NORM] = s->alien_q_norm;
  data[myindex + MRDPLOT_ALIEN_XD] = s->alien_xd[XX];
  data[myindex + MRDPLOT_ALIEN_YD] = s->alien_xd[YY];
  data[myindex + MRDPLOT_ALIEN_ZD] = s->alien_xd[ZZ];
  data[myindex + MRDPLOT_ALIEN_WX] = s->alien_w[XX];
  data[myindex + MRDPLOT_ALIEN_WY] = s->alien_w[YY];
  data[myindex + MRDPLOT_ALIEN_WZ] = s->alien_w[ZZ];
  data[myindex + MRDPLOT_LANDER_X] = s->lander_x[XX];
  data[myindex + MRDPLOT_LANDER_Y] = s->lander_x[YY];
  data[myindex + MRDPLOT_LANDER_Z] = s->lander_x[ZZ];
  data[myindex + MRDPLOT_LANDER_Q0] = s->lander_q[0];
  data[myindex + MRDPLOT_LANDER_Q1] = s->lander_q[1];
  data[myindex + MRDPLOT_LANDER_Q2] = s->lander_q[2];
  data[myindex + MRDPLOT_LANDER_Q3] = s->lander_q[3];
  data[myindex + MRDPLOT_LANDER_Q_NORM] = s->lander_q_norm;
  data[myindex + MRDPLOT_LANDER_XD] = s->lander_xd[XX];
  data[myindex + MRDPLOT_LANDER_YD] = s->lander_xd[YY];
  data[myindex + MRDPLOT_LANDER_ZD] = s->lander_xd[ZZ];
  data[myindex + MRDPLOT_LANDER_WX] = s->lander_w[XX];
  data[myindex + MRDPLOT_LANDER_WY] = s->lander_w[YY];
  data[myindex + MRDPLOT_LANDER_WZ] = s->lander_w[ZZ];
  data[myindex + MRDPLOT_LANDER_TRQ_X] = s->lander_torque[XX];
  data[myindex + MRDPLOT_LANDER_TRQ_Y] = s->lander_torque[YY];
  data[myindex + MRDPLOT_LANDER_TRQ_Z] = s->lander_torque[ZZ];
  data[myindex + MRDPLOT_LANDER_ROTVEC_X] = s->rotvec[XX];
  data[myindex + MRDPLOT_LANDER_ROTVEC_Y] = s->rotvec[YY];
  data[myindex + MRDPLOT_LANDER_ROTVEC_Z] = s->rotvec[ZZ];
  data[myindex + MRDPLOT_A_R00] = s->alien_r[XX][XX];
  data[myindex + MRDPLOT_A_R01] = s->alien_r[XX][YY];
  data[myindex + MRDPLOT_A_R02] = s->alien_r[XX][ZZ];
  data[myindex + MRDPLOT_A_R10] = s->alien_r[YY][XX];
  data[myindex + MRDPLOT_A_R11] = s->alien_r[YY][YY];
  data[myindex + MRDPLOT_A_R12] = s->alien_r[YY][ZZ];
  data[myindex + MRDPLOT_A_R20] = s->alien_r[ZZ][XX];
  data[myindex + MRDPLOT_A_R21] = s->alien_r[ZZ][YY];
  data[myindex + MRDPLOT_A_R22] = s->alien_r[ZZ][ZZ];
  data[myindex + MRDPLOT_L_R00] = s->lander_r[XX][XX];
  data[myindex + MRDPLOT_L_R01] = s->lander_r[XX][YY];
  data[myindex + MRDPLOT_L_R02] = s->lander_r[XX][ZZ];
  data[myindex + MRDPLOT_L_R10] = s->lander_r[YY][XX];
  data[myindex + MRDPLOT_L_R11] = s->lander_r[YY][YY];
  data[myindex + MRDPLOT_L_R12] = s->lander_r[YY][ZZ];
  data[myindex + MRDPLOT_L_R20] = s->lander_r[ZZ][XX];
  data[myindex + MRDPLOT_L_R21] = s->lander_r[ZZ][YY];
  data[myindex + MRDPLOT_L_R22] = s->lander_r[ZZ][ZZ];
  data[myindex + MRDPLOT_MZX] = s->marker_zero[XX];
  data[myindex + MRDPLOT_MZY] = s->marker_zero[YY];
  data[myindex + MRDPLOT_MZZ] = s->marker_zero[ZZ];
  data[myindex + MRDPLOT_M0X] = s->markers_world[0][XX];
  data[myindex + MRDPLOT_M0Y] = s->markers_world[0][YY];
  data[myindex + MRDPLOT_M0Z] = s->markers_world[0][ZZ];
  data[myindex + MRDPLOT_M1X] = s->markers_world[1][XX];
  data[myindex + MRDPLOT_M1Y] = s->markers_world[1][YY];
  data[myindex + MRDPLOT_M1Z] = s->markers_world[1][ZZ];
  data[myindex + MRDPLOT_M2X] = s->markers_world[2][XX];
  data[myindex + MRDPLOT_M2Y] = s->markers_world[2][YY];
  data[myindex + MRDPLOT_M2Z] = s->markers_world[2][ZZ];
  data[myindex + MRDPLOT_M3X] = s->markers_world[3][XX];
  data[myindex + MRDPLOT_M3Y] = s->markers_world[3][YY];
  data[myindex + MRDPLOT_M3Z] = s->markers_world[3][ZZ];
  data[myindex + MRDPLOT_M4X] = s->markers_world[4][XX];
  data[myindex + MRDPLOT_M4Y] = s->markers_world[4][YY];
  data[myindex + MRDPLOT_M4Z] = s->markers_world[4][ZZ];
  data[myindex + MRDPLOT_M5X] = s->markers_world[5][XX];
  data[myindex + MRDPLOT_M5Y] = s->markers_world[5][YY];
  data[myindex + MRDPLOT_M5Z] = s->markers_world[5][ZZ];
  data[myindex + MRDPLOT_M6X] = s->markers_world[6][XX];
  data[myindex + MRDPLOT_M6Y] = s->markers_world[6][YY];
  data[myindex + MRDPLOT_M6Z] = s->markers_world[6][ZZ];
  data[myindex + MRDPLOT_M7X] = s->markers_world[7][XX];
  data[myindex + MRDPLOT_M7Y] = s->markers_world[7][YY];
  data[myindex + MRDPLOT_M7Z] = s->markers_world[7][ZZ];
  data[myindex + MRDPLOT_ML0X] = s->markers_lander[0][XX];
  data[myindex + MRDPLOT_ML0Y] = s->markers_lander[0][YY];
  data[myindex + MRDPLOT_ML0Z] = s->markers_lander[0][ZZ];
  data[myindex + MRDPLOT_ML1X] = s->markers_lander[1][XX];
  data[myindex + MRDPLOT_ML1Y] = s->markers_lander[1][YY];
  data[myindex + MRDPLOT_ML1Z] = s->markers_lander[1][ZZ];
  data[myindex + MRDPLOT_ML2X] = s->markers_lander[2][XX];
  data[myindex + MRDPLOT_ML2Y] = s->markers_lander[2][YY];
  data[myindex + MRDPLOT_ML2Z] = s->markers_lander[2][ZZ];
  data[myindex + MRDPLOT_ML3X] = s->markers_lander[3][XX];
  data[myindex + MRDPLOT_ML3Y] = s->markers_lander[3][YY];
  data[myindex + MRDPLOT_ML3Z] = s->markers_lander[3][ZZ];
  data[myindex + MRDPLOT_ML4X] = s->markers_lander[4][XX];
  data[myindex + MRDPLOT_ML4Y] = s->markers_lander[4][YY];
  data[myindex + MRDPLOT_ML4Z] = s->markers_lander[4][ZZ];
  data[myindex + MRDPLOT_ML5X] = s->markers_lander[5][XX];
  data[myindex + MRDPLOT_ML5Y] = s->markers_lander[5][YY];
  data[myindex + MRDPLOT_ML5Z] = s->markers_lander[5][ZZ];
  data[myindex + MRDPLOT_ML6X] = s->markers_lander[6][XX];
  data[myindex + MRDPLOT_ML6Y] = s->markers_lander[6][YY];
  data[myindex + MRDPLOT_ML6Z] = s->markers_lander[6][ZZ];
  data[myindex + MRDPLOT_ML7X] = s->markers_lander[7][XX];
  data[myindex + MRDPLOT_ML7Y] = s->markers_lander[7][YY];
  data[myindex + MRDPLOT_ML7Z] = s->markers_lander[7][ZZ];
  data[myindex + MRDPLOT_MN0X] = s->markers_noisy[0][XX];
  data[myindex + MRDPLOT_MN0Y] = s->markers_noisy[0][YY];
  data[myindex + MRDPLOT_MN0Z] = s->markers_noisy[0][ZZ];
  data[myindex + MRDPLOT_MN1X] = s->markers_noisy[1][XX];
  data[myindex + MRDPLOT_MN1Y] = s->markers_noisy[1][YY];
  data[myindex + MRDPLOT_MN1Z] = s->markers_noisy[1][ZZ];
  data[myindex + MRDPLOT_MN2X] = s->markers_noisy[2][XX];
  data[myindex + MRDPLOT_MN2Y] = s->markers_noisy[2][YY];
  data[myindex + MRDPLOT_MN2Z] = s->markers_noisy[2][ZZ];
  data[myindex + MRDPLOT_MN3X] = s->markers_noisy[3][XX];
  data[myindex + MRDPLOT_MN3Y] = s->markers_noisy[3][YY];
  data[myindex + MRDPLOT_MN3Z] = s->markers_noisy[3][ZZ];
  data[myindex + MRDPLOT_MN4X] = s->markers_noisy[4][XX];
  data[myindex + MRDPLOT_MN4Y] = s->markers_noisy[4][YY];
  data[myindex + MRDPLOT_MN4Z] = s->markers_noisy[4][ZZ];
  data[myindex + MRDPLOT_MN5X] = s->markers_noisy[5][XX];
  data[myindex + MRDPLOT_MN5Y] = s->markers_noisy[5][YY];
  data[myindex + MRDPLOT_MN5Z] = s->markers_noisy[5][ZZ];
  data[myindex + MRDPLOT_MN6X] = s->markers_noisy[6][XX];
  data[myindex + MRDPLOT_MN6Y] = s->markers_noisy[6][YY];
  data[myindex + MRDPLOT_MN6Z] = s->markers_noisy[6][ZZ];
  data[myindex + MRDPLOT_MN7X] = s->markers_noisy[7][XX];
  data[myindex + MRDPLOT_MN7Y] = s->markers_noisy[7][YY];
  data[myindex + MRDPLOT_MN7Z] = s->markers_noisy[7][ZZ];

  myindex += N_CHANNELS;
  n_points++;

  return 0;
}

/*****************************************************************************/

int write_matlab_file( char *filename )
{
  FILE *stream;
  int i;
  static int myindex = 0;

  stream = fopen( filename, "w" );
  if ( stream == NULL )
    {
      fprintf( stderr, "Can't open %s for write.\n", filename );
      exit( -1 );
    }
  for ( i = 0; i < n_points; i++ )
    {
      /*
      fprintf( stream, "%g ", data[myindex + MRDPLOT_TIME] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_ANKLE] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_KNEE] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_HIP] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_ANKLED] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_KNEED] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_HIPD] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_ANKLE_TORQUE] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_KNEE_TORQUE] );
      fprintf( stream, "%g ", data[myindex + MRDPLOT_L_HIP_TORQUE] );
      */
      fprintf( stream, "\n" );
      myindex += N_CHANNELS;
    }
  fclose( stream );

  return 0;
}

/*****************************************************************************/

int write_the_mrdplot_file( SIM *s )
{
  MRDPLOT_DATA *d; 

  d = malloc_mrdplot_data( 0, 0 );
  d->filename = generate_file_name();
  d->n_channels = N_CHANNELS;
  d->n_points = n_points;
  d->total_n_numbers = d->n_channels*d->n_points;
  d->frequency = 1/s->time_step;
  d->data = data;
  d->names = names;
  d->units = units;

  write_mrdplot_file( d );

  // write_matlab_file( "dd" );

  return 0;
}

/*****************************************************************************/
