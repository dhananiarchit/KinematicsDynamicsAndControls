/*****************************************************************************/
/*
animate.c: animate a data file.
Animate "birds eye" view of alien artifact and lander.
*/
/*****************************************************************************/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "drawstuff.h" /* Graphics stuff */
#include "drawstuff-cga.h" /* CGA stuff to make things clearer */

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
  MZX,
  MZY,
  MZZ,
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

static void start()
{
  // set up view point
  static float xyz[3] = {2.5f,3.5f,17.0f};
  static float hpr[3] = {-90.0000f,-90.0000f,0.0000f};
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
  static int index = 0;
  float f;
  float alien_center[3];
  float lander_center[3];
  float marker_center[3];
  float alien_R[12];
  float lander_R[12];
  int i;
  float alien_sides[3] = { 2.0, 4.0, 6.0 };
  float lander_sides[3] = { 4.0, 2.0, 1.0 };

  /* Alien */
  /*
  alien_center[XX] = lookup_value( d, index, A_X );
  alien_center[YY] = lookup_value( d, index, A_Y );
  alien_center[ZZ] = lookup_value( d, index, A_Z );
  */
  alien_center[XX] = lookup_value( d, index, MZX );
  alien_center[YY] = lookup_value( d, index, MZY );
  alien_center[ZZ] = lookup_value( d, index, MZZ );

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

  dsSetTexture (DS_WOOD);
  dsSetColor (1,0,0);
  dsDrawBox( alien_center, alien_R, alien_sides );

  /* Lander */
  lander_center[XX] = lookup_value( d, index, L_X );
  lander_center[YY] = lookup_value( d, index, L_Y );
  lander_center[ZZ] = lookup_value( d, index, L_Z );

  for ( i = 0; i < 12; i++ )
    lander_R[i] = 0;
  // 0 1 2 3; 4 5 6 7; 8 9 10 11
  lander_R[0] = lookup_value( d, index, L_R00 );
  lander_R[1] = lookup_value( d, index, L_R01 );
  lander_R[2] = lookup_value( d, index, L_R02 );
  lander_R[4] = lookup_value( d, index, L_R10 );
  lander_R[5] = lookup_value( d, index, L_R11 );
  lander_R[6] = lookup_value( d, index, L_R12 );
  lander_R[8] = lookup_value( d, index, L_R20 );
  lander_R[9] = lookup_value( d, index, L_R21 );
  lander_R[10] = lookup_value( d, index, L_R22 );

  dsSetTexture (DS_WOOD);
  dsSetColor (0,1,0);
  dsDrawBox( lander_center, lander_R, lander_sides );

  /* Markers */
  marker_center[XX] = lookup_value( d, index, M0X );
  marker_center[YY] = lookup_value( d, index, M0Y );
  marker_center[ZZ] = lookup_value( d, index, M0Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M1X );
  marker_center[YY] = lookup_value( d, index, M1Y );
  marker_center[ZZ] = lookup_value( d, index, M1Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M2X );
  marker_center[YY] = lookup_value( d, index, M2Y );
  marker_center[ZZ] = lookup_value( d, index, M2Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M3X );
  marker_center[YY] = lookup_value( d, index, M3Y );
  marker_center[ZZ] = lookup_value( d, index, M3Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M4X );
  marker_center[YY] = lookup_value( d, index, M4Y );
  marker_center[ZZ] = lookup_value( d, index, M4Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M5X );
  marker_center[YY] = lookup_value( d, index, M5Y );
  marker_center[ZZ] = lookup_value( d, index, M5Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M6X );
  marker_center[YY] = lookup_value( d, index, M6Y );
  marker_center[ZZ] = lookup_value( d, index, M6Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

  marker_center[XX] = lookup_value( d, index, M7X );
  marker_center[YY] = lookup_value( d, index, M7Y );
  marker_center[ZZ] = lookup_value( d, index, M7Z );

  dsSetTexture (DS_WOOD);
  dsSetColor (1,1,1);
  dsDrawSphere( marker_center, alien_R, 0.2 );

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
  /*
  channels[A_X] = find_channel( "a_x", d );
  channels[A_Y] = find_channel( "a_y", d );
  channels[A_Z] = find_channel( "a_z", d );
  */
  channels[MZX] = find_channel( "mzx", d );
  channels[MZY] = find_channel( "mzy", d );
  channels[MZZ] = find_channel( "mzz", d );
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
  channels[M0X] = find_channel( "m0x", d );
  channels[M0Y] = find_channel( "m0y", d );
  channels[M0Z] = find_channel( "m0z", d );
  channels[M1X] = find_channel( "m1x", d );
  channels[M1Y] = find_channel( "m1y", d );
  channels[M1Z] = find_channel( "m1z", d );
  channels[M2X] = find_channel( "m2x", d );
  channels[M2Y] = find_channel( "m2y", d );
  channels[M2Z] = find_channel( "m2z", d );
  channels[M3X] = find_channel( "m3x", d );
  channels[M3Y] = find_channel( "m3y", d );
  channels[M3Z] = find_channel( "m3z", d );
  channels[M4X] = find_channel( "m4x", d );
  channels[M4Y] = find_channel( "m4y", d );
  channels[M4Z] = find_channel( "m4z", d );
  channels[M5X] = find_channel( "m5x", d );
  channels[M5Y] = find_channel( "m5y", d );
  channels[M5Z] = find_channel( "m5z", d );
  channels[M6X] = find_channel( "m6x", d );
  channels[M6Y] = find_channel( "m6y", d );
  channels[M6Z] = find_channel( "m6z", d );
  channels[M7X] = find_channel( "m7x", d );
  channels[M7Y] = find_channel( "m7y", d );
  channels[M7Z] = find_channel( "m7z", d );

  for( i = 0; i < N_CHANNELS; i++ )
    printf( "%d %d\n", i, channels[i] );

  // setup pointers to drawstuff callback functions
  fn.version = DS_VERSION; 
  fn.start = &start; 
  fn.step = &display; 
  fn.command = &command; 
  fn.stop = 0; 
#ifdef WIN32
  fn.path_to_textures = "C:/Users/archi/Desktop/Somaiya drive/Sem2/16711/assignment3/lander07/lander07/useful/drawstuff-windows/textures";
#else
  fn.path_to_textures = "/home/cga/kdc/lander06/useful/drawstuff-linux/textures";
#endif

  // do display
  dsSimulationLoop( argc, argv, /* command line arguments */
                    500, 500, /* window size */
                    &fn ); /* callback info */

  return 0;
}

/********************************************************************/
