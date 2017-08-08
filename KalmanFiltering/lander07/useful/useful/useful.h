#define TRUE 1
#define FALSE 0

#define OKAY 0
#define OK OKAY
#define ERROR 1

/* OS limitations */
#define MAX_FWRITE_BYTES 1000000000
#define MAX_FREAD_BYTES 1000000000

/* MATH */
#define PI M_PI
#define G (9.81)
#define pos_round(f) ((int) ((f) + 0.5))
#define square(x) ((x)*(x))
#define sq(x) ((x)*(x))
float square_float( float x );
float sqf( float x );
double square_double( double x );
double sqd( double x);
float random_float( float min, float max );
float randomf( float min, float max );
double random_double( double min, double max );
double randomd( double min, double max );
int random_int( int bound );
int randomi( int bound );
double gaussian_double( double mean, double stddev );
double gaussiand( double mean, double stddev );

/* I/O */

/* Allocation */
char *xmyalloc( long size, char *file, int line);
#define myalloc(s) ((char *)xmyalloc((s),__FILE__,__LINE__))
#define iv(n) int_vector(n)
#define fv(n) float_vector(n)
#define dv(n) double_vector(n)
#define ivector(n) int_vector(n)
#define fvector(n) float_vector(n)
#define dvector(n) double_vector(n)
#define int_vector(n) ((int *)xmyalloc(((unsigned long)n)*sizeof(int),__FILE__,__LINE__))
#define float_vector(n) ((float *)xmyalloc(((unsigned long)n)*sizeof(float),__FILE__,__LINE__))
#define double_vector(n) ((double *)xmyalloc(((unsigned long)n)*sizeof(double),__FILE__,__LINE__))

/* I/O */
FILE *xmyfopen();
#define myfopen(a1,a2) ((FILE *)xmyfopen((a1,a2),__FILE__,__LINE__))

/* Error handling */
void perr( char *name, char *file_name, int line, char *fmt, ... );
// void perr(); /* See useful.c for arguments */

