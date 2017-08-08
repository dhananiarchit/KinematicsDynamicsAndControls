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

struct data {
	//COM of Alien
	float COM_x[2000];
	float COM_y[2000];
	float COM_z[2000];

	//quaternion of alien
	float q_scalar[2000];
	float q_x[2000];
	float q_y[2000];
	float q_z[2000];

	//angular velocity of alien
	float w_x[2000];
	float w_y[2000];
	float w_z[2000];
};

void readDataFile(float data[], char file[])
{

	FILE *fp;
	char str[25];

	fp = fopen(file, "r");

	if (fp == NULL)
	{
		printf("error openning q_scalar\n\n");
	}
	else
	{
		int x = 0;
		while (fgets(str, 24, fp))
		{
			if (x>0 && x<5001)
			{
				data[x - 1] = atof(str);
			}
			x++;
		}
	}
	fclose(fp);
}


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

	struct data a_data;

	readDataFile(a_data.q_scalar, "q_scalar.txt");
	readDataFile(a_data.q_x, "q_x.txt");
	readDataFile(a_data.q_y, "q_y.txt");
	readDataFile(a_data.q_z, "q_z.txt");
	readDataFile(a_data.COM_x, "COM_X.txt");
	readDataFile(a_data.COM_y, "COM_Y.txt");
	readDataFile(a_data.COM_z, "COM_Z.txt");
	readDataFile(a_data.w_x, "W_X.txt");
	readDataFile(a_data.w_y, "W_Y.txt");
	readDataFile(a_data.w_z, "W_Z.txt");

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
	  sim.lander_x_d[0] = a_data.COM_x[i];
	  sim.lander_x_d[1] = a_data.COM_y[i];
	  sim.lander_x_d[2] = a_data.COM_z[i];
	  sim.lander_q_d[Q0] = a_data.q_scalar[i];
	  sim.lander_q_d[Q1] = a_data.q_x[i];
	  sim.lander_q_d[Q2] = a_data.q_y[i];
	  sim.lander_q_d[Q3] = a_data.q_z[i];
      controller( &sim );
      save_data( &sim );
      if ( sim.status == CRASHED )
	break;
      integrate_one_time_step( &sim );
    }

  write_the_mrdplot_file( &sim );
}

/*****************************************************************************/
