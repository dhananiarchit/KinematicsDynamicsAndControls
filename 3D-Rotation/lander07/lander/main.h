/******************************************************************/
/* 
Defines, typedefs, and structs
*/
/******************************************************************/

/* These are handy constants. XX rather than X to avoid math.h conflicts */
#define N_XYZ 3
#define XX 0
#define YY 1
#define ZZ 2

// Quaternion. Q0 is cos(a/2), Q1-3 is axis*sin(a/2)
#define N_Q 4
#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3

/* Status flags */
#define OK 0
#define CRASHED 1

/* May have N_CONTROLS != N_CTRL_INPUTS eventually
   include COM_X, COM_Y, TORSO_PITCH, or other variables in N_CTRL_INPUTS */
/* Joints (for trajectories and gains) */
#define N_DOFS 6
#define N_CONTROLS 6
#define N_CTRL_INPUTS 6

/* This is used to allocate parameter vectors etc. */
#define MAX_N_PARAMETERS 100

/* This is used to allocate sdfast state */
#define MAX_N_SDFAST_STATE 100

#define MAX_N_MARKERS 100

/******************************************************************/

/* For each parameter read in from a file we have this information */
typedef struct parameter
{
  char *name;
  double value;
  int optimize;
  int regularize;
  double nominal_value;
  double regularize_weight;
  struct parameter *next;
  double *pointer;
} PARAMETER;

/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
// Overall simulation structure.

typedef struct {

  // *** COMMON VARIABLES ACROSS ALL SIMULATIONS

  double time_step; // controller time step    
  double time;      // current time in simulation
  double alien_time;
  double lander_time;
  double duration;   // simulation duration
  int status;       // Are we CRASHED? 

  // Joint angles
  double alien_x[N_XYZ]; // location of alien
  double alien_q[N_Q]; // quaternion giving alien orientation
  double alien_q_last[N_Q]; // quaternion giving alien orientation
  double alien_q_norm; // quaternion length
  double lander_x[N_XYZ]; // location of lander craft
  double lander_q[N_Q]; // quaternion giving spacecraft orientation
  double lander_q_last[N_Q]; // quaternion giving spacecraft orientation
  double lander_q_norm; // quaternion length

  // rotation matrices
  double alien_r[N_XYZ][N_XYZ]; // computed from quaternion
  double lander_r[N_XYZ][N_XYZ]; // computed from quaternion

  // Joint velocities
  double alien_xd[N_XYZ]; // velocity of alien
  double alien_w[N_Q]; // angular velocity in body coordinates
  double alien_w_world[N_Q]; // angular velocity in world coordinates
  double lander_xd[N_XYZ]; // location of lander craft
  double lander_w[N_Q]; // angular velocity in body coordinates
  double lander_w_world[N_Q]; // angular velocity in world coordinates

  // commands
  double lander_thrust[N_XYZ]; // translational thrusters in body coords.
  double lander_torque[N_XYZ]; // rotational torques in body coords.

  /* no limits!
  double lander_thrust_min[N_XYZ]; // translational thrusters
  double lander_torques_min[N_XYZ]; // rotational torques
  double lander_thrust_max[N_XYZ]; // translational thrusters
  double lander_torques_max[N_XYZ]; // rotational torques
  */

  // alien center of mass (only effect is to offset markers)
  double alien_com[N_XYZ];
  double marker_zero[N_XYZ]; // useful for plotting.

  // markers
  int n_markers;
  double markers_alien[MAX_N_MARKERS][N_XYZ];
  double markers_world[MAX_N_MARKERS][N_XYZ];
  double markers_lander[MAX_N_MARKERS][N_XYZ];
  double markers_noisy[MAX_N_MARKERS][N_XYZ];
  double uniform_noise_min;
  double uniform_noise_max;

  // other useful variables
  double a_x_axis[N_XYZ]; // sdfast version of location of axis in world coords.
  double a_y_axis[N_XYZ];
  double a_z_axis[N_XYZ];
  double l_x_axis[N_XYZ]; // sdfast version of location of axis in world coords.
  double l_y_axis[N_XYZ];
  double l_z_axis[N_XYZ];

  // *** KINEMATIC AND DYNAMIC PARAMETERS

  // *** DYNAMICS **************

  double alien_I[N_XYZ][N_XYZ]; // I in body coordinates
  double lander_I[N_XYZ][N_XYZ]; // I in body coordinates

  // SDFAST
  double alien_sdfast_state[MAX_N_SDFAST_STATE]; // sdfast state
  double alien_sdfast_stated[MAX_N_SDFAST_STATE]; // derivative of sdfast state
  double lander_sdfast_state[MAX_N_SDFAST_STATE]; // sdfast state
  double lander_sdfast_stated[MAX_N_SDFAST_STATE];
         // derivative of sdfast state
  int sdfast_integration_steps_per_control_step;
  double sdfast_ctol;
  double sdfast_baumgarte;

  // sdfast flags to prevent error
  int alien_state_called;
  int lander_state_called;

  // *** CONTROLLER **************

  double lander_x_d[N_XYZ]; // desired location of lander craft
  double lander_q_d[N_Q]; // desired orientation of lander craft
  double rotvec[N_XYZ]; // orientation error of lander craft
  double lander_thrust_world[N_XYZ];
         // translational thrusters in world coords.
  double lander_torque_world[N_XYZ]; // rotational torques in world coords.

  /* Useful variables for optimization */
  int n_parameters;
  double all_time_low_cost;
  double debug_criterion;
  int func_calls;
  int n_func_calls_per_eval;
  PARAMETER *params;
  char output_file[10000];
  int iter;

  /* debugging message flags */
  int controller_print;

  // *** MISCELLANEOUS ***********************

  // random stuff
  // Make this thread safe: random number generator seed for rand_r() and rand()
  int rand_seed;
  double rand_scale;

} SIM;

/******************************************************************/
