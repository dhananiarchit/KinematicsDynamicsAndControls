/*****************************************************************************/
/*
  parameters.c: manage simulation parameters
*/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#include "main.h"
#include "main2.h"

/*****************************************************************************/

void
init_default_parameters( SIM *s )
{
  int i, j;
  double x, y, z;

  /* Overall parameters */
  s->duration = 50.0;
  // s->duration = 0.02;
  s->time_step = 0.01;
  s->rand_scale = 0.0;
  s->rand_seed = 1;
  s->uniform_noise_min = -1.0;
  s->uniform_noise_max = 1.0;

  s->sdfast_integration_steps_per_control_step = 1;
  s->sdfast_ctol = 1e-1; /* constraint tolerance */
  s->sdfast_baumgarte = 0.01;

  s->n_func_calls_per_eval = 1;
  s->all_time_low_cost = 1e20;
  s->debug_criterion = 1;

  s->alien_state_called = 0;
  s->lander_state_called = 0;

  for( i = 0; i < 3; i++ )
    for( j = 0; j < 3; j++ )
      {
	s->alien_I[i][j] = 0.0;
	s->lander_I[i][j] = 0.0;
      }

  // sdfast code expects diagonal I until fix .sd file
  s->alien_I[XX][XX] = 1.571428571428571;
  s->alien_I[XX][YY] = 0.0;
  s->alien_I[XX][ZZ] = 0.0;

  s->alien_I[YY][XX] = 0.0;
  s->alien_I[YY][YY] = 5.362637362637362;
  s->alien_I[YY][ZZ] = 0.0;

  s->alien_I[ZZ][XX] = 0.0;
  s->alien_I[ZZ][YY] = 0.0;
  s->alien_I[ZZ][ZZ] = 7.065934065934067;

  s->lander_I[XX][XX] = 4.0;
  s->lander_I[YY][YY] = 1.0;
  s->lander_I[ZZ][ZZ] = 0.25;

  s->alien_com[XX] = 0.5;
  s->alien_com[YY] = 1.0;
  s->alien_com[ZZ] = 1.5;

  s->n_markers = 0;
  for ( x = -1.0; x < 1.1; x += 2.0 )
    for ( y = -2.0; y < 2.1; y += 4.0 )
      for ( z = -3.0; z < 3.1; z += 6.0 )
	{
	  s->markers_alien[s->n_markers][XX] = x - s->alien_com[XX];
	  s->markers_alien[s->n_markers][YY] = y - s->alien_com[YY];
	  s->markers_alien[s->n_markers][ZZ] = z - s->alien_com[ZZ];
	  /*
	  printf( "%20.15f %20.15f %20.15f\n",
		  s->markers_alien[s->n_markers][XX],
		  s->markers_alien[s->n_markers][YY],
		  s->markers_alien[s->n_markers][ZZ] );
	  */
	  s->n_markers++;
	}
}

/*****************************************************************************/
/******************************************************************/

PARAMETER *malloc_parameter()
{
  PARAMETER *result;

  result = (PARAMETER *) malloc( sizeof( PARAMETER ) );
  if ( result == NULL )
    {
      fprintf( stderr, "No memory to allocate PARAMETER.\n" );
      exit( -1 );
    }
  result->name = NULL;
  result->value = 0;
  result->optimize = 0;
  result->regularize = 0;
  result->nominal_value = 0;
  result->regularize_weight = 0;
  result->next = NULL;
  result->pointer = NULL;
  return result;
}

/******************************************************************/

PARAMETER *read_parameter_file( char *filename )
{
  FILE *stream;
  char buffer[10000];
  PARAMETER *p, *top, *bottom;

  top = NULL;
  bottom = NULL;
  p = NULL;
  stream = fopen( filename, "r" );
  if ( stream == NULL )
    {
      fprintf( stderr, "Can't open %s\n", filename );
      exit( -1 );
    }
  for(;;)
    {
      /* get name of variable */
      if ( fscanf( stream, "%s", buffer ) < 1 )
	break;
      p = malloc_parameter();
      p->name = strdup( buffer );
      if ( fscanf( stream, "%lf", &(p->value) ) < 1 )
	{
	  fprintf( stderr, "Missing value for %s in %s\n",
		   p->name, filename );
	  exit( -1 );
	}

      /* read various commands */
      for( ; ; )
	{
	  if ( fscanf( stream, "%s", buffer ) < 1 )
	    {
	      fprintf( stderr, "Missing end for %s in %s\n",
		       p->name, filename );
	      exit( -1 );
	    }
	  if ( strcmp( buffer, "end" ) == 0 )
	    break;
	  if ( strcmp( buffer, "opt" ) == 0 )
	    p->optimize = 1;
	}

      if ( top == NULL )
	top = p;
      if ( bottom != NULL )
	bottom->next = p;
      bottom = p;
    }
  fclose( stream );
  return top;
}

