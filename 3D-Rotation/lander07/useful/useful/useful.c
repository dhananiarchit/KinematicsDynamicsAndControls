/****************************************************************************/
/****************************************************************************/
/* INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <setjmp.h>
#include "useful.h"

/****************************************************************************/

/****************************************************************************/
/* MATH */
/****************************************************************************/

float square_float( float x )
{
  return x*x;
}

/****************************************************************************/

float sqf( float x )
{
  return x*x;
}

/*****************************************************************************/

double square_double( double x )
{
  return x*x;
}

/*****************************************************************************/

double sqd( double x )
{
  return x*x;
}

/****************************************************************************/

float random_float( float min, float max )
{
  return (float) ( scalbn( (double) random(), -31 )*(max-min) + min );
}

/****************************************************************************/

float randomf( float min, float max )
{
  return (float) ( scalbn( (double) random(), -31 )*(max-min) + min );
}

/****************************************************************************/

double random_double( double min, double max )
{
  return (double) ( scalbn( (double) random(), -31 )*(max-min) + min );
}

/****************************************************************************/

double randomd( min, max )
     double min, max;
{
  return (double) ( scalbn( (double) random(), -31 )*(max-min) + min );
}

/****************************************************************************/
/* Random int less than bound */

int random_int( int bound )
{
  int result;

  result = (int) random_float( 0.0, (float) bound );
  if ( result >= bound ) 
    result = bound - 1;
  if ( result < 0 )
    result = 0;
  return result;
}

/****************************************************************************/
/* Random int less than bound */

int randomi( int bound )
{
  int result;

  result = (int) random_float( 0.0, (float) bound );
  if ( result >= bound ) 
    result = bound - 1;
  if ( result < 0 )
    result = 0;
  return result;
}

/****************************************************************************/

double gaussian_double( double mean, double stddev )
{
  static int have_n_numbers = 0;
  static double number = 0.0;
  double n1, n2;
  double rsq, fac;

  switch( have_n_numbers )
    {
    case 1:
      have_n_numbers = 0;
      return number*stddev + mean;
      break;
    case 0:
      do
	{
	  n1 = 2.0*random()/2.147483647000000e+09 - 1.0;
	  n2 = 2.0*random()/2.147483647000000e+09 - 1.0;
	  rsq = n1*n1 + n2*n2;
	}
      while ( rsq >= 1.0 || rsq == 0.0 );
      fac = sqrt( -2.0*log(rsq)/rsq );
      number = n1*fac;
      have_n_numbers = 1;
      // printf( "%g %g %g %g %g %g\n", n1, n2, rsq, fac, n1*fac, n2*fac );
      return n2*fac*stddev + mean;
    }
}

/****************************************************************************/

double gaussiand( double mean, double stddev )
{
  return gaussian_double( mean, stddev );
}

/****************************************************************************/
/* File based random seed management */

int set_seed( file_name )
     char *file_name;
{     
  FILE *stream;
  int seed;

  stream = fopen( file_name, "r" );
  if ( stream != NULL ) 
  {
    fscanf( stream, "%d", &seed );
    fclose( stream );
  }
  else
    seed = 1;
  printf( "seed = %d\n", seed ); 
  srandom( seed++ );
  stream = myfopen( file_name, "w" );
  fprintf( stream, "%d\n", seed );
  fclose( stream );
  return seed;
}

/****************************************************************************/
/* I/O */
/****************************************************************************/

int scanf_ivector( stream, vector, n )
     FILE *stream;
     int *vector;
     int n;
{
  int i;
  
  for( i = 0; i < n; i++ )
    fscanf( stream, "%d", &(vector[i]) );
  fscanf( stream, "\n" ); /* read last character. */
  return n;
}

/****************************************************************************/

int printf_ivector( stream, vector, n )
     FILE *stream;
     int *vector;
     int n;
{
  int i;
  
  for( i = 0; i < n; i++ )
    fprintf( stream, "%d ", vector[i] );
  fprintf( stream, "\n" );
  return n;
}

/****************************************************************************/
/****************************************************************************/

int scanf_fvector( stream, vector, n )
     FILE *stream;
     float *vector;
     int n;
{
  int i;
  
  for( i = 0; i < n; i++ )
    fscanf( stream, "%f", &(vector[i]) );
  fscanf( stream, "\n" ); /* read last character. */
  return n;
}

