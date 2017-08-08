/********************************************************************/
/* Some ODE/graphics hacks. */

// #include "textures.h"

#ifdef _MSC_VER
#pragma warning(disable:4244 4305)  // for VC++, no precision loss complaints
#endif

// select correct drawing functions
#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawSphere dsDrawSphereD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCappedCylinder dsDrawCappedCylinderD
#endif

// setup pointers to drawstuff callback functions
#define CALLBACK_STUFF  dsFunctions fn; fn.version = DS_VERSION; fn.start = &start; fn.step = &simLoop; fn.command = &command; fn.stop = 0; fn.path_to_textures = "C:\cga\seegrid\cga-sim-windows-002\useful\drawstuff\textures";

/********************************************************************/