/******************************************************************/
/******************************************************************/

int process_parameters( PARAMETER *p, SIM *s, int verbose )
{
  int total = 0;

  for( ; ; )
    {
      if ( p == NULL )
	break;
      /*
      if ( strcmp( p->name, "swing_time" ) == 0 )
	p->pointer = &(s->swing_time);
      else if ( strcmp( p->name, "thrust1" ) == 0 )
	p->pointer = &(s->thrust1);
      */

      /*
      else if ( strcmp( p->name, "" ) == 0 )
	p->pointer = &(s->);
      */

      else 
	{
	  fprintf( stderr, "Don't recognize %s in process_parameters()\n", p->name );
	  exit( -1 );
	}
      *(p->pointer) = p->value;
      if ( p->optimize )
	{
	  if ( verbose )
	    printf( "%d: %s\n", total, p->name );
	  total++;
	}
      p = p->next;
    }

  if ( verbose )
    printf( "Optimizing %d parameters.\n", total );
  return total;
}

/************************************************************************/

void
parameters_to_vector( PARAMETER *p, float *v )
{
  int indx = 0;

  printf( "Parameters_to_vector:\n" );
  for( ; ; )
    {
      if ( p == NULL )
	break;
      if ( p->optimize )
	{
	  v[indx++] = *(p->pointer);
	  printf( "%d: %g\n", indx-1, v[indx-1] );
	}
      p = p->next;
    }
}

/************************************************************************/

void
parameters_to_dvector( PARAMETER *p, double *v )
{
  int indx = 0;

  printf( "Parameters_to_vector:\n" );
  for( ; ; )
    {
      if ( p == NULL )
	break;
      if ( p->optimize )
	{
	  v[indx++] = *(p->pointer);
	  printf( "%d: %lg\n", indx-1, v[indx-1] );
	}
      p = p->next;
    }
}

/************************************************************************/

void
vector_to_sim( float *v, int n_parameters, PARAMETER *p )
{
  int indx;

  for( indx = 0; indx < n_parameters; indx++ )
    {
      /* Find next parameter to optimize */
      for( ; ; )
	{
	  if ( p == NULL )
	    {
	      fprintf( stderr, "Failure in vector_to_parameters: %d\n",
		       indx );
	      exit( - 1 );
	    }
	  if ( p->optimize )
	    break;
	  p = p->next;
	}
      *(p->pointer) = v[indx];
      /*
      printf( "%d: %g\n", indx, v[indx] );
      */
      p = p->next;
    }
}

/************************************************************************/

void
dvector_to_sim( double *v, int n_parameters, PARAMETER *p )
{
  int indx;

  for( indx = 0; indx < n_parameters; indx++ )
    {
      /* Find next parameter to optimize */
      for( ; ; )
	{
	  if ( p == NULL )
	    {
	      fprintf( stderr, "Failure in vector_to_parameters: %d\n",
		       indx );
	      exit( - 1 );
	    }
	  if ( p->optimize )
	    break;
	  p = p->next;
	}
      *(p->pointer) = v[indx];
      /*
      printf( "%d: %g\n", indx, v[indx] );
      */
      p = p->next;
    }
}

/******************************************************************/

int write_param_file( char *filename, PARAMETER *p )
{
  FILE *stream;

  stream = fopen( filename, "w" );
  if ( stream == NULL )
    {
      fprintf( stderr, "Can't open %s for write.\n", filename );
      exit( -1 );
    }

  for( ; ; )
    {
      if ( p == NULL )
	break;
      fprintf( stream, "%s %25.20lg", p->name, *(p->pointer) );
      if ( p->optimize )
	fprintf( stream, " opt" );
      fprintf( stream, " end\n" );
      p = p->next;
    }

  fclose( stream );

  return 0;
}

/*****************************************************************************/

