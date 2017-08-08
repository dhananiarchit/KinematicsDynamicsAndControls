/*****************************************************************************/
/*
  controller.c: control strategy.
*/
/*****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "matrix3.h"
#include "main.h"
#include "main2.h"
#include "sdfast/alien.h"
#include "sdfast/lander.h"

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/* call this once to do one-time initialize: allocate memeory etc. */

void init_controller( SIM *s )
{
}

/*****************************************************************************/
/* call this many times to restart a controller */

FILE *marker_file = NULL;
FILE *marker_file_noisy = NULL;
FILE *state_file = NULL;

void reinit_controller( SIM *s )
{
  marker_file = fopen( "markers", "w" );
  if ( marker_file == NULL )
    {
      fprintf( stderr, "Can't open marker file.\n" );
      exit( -1 );
    }
  marker_file_noisy = fopen( "markersn", "w" );
  if ( marker_file_noisy == NULL )
    {
      fprintf( stderr, "Can't open marker file.\n" );
      exit( -1 );
    }
  state_file = fopen( "states", "w" );
  if ( state_file == NULL )
    {
      fprintf( stderr, "Can't open state file.\n" );
      exit( -1 );
    }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

int controller( SIM *s )
{
  int i;
  static int count = -1;
  double k_x = 1.0;
  double b_x = 2.0;
  double k_r = 1.0;
  double b_r = 2.0;
  double q_minus[N_Q];
  double q_diff[N_Q];

  count++;

  // desired lander position
  s->lander_x_d[XX] = 0.0;
  // s->lander_x_d[YY] = 6.0;
  s->lander_x_d[YY] = 11.0;
  s->lander_x_d[ZZ] = 4.0;

  // desired lander orientation
  s->lander_q_d[Q0] = 1.0;
  s->lander_q_d[Q1] = 0.0;
  s->lander_q_d[Q2] = 0.0;
  s->lander_q_d[Q3] = 0.0;
  /*
  s->lander_q_d[Q0] = 0.70710678118655;
  s->lander_q_d[Q1] = 0.0;
  s->lander_q_d[Q2] = 0.0;
  s->lander_q_d[Q3] = 0.70710678118655;
  */

  // lander translational control (PD servo)
  for ( i = 0; i < 3; i++ )
    {
      s->lander_thrust_world[i] = 
	k_x*( s->lander_x_d[i] - s->lander_x[i] ) +
	b_x*( - s->lander_xd[i] );
    }
  multiply_transpose_m3_v3( s->lander_r, s->lander_thrust_world, 
			    s->lander_thrust );

  // lander orientation control
  // Attempt to do PD control, but orientations not vectors, so complicated
  // "subtract quaternions"
  invert_q( s->lander_q, q_minus );
  compose_q( q_minus, s->lander_q_d, q_diff );
  q_to_rotvec( q_diff, s->rotvec ); 
  // printf( "%g %g %g %g\n", q_diff[0], q_diff[1], q_diff[2], q_diff[3] );
  // printf( "%g %g %g\n", s->rotvec[0], s->rotvec[1], s->rotvec[2] );

  // PD servo for orientation
  // w and rotvec are in body coordinates.
  for ( i = 0; i < N_XYZ; i++ )
    {
      s->lander_torque[i] = k_r*s->rotvec[i] - b_r*s->lander_w[i];
    }
  multiply_m3_v3( s->lander_r, s->lander_torque, s->lander_torque_world );

  // To get better control should compute desired acceleration and use
  // inverse dynamics to compute torque.

  // Handy for generating a data file for Matlab
  if ( count % 10 == 0 )
    {
      // printf( "%d ", count );
      for( i = 0; i < s->n_markers; i++ )
	{
	  fprintf( marker_file, "%20.15f %20.15f %20.15f ",
		   s->markers_lander[i][0],
		   s->markers_lander[i][1], s->markers_lander[i][2] );
	}
      fprintf( marker_file, "\n" );
      fflush( marker_file );

      for( i = 0; i < s->n_markers; i++ )
	{
	  fprintf( marker_file_noisy, "%20.15f %20.15f %20.15f ",
		   s->markers_noisy[i][0],
		   s->markers_noisy[i][1], s->markers_noisy[i][2] );
	}
      fprintf( marker_file_noisy, "\n" );
      fflush( marker_file_noisy );

      fprintf( state_file, "%20.15f %20.15f %20.15f ",
	       s->alien_x[0] - s->lander_x[0],
	       s->alien_x[1] - s->lander_x[1],
	       s->alien_x[2] - s->lander_x[2] );
      fprintf( state_file, "%20.15f %20.15f %20.15f ",
	       s->alien_xd[0],
	       s->alien_xd[1],
	       s->alien_xd[2] );
      fprintf( state_file, "%20.15f %20.15f %20.15f %20.15f ",
	       s->alien_q[0],
	       s->alien_q[1],
	       s->alien_q[2],
	       s->alien_q[3] );
      fprintf( state_file, "%20.15f %20.15f %20.15f ",
	       s->alien_w_world[0],
	       s->alien_w_world[1],
	       s->alien_w_world[2] );
      fprintf( state_file, "\n" );
      fflush( state_file );
    }

  return 0;
}

/*****************************************************************************/
