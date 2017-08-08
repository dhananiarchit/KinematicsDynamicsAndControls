/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "main2.h"

/*****************************************************************************/
/*****************************************************************************/

extern SIM sim;

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/* Call this once to do one time operations like memory allocation */

int init_sim( SIM *s )
{

  init_dynamics( s );
  init_controller( s );
  init_data( s );

  reinit_sim( s );
}

/*****************************************************************************/
/* call this many times to restart a simulation */

int reinit_sim( SIM *s )
{

  srand( s->rand_seed );

  reinit_dynamics( s );
  reinit_controller( s );
}

/*****************************************************************************/

main( int argc, char **argv )
{
  PARAMETER *params;
  int n_parameters;
  int i;

  init_default_parameters( &sim );
  sim.rand_scale = 0;
  sim.controller_print = 1;

  /* Parameter file argument? */
  if ( argc > 1 )
    {
      params = read_parameter_file( argv[1] );
      n_parameters = process_parameters( params, &sim, 1 );
      if ( n_parameters > MAX_N_PARAMETERS )
	{
	  fprintf( stderr, "Too many parameters %d > %d\n",
		   n_parameters, MAX_N_PARAMETERS );
	  exit( -1 );
	}
    }

  init_sim( &sim );

  for( i = 0; sim.time < sim.duration; i++ )
    {
      if ( (i % 1000) == 0 )
        {
	  /*
          printf( "%g: %g %g\n", sim.time,
		  sim.foot[LEFT][XX], sim.foot[LEFT][ZZ] );
	  */
        }
      controller( &sim );
      save_data( &sim );
      if ( sim.status == CRASHED )
	break;
      integrate_one_time_step( &sim );
    }

  write_the_mrdplot_file( &sim );
}

/*****************************************************************************/
