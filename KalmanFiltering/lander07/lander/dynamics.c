/************************************************************************/
/*
  dynamics.c: This is where the numerical integration and SDFAST stuff is done.
*/
/************************************************************************/
/*
x forward
y left
z up
*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix3.h"
#include "main.h"
#include "main2.h"
#include "sdfast/alien.h"
#include "sdfast/lander.h"

/************************************************************************/
/* DEFINES */

#ifdef WIN32
int isnan( double x )
{ return 0; }

int isinf( double x )
{ return 0; }
#endif

/************************************************************************/
/* GLOBAL VARIABLES */

/* Simulation structure */
SIM sim;

/************************************************************************/
/************************************************************************/
// reverse order from sdfast's quaternion to q that starts with cos() term    

void to_sdfast_q( double *q_src, double *q_dst )
{
  q_dst[Q3] = q_src[Q0];
  q_dst[Q0] = q_src[Q1];
  q_dst[Q1] = q_src[Q2];
  q_dst[Q2] = q_src[Q3];
}

void from_sdfast_q( double *q_src, double *q_dst )
{
  q_dst[Q0] = q_src[Q3];
  q_dst[Q1] = q_src[Q0];
  q_dst[Q2] = q_src[Q1];
  q_dst[Q3] = q_src[Q2];
}

/************************************************************************/
// Copy information from SDFAST simulation. Compute marker locations

