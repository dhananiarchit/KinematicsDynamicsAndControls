/*****************************************************************************/
/*
  animate.c: animate a data file.
*/
/*****************************************************************************/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "drawstuff.h" /* Graphics stuff */
#include "drawstuff-cga.h" /* CGA stuff to make things clearer */

#include "matrix3.h"
#include "../useful/mrdplot/mrdplot.h"
#include "main.h"
#include "main2.h"

/*****************************************************************************/

enum channels {
  TIME,
  A_X,
  A_Y,
  A_Z,
  A_R00,
  A_R01,
  A_R02,
  A_R10,
  A_R11,
  A_R12,
  A_R20,
  A_R21,
  A_R22,
  L_X,
  L_Y,
  L_Z,
  L_R00,
  L_R01,
  L_R02,
  L_R10,
  L_R11,
  L_R12,
  L_R20,
  L_R21,
  L_R22,
  M0X,
  M0Y,
  M0Z,
  M1X,
  M1Y,
  M1Z,
  M2X,
  M2Y,
  M2Z,
  M3X,
  M3Y,
  M3Z,
  M4X,
  M4Y,
  M4Z,
  M5X,
  M5Y,
  M5Z,
  M6X,
  M6Y,
  M6Z,
  M7X,
  M7Y,
  M7Z,
  N_CHANNELS,
};

/*****************************************************************************/

SIM sim;

MRDPLOT_DATA *d;

int channels[N_CHANNELS];

/*****************************************************************************/
/*****************************************************************************/

double lookup_value( MRDPLOT_DATA *d, int point, int channel )
{
  if ( channels[channel] < 0 || channels[channel] >= d->n_channels )
    {
      fprintf( stderr, "Bad channel: %d %d\n", channel, channels[channel] );
      exit( -1 );
    }
  return d->data[point*d->n_channels + channels[channel]];
}

/********************************************************************/
// start(): set things up

  // set up view point
static float xyz[3] = {40.0f,0.0f,4.0f};
static float hpr[3] = {-180.0000f,0.0000f,0.0000f};

static void start()
{
  dsSetViewpoint (xyz,hpr);
}

/********************************************************************/
// called when a key pressed

static void command (int cmd)
{
  // don't handle user input yet.
  dsPrint ("received command %d (`%c')\n",cmd,cmd);
}

/*****************************************************************************/