/****************************************************************************/

int printf_fvector( stream, vector, n )
     FILE *stream;
     float *vector;
     int n;
{
  int i;
  
  for( i = 0; i < n; i++ )
    fprintf( stream, "%g ", vector[i] );
  fprintf( stream, "\n" );
  return n;
}

/****************************************************************************/

int scanf_dvector( stream, vector, n )
     FILE *stream;
     double *vector;
     int n;
{
  int i;
  
  for( i = 0; i < n; i++ )
    fscanf( stream, "%lf", &(vector[i]) );
  fscanf( stream, "\n" ); /* read last character. */
  return n;
}

/****************************************************************************/

int printf_dvector( stream, vector, n )
     FILE *stream;
     double *vector;
     int n;
{
  int i;
  
  for( i = 0; i < n; i++ )
    fprintf( stream, "%lg ", vector[i] );
  fprintf( stream, "\n" );
  return n;
}

/****************************************************************************/
/****************************************************************************/

int
create_directory( name )
     char *name;
{
  int status;

  printf( "mkdir %s\n", name );
  /* printf( "%d 0x%x\n", status, status ); */
  status = mkdir( name, 07777 );
  if ( status == 0 )
    return TRUE;
  printf( "create_directory failed: %d; %s\n", status, name );
  exit( -1 );
}

/****************************************************************************/

int
rm( name )
     char *name;
{
  int status;
  char command[10000];

  sprintf( command, "rm %s", name );
  status = system( command );
  printf( "%s: %d\n", command, status );
  if ( status == 0 )
    return TRUE;
  return FALSE;
}

/****************************************************************************/

char *string_cat( s1, s2, s3 )
     char *s1, *s2, *s3;
{

  strcpy( s3, s1 );
  strcat( s3, s2 );
  return s3;
}

/****************************************************************************/

FILE *xmyfopen( char *filename, char *action, char *file, int line )
{
  FILE *stream;

  stream = fopen( filename, action );
  if ( stream == NULL )
    perr( "myfopen", file, line, "fopen( %s, %s) failed\n", filename, action );
  /*
    {
      fprintf( stderr, "fopen failed: %s %s\n", filename, action );
      exit( -1 );
    }
  */
}

/****************************************************************************/
/* Does this correctly handle (4G-1) 32bit addresses?,
64 bit addresses? */

char *xmyalloc(size, file, line)
    long size;
    char *file;
    int line;