static void forward_kinematics( SIM *s )
{
  int i, j;
  static int count = 0;
  double offset[N_XYZ] = { 0.0, 0.0, 0.0 };
  double tmp[N_XYZ];

  // set overall system time
  s->time = s->alien_time;

  // get position
  s->alien_x[XX] = s->alien_sdfast_state[ALIEN_X];
  s->alien_x[YY] = s->alien_sdfast_state[ALIEN_Y];
  s->alien_x[ZZ] = s->alien_sdfast_state[ALIEN_Z];

  // reverse order from sdfast's quaternion to q that starts with cos() term
  from_sdfast_q( &(s->alien_sdfast_state[ALIEN_Q0]), s->alien_q );

  // track quaternion norm errors
  s->alien_q_norm = normalize_q( s->alien_q, NULL ) - 1.0;

  // get position
  s->lander_x[XX] = s->lander_sdfast_state[LANDER_X];
  s->lander_x[YY] = s->lander_sdfast_state[LANDER_Y];
  s->lander_x[ZZ] = s->lander_sdfast_state[LANDER_Z];

  // reverse order from sdfast's quaternion to q that starts with cos() term
  from_sdfast_q( &(s->lander_sdfast_state[LANDER_Q0]), s->lander_q );

  // track quaternion norm errors
  s->lander_q_norm = normalize_q( s->lander_q, NULL ) - 1.0;

  /************************************************************/

  // get velocity
  s->alien_xd[XX] = s->alien_sdfast_state[ALIEN_XD];
  s->alien_xd[YY] = s->alien_sdfast_state[ALIEN_YD];
  s->alien_xd[ZZ] = s->alien_sdfast_state[ALIEN_ZD];

  // get angular velocity
  s->alien_w[XX] = s->alien_sdfast_state[ALIEN_WX];
  s->alien_w[YY] = s->alien_sdfast_state[ALIEN_WY];
  s->alien_w[ZZ] = s->alien_sdfast_state[ALIEN_WZ];

  // get velocity
  s->lander_xd[XX] = s->lander_sdfast_state[LANDER_XD];
  s->lander_xd[YY] = s->lander_sdfast_state[LANDER_YD];
  s->lander_xd[ZZ] = s->lander_sdfast_state[LANDER_ZD];

  // get angular velocity
  s->lander_w[XX] = s->lander_sdfast_state[LANDER_WX];
  s->lander_w[YY] = s->lander_sdfast_state[LANDER_WY];
  s->lander_w[ZZ] = s->lander_sdfast_state[LANDER_WZ];

  /************************************************************/

  // For debugging, get sdfast location of coordinate axes
  if ( s->alien_state_called )
    {
      offset[XX] = 1.0;
      alien_pos( ALIEN_BODY, offset, s->a_x_axis );    
      offset[XX] = 0.0;
      offset[YY] = 1.0;
      alien_pos( ALIEN_BODY, offset, s->a_y_axis );    
      offset[YY] = 0.0;
      offset[ZZ] = 1.0;
      alien_pos( ALIEN_BODY, offset, s->a_z_axis );    
      offset[ZZ] = 0.0;
    }

  // quaternion to rotation matrix
  q_to_r( s->alien_q, s->alien_r );

  /* This is the comparison of the rotation matrix to the coordinate axes.
     They should be the same.
  printf( "%g %g %g\n", s->a_x_axis[XX] - s->alien_r[XX][XX],
	  s->a_x_axis[YY] - s->alien_r[YY][XX],
	  s->a_x_axis[ZZ] - s->alien_r[ZZ][XX] );
  printf( "%g %g %g\n", s->a_y_axis[XX] - s->alien_r[XX][YY],
	  s->a_y_axis[YY] - s->alien_r[YY][YY],
	  s->a_y_axis[ZZ] - s->alien_r[ZZ][YY] );
  printf( "%g %g %g\n", s->a_z_axis[XX] - s->alien_r[XX][ZZ],
	  s->a_z_axis[YY] - s->alien_r[YY][ZZ],
	  s->a_z_axis[ZZ] - s->alien_r[ZZ][ZZ] );
  */

  // For debugging, get sdfast location of coordinate axes
  if ( s->lander_state_called )
    {
      offset[XX] = 1.0;
      lander_pos( LANDER_BODY, offset, s->l_x_axis );    
      offset[XX] = 0.0;
      offset[YY] = 1.0;
      lander_pos( LANDER_BODY, offset, s->l_y_axis );    
      offset[YY] = 0.0;
      offset[ZZ] = 1.0;
      lander_pos( LANDER_BODY, offset, s->l_z_axis );    
      offset[ZZ] = 0.0;
    }

  // quaternion to rotation matrix
  q_to_r( s->lander_q, s->lander_r );

  /* This is the comparison of the rotation matrix to the coordinate axes.
     They should be the same.
  printf( "%g %g %g\n", s->l_x_axis[XX] - s->lander_r[XX][XX],
	  s->l_x_axis[YY] - s->lander_r[YY][XX],
	  s->l_x_axis[ZZ] - s->lander_r[ZZ][XX] );
  printf( "%g %g %g\n", s->l_y_axis[XX] - s->lander_r[XX][YY],
	  s->l_y_axis[YY] - s->lander_r[YY][YY],
	  s->l_y_axis[ZZ] - s->lander_r[ZZ][YY] );
  printf( "%g %g %g\n", s->l_z_axis[XX] - s->lander_r[XX][ZZ],
	  s->l_z_axis[YY] - s->lander_r[YY][ZZ],
	  s->l_z_axis[ZZ] - s->lander_r[ZZ][ZZ] );
  */

  // rotate angular velocity in body coordinates to inertial coordinates
  multiply_m3_v3( s->alien_r, s->alien_w, s->alien_w_world );
  multiply_m3_v3( s->lander_r, s->lander_w, s->lander_w_world );

  /************************************************************/

  // create markers
  // THIS IS THE MEASUREMENT PROCESS AND THE CONVERSION TO LANDER COORDINATES
  for( i = 0; i < N_XYZ; i++ )
    tmp[i] = -s->alien_com[i];
  alien_pos( ALIEN_BODY, tmp, s->marker_zero );    
  for( i = 0; i < s->n_markers; i++ )
    {
      alien_pos( ALIEN_BODY, &(s->markers_alien[i][0]),
		 &(s->markers_world[i][0]) );    
      subtract_v3( &(s->markers_world[i][0]), s->lander_x, tmp );
      multiply_transpose_m3_v3( s->lander_r, tmp, &(s->markers_lander[i][0]) );
      for ( j = XX; j <= ZZ; j++ )
	{
	  s->markers_noisy[i][j] 
	    = s->markers_lander[i][j] + s->uniform_noise_min
	    + rand()*(s->uniform_noise_max - s->uniform_noise_min)/RAND_MAX;
	}
    }

  /************************************************************/

  count++;
}

/************************************************************************/
/* Initialize the sdfast state vector */

void set_alien_sdfast_state( SIM *s, double *sdfast_state )
{
  int i, j;

  for( i = 0; i < ALIEN_NQU; i++ )
    {
      s->alien_sdfast_state[i] = sdfast_state[i];
      s->alien_sdfast_stated[i] = 0;
    }

  for( i = 0, j = ALIEN_NQ; i < ALIEN_NU; i++, j++ )
    { 
      s->alien_sdfast_stated[i] = s->alien_sdfast_state[j];
    }

  alien_state( 0.0, s->alien_sdfast_state, s->alien_sdfast_stated );

  s->alien_state_called = 1;

  forward_kinematics( s );

  s->status = OK;
}

/************************************************************************/
/* Initialize the sdfast state vector */

void set_lander_sdfast_state( SIM *s, double *sdfast_state )
{
  int i, j;

  for( i = 0; i < LANDER_NQU; i++ )
    {
      s->lander_sdfast_state[i] = sdfast_state[i];
      s->lander_sdfast_stated[i] = 0;
    }

  for( i = 0, j = LANDER_NQ; i < LANDER_NU; i++, j++ )
    { 
      s->lander_sdfast_stated[i] = s->lander_sdfast_state[j];
    }

  lander_state( 0.0, s->lander_sdfast_state, s->lander_sdfast_stated );

  s->lander_state_called = 1;

  forward_kinematics( s );

  s->status = OK;
}

