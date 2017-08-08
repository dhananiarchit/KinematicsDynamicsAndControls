CC=gcc
# LINK=gcc
LINK=g++  # might be needed for Fedora Core 13
CFLAGS=-O3
XLIBS = -lGLU -lGL -lX11

DYNAMICS = dynamics.o matrix3.o sdfast/alien_d.o sdfast/alien_s.o sdfast/alien_lib.o sdfast/lander_d.o sdfast/lander_s.o sdfast/lander_lib.o

all: simulate animate animate-lander

simulate: simulate.o parameters.o controller.o data.o $(DYNAMICS) ../useful/mrdplot/mrdplot.o
	$(CC) $(CFLAGS) -o $@ simulate.o parameters.o controller.o data.o $(DYNAMICS) ../useful/mrdplot/mrdplot.o -lm

animate.o: animate.c main.h
	$(CC) -c $(CFLAGS) -Wall -fno-exceptions -fomit-frame-pointer -ffast-math -I../useful/drawstuff-linux -DdNODEBUG -o animate.o animate.c

animate: animate.o parameters.o ../useful/mrdplot/mrdplot.o
	$(LINK) $(CFLAGS) -o $@ animate.o parameters.o ../useful/mrdplot/mrdplot.o ../useful/drawstuff-linux/libdrawstuff.a $(XLIBS) -lm

animate-lander.o: animate-lander.c main.h
	$(CC) -c $(CFLAGS) -Wall -fno-exceptions -fomit-frame-pointer -ffast-math -I../useful/drawstuff-linux -DdNODEBUG -o animate-lander.o animate-lander.c

animate-lander: animate-lander.o parameters.o matrix3.o ../useful/mrdplot/mrdplot.o
	$(LINK) $(CFLAGS) -o $@ animate-lander.o parameters.o matrix3.o ../useful/mrdplot/mrdplot.o ../useful/drawstuff-linux/libdrawstuff.a $(XLIBS) -lm

animate.o:	main.h main2.h
animate-lander.o:	main.h main2.h
controller.o:	main.h main2.h
data.o:	main.h main2.h
dynamics.o:	main.h main2.h
parameters.o:	main.h main2.h
simulate.o:	main.h main2.h