/*----------------------------------------------------------------------
 * size: amount of memory in bytes to be allocated
 *
 * effects: allocates size bytes of memory and returns a pointer to it.
 *          Prints out error message if the memory cannot be allocated.
 ----------------------------------------------------------------------*/
{
    static long total_mem = 0;
    char *new_ptr;

    if (size <= 0)
      perr( "myalloc", file, line, "Absurd block size %d\n", size );
    /*
      {
	fprintf( stderr, "Absurd block size %d\n", size );
	exit( -1 );
      }
    */

    new_ptr = (char *) malloc(size);

    if (new_ptr == NULL)
      perr( "myalloc", file, line, "Memory allocation failed for block of size %d, total allocated: %d\n", size, total_mem);
    /*
      {
	fprintf( stderr, "Memory allocation failed for block of size %d, total allocated: %d\n",
		 size, total_mem );
	exit( -1 );
      }
    */
    total_mem += size;

/*  printf("allocating memory size %d, file %s, line %d, %x\n",total_mem, file, line, new_ptr);*/

    return new_ptr;
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

/*****************************************************************************/
/************************************************************************/
/****************************************************************************/
/****************************************************************************/
/************************************************************************/
/* write array to output file */

int fwrite_float_array( char *name, float *array, int size )
{
  FILE *output;
  int n_written;

  output = fopen( name, "w" );
  if ( output == NULL )
    {
      fprintf( stderr, "Couldn't open file %s.\n", name );
      exit( -1 );
    }
  n_written = fwrite( (void *) array, sizeof ( float ), size, output );
  fclose( output );

  if ( n_written < size )
    {
      fprintf( stderr, "fwrite_float_array( %s ): Write size error %d < %d\n",
	       name, n_written, size );
      exit( -1 );
    }

  return TRUE;
}

/************************************************************************/
/* read an array from a file */

int fread_float_array( char *name, float *array, int size )
{
  int n_read;
  FILE *input;

  input = fopen( name, "r" );
  if ( input == NULL )
    {
      fprintf( stderr, "Couldn't open file %s.\n", name );
      exit( -1 );
    }

  n_read = fread( (void *) array, sizeof ( float ), size, input );
  fclose( input );

  if ( n_read < size )
    {
      fprintf( stderr, "fread_float_array( %s ): Read size error %d < %d\n",
	       name, n_read, size );
      exit( -1 );
    }

  return TRUE;
}

/************************************************************************/
/* write array to output file */

int fwrite_int_array( char *name, int *array, int size )
{
  FILE *output;
  int n_written;

  output = fopen( name, "w" );
  if ( output == NULL )
    {
      fprintf( stderr, "Couldn't open file %s.\n", name );
      exit( -1 );
    }
  n_written = fwrite( (void *) array, sizeof ( float ), size, output );
  fclose( output );

  if ( n_written < size )
    {
      fprintf( stderr, "fwrite_int_array( %s ): Write size error %d < %d\n",
	       name, n_written, size );
      exit( -1 );
    }

  return TRUE;
}

/************************************************************************/
/* read an array from a file */

int fread_int_array( char *name, int *array, int size )
{
  int n_read;
  FILE *input;

  input = fopen( name, "r" );
  if ( input == NULL )
    {
      fprintf( stderr, "Couldn't open file %s.\n", name );
      exit( -1 );
    }

  n_read = fread( (void *) array, sizeof ( int ), size, input );
  fclose( input );

  if ( n_read < size )
    {
      fprintf( stderr, "fread_int_array( %s ): Read size error %d < %d\n",
	       name, n_read, size );
      exit( -1 );
    }

  return TRUE;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/* This is used to force an error, to allowing debugging in the right
context. Probably not portable */

int die()
{
  int *p;

  p = (int *) 0;
  *p = 5;
}

/****************************************************************************/
/*----------------------------------------------------------------------
perr()

 * procedure: name of the procedure in which error ocurred.
 * 
 * file_name: name of file in which procedure was called
 *
 * line: line at which the procedure was called in a file
 *
 * fmt: a printf-style format string, including number formats etc.
 *
 * var_arglist: a list of zero or more arguments which match the format 
 *              of format_string.  Just like in printf.
 *
 * effects: prints out helpful debugging info and terminates the program.
 ----------------------------------------------------------------------*/
/****************************************************************************/

//#ifdef TRY2

#include <stdarg.h>

void perr( char *procedure, char *file_name, int line, char *fmt, ... )
{
  va_list args;

  va_start( args, fmt );
  fflush( stdout );

  /* print name of function causing error */
  (void) fprintf( stderr,
		 "\n*** ERROR in %s,\n called in file: %s, line: %d\n",
		 procedure, file_name, line );

  /* print out remainder of message */
  (void) vfprintf( stderr, fmt, args );
  va_end(args);
  fflush( stderr );

/*  longjmp(jmp,1);*/
  (void) exit(-1);
}

//#endif

/****************************************************************************/

#ifdef COMMENT
No more varargs:
// #include <varargs.h>
/*
/usr/lib/gcc/i386-redhat-linux/3.4.4/include/varargs.h:4:2: #error "GCC no longer implements <varargs.h>."
/usr/lib/gcc/i386-redhat-linux/3.4.4/include/varargs.h:5:2: #error "Revise your code to use <stdarg.h>."
*/

/*VARARGS0*/
void perr(va_alist) 
va_dcl
{
    va_list args;
    char *fmt;

    va_start(args);
    /* print name of function causing error */
    (void) fprintf(stderr, "\n*** ERROR in %s,\n called in file: %s, line: %d\n", va_arg(args, char *), va_arg(args, char *), va_arg(args, int));
    fmt = va_arg(args, char *);
    /* print out remainder of message */

    (void) vfprintf(stderr, fmt, args);
    va_end(args);

/*  longjmp(jmp,1);*/
    (void) exit(-1);
}

#endif

/****************************************************************************/
