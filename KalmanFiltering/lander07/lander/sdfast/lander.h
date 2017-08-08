/* Sizes */
#define LANDER_NQ 7
#define LANDER_NU 6
#define LANDER_NQU 13

/* Indices for sdfast state */
#define LANDER_X 0
#define LANDER_Y 1
#define LANDER_Z 2
#define LANDER_Q0 3
#define LANDER_Q1 4
#define LANDER_Q2 5
#define LANDER_Q3 6

#define LANDER_XD 7
#define LANDER_YD 8
#define LANDER_ZD 9
#define LANDER_WX 10
#define LANDER_WY 11
#define LANDER_WZ 12

// Body index definitions (for sdpointf, etc.)
#define LANDER_WORLD -1
#define LANDER_BODY 0

// Joint index definitions (for sdhinget, etc.)
// All are joint 0, these are axes
#define LANDER_JOINT_0_AXIS_X 0
#define LANDER_JOINT_0_AXIS_Y 1
#define LANDER_JOINT_0_AXIS_Z 2
#define LANDER_JOINT_0_AXIS_Q0 3
#define LANDER_JOINT_0_AXIS_Q1 4
#define LANDER_JOINT_0_AXIS_Q2 5
#define LANDER_JOINT_0_AXIS_Q3 6


void lander_init(void);
void lander_pos(int body,
	       double pt[3],
	       double loc[3]);
void lander_state(double timein,
		  double qin[7],
		  double uin[6]);
void lander_stab(double velin,
		 double posin);
void lander_printerr(FILE *fnum);
void lander_clearerr(void);
void lander_fmotion(double *time,
		    double state[13],
		    double dstate[13],
		    double dt,
		    double ctol,
		    int *flag,
		    double *errest,
		    int *err);
void lander_pointf(int body,
		   double point[3],
		   double force[3]);
void lander_bodyt(int body,
		  double torque[3]);
