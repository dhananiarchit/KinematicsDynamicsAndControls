/*
Generated 24-Feb-2009 21:33:12 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
#include <math.h>

/* These routines are passed to alien_root. */

void alien_posfunc(double vars[6],
    double param[1],
    double resid[1])
{
    int i;
    double pos[7],vel[6];

    for (i = 0; i < 6; i++) {
        vel[i] = 0.;
    }
    alien_ang2st(vars,pos);
    alien_state(param[0],pos,vel);
    alien_perr(resid);
}

void alien_velfunc(double vars[6],
    double param[8],
    double resid[1])
{

    alien_state(param[7],param,vars);
    alien_verr(resid);
}

void alien_statfunc(double vars[6],
    double param[7],
    double resid[6])
{
    double pos[7],qdotdum[7];

    alien_ang2st(vars,pos);
    alien_state(param[6],pos,param);
    alien_uforce(param[6],pos,param);
    alien_perr(resid);
    alien_deriv(qdotdum,&resid[0]);
}

void alien_stdyfunc(double vars[12],
    double param[1],
    double resid[6])
{
    double pos[7],qdotdum[7];

    alien_ang2st(vars,pos);
    alien_state(param[0],pos,&vars[6]);
    alien_uforce(param[0],pos,&vars[6]);
    alien_perr(resid);
    alien_verr(&resid[0]);
    alien_deriv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

void alien_motfunc(double time,
    double state[13],
    double dstate[13],
    double param[1],
    int *status)
{

    alien_state(time,state,&state[7]);
    alien_uforce(time,state,&state[7]);
    alien_deriv(dstate,&dstate[7]);
    *status = 0;
}

/* This routine performs assembly analysis. */

void alien_assemble(double time,
    double state[13],
    int lock[6],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double perrs[1],param[1];
    int i;

    alien_gentime(&i);
    if (i != 213312) {
        alien_seterr(50,42);
    }
    param[0] = time;
    alien_st2ang(state,state);
    *err = 0;
    *fcnt = 0;
    alien_posfunc(state,param,perrs);
    *fcnt = *fcnt+1;
    alien_ang2st(state,state);
}

/* This routine performs initial velocity analysis. */

void alien_initvel(double time,
    double state[13],
    int lock[6],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double verrs[1],param[8];
    int i;

    alien_gentime(&i);
    if (i != 213312) {
        alien_seterr(51,42);
    }
    for (i = 0; i < 7; i++) {
        param[i] = state[i];
    }
    param[7] = time;
    *err = 0;
    *fcnt = 0;
    alien_velfunc(&state[7],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

void alien_static(double time,
    double state[13],
    int lock[6],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[6],param[7],jw[36],dw[288],rw[96];
    int iw[48],rooterr,i;

    alien_gentime(&i);
    if (i != 213312) {
        alien_seterr(52,42);
    }
    for (i = 0; i < 6; i++) {
        param[i] = state[7+i];
    }
    param[6] = time;
    alien_st2ang(state,state);
    alien_root(alien_statfunc,state,param,6,6,6,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    alien_statfunc(state,param,resid);
    *fcnt = *fcnt+1;
    alien_ang2st(state,state);
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs steady motion analysis. */

void alien_steady(double time,
    double state[13],
    int lock[12],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[6],param[1],vars[12];
    double jw[72],dw[648],rw[150];
    int iw[72],rooterr,i;

    alien_gentime(&i);
    if (i != 213312) {
        alien_seterr(53,42);
    }
    param[0] = time;
    alien_st2ang(state,vars);
    for (i = 0; i < 6; i++) {
        vars[6+i] = state[7+i];
    }
    alien_root(alien_stdyfunc,vars,param,6,12,6,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    alien_stdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    alien_ang2st(vars,state);
    for (i = 0; i < 6; i++) {
        state[7+i] = vars[6+i];
    }
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs state integration. */

void alien_motion(double *time,
    double state[13],
    double dstate[13],
    double dt,
    double ctol,
    double tol,
    int *flag,
    int *err)
{
    static double step;
    double work[78],ttime,param[1];
    int vintgerr,which,ferr,i;

    alien_gentime(&i);
    if (i != 213312) {
        alien_seterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        alien_motfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    alien_vinteg(alien_motfunc,&ttime,state,dstate,param,dt,&step,13,tol,work,&
      vintgerr,&which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void alien_fmotion(double *time,
    double state[13],
    double dstate[13],
    double dt,
    double ctol,
    int *flag,
    double *errest,
    int *err)
{
    double work[52],ttime,param[1];
    int ferr,i;

    alien_gentime(&i);
    if (i != 213312) {
        alien_seterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        alien_motfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    alien_finteg(alien_motfunc,&ttime,state,dstate,param,dt,13,work,errest,&
      ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
