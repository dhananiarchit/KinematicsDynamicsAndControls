/************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix3.h"

/************************************************/
// VECTOR
/************************************************/

void subtract_v3( double *v1, double *v2, double *v_out )
{
  int i;

  for ( i = 0; i < 3; i++ )
    {
      v_out[i] = v1[i] - v2[i];
    }
}

/************************************************/

void cross_product_v3( double *v1, double *v2, double *v_out )
{
  v_out[0] = v1[1]*v2[2] - v1[2]*v2[1];
  v_out[1] = v1[2]*v2[0] - v1[0]*v2[2];
  v_out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

/************************************************/
// MATRIX
/************************************************/

void multiply_m3_v3( double r[3][3], double *v_in, double *v_out )
{
  int i, j;

  for ( i = 0; i < 3; i++ )
    {
      v_out[i] = 0.0;
      for ( j = 0; j < 3; j++ )
	v_out[i] += r[i][j]*v_in[j];
    }
}

/************************************************/

void multiply_transpose_m3_v3( double r[3][3], double *v_in, double *v_out )
{
  int i, j;

  for ( i = 0; i < 3; i++ )
    {
      v_out[i] = 0.0;
      for ( j = 0; j < 3; j++ )
	v_out[i] += r[j][i]*v_in[j];
    }
}

/************************************************/

void invert_m3( double m[3][3], double result[3][3] )
{
  double one_over_determinant;

  one_over_determinant = 1/(- m[0][2]*m[1][1]*m[2][0] + m[0][1]*m[1][2]*m[2][0] 
			    + m[0][2]*m[1][0]*m[2][1] - m[0][0]*m[1][2]*m[2][1]
			    - m[0][1]*m[1][0]*m[2][2] + m[0][0]*m[1][1]*m[2][2]);
  result[0][0] = (- m[1][2]*m[2][1] + m[1][1]*m[2][2])*one_over_determinant;
  result[0][1] = (m[0][2]*m[2][1] - m[0][1]*m[2][2])*one_over_determinant;
  result[0][2] = (- m[0][2]*m[1][1] + m[0][1]*m[1][2])*one_over_determinant; 
  result[1][0] = (m[1][2]*m[2][0] - m[1][0]*m[2][2])*one_over_determinant;
  result[1][1] = (- m[0][2]*m[2][0] + m[0][0]*m[2][2])*one_over_determinant;
  result[1][2] = (m[0][2]*m[1][0] - m[0][0]*m[1][2])*one_over_determinant;
  result[2][0] = (- m[1][1]*m[2][0] + m[1][0]*m[2][1])*one_over_determinant;
  result[2][1] = (m[0][1]*m[2][0] - m[0][0]*m[2][1])*one_over_determinant;
  result[2][2] = (- m[0][1]*m[1][0] + m[0][0]*m[1][1])*one_over_determinant;
}

/************************************************/
// QUATERNION
/************************************************/

/*
Need to include
convert to Euler angles
http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
rotation matrix to quaternion and convert to axis angle
http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
Google "quaternion" for more stuff.
 */

/************************************************/

void invert_q( double *q_in, double *q_out )
{
  int i;
  q_out[0] = q_in[0];
  for ( i = 1; i < 4; i++ )
    q_out[i] = -q_in[i];
}

/************************************************/

// make the quaternion length = 1.
double normalize_q( double *q_in, double *q_out )
{
  int i;
  double length_2 = 0;
  double length;
  double scale;

  for ( i = 0; i < 4; i++ )
    length_2 += q_in[i]*q_in[i];
  length = sqrt( length_2 );
  scale = 1.0/length;
  if ( q_out != NULL )
    {
      for ( i = 0; i < 4; i++ )
	q_out[i] = scale*q_in[i];
    }
  return length;
}

/************************************************/

// convert a quaternion to a rotation matrix
void q_to_r( double *q, double r[3][3] )
{
  r[0][0] = 2*(q[0]*q[0] + q[1]*q[1]) - 1.0;
  r[0][1] = 2*(q[1]*q[2] - q[0]*q[3]);
  r[0][2] = 2*(q[1]*q[3] + q[0]*q[2]);
  r[1][0] = 2*(q[1]*q[2] + q[0]*q[3]);
  r[1][1] = 2*(q[0]*q[0] + q[2]*q[2]) - 1.0;
  r[1][2] = 2*(q[2]*q[3] - q[0]*q[1]);
  r[2][0] = 2*(q[1]*q[3] - q[0]*q[2]);
  r[2][1] = 2*(q[2]*q[3] + q[0]*q[1]);
  r[2][2] = 2*(q[0]*q[0] + q[3]*q[3]) - 1.0;
}

/************************************************/
// apply two rotations. Not sure which is first.

void compose_q( double *q, double *p, double *result )
{
  result[0] = q[0]*p[0] - q[1]*p[1] - q[2]*p[2] - q[3]*p[3];
  result[1] = q[0]*p[1] + q[1]*p[0] + q[2]*p[3] - q[3]*p[2];
  result[2] = q[0]*p[2] + q[2]*p[0] + q[3]*p[1] - q[1]*p[3];
  result[3] = q[0]*p[3] + q[3]*p[0] + q[1]*p[2] - q[2]*p[1];
}

/************************************************/
// Create a 3 vector that is the axis of rotation times the angle

void q_to_rotvec( double *q, double *rotvec )
{
  int i;
  double s;
  double ang;

  s = sqrt( q[1]*q[1] + q[2]*q[2] + q[3]*q[3] );
  ang = 2*atan2( s, q[0] );
  if ( fabs( s ) > 1e-7 )
    {
      for ( i = 0; i < 3; i++ )
	rotvec[i] = ang*q[i+1]/s;
    }
  else
    {
      for ( i = 0; i < 3; i++ )
	rotvec[i] = 0.0;
    }
}

/************************************************/
/************************************************/