/************************************************************************/
/* Call this once to do one time operations: Initialize sdfast  */

void init_dynamics( SIM *s )
{
  int i, j;
  double vector[N_XYZ];
  double inertia[N_XYZ][N_XYZ];

  if ( ALIEN_NQU > MAX_N_SDFAST_STATE )
    {
      fprintf( stderr, 
	       "Need to increast MAX_N_SDFAST_STATE (%d) to be at least %d\n",
	       MAX_N_SDFAST_STATE, ALIEN_NQU );
      exit( -1 );
    }

  if ( LANDER_NQU > MAX_N_SDFAST_STATE )
    {
      fprintf( stderr, 
	       "Need to increast MAX_N_SDFAST_STATE (%d) to be at least %d\n",
	       MAX_N_SDFAST_STATE, LANDER_NQU );
      exit( -1 );
    }

  s->status = OK;

  // set up moments of inertia
  alien_iner( ALIEN_BODY, s->alien_I );
  lander_iner( LANDER_BODY, s->lander_I );

  alien_init(); /* initialize SDFAST model */
  lander_init(); /* initialize SDFAST model */

  alien_stab( 2.0*s->sdfast_baumgarte,
		  s->sdfast_baumgarte*s->sdfast_baumgarte ); 
  lander_stab( 2.0*s->sdfast_baumgarte,
		  s->sdfast_baumgarte*s->sdfast_baumgarte ); 

  for( i = 0; i < ALIEN_NQU; i++ )
    s->alien_sdfast_state[i] = 0;
  s->alien_sdfast_state[ALIEN_Q3] = 1.0;
  for( i = 0; i < LANDER_NQU; i++ )
    s->lander_sdfast_state[i] = 0;
  s->lander_sdfast_state[LANDER_Q3] = 1.0;

  set_alien_sdfast_state( s, s->alien_sdfast_state );
  set_lander_sdfast_state( s, s->lander_sdfast_state );

  alien_printerr(stderr);
  lander_printerr(stderr);

}

/************************************************************************/
/* call this many times to restart a simulation */

void reinit_dynamics( SIM *s )
{
  double sdfast_state[MAX_N_SDFAST_STATE];
  double q[N_Q];

  s->status = OK;

  s->time = 0.0;

  // initialize alien artifact position
  sdfast_state[ALIEN_X] = 0;
  sdfast_state[ALIEN_Y] = 0;
  sdfast_state[ALIEN_Z] = 4.0;
  q[Q0] = 1;
  q[Q1] = 0;
  q[Q2] = 0;
  q[Q3] = 0;
  to_sdfast_q( q, &(sdfast_state[ALIEN_Q0]) );

  // initialize alien artifact velocity
  // change w to see how tumbling depends on I
  sdfast_state[ALIEN_XD] = 0.05;
  sdfast_state[ALIEN_YD] = 0.02;
  sdfast_state[ALIEN_ZD] = 0.01;
  sdfast_state[ALIEN_WX] = 0.3/3;
  sdfast_state[ALIEN_WY] = 1.0/3;
  sdfast_state[ALIEN_WZ] = 0.1/3;
  // HACK
  sdfast_state[ALIEN_WX] = 0.0;
  sdfast_state[ALIEN_WY] = 0.0;
  sdfast_state[ALIEN_WZ] = 0.0;

  set_alien_sdfast_state( s, sdfast_state );

  // initialize lander position
  sdfast_state[LANDER_X] = 0.0;
  sdfast_state[LANDER_Y] = 11.0;
  sdfast_state[LANDER_Z] = 4.0;
  /*
  sdfast_state[LANDER_X] = 6.0;
  sdfast_state[LANDER_Y] = 11.0;
  sdfast_state[LANDER_Z] = 2.0;
  */
  // yaw 90 degrees
  q[Q0] = 1.0;
  q[Q1] = 0;
  q[Q2] = 0;
  q[Q3] = 0;
  to_sdfast_q( q, &(sdfast_state[LANDER_Q0]) );

  // start in desired position
  /*
  q[Q0] = 0.70710678118655;
  q[Q1] = 0.0;
  q[Q2] = 0.0;
  q[Q3] = 0.70710678118655;
  to_sdfast_q( q, &(sdfast_state[LANDER_Q0]) );
  */

  // a more twisty startup
  /*
  q[Q0] = 0.0;
  q[Q1] = -0.70710678118655;
  q[Q2] = 0.0;
  q[Q3] = -0.70710678118655;
  to_sdfast_q( q, &(sdfast_state[LANDER_Q0]) );
  */

  // initialize lander velocity
  sdfast_state[LANDER_XD] = 0.0;
  sdfast_state[LANDER_YD] = 0.0;
  sdfast_state[LANDER_ZD] = 0.0;
  // w in body coordinates
  sdfast_state[LANDER_WX] = 0.0;
  sdfast_state[LANDER_WY] = 0.0;
  sdfast_state[LANDER_WZ] = 0.0;

  set_lander_sdfast_state( s, sdfast_state );

  // initialize xxx_q_last stuff
  from_sdfast_q( &(sdfast_state[ALIEN_Q0]), s->alien_q_last );
  from_sdfast_q( &(sdfast_state[LANDER_Q0]), s->lander_q_last );
}

