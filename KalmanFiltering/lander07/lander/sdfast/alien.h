/* Sizes */
#define ALIEN_NQ 7
#define ALIEN_NU 6
#define ALIEN_NQU 13

/* Indices for sdfast state */
#define ALIEN_X 0
#define ALIEN_Y 1
#define ALIEN_Z 2
#define ALIEN_Q0 3
#define ALIEN_Q1 4
#define ALIEN_Q2 5
#define ALIEN_Q3 6

#define ALIEN_XD 7
#define ALIEN_YD 8
#define ALIEN_ZD 9
#define ALIEN_WX 10
#define ALIEN_WY 11
#define ALIEN_WZ 12

// Body index definitions (for sdpointf, etc.)
#define ALIEN_WORLD -1
#define ALIEN_BODY 0

// Joint index definitions (for sdhinget, etc.)
// All are joint 0, these are axes
#define ALIEN_JOINT_0_AXIS_X 0
#define ALIEN_JOINT_0_AXIS_Y 1
#define ALIEN_JOINT_0_AXIS_Z 2
#define ALIEN_JOINT_0_AXIS_Q0 3
#define ALIEN_JOINT_0_AXIS_Q1 4
#define ALIEN_JOINT_0_AXIS_Q2 5
#define ALIEN_JOINT_0_AXIS_Q3 6

void alien_init(void);
void alien_pos(int body,
	       double pt[3],
	       double loc[3]);
void alien_state(double timein,
		 double qin[7],
		 double uin[6]);
void alien_stab(double velin,
		double posin);
void alien_printerr(FILE *fnum);
void alien_clearerr(void);
void alien_fmotion(double *time,
		   double state[13],
		   double dstate[13],
		   double dt,
		   double ctol,
		   int *flag,
		   double *errest,
		   int *err);
void alien_pointf(int body,
		  double point[3],
		  double force[3]);
void alien_bodyt(int body,
		 double torque[3]);
