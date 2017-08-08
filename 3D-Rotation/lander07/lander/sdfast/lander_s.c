/*
Generated 24-Feb-2009 21:32:57 by SD/FAST, Kane's formulation
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

/* These routines are passed to lander_root. */

void lander_posfunc(double vars[6],
    double param[1],
    double resid[1])
{
    int i;
    double pos[7],vel[6];

    for (i = 0; i < 6; i++) {
        vel[i] = 0.;
    }
    lander_ang2st(vars,pos);
    lander_state(param[0],pos,vel);
    lander_perr(resid);
}

void lander_velfunc(double vars[6],
    double param[8],
    double resid[1])
{

    lander_state(param[7],param,vars);
    lander_verr(resid);
}

void lander_statfunc(double vars[6],
    double param[7],
    double resid[6])
{
    double pos[7],qdotdum[7];

    lander_ang2st(vars,pos);
    lander_state(param[6],pos,param);
    lander_uforce(param[6],pos,param);
    lander_perr(resid);
    lander_deriv(qdotdum,&resid[0]);
}

void lander_stdyfunc(double vars[12],
    double param[1],
    double resid[6])
{
    double pos[7],qdotdum[7];

    lander_ang2st(vars,pos);
    lander_state(param[0],pos,&vars[6]);
    lander_uforce(param[0],pos,&vars[6]);
    lander_perr(resid);
    lander_verr(&resid[0]);
    lander_deriv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

void lander_motfunc(double time,
    double state[13],
    double dstate[13],
    double param[1],
    int *status)
{

    lander_state(time,state,&state[7]);
    lander_uforce(time,state,&state[7]);
    lander_deriv(dstate,&dstate[7]);
    *status = 0;
}

/* This routine performs assembly analysis. */

void lander_assemble(double time,
    double state[13],
    int lock[6],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double perrs[1],param[1];
    int i;

    lander_gentime(&i);
    if (i != 213257) {
        lander_seterr(50,42);
    }
    param[0] = time;
    lander_st2ang(state,state);
    *err = 0;
    *fcnt = 0;
    lander_posfunc(state,param,perrs);
    *fcnt = *fcnt+1;
    lander_ang2st(state,state);
}

/* This routine performs initial velocity analysis. */

void lander_initvel(double time,
    double state[13],
    int lock[6],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double verrs[1],param[8];
    int i;

    lander_gentime(&i);
    if (i != 213257) {
        lander_seterr(51,42);
    }
    for (i = 0; i < 7; i++) {
        param[i] = state[i];
    }
    param[7] = time;
    *err = 0;
    *fcnt = 0;
    lander_velfunc(&state[7],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

void lander_static(double time,
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

    lander_gentime(&i);
    if (i != 213257) {
        lander_seterr(52,42);
    }
    for (i = 0; i < 6; i++) {
        param[i] = state[7+i];
    }
    param[6] = time;
    lander_st2ang(state,state);
    lander_root(lander_statfunc,state,param,6,6,6,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    lander_statfunc(state,param,resid);
    *fcnt = *fcnt+1;
    lander_ang2st(state,state);
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

void lander_steady(double time,
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

    lander_gentime(&i);
    if (i != 213257) {
        lander_seterr(53,42);
    }
    param[0] = time;
    lander_st2ang(state,vars);
    for (i = 0; i < 6; i++) {
        vars[6+i] = state[7+i];
    }
    lander_root(lander_stdyfunc,vars,param,6,12,6,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    lander_stdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    lander_ang2st(vars,state);
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

void lander_motion(double *time,
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

    lander_gentime(&i);
    if (i != 213257) {
        lander_seterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        lander_motfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    lander_vinteg(lander_motfunc,&ttime,state,dstate,param,dt,&step,13,tol,work,
      &vintgerr,&which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void lander_fmotion(double *time,
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

    lander_gentime(&i);
    if (i != 213257) {
        lander_seterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        lander_motfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    lander_finteg(lander_motfunc,&ttime,state,dstate,param,dt,13,work,errest,&
      ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