/************************************************************************/
/* This is what is called on each integration step */

void integrate_one_time_step( SIM *s )
{ 
  int i, step;
  int err; 
    /* { OK, DERIVATIVE_DISCONTINUITY, SYSTEM_LOCKED, CONSTRAINTS_ERR } */
  double errest;
  int is_bad_number = 0;
  int flag = 1;

  if( s->status == CRASHED )
    {
      s->time += s->time_step;
      return;
    }

  // clear outstanding error flags
  alien_clearerr();
  lander_clearerr();

  // keep track of old quaternions. 
  for ( i = 0; i < 4; i++ )
    {
      s->alien_q_last[i] = s->alien_q[i];
      s->lander_q_last[i] = s->lander_q[i];
    }

  for( step = 0; step < s->sdfast_integration_steps_per_control_step; step++ )
    {
      alien_fmotion( &(s->alien_time), s->alien_sdfast_state,
			 s->alien_sdfast_stated,
			 s->time_step/s->sdfast_integration_steps_per_control_step,
			 s->sdfast_ctol, &flag, &errest, &err );
      alien_printerr(stderr);
      flag = 1;
      lander_fmotion( &(s->lander_time), s->lander_sdfast_state,
			 s->lander_sdfast_stated,
			 s->time_step/s->sdfast_integration_steps_per_control_step,
			 s->sdfast_ctol, &flag, &errest, &err );
      lander_printerr(stderr);

      for( i = 0; i < ALIEN_NQ; i++ )
	{ // isfinite() should have worked.
	  if ( isnan( s->alien_sdfast_state[i] ) 
	       || isinf( s->alien_sdfast_state[i]) )
	    {
	      is_bad_number = 1;
	      fprintf( stderr, "Nan detected.\n" );
	      break;
	    }
	}

      for( i = 0; i < ALIEN_NU; i++ )
	{ // isfinite() should have worked.
	  if ( isnan( s->alien_sdfast_stated[i+ALIEN_NQ] ) 
	       || isinf( s->alien_sdfast_stated[i+ALIEN_NQ]) ) 
	    {
	      is_bad_number = 1;
	      fprintf( stderr, "Nan detected.\n" );
	      break;
	    }
	}

       for( i = 0; i < LANDER_NQ; i++ )
	{ // isfinite() should have worked.
	  if ( isnan( s->lander_sdfast_state[i] ) 
	       || isinf( s->lander_sdfast_state[i]) )
	    {
	      is_bad_number = 1;
	      fprintf( stderr, "Nan detected.\n" );
	      break;
	    }
	}

      for( i = 0; i < LANDER_NU; i++ )
	{ // isfinite() should have worked.
	  if ( isnan( s->lander_sdfast_stated[i+LANDER_NQ] ) 
	       || isinf( s->lander_sdfast_stated[i+LANDER_NQ]) ) 
	    {
	      is_bad_number = 1;
	      fprintf( stderr, "Nan detected.\n" );
	      break;
	    }
	}

      if ( err > 0 )
	{
	  fprintf( stderr, "sdfast error %d\n", err );
	  break;
	}
    }

  if ( is_bad_number || (err > 0) )
    {
      s->status = CRASHED;
      return;
    }

  forward_kinematics( s );

  /*
  printf( "Press return to continue.\n" );
  getchar();
  */
}

/****************************************************************/
/************************************************************************/
/* SDFAST stuff */
/************************************************************************/
/* This is where the control (joint torques) are applied. May be called many
times per integration step at any time or state. */

void alien_uforce( double t, double *q, double *u )
{
}

/************************************************************************/
/* This is where the control (joint torques) are applied. May be called many
times per integration step at any time or state. */

void lander_uforce( double t, double *q, double *u )
{
  double point[N_XYZ] = { 0.0, 0.0, 0.0 };

  lander_pointf( LANDER_BODY, point, sim.lander_thrust );
  lander_bodyt( LANDER_BODY, sim.lander_torque );
}

/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