static void display (int pause)
{
  int i;
  static int index = 0;
  float f;
  double lander_x[3];
  double lander_r[3][3]; // rotation of space craft wrt world.
  double tmp[3];
  float resultf[3];
  float alien_R[12];
  float radius = 0.2;

  /* Alien */
  for ( i = 0; i < 12; i++ )
    alien_R[i] = 0;
  // 0 1 2 3; 4 5 6 7; 8 9 10 11
  alien_R[0] = lookup_value( d, index, A_R00 );
  alien_R[1] = lookup_value( d, index, A_R01 );
  alien_R[2] = lookup_value( d, index, A_R02 );
  alien_R[4] = lookup_value( d, index, A_R10 );
  alien_R[5] = lookup_value( d, index, A_R11 );
  alien_R[6] = lookup_value( d, index, A_R12 );
  alien_R[8] = lookup_value( d, index, A_R20 );
  alien_R[9] = lookup_value( d, index, A_R21 );
  alien_R[10] = lookup_value( d, index, A_R22 );

  /* Lander */
  lander_x[XX] = lookup_value( d, index, L_X );
  lander_x[YY] = lookup_value( d, index, L_Y );
  lander_x[ZZ] = lookup_value( d, index, L_Z );

  lander_r[0][0] = lookup_value( d, index, L_R00 );
  lander_r[0][1] = lookup_value( d, index, L_R01 );
  lander_r[0][2] = lookup_value( d, index, L_R02 );
  lander_r[1][0] = lookup_value( d, index, L_R10 );
  lander_r[1][1] = lookup_value( d, index, L_R11 );
  lander_r[1][2] = lookup_value( d, index, L_R12 );
  lander_r[2][0] = lookup_value( d, index, L_R20 );
  lander_r[2][1] = lookup_value( d, index, L_R21 );
  lander_r[2][2] = lookup_value( d, index, L_R22 );

  /* Markers */
  tmp[0] = lookup_value( d, index, M0X );
  tmp[1] = lookup_value( d, index, M0Y );
  tmp[2] = lookup_value( d, index, M0Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M1X );
  tmp[1] = lookup_value( d, index, M1Y );
  tmp[2] = lookup_value( d, index, M1Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M2X );
  tmp[1] = lookup_value( d, index, M2Y );
  tmp[2] = lookup_value( d, index, M2Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M3X );
  tmp[1] = lookup_value( d, index, M3Y );
  tmp[2] = lookup_value( d, index, M3Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M4X );
  tmp[1] = lookup_value( d, index, M4Y );
  tmp[2] = lookup_value( d, index, M4Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M5X );
  tmp[1] = lookup_value( d, index, M5Y );
  tmp[2] = lookup_value( d, index, M5Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M6X );
  tmp[1] = lookup_value( d, index, M6Y );
  tmp[2] = lookup_value( d, index, M6Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  tmp[0] = lookup_value( d, index, M7X );
  tmp[1] = lookup_value( d, index, M7Y );
  tmp[2] = lookup_value( d, index, M7Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  resultf[XX] = tmp[XX] + xyz[XX];
  resultf[YY] = tmp[YY] + xyz[YY];
  resultf[ZZ] = tmp[ZZ] + xyz[ZZ];
  dsDrawSphere( resultf, alien_R, radius );

  /* Delay */
#ifdef WIN32
  for( f = 0.0; f < 7000000.0; f += 1.0 )
    ;
#else
  for( f = 0.0; f < 10000000.0; f += 1.0 )
    ;
#endif

  index += 3;
  // index += 33;
  if ( index > d->n_points )
    index = 0;
}

/*****************************************************************************/
/********************************************************************/

int main (int argc, char **argv)
{
  char *filename;
  int i;
  dsFunctions fn; 

  if ( argc > 1 )
    filename = strdup( argv[1] );
  else
    filename = last_data();
  
  printf( "Reading: %s\n", filename );

  d = read_mrdplot( filename );

  for( i = 0; i < N_CHANNELS; i++ )
    channels[i] = -1;

  channels[TIME] = find_channel( "time", d );
  channels[A_X] = find_channel( "a_x", d );
  channels[A_Y] = find_channel( "a_y", d );
  channels[A_Z] = find_channel( "a_z", d );
  channels[A_R00] = find_channel( "a_r00", d );
  channels[A_R01] = find_channel( "a_r01", d );
  channels[A_R02] = find_channel( "a_r02", d );
  channels[A_R10] = find_channel( "a_r10", d );
  channels[A_R11] = find_channel( "a_r11", d );
  channels[A_R12] = find_channel( "a_r12", d );
  channels[A_R20] = find_channel( "a_r20", d );
  channels[A_R21] = find_channel( "a_r21", d );
  channels[A_R22] = find_channel( "a_r22", d );
  channels[L_X] = find_channel( "l_x", d );
  channels[L_Y] = find_channel( "l_y", d );
  channels[L_Z] = find_channel( "l_z", d );
  channels[L_R00] = find_channel( "l_r00", d );
  channels[L_R01] = find_channel( "l_r01", d );
  channels[L_R02] = find_channel( "l_r02", d );
  channels[L_R10] = find_channel( "l_r10", d );
  channels[L_R11] = find_channel( "l_r11", d );
  channels[L_R12] = find_channel( "l_r12", d );
  channels[L_R20] = find_channel( "l_r20", d );
  channels[L_R21] = find_channel( "l_r21", d );
  channels[L_R22] = find_channel( "l_r22", d );

  /* no noise version */
  channels[M0X] = find_channel( "ml0x", d );
  channels[M0Y] = find_channel( "ml0y", d );
  channels[M0Z] = find_channel( "ml0z", d );
  channels[M1X] = find_channel( "ml1x", d );
  channels[M1Y] = find_channel( "ml1y", d );
  channels[M1Z] = find_channel( "ml1z", d );
  channels[M2X] = find_channel( "ml2x", d );
  channels[M2Y] = find_channel( "ml2y", d );
  channels[M2Z] = find_channel( "ml2z", d );
  channels[M3X] = find_channel( "ml3x", d );
  channels[M3Y] = find_channel( "ml3y", d );
  channels[M3Z] = find_channel( "ml3z", d );
  channels[M4X] = find_channel( "ml4x", d );
  channels[M4Y] = find_channel( "ml4y", d );
  channels[M4Z] = find_channel( "ml4z", d );
  channels[M5X] = find_channel( "ml5x", d );
  channels[M5Y] = find_channel( "ml5y", d );
  channels[M5Z] = find_channel( "ml5z", d );
  channels[M6X] = find_channel( "ml6x", d );
  channels[M6Y] = find_channel( "ml6y", d );
  channels[M6Z] = find_channel( "ml6z", d );
  channels[M7X] = find_channel( "ml7x", d );
  channels[M7Y] = find_channel( "ml7y", d );
  channels[M7Z] = find_channel( "ml7z", d );

  /* Show noisy data version
  channels[M0X] = find_channel( "mn0x", d );
  channels[M0Y] = find_channel( "mn0y", d );
  channels[M0Z] = find_channel( "mn0z", d );
  channels[M1X] = find_channel( "mn1x", d );
  channels[M1Y] = find_channel( "mn1y", d );
  channels[M1Z] = find_channel( "mn1z", d );
  channels[M2X] = find_channel( "mn2x", d );
  channels[M2Y] = find_channel( "mn2y", d );
  channels[M2Z] = find_channel( "mn2z", d );
  channels[M3X] = find_channel( "mn3x", d );
  channels[M3Y] = find_channel( "mn3y", d );
  channels[M3Z] = find_channel( "mn3z", d );
  channels[M4X] = find_channel( "mn4x", d );
  channels[M4Y] = find_channel( "mn4y", d );
  channels[M4Z] = find_channel( "mn4z", d );
  channels[M5X] = find_channel( "mn5x", d );
  channels[M5Y] = find_channel( "mn5y", d );
  channels[M5Z] = find_channel( "mn5z", d );
  channels[M6X] = find_channel( "mn6x", d );
  channels[M6Y] = find_channel( "mn6y", d );
  channels[M6Z] = find_channel( "mn6z", d );
  channels[M7X] = find_channel( "mn7x", d );
  channels[M7Y] = find_channel( "mn7y", d );
  channels[M7Z] = find_channel( "mn7z", d );
  */

  for( i = 0; i < N_CHANNELS; i++ )
    printf( "%d %d\n", i, channels[i] );

  // setup pointers to drawstuff callback functions
  fn.version = DS_VERSION; 
  fn.start = &start; 
  fn.step = &display; 
  fn.command = &command; 
  fn.stop = 0; 
#ifdef WIN32
  fn.path_to_textures = "C:/cga/kdc/walk02/useful/drawstuff-windows/textures";
#else
  fn.path_to_textures = "/home/cga/new/kdc/lander/useful/drawstuff-linux/textures";
#endif

  // do display
  dsSimulationLoop( argc, argv, /* command line arguments */
                    500, 500, /* window size */
                    &fn ); /* callback info */

  return 0;
}

/********************************************************************/
