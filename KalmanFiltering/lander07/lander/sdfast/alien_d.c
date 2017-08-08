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


ROADMAP (alien.sd)

Bodies        Inb
No  Name      body Joint type  Coords q
--- --------- ---- ----------- ----------------
 -1 $ground                                    
  0 alien      -1  Sixdof        0   1   2 
                   ...           3   4   5   6 

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[1],inb_[1],outb_[1],njntdof_[1],njntc_[1],njntp_[1],firstq_[1],
      ballq_[1],firstm_[1],firstp_[1];
    int trans_[6];
} alien_gtopo_t;
#define ground (alien_gtopo.ground_)
#define nbod (alien_gtopo.nbod_)
#define ndof (alien_gtopo.ndof_)
#define ncons (alien_gtopo.ncons_)
#define nloop (alien_gtopo.nloop_)
#define nldof (alien_gtopo.nldof_)
#define nloopc (alien_gtopo.nloopc_)
#define nball (alien_gtopo.nball_)
#define nlball (alien_gtopo.nlball_)
#define npres (alien_gtopo.npres_)
#define nuser (alien_gtopo.nuser_)
#define jtype (alien_gtopo.jtype_)
#define inb (alien_gtopo.inb_)
#define outb (alien_gtopo.outb_)
#define njntdof (alien_gtopo.njntdof_)
#define njntc (alien_gtopo.njntc_)
#define njntp (alien_gtopo.njntp_)
#define firstq (alien_gtopo.firstq_)
#define ballq (alien_gtopo.ballq_)
#define firstm (alien_gtopo.firstm_)
#define firstp (alien_gtopo.firstp_)
#define trans (alien_gtopo.trans_)

typedef struct {
    double grav_[3],mk_[1],ik_[1][3][3],pin_[6][3];
    double rk_[1][3],ri_[1][3],pres_[6],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[6];
    int gravq_[3],mkq_[1],ikq_[1][3][3],pinq_[6][3],rkq_[1][3],riq_[1][3],presq_
      [6],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[1][3],rcom_[1][3],mkrcomt_[1][3][3],psikg_[3][3],
      psrcomg_[3],psrkg_[3],psrig_[3],psmk_[6],psik_[6][3][3],psrcom_[6][3],
      psrk_[6][3],psri_[6][3];
} alien_ginput_t;
#define grav (alien_ginput.grav_)
#define mk (alien_ginput.mk_)
#define ik (alien_ginput.ik_)
#define pin (alien_ginput.pin_)
#define rk (alien_ginput.rk_)
#define ri (alien_ginput.ri_)
#define pres (alien_ginput.pres_)
#define stabvel (alien_ginput.stabvel_)
#define stabpos (alien_ginput.stabpos_)
#define rhead (alien_ginput.rhead_)
#define rcom (alien_ginput.rcom_)
#define psrcomg (alien_ginput.psrcomg_)
#define psrcom (alien_ginput.psrcom_)
#define mkrcomt (alien_ginput.mkrcomt_)
#define psmk (alien_ginput.psmk_)
#define psik (alien_ginput.psik_)
#define psrk (alien_ginput.psrk_)
#define psri (alien_ginput.psri_)
#define psmkg (alien_ginput.psmkg_)
#define psikg (alien_ginput.psikg_)
#define psrkg (alien_ginput.psrkg_)
#define psrig (alien_ginput.psrig_)
#define mtot (alien_ginput.mtot_)
#define mfrcflg (alien_ginput.mfrcflg_)
#define roustate (alien_ginput.roustate_)
#define vpkflg (alien_ginput.vpkflg_)
#define inerflg (alien_ginput.inerflg_)
#define mmflg (alien_ginput.mmflg_)
#define mmlduflg (alien_ginput.mmlduflg_)
#define wwflg (alien_ginput.wwflg_)
#define ltauflg (alien_ginput.ltauflg_)
#define fs0flg (alien_ginput.fs0flg_)
#define ii (alien_ginput.ii_)
#define mmap (alien_ginput.mmap_)
#define gravq (alien_ginput.gravq_)
#define mkq (alien_ginput.mkq_)
#define ikq (alien_ginput.ikq_)
#define pinq (alien_ginput.pinq_)
#define rkq (alien_ginput.rkq_)
#define riq (alien_ginput.riq_)
#define presq (alien_ginput.presq_)
#define stabvelq (alien_ginput.stabvelq_)
#define stabposq (alien_ginput.stabposq_)

typedef struct {
    double curtim_,q_[7],qn_[7],u_[6],cnk_[6][3][3],cnb_[1][3][3];
    double rnk_[6][3],vnk_[6][3],wk_[6][3],rnb_[1][3],vnb_[1][3],wb_[1][3],
      wbrcom_[1][3],com_[3],rnkg_[3];
    double Cik_[6][3][3],rikt_[6][3][3],Iko_[6][3][3],mkrk_[6][3][3],Cib_[1][3][
      3];
    double Wkk_[6][3],Vkk_[6][3],dik_[6][3],rpp_[6][3],rpk_[6][3],rik_[6][3],
      rik2_[6][3];
    double rpri_[6][3],Wik_[6][3],Vik_[6][3],Wirk_[6][3],rkWkk_[6][3],Wkrpk_[6][
      3],VikWkr_[6][3];
    double perr_[1],verr_[1],aerr_[1],mult_[1],ufk_[1][3],utk_[1][3],mfk_[1][3],
      mtk_[1][3];
    double utau_[6],mtau_[6],uacc_[6],uvel_[6],upos_[7];
} alien_gstate_t;
#define curtim (alien_gstate.curtim_)
#define q (alien_gstate.q_)
#define qn (alien_gstate.qn_)
#define u (alien_gstate.u_)
#define cnk (alien_gstate.cnk_)
#define cnb (alien_gstate.cnb_)
#define rnkg (alien_gstate.rnkg_)
#define rnk (alien_gstate.rnk_)
#define rnb (alien_gstate.rnb_)
#define vnk (alien_gstate.vnk_)
#define vnb (alien_gstate.vnb_)
#define wk (alien_gstate.wk_)
#define wb (alien_gstate.wb_)
#define com (alien_gstate.com_)
#define Cik (alien_gstate.Cik_)
#define Cib (alien_gstate.Cib_)
#define rikt (alien_gstate.rikt_)
#define Iko (alien_gstate.Iko_)
#define mkrk (alien_gstate.mkrk_)
#define Wkk (alien_gstate.Wkk_)
#define Vkk (alien_gstate.Vkk_)
#define dik (alien_gstate.dik_)
#define rpp (alien_gstate.rpp_)
#define rpk (alien_gstate.rpk_)
#define rik (alien_gstate.rik_)
#define rik2 (alien_gstate.rik2_)
#define rpri (alien_gstate.rpri_)
#define Wik (alien_gstate.Wik_)
#define Vik (alien_gstate.Vik_)
#define Wirk (alien_gstate.Wirk_)
#define rkWkk (alien_gstate.rkWkk_)
#define Wkrpk (alien_gstate.Wkrpk_)
#define VikWkr (alien_gstate.VikWkr_)
#define wbrcom (alien_gstate.wbrcom_)
#define perr (alien_gstate.perr_)
#define verr (alien_gstate.verr_)
#define aerr (alien_gstate.aerr_)
#define mult (alien_gstate.mult_)
#define ufk (alien_gstate.ufk_)
#define utk (alien_gstate.utk_)
#define utau (alien_gstate.utau_)
#define mfk (alien_gstate.mfk_)
#define mtk (alien_gstate.mtk_)
#define mtau (alien_gstate.mtau_)
#define uacc (alien_gstate.uacc_)
#define uvel (alien_gstate.uvel_)
#define upos (alien_gstate.upos_)

typedef struct {
    double fs0_[6],qdot_[7],Otk_[6][3],Atk_[6][3],AiOiWi_[6][3],Fstar_[6][3];
    double Tstar_[6][3],Fstark_[6][3],Tstark_[6][3],IkWk_[6][3],WkIkWk_[6][3],
      gk_[6][3],IkbWk_[1][3],WkIkbWk_[1][3];
    double w0w0_[1],w1w1_[1],w2w2_[1],w0w1_[1],w0w2_[1],w1w2_[1];
    double w00w11_[1],w00w22_[1],w11w22_[1],ww_[1][1],qraux_[1];
    double mm_[6][6],mlo_[6][6],mdi_[6],IkWpk_[6][6][3],works_[6],workss_[6][6];
    double Wpk_[6][6][3],Vpk_[6][6][3],VWri_[6][6][3];
    int wmap_[1],multmap_[1],jpvt_[1],wsiz_,wrank_;
} alien_glhs_t;
#define qdot (alien_glhs.qdot_)
#define Otk (alien_glhs.Otk_)
#define Atk (alien_glhs.Atk_)
#define AiOiWi (alien_glhs.AiOiWi_)
#define Fstar (alien_glhs.Fstar_)
#define Tstar (alien_glhs.Tstar_)
#define fs0 (alien_glhs.fs0_)
#define Fstark (alien_glhs.Fstark_)
#define Tstark (alien_glhs.Tstark_)
#define IkWk (alien_glhs.IkWk_)
#define IkbWk (alien_glhs.IkbWk_)
#define WkIkWk (alien_glhs.WkIkWk_)
#define WkIkbWk (alien_glhs.WkIkbWk_)
#define gk (alien_glhs.gk_)
#define w0w0 (alien_glhs.w0w0_)
#define w1w1 (alien_glhs.w1w1_)
#define w2w2 (alien_glhs.w2w2_)
#define w0w1 (alien_glhs.w0w1_)
#define w0w2 (alien_glhs.w0w2_)
#define w1w2 (alien_glhs.w1w2_)
#define w00w11 (alien_glhs.w00w11_)
#define w00w22 (alien_glhs.w00w22_)
#define w11w22 (alien_glhs.w11w22_)
#define ww (alien_glhs.ww_)
#define qraux (alien_glhs.qraux_)
#define mm (alien_glhs.mm_)
#define mlo (alien_glhs.mlo_)
#define mdi (alien_glhs.mdi_)
#define IkWpk (alien_glhs.IkWpk_)
#define works (alien_glhs.works_)
#define workss (alien_glhs.workss_)
#define Wpk (alien_glhs.Wpk_)
#define Vpk (alien_glhs.Vpk_)
#define VWri (alien_glhs.VWri_)
#define wmap (alien_glhs.wmap_)
#define multmap (alien_glhs.multmap_)
#define jpvt (alien_glhs.jpvt_)
#define wsiz (alien_glhs.wsiz_)
#define wrank (alien_glhs.wrank_)

typedef struct {
    double fs_[6],udot_[6],tauc_[6],dyad_[1][3][3],fc_[6][3],tc_[6][3];
    double ank_[6][3],onk_[6][3],Onkb_[6][3],AOnkri_[6][3],Ankb_[6][3],AnkAtk_[6
      ][3],anb_[1][3],onb_[1][3],dyrcom_[1][3];
    double ffk_[6][3],ttk_[6][3],fccikt_[6][3],ffkb_[1][3],ttkb_[1][3];
} alien_grhs_t;
#define fs (alien_grhs.fs_)
#define udot (alien_grhs.udot_)
#define ank (alien_grhs.ank_)
#define anb (alien_grhs.anb_)
#define onk (alien_grhs.onk_)
#define onb (alien_grhs.onb_)
#define Onkb (alien_grhs.Onkb_)
#define AOnkri (alien_grhs.AOnkri_)
#define Ankb (alien_grhs.Ankb_)
#define AnkAtk (alien_grhs.AnkAtk_)
#define dyrcom (alien_grhs.dyrcom_)
#define ffk (alien_grhs.ffk_)
#define ttk (alien_grhs.ttk_)
#define fccikt (alien_grhs.fccikt_)
#define ffkb (alien_grhs.ffkb_)
#define ttkb (alien_grhs.ttkb_)
#define dyad (alien_grhs.dyad_)
#define fc (alien_grhs.fc_)
#define tc (alien_grhs.tc_)
#define tauc (alien_grhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} alien_gtemp_t;
#define temp (alien_gtemp.temp_)
#define tmat1 (alien_gtemp.tmat1_)
#define tmat2 (alien_gtemp.tmat2_)
#define tvec1 (alien_gtemp.tvec1_)
#define tvec2 (alien_gtemp.tvec2_)
#define tvec3 (alien_gtemp.tvec3_)
#define tvec4 (alien_gtemp.tvec4_)
#define tvec5 (alien_gtemp.tvec5_)
#define tsc1 (alien_gtemp.tsc1_)
#define tsc2 (alien_gtemp.tsc2_)
#define tsc3 (alien_gtemp.tsc3_)

alien_gtopo_t alien_gtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 1,
    /* ndof */ 6,
    /* ncons */ 0,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 1,
    /* nlball */ 0,
    /* npres */ 0,
    /* nuser */ 0,
    /* jtype[0] */ 6,
    /* inb[0] */ -1,
    /* outb[0] */ 0,
    /* njntdof[0] */ 6,
    /* njntc[0] */ 0,
    /* njntp[0] */ 0,
    /* firstq[0] */ 0,
    /* ballq[0] */ 6,
    /* firstm[0] */ -1,
    /* firstp[0] */ -1,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 1,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
};
alien_ginput_t alien_ginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ 0.,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 1.,

/* inertia */
    /* ik[0][0][0] */ 1.,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ 4.,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ 9.,

/* tree hinge axis vectors */
    /* pin[0][0] */ 1.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 0.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 1.,
    /* pin[1][2] */ 0.,
    /* pin[2][0] */ 0.,
    /* pin[2][1] */ 0.,
    /* pin[2][2] */ 1.,
    /* pin[3][0] */ 0.,
    /* pin[3][1] */ 0.,
    /* pin[3][2] */ 0.,
    /* pin[4][0] */ 0.,
    /* pin[4][1] */ 0.,
    /* pin[4][2] */ 0.,
    /* pin[5][0] */ 0.,
    /* pin[5][1] */ 0.,
    /* pin[5][2] */ 0.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ 0.,
    /* rk[0][2] */ 0.,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,
    /* pres[2] */ 0.,
    /* pres[3] */ 0.,
    /* pres[4] */ 0.,
    /* pres[5] */ 0.,

/* stabilization parameters */
    /* stabvel */ 0.,
    /* stabpos */ 0.,

/* miscellaneous */
    /* mfrcflg */ 0,
    /* roustate */ 0,
    /* vpkflg */ 0,
    /* inerflg */ 0,
    /* mmflg */ 0,
    /* mmlduflg */ 0,
    /* wwflg */ 0,
    /* ltauflg */ 0,
    /* fs0flg */ 0,
    /* ii */ 0,
    /* mmap[0] */ 0,
    /* mmap[1] */ 1,
    /* mmap[2] */ 2,
    /* mmap[3] */ 3,
    /* mmap[4] */ 4,
    /* mmap[5] */ 5,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 0,
    /* gravq[1] */ 0,
    /* gravq[2] */ 0,
    /* mkq[0] */ 3,
    /* ikq[0][0][0] */ 3,
    /* ikq[0][0][1] */ 0,
    /* ikq[0][0][2] */ 0,
    /* ikq[0][1][0] */ 0,
    /* ikq[0][1][1] */ 3,
    /* ikq[0][1][2] */ 0,
    /* ikq[0][2][0] */ 0,
    /* ikq[0][2][1] */ 0,
    /* ikq[0][2][2] */ 3,
    /* pinq[0][0] */ 0,
    /* pinq[0][1] */ 0,
    /* pinq[0][2] */ 0,
    /* pinq[1][0] */ 0,
    /* pinq[1][1] */ 0,
    /* pinq[1][2] */ 0,
    /* pinq[2][0] */ 0,
    /* pinq[2][1] */ 0,
    /* pinq[2][2] */ 0,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* pinq[5][0] */ 0,
    /* pinq[5][1] */ 0,
    /* pinq[5][2] */ 0,
    /* rkq[0][0] */ 0,
    /* rkq[0][1] */ 0,
    /* rkq[0][2] */ 0,
    /* riq[0][0] */ 0,
    /* riq[0][1] */ 0,
    /* riq[0][2] */ 0,
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* presq[5] */ 0,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
alien_gstate_t alien_gstate;
alien_glhs_t alien_glhs;
alien_grhs_t alien_grhs;
alien_gtemp_t alien_gtemp;


void alien_init(void)
{
/*
Initialization routine


 This routine must be called before the first call to sdstate(), after
 supplying values for any `?' parameters in the input.
*/
    double sumsq,norminv;
    int i,j,k;


/* Check that all `?' parameters have been assigned values */

    for (k = 0; k < 3; k++) {
        if (gravq[k] == 1) {
            alien_seterr(7,25);
        }
    }
    for (k = 0; k < 1; k++) {
        if (mkq[k] == 1) {
            alien_seterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                alien_seterr(7,29);
            }
            if (riq[k][i] == 1) {
                alien_seterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    alien_seterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 6; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                alien_seterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out Vpk and Wpk */

    for (i = 0; i < 6; i++) {
        for (j = i; j <= 5; j++) {
            for (k = 0; k < 3; k++) {
                Vpk[i][j][k] = 0.;
                Wpk[i][j][k] = 0.;
            }
        }
    }

/* Compute pseudobody-related constants */

    rcom[0][0] = 0.;
    rcom[0][1] = 0.;
    rcom[0][2] = 0.;

/* Compute mass properties-related constants */

    mtot = mk[0];
    alien_serialno(&i);
    if (i != 30123) {
        alien_seterr(7,41);
    }
    roustate = 1;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void alien_st2ang(double st[7],
    double stang[6])
{
    int i;
    double dc[3][3];

    for (i = 0; i < 6; i++) {
        stang[i] = st[i];
    }
    alien_quat2dc(st[3],st[4],st[5],st[6],dc);
    alien_dc2ang(dc,&stang[3],&stang[4],&stang[5]);
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void alien_ang2st(double stang[6],
    double st[7])
{
    int i;
    double dc[3][3];

    for (i = 0; i < 6; i++) {
        st[i] = stang[i];
    }
    alien_ang2dc(stang[3],stang[4],stang[5],dc);
    alien_dc2quat(dc,&st[3],&st[4],&st[5],&st[6]);
}

/* Normalize Euler parameters in state. */

void alien_nrmsterr(double st[7],
    double normst[7],
    int routine)
{
    int i;
    double norm;

    for (i = 0; i < 7; i++) {
        normst[i] = st[i];
    }
    norm = sqrt(st[3]*st[3]+st[4]*st[4]+st[5]*st[5]+st[6]*st[6]);
    if (routine != 0) {
        if ((norm < .9) || (norm > 1.1)) {
            alien_seterr(routine,14);
        }
    }
    if (norm == 0.) {
        normst[6] = 1.;
        norm = 1.;
    }
    norm = 1./norm;
    normst[3] = normst[3]*norm;
    normst[4] = normst[4]*norm;
    normst[5] = normst[5]*norm;
    normst[6] = normst[6]*norm;
}

void alien_normst(double st[7],
    double normst[7])
{

    alien_nrmsterr(st,normst,0);
}

void alien_state(double timein,
    double qin[7],
    double uin[6])
{
/*
Compute kinematic information and store it in sdgstate.

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
    int i,j,qchg,uchg;
    double ee,stab;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        alien_seterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 6; i++) {
            if (presq[i] == 1) {
                alien_seterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 7; i++) {
            if (qin[i] != q[i]) {
                qchg = 1;
                break;
            }
        }
    } else {
        qchg = 1;
    }
/*
If time and qs are unchanged, check us
*/
    if (qchg == 0) {
        uchg = 0;
        for (i = 0; i < 6; i++) {
            if (uin[i] != u[i]) {
                uchg = 1;
                break;
            }
        }
    } else {
        uchg = 1;
    }
    curtim = timein;
    roustate = 2;
    if (qchg == 0) {
        goto skipqs;
    }
/*
Position-related variables need to be computed
*/
    vpkflg = 0;
    mmflg = 0;
    mmlduflg = 0;
    wwflg = 0;
    for (i = 0; i < 7; i++) {
        q[i] = qin[i];
    }
/*
Normalize Euler parameters in state
*/
    alien_nrmsterr(q,qn,8);
/*
Compute sines and cosines of q
*/
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = (1.-(2.*((qn[4]*qn[4])+(qn[5]*qn[5]))));
    Cik[3][0][1] = (2.*((qn[3]*qn[4])-(qn[5]*qn[6])));
    Cik[3][0][2] = (2.*((qn[3]*qn[5])+(qn[4]*qn[6])));
    Cik[3][1][0] = (2.*((qn[3]*qn[4])+(qn[5]*qn[6])));
    Cik[3][1][1] = (1.-(2.*((qn[3]*qn[3])+(qn[5]*qn[5]))));
    Cik[3][1][2] = (2.*((qn[4]*qn[5])-(qn[3]*qn[6])));
    Cik[3][2][0] = (2.*((qn[3]*qn[5])-(qn[4]*qn[6])));
    Cik[3][2][1] = (2.*((qn[3]*qn[6])+(qn[4]*qn[5])));
    Cik[3][2][2] = (1.-(2.*((qn[3]*qn[3])+(qn[4]*qn[4]))));
/*
Compute across-joint direction cosines Cib
*/
/*
Compute gravity
*/
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnb[0][0][0] = Cik[3][0][0];
    cnb[0][0][1] = Cik[3][0][1];
    cnb[0][0][2] = Cik[3][0][2];
    cnb[0][1][0] = Cik[3][1][0];
    cnb[0][1][1] = Cik[3][1][1];
    cnb[0][1][2] = Cik[3][1][2];
    cnb[0][2][0] = Cik[3][2][0];
    cnb[0][2][1] = Cik[3][2][1];
    cnb[0][2][2] = Cik[3][2][2];
/*
Compute q-related auxiliary variables
*/
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnb[0][0] = q[0];
    rnb[0][1] = q[1];
    rnb[0][2] = q[2];
/*
Compute com (system mass center location in N)
*/
    com[0] = ((1./mk[0])*(mk[0]*q[0]));
    com[1] = ((1./mk[0])*(mk[0]*q[1]));
    com[2] = ((1./mk[0])*(mk[0]*q[2]));
    skipqs: ;
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 6; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wb[0][0] = u[3];
    wb[0][1] = u[4];
    wb[0][2] = u[5];
/*
Compute auxiliary variables involving wk
*/
    IkWk[5][0] = (ik[0][0][0]*u[3]);
    IkWk[5][1] = (ik[0][1][1]*u[4]);
    IkWk[5][2] = (ik[0][2][2]*u[5]);
    WkIkWk[5][0] = ((IkWk[5][2]*u[4])-(IkWk[5][1]*u[5]));
    WkIkWk[5][1] = ((IkWk[5][0]*u[5])-(IkWk[5][2]*u[3]));
    WkIkWk[5][2] = ((IkWk[5][1]*u[3])-(IkWk[5][0]*u[4]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (u[3]*u[3]);
    w1w1[0] = (u[4]*u[4]);
    w2w2[0] = (u[5]*u[5]);
    w0w1[0] = (u[3]*u[4]);
    w0w2[0] = (u[3]*u[5]);
    w1w2[0] = (u[4]*u[5]);
    w00w11[0] = -(w0w0[0]+w1w1[0]);
    w00w22[0] = -(w0w0[0]+w2w2[0]);
    w11w22[0] = -(w1w1[0]+w2w2[0]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnb[0][0] = u[0];
    vnb[0][1] = u[1];
    vnb[0][2] = u[2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = (.5*((q[6]*u[3])+((q[4]*u[5])-(q[5]*u[4]))));
    qdot[4] = (.5*((q[5]*u[3])+((q[6]*u[4])-(q[3]*u[5]))));
    qdot[5] = (.5*(((q[3]*u[4])+(q[6]*u[5]))-(q[4]*u[3])));
    qdot[6] = -(.5*((q[3]*u[3])+((q[4]*u[4])+(q[5]*u[5]))));
    if (stabvel  !=  0.) {
        ee = ((q[6]*q[6])+((q[5]*q[5])+((q[3]*q[3])+(q[4]*q[4]))));
        stab = ((stabvel*(1.-ee))/ee);
        qdot[3] = (qdot[3]+(q[3]*stab));
        qdot[4] = (qdot[4]+(q[4]*stab));
        qdot[5] = (qdot[5]+(q[5]*stab));
        qdot[6] = (qdot[6]+(q[6]*stab));
    }
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 6; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   38 adds/subtracts/negates
                     73 multiplies
                      4 divides
                     83 assignments
*/
}

void alien_qdot(double oqdot[7])
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(63,23);
        return;
    }
    for (i = 0; i <= 6; i++) {
        oqdot[i] = qdot[i];
    }
}

void alien_u2qdot(double uin[6],
    double oqdot[7])
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(64,23);
        return;
    }
    for (i = 0; i <= 5; i++) {
        oqdot[i] = uin[i];
    }
    oqdot[3] = (.5*((q[6]*uin[3])+((q[4]*uin[5])-(q[5]*uin[4]))));
    oqdot[4] = (.5*((q[5]*uin[3])+((q[6]*uin[4])-(q[3]*uin[5]))));
    oqdot[5] = (.5*(((q[3]*uin[4])+(q[6]*uin[5]))-(q[4]*uin[3])));
    oqdot[6] = -(.5*((q[3]*uin[3])+((q[4]*uin[4])+(q[5]*uin[5]))));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                     16 multiplies
                      0 divides
                     10 assignments
*/
}

void alien_psstate(double lqin[1])
{

    if (roustate != 2) {
        alien_seterr(9,23);
        return;
    }
}

void alien_dovpk(void)
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[3][3][0] = 1.;
        Wpk[3][4][0] = 1.;
        Wpk[3][5][0] = 1.;
        Wpk[4][4][1] = 1.;
        Wpk[4][5][1] = 1.;
        Wpk[5][5][2] = 1.;
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = 1.;
        Vpk[0][1][0] = 1.;
        Vpk[0][2][0] = 1.;
        Vpk[0][3][0] = Cik[3][0][0];
        Vpk[0][3][1] = Cik[3][0][1];
        Vpk[0][3][2] = Cik[3][0][2];
        Vpk[0][4][0] = Cik[3][0][0];
        Vpk[0][4][1] = Cik[3][0][1];
        Vpk[0][4][2] = Cik[3][0][2];
        Vpk[0][5][0] = Cik[3][0][0];
        Vpk[0][5][1] = Cik[3][0][1];
        Vpk[0][5][2] = Cik[3][0][2];
        Vpk[1][1][1] = 1.;
        Vpk[1][2][1] = 1.;
        Vpk[1][3][0] = Cik[3][1][0];
        Vpk[1][3][1] = Cik[3][1][1];
        Vpk[1][3][2] = Cik[3][1][2];
        Vpk[1][4][0] = Cik[3][1][0];
        Vpk[1][4][1] = Cik[3][1][1];
        Vpk[1][4][2] = Cik[3][1][2];
        Vpk[1][5][0] = Cik[3][1][0];
        Vpk[1][5][1] = Cik[3][1][1];
        Vpk[1][5][2] = Cik[3][1][2];
        Vpk[2][2][2] = 1.;
        Vpk[2][3][0] = Cik[3][2][0];
        Vpk[2][3][1] = Cik[3][2][1];
        Vpk[2][3][2] = Cik[3][2][2];
        Vpk[2][4][0] = Cik[3][2][0];
        Vpk[2][4][1] = Cik[3][2][1];
        Vpk[2][4][2] = Cik[3][2][2];
        Vpk[2][5][0] = Cik[3][2][0];
        Vpk[2][5][1] = Cik[3][2][1];
        Vpk[2][5][2] = Cik[3][2][2];
        vpkflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     39 assignments
*/
}

void alien_doltau(void)
{

/*
Compute effect of loop hinge torques
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void alien_doiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
/*
Compute Atk (inertial linear acceleration)
*/
        inerflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void alien_dofs0(void)
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        alien_doltau();
        alien_doiner();
/*
Compute Fstar (forces)
*/
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = (WkIkWk[5][0]-utk[0][0]);
        Tstar[5][1] = (WkIkWk[5][1]-utk[0][1]);
        Tstar[5][2] = (WkIkWk[5][2]-utk[0][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        alien_dovpk();
        fs0[0] = (utau[0]+((Cik[3][0][2]*ufk[0][2])+((Cik[3][0][0]*ufk[0][0])+(
          Cik[3][0][1]*ufk[0][1]))));
        fs0[1] = (utau[1]+((Cik[3][1][2]*ufk[0][2])+((Cik[3][1][0]*ufk[0][0])+(
          Cik[3][1][1]*ufk[0][1]))));
        fs0[2] = (utau[2]+((Cik[3][2][2]*ufk[0][2])+((Cik[3][2][0]*ufk[0][0])+(
          Cik[3][2][1]*ufk[0][1]))));
        fs0[3] = (utau[3]-Tstar[5][0]);
        fs0[4] = (utau[4]-Tstar[5][1]);
        fs0[5] = (utau[5]-Tstar[5][2]);
        fs0flg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   15 adds/subtracts/negates
                      9 multiplies
                      0 divides
                      9 assignments
*/
}

void alien_domm(int routine)
{
    int dumroutine,errnum;
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        alien_dovpk();
        mm[0][0] = (mk[0]*((Cik[3][0][2]*Cik[3][0][2])+((Cik[3][0][0]*
          Cik[3][0][0])+(Cik[3][0][1]*Cik[3][0][1]))));
        mm[0][1] = (mk[0]*((Cik[3][0][2]*Cik[3][1][2])+((Cik[3][0][0]*
          Cik[3][1][0])+(Cik[3][0][1]*Cik[3][1][1]))));
        mm[0][2] = (mk[0]*((Cik[3][0][2]*Cik[3][2][2])+((Cik[3][0][0]*
          Cik[3][2][0])+(Cik[3][0][1]*Cik[3][2][1]))));
        mm[0][3] = 0.;
        mm[0][4] = 0.;
        mm[0][5] = 0.;
        mm[1][1] = (mk[0]*((Cik[3][1][2]*Cik[3][1][2])+((Cik[3][1][0]*
          Cik[3][1][0])+(Cik[3][1][1]*Cik[3][1][1]))));
        mm[1][2] = (mk[0]*((Cik[3][1][2]*Cik[3][2][2])+((Cik[3][1][0]*
          Cik[3][2][0])+(Cik[3][1][1]*Cik[3][2][1]))));
        mm[1][3] = 0.;
        mm[1][4] = 0.;
        mm[1][5] = 0.;
        mm[2][2] = (mk[0]*((Cik[3][2][2]*Cik[3][2][2])+((Cik[3][2][0]*
          Cik[3][2][0])+(Cik[3][2][1]*Cik[3][2][1]))));
        mm[2][3] = 0.;
        mm[2][4] = 0.;
        mm[2][5] = 0.;
        mm[3][3] = ik[0][0][0];
        mm[3][4] = 0.;
        mm[3][5] = 0.;
        mm[4][4] = ik[0][1][1];
        mm[4][5] = 0.;
        mm[5][5] = ik[0][2][2];
/*
Check for singular mass matrix
*/
        for (i = 0; i < 6; i++) {
            if (mm[i][i] < 1e-13) {
                alien_seterr(routine,47);
            }
        }
        alien_error(&dumroutine,&errnum);
        if (errnum == 0) {
            mmflg = 1;
        }
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   12 adds/subtracts/negates
                     24 multiplies
                      0 divides
                     21 assignments
*/
}

void alien_dommldu(int routine)
{
    int i;
    int dumroutine,errnum;

    if (mmlduflg == 0) {
        alien_domm(routine);
/*
Numerically decompose the mass matrix
*/
        alien_ldudcomp(6,6,mmap,1e-13,workss,works,mm,mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 6; i++) {
            if (mdi[i] <= 1e-13) {
                alien_seterr(routine,47);
            }
        }
        alien_error(&dumroutine,&errnum);
        if (errnum == 0) {
            mmlduflg = 1;
        }
    }
}

void alien_lhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    alien_dommldu(routine);
    alien_dofs0();
}

void alien_mfrc(double imult[1])
{

}

void alien_equivht(double tau[6])
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[6][3],tstareq[6][3];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    alien_dovpk();
    tau[0] = (utau[0]+((Cik[3][0][2]*ufk[0][2])+((Cik[3][0][0]*ufk[0][0])+(
      Cik[3][0][1]*ufk[0][1]))));
    tau[1] = (utau[1]+((Cik[3][1][2]*ufk[0][2])+((Cik[3][1][0]*ufk[0][0])+(
      Cik[3][1][1]*ufk[0][1]))));
    tau[2] = (utau[2]+((Cik[3][2][2]*ufk[0][2])+((Cik[3][2][0]*ufk[0][0])+(
      Cik[3][2][1]*ufk[0][1]))));
    tau[3] = (utau[3]+utk[0][0]);
    tau[4] = (utau[4]+utk[0][1]);
    tau[5] = (utau[5]+utk[0][2]);
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   12 adds/subtracts/negates
                      9 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_fs0(void)
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
    fs[2] = fs0[2];
    fs[3] = fs0[3];
    fs[4] = fs0[4];
    fs[5] = fs0[5];
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_fsmult(void)
{
    int i;

/*
Compute Fs (multiplier-generated forces only)
*/
    for (i = 0; i < 6; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_fsfull(void)
{

/*
Compute Fs (including all forces)
*/
    alien_fsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    6 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_fsgenmult(void)
{
    int i;

/*
Compute Fs (generic multiplier-generated forces)
*/
    for (i = 0; i < 6; i++) {
        fs[i] = 0.;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_fsgenfull(void)
{

/*
Compute Fs (incl generic mult & other forces)
*/
    alien_fsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    6 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_fulltrq(double udotin[6],
    double multin[1],
    double trqout[6])
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[6][3],tstarr[6][3],Otkr[6][3],Atir[6][3],Atkr[6][3];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(61,23);
        return;
    }
/*
Account for inertial accelerations and supplied udots
*/
    Atkr[3][0] = ((Cik[3][2][0]*udotin[2])+((Cik[3][0][0]*udotin[0])+(
      Cik[3][1][0]*udotin[1])));
    Atkr[3][1] = ((Cik[3][2][1]*udotin[2])+((Cik[3][0][1]*udotin[0])+(
      Cik[3][1][1]*udotin[1])));
    Atkr[3][2] = ((Cik[3][2][2]*udotin[2])+((Cik[3][0][2]*udotin[0])+(
      Cik[3][1][2]*udotin[1])));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = (ufk[0][0]-(Atkr[3][0]*mk[0]));
    fstarr[5][1] = (ufk[0][1]-(Atkr[3][1]*mk[0]));
    fstarr[5][2] = (ufk[0][2]-(Atkr[3][2]*mk[0]));
    tstarr[5][0] = (utk[0][0]-(WkIkWk[5][0]+(ik[0][0][0]*udotin[3])));
    tstarr[5][1] = (utk[0][1]-(WkIkWk[5][1]+(ik[0][1][1]*udotin[4])));
    tstarr[5][2] = (utk[0][2]-(WkIkWk[5][2]+(ik[0][2][2]*udotin[5])));
/*
Now calculate the torques
*/
    alien_dovpk();
    trqout[0] = -(utau[0]+((Cik[3][0][2]*fstarr[5][2])+((Cik[3][0][0]*
      fstarr[5][0])+(Cik[3][0][1]*fstarr[5][1]))));
    trqout[1] = -(utau[1]+((Cik[3][1][2]*fstarr[5][2])+((Cik[3][1][0]*
      fstarr[5][0])+(Cik[3][1][1]*fstarr[5][1]))));
    trqout[2] = -(utau[2]+((Cik[3][2][2]*fstarr[5][2])+((Cik[3][2][0]*
      fstarr[5][0])+(Cik[3][2][1]*fstarr[5][1]))));
    trqout[3] = -(tstarr[5][0]+utau[3]);
    trqout[4] = -(tstarr[5][1]+utau[4]);
    trqout[5] = -(tstarr[5][2]+utau[5]);
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   33 adds/subtracts/negates
                     24 multiplies
                      0 divides
                     15 assignments
*/
}

void alien_comptrq(double udotin[6],
    double trqout[6])
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    double multin[1];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(60,23);
        return;
    }
    alien_fulltrq(udotin,multin,trqout);
}

void alien_multtrq(double multin[1],
    double trqout[6])
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(65,23);
        return;
    }
    for (i = 0; i < 6; i++) {
        trqout[i] = 0.;
    }
}

void alien_rhs(void)
{
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

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = utau[0];
    tauc[1] = utau[1];
    tauc[2] = utau[2];
    tauc[3] = utau[3];
    tauc[4] = utau[4];
    tauc[5] = utau[5];
    alien_doiner();
/*
Compute onk & onb (angular accels in N)
*/
    onb[0][0] = udot[3];
    onb[0][1] = udot[4];
    onb[0][2] = udot[5];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = w11w22[0];
    dyad[0][0][1] = (w0w1[0]-udot[5]);
    dyad[0][0][2] = (udot[4]+w0w2[0]);
    dyad[0][1][0] = (udot[5]+w0w1[0]);
    dyad[0][1][1] = w00w22[0];
    dyad[0][1][2] = (w1w2[0]-udot[3]);
    dyad[0][2][0] = (w0w2[0]-udot[4]);
    dyad[0][2][1] = (udot[3]+w1w2[0]);
    dyad[0][2][2] = w00w11[0];
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[3][0] = ((Cik[3][2][0]*udot[2])+((Cik[3][0][0]*udot[0])+(Cik[3][1][0]*
      udot[1])));
    Ankb[3][1] = ((Cik[3][2][1]*udot[2])+((Cik[3][0][1]*udot[0])+(Cik[3][1][1]*
      udot[1])));
    Ankb[3][2] = ((Cik[3][2][2]*udot[2])+((Cik[3][0][2]*udot[0])+(Cik[3][1][2]*
      udot[1])));
    ank[5][0] = ((Ankb[3][2]*Cik[3][0][2])+((Ankb[3][0]*Cik[3][0][0])+(
      Ankb[3][1]*Cik[3][0][1])));
    ank[5][1] = ((Ankb[3][2]*Cik[3][1][2])+((Ankb[3][0]*Cik[3][1][0])+(
      Ankb[3][1]*Cik[3][1][1])));
    ank[5][2] = ((Ankb[3][2]*Cik[3][2][2])+((Ankb[3][0]*Cik[3][2][0])+(
      Ankb[3][1]*Cik[3][2][1])));
    anb[0][0] = ank[5][0];
    anb[0][1] = ank[5][1];
    anb[0][2] = ank[5][2];
    roustate = 3;
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   18 adds/subtracts/negates
                     18 multiplies
                      0 divides
                     27 assignments
*/
}

void alien_massmat(double mmat[6][6])
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(57,23);
        return;
    }
    alien_domm(57);
    for (i = 0; i < 6; i++) {
        for (j = i; j <= 5; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

void alien_frcmat(double fmat[6])
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(58,23);
        return;
    }
    alien_dofs0();
    for (i = 0; i < 6; i++) {
        fmat[i] = fs0[i];
    }
}

void alien_pseudo(double lqout[1],
    double luout[1])
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void alien_psqdot(double lqdout[1])
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void alien_psudot(double ludout[1])
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void alien_perr(double errs[1])
{

}

void alien_verr(double errs[1])
{

}

void alien_aerr(double errs[1])
{

}
int 
alien_chkbnum(int routine,
    int bnum)
{

    if ((bnum < -1) || (bnum > 0)) {
        alien_seterr(routine,15);
        return 1;
    }
    return 0;
}
int 
alien_chkjnum(int routine,
    int jnum)
{

    if ((jnum < 0) || (jnum > 0)) {
        alien_seterr(routine,16);
        return 1;
    }
    return 0;
}
int 
alien_chkucnum(int routine,
    int ucnum)
{

    if ((ucnum < 0) || (ucnum > -1)) {
        alien_seterr(routine,21);
        return 1;
    }
    return 0;
}
int 
alien_chkjaxis(int routine,
    int jnum,
    int axnum)
{
    int maxax;

    if (alien_chkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        alien_seterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        alien_seterr(routine,18);
        return 1;
    }
    return 0;
}
int 
alien_chkjpin(int routine,
    int jnum,
    int pinno)
{
    int maxax,pinok;

    if (alien_chkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        alien_seterr(routine,17);
        return 1;
    }
    if (njntdof[jnum] >= 3) {
        maxax = 2;
    } else {
        maxax = njntdof[jnum]-1;
    }
    if (jtype[jnum] == 4) {
        maxax = -1;
    }
    if (jtype[jnum] == 7) {
        maxax = 0;
    }
    pinok = 0;
    if (pinno <= maxax) {
        pinok = 1;
    }
    if (pinok == 0) {
        alien_seterr(routine,18);
        return 1;
    }
    return 0;
}
int 
alien_indx(int joint,
    int axis)
{
    int offs,gotit;

    if (alien_chkjaxis(36,joint,axis) != 0) {
        return 0;
    }
    gotit = 0;
    if (jtype[joint] == 4) {
        if (axis == 3) {
            offs = ballq[joint];
            gotit = 1;
        }
    } else {
        if ((jtype[joint] == 6) || (jtype[joint] == 21)) {
            if (axis == 6) {
                offs = ballq[joint];
                gotit = 1;
            }
        }
    }
    if (gotit == 0) {
        offs = firstq[joint]+axis;
    }
    return offs;
}

void alien_presacc(int joint,
    int axis,
    double prval)
{

}

void alien_presvel(int joint,
    int axis,
    double prval)
{

}

void alien_prespos(int joint,
    int axis,
    double prval)
{

}

void alien_getht(int joint,
    int axis,
    double *torque)
{

    if (alien_chkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        alien_seterr(30,24);
        return;
    }
    *torque = tauc[alien_indx(joint,axis)];
}

void alien_hinget(int joint,
    int axis,
    double torque)
{

    if (alien_chkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        alien_seterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[alien_indx(joint,axis)] = mtau[alien_indx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[alien_indx(joint,axis)] = utau[alien_indx(joint,axis)]+torque;
    }
}

void alien_pointf(int body,
    double point[3],
    double force[3])
{
    double torque[3];

    if (alien_chkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        alien_seterr(11,23);
        return;
    }
    if (body == -1) {
        return;
    }
    torque[0] = point[1]*force[2]-point[2]*force[1];
    torque[1] = point[2]*force[0]-point[0]*force[2];
    torque[2] = point[0]*force[1]-point[1]*force[0];
    if (mfrcflg != 0) {
        mfk[body][0] = mfk[body][0]+force[0];
        mtk[body][0] = mtk[body][0]+torque[0];
        mfk[body][1] = mfk[body][1]+force[1];
        mtk[body][1] = mtk[body][1]+torque[1];
        mfk[body][2] = mfk[body][2]+force[2];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        ufk[body][0] = ufk[body][0]+force[0];
        utk[body][0] = utk[body][0]+torque[0];
        ufk[body][1] = ufk[body][1]+force[1];
        utk[body][1] = utk[body][1]+torque[1];
        ufk[body][2] = ufk[body][2]+force[2];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void alien_bodyt(int body,
    double torque[3])
{

    if (alien_chkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        alien_seterr(12,23);
        return;
    }
    if (body == -1) {
        return;
    }
    if (mfrcflg != 0) {
        mtk[body][0] = mtk[body][0]+torque[0];
        mtk[body][1] = mtk[body][1]+torque[1];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        utk[body][0] = utk[body][0]+torque[0];
        utk[body][1] = utk[body][1]+torque[1];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void alien_doww(int routine)
{

    roustate = 2;
    if (wwflg == 0) {
        wwflg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void alien_xudot0(int routine,
    double oudot0[6])
{
/*
Compute unconstrained equations
*/
    int i;

    alien_lhs(routine);
/*
Solve equations for udots
*/
    alien_fs0();
    alien_ldubslv(6,6,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 5; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      6 assignments
*/
}

void alien_udot0(double oudot0[6])
{

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(66,23);
        return;
    }
    alien_xudot0(66,oudot0);
}

void alien_setudot(double iudot[6])
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(68,23);
        return;
    }
    for (i = 0; i <= 5; i++) {
        udot[i] = iudot[i];
    }
    alien_rhs();
}

void alien_xudotm(int routine,
    double imult[1],
    double oudotm[6])
{
/*
Compute udots due only to multipliers
*/
    int i;

    alien_lhs(routine);
    for (i = 0; i <= 5; i++) {
        udot[i] = 0.;
    }
    for (i = 0; i <= 5; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     12 assignments
*/
}

void alien_udotm(double imult[1],
    double oudotm[6])
{

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(67,23);
        return;
    }
    alien_xudotm(67,imult,oudotm);
}

void alien_deriv(double oqdot[7],
    double oudot[6])
{
/*
This is the derivative section for a 1-body ground-based
system with 6 hinge degree(s) of freedom.
*/
    int i;
    double udot0[6],udot1[6];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        alien_seterr(17,32);
    }
    if (stabposq == 1) {
        alien_seterr(17,33);
    }
    wsiz = 0;
/*
Compute unconstrained equations
*/
    alien_xudot0(17,udot0);
    alien_rhs();
    wrank = 0;
    for (i = 0; i <= 6; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 5; i++) {
        oudot[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     13 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void alien_resid(double eqdot[7],
    double eudot[6],
    double emults[1],
    double resid[13])
{
    int i;
    double uderrs[6];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(16,23);
        return;
    }
    if (stabposq == 1) {
        alien_seterr(16,33);
    }
    alien_fulltrq(eudot,emults,uderrs);
    for (i = 0; i < 7; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 6; i++) {
        resid[7+i] = uderrs[i];
    }
    for (i = 0; i < 6; i++) {
        udot[i] = eudot[i];
    }
    alien_rhs();
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    7 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     19 assignments
*/
}

void alien_mult(double omults[1],
    int *owrank,
    int omultmap[1])
{

    if (roustate != 3) {
        alien_seterr(34,24);
        return;
    }
    *owrank = wrank;
}

void alien_reac(double force[1][3],
    double torque[1][3])
{
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

    if (roustate != 3) {
        alien_seterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    fc[5][0] = ((Ankb[3][0]*mk[0])-ufk[0][0]);
    fc[5][1] = ((Ankb[3][1]*mk[0])-ufk[0][1]);
    fc[5][2] = ((Ankb[3][2]*mk[0])-ufk[0][2]);
    tc[5][0] = ((WkIkWk[5][0]+(ik[0][0][0]*udot[3]))-utk[0][0]);
    tc[5][1] = ((WkIkWk[5][1]+(ik[0][1][1]*udot[4]))-utk[0][1]);
    tc[5][2] = ((WkIkWk[5][2]+(ik[0][2][2]*udot[5]))-utk[0][2]);
    fccikt[5][0] = fc[5][0];
    fccikt[5][1] = fc[5][1];
    fccikt[5][2] = fc[5][2];
    ffk[4][0] = -fccikt[5][0];
    ffk[4][1] = -fccikt[5][1];
    ffk[4][2] = -fccikt[5][2];
    ttk[4][0] = -tc[5][0];
    ttk[4][1] = -tc[5][1];
    ttk[4][2] = -tc[5][2];
    fc[4][0] = -ffk[4][0];
    fc[4][1] = -ffk[4][1];
    fc[4][2] = -ffk[4][2];
    tc[4][0] = -ttk[4][0];
    tc[4][1] = -ttk[4][1];
    tc[4][2] = -ttk[4][2];
    fccikt[4][0] = fc[4][0];
    fccikt[4][1] = fc[4][1];
    fccikt[4][2] = fc[4][2];
    ffk[3][0] = -fccikt[4][0];
    ffk[3][1] = -fccikt[4][1];
    ffk[3][2] = -fccikt[4][2];
    ttk[3][0] = -tc[4][0];
    ttk[3][1] = -tc[4][1];
    ttk[3][2] = -tc[4][2];
    fc[3][0] = -ffk[3][0];
    fc[3][1] = -ffk[3][1];
    fc[3][2] = -ffk[3][2];
    tc[3][0] = -ttk[3][0];
    tc[3][1] = -ttk[3][1];
    tc[3][2] = -ttk[3][2];
    fccikt[3][0] = ((Cik[3][0][2]*fc[3][2])+((Cik[3][0][0]*fc[3][0])+(
      Cik[3][0][1]*fc[3][1])));
    fccikt[3][1] = ((Cik[3][1][2]*fc[3][2])+((Cik[3][1][0]*fc[3][0])+(
      Cik[3][1][1]*fc[3][1])));
    fccikt[3][2] = ((Cik[3][2][2]*fc[3][2])+((Cik[3][2][0]*fc[3][0])+(
      Cik[3][2][1]*fc[3][1])));
    ffk[2][0] = -fccikt[3][0];
    ffk[2][1] = -fccikt[3][1];
    ffk[2][2] = -fccikt[3][2];
    ttk[2][0] = -((Cik[3][0][2]*tc[3][2])+((Cik[3][0][0]*tc[3][0])+(Cik[3][0][1]
      *tc[3][1])));
    ttk[2][1] = -((Cik[3][1][2]*tc[3][2])+((Cik[3][1][0]*tc[3][0])+(Cik[3][1][1]
      *tc[3][1])));
    ttk[2][2] = -((Cik[3][2][2]*tc[3][2])+((Cik[3][2][0]*tc[3][0])+(Cik[3][2][1]
      *tc[3][1])));
    fc[2][0] = -ffk[2][0];
    fc[2][1] = -ffk[2][1];
    fc[2][2] = -ffk[2][2];
    tc[2][0] = -ttk[2][0];
    tc[2][1] = -ttk[2][1];
    tc[2][2] = -ttk[2][2];
    fccikt[2][0] = fc[2][0];
    fccikt[2][1] = fc[2][1];
    fccikt[2][2] = fc[2][2];
    ffk[1][0] = -fccikt[2][0];
    ffk[1][1] = -fccikt[2][1];
    ffk[1][2] = -fccikt[2][2];
    ttk[1][0] = -(tc[2][0]-(fccikt[2][1]*q[2]));
    ttk[1][1] = -(tc[2][1]+(fccikt[2][0]*q[2]));
    ttk[1][2] = -tc[2][2];
    fc[1][0] = -ffk[1][0];
    fc[1][1] = -ffk[1][1];
    fc[1][2] = -ffk[1][2];
    tc[1][0] = -ttk[1][0];
    tc[1][1] = -ttk[1][1];
    tc[1][2] = -ttk[1][2];
    fccikt[1][0] = fc[1][0];
    fccikt[1][1] = fc[1][1];
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = -fccikt[1][0];
    ffk[0][1] = -fccikt[1][1];
    ffk[0][2] = -fccikt[1][2];
    ttk[0][0] = -(tc[1][0]+(fccikt[1][2]*q[1]));
    ttk[0][1] = -tc[1][1];
    ttk[0][2] = -(tc[1][2]-(fccikt[1][0]*q[1]));
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[0][0] = fc[5][0];
    torque[0][0] = tc[5][0];
    force[0][1] = fc[5][1];
    torque[0][1] = tc[5][1];
    force[0][2] = fc[5][2];
    torque[0][2] = tc[5][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.00 seconds CPU time,
 1159168 additional bytes of memory.
 Equations contain   85 adds/subtracts/negates
                     28 multiplies
                      0 divides
                     87 assignments
*/
}

void alien_mom(double lm[3],
    double am[3],
    double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

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
    double lk[1][3],hnk[1][3];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(19,23);
        return;
    }
    lk[0][0] = (mk[0]*u[0]);
    lk[0][1] = (mk[0]*u[1]);
    lk[0][2] = (mk[0]*u[2]);
    hnk[0][0] = (ik[0][0][0]*u[3]);
    hnk[0][1] = (ik[0][1][1]*u[4]);
    hnk[0][2] = (ik[0][2][2]*u[5]);
    lm[0] = lk[0][0];
    lm[1] = lk[0][1];
    lm[2] = lk[0][2];
    am[0] = ((((Cik[3][0][2]*hnk[0][2])+((Cik[3][0][0]*hnk[0][0])+(Cik[3][0][1]*
      hnk[0][1])))+((lk[0][2]*q[1])-(lk[0][1]*q[2])))-((com[1]*lk[0][2])-(com[2]
      *lk[0][1])));
    am[1] = ((((Cik[3][1][2]*hnk[0][2])+((Cik[3][1][0]*hnk[0][0])+(Cik[3][1][1]*
      hnk[0][1])))+((lk[0][0]*q[2])-(lk[0][2]*q[0])))-((com[2]*lk[0][0])-(com[0]
      *lk[0][2])));
    am[2] = ((((Cik[3][2][2]*hnk[0][2])+((Cik[3][2][0]*hnk[0][0])+(Cik[3][2][1]*
      hnk[0][1])))+((lk[0][1]*q[0])-(lk[0][0]*q[1])))-((com[0]*lk[0][1])-(com[1]
      *lk[0][0])));
    *ke = (.5*(((hnk[0][2]*u[5])+((hnk[0][0]*u[3])+(hnk[0][1]*u[4])))+((lk[0][2]
      *u[2])+((lk[0][0]*u[0])+(lk[0][1]*u[1])))));
/*
 Used 0.00 seconds CPU time,
 2560000 additional bytes of memory.
 Equations contain   23 adds/subtracts/negates
                     34 multiplies
                      0 divides
                     13 assignments
*/
}

void alien_sys(double *mtoto,
    double cm[3],
    double icm[3][3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

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
    double ikcnkt[6][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(20,23);
        return;
    }
    *mtoto = mk[0];
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    ikcnkt[5][0][0] = (Cik[3][0][0]*ik[0][0][0]);
    ikcnkt[5][0][1] = (Cik[3][1][0]*ik[0][0][0]);
    ikcnkt[5][0][2] = (Cik[3][2][0]*ik[0][0][0]);
    ikcnkt[5][1][0] = (Cik[3][0][1]*ik[0][1][1]);
    ikcnkt[5][1][1] = (Cik[3][1][1]*ik[0][1][1]);
    ikcnkt[5][1][2] = (Cik[3][2][1]*ik[0][1][1]);
    ikcnkt[5][2][0] = (Cik[3][0][2]*ik[0][2][2]);
    ikcnkt[5][2][1] = (Cik[3][1][2]*ik[0][2][2]);
    ikcnkt[5][2][2] = (Cik[3][2][2]*ik[0][2][2]);
    icm[0][0] = (((mk[0]*((q[1]*q[1])+(q[2]*q[2])))+((Cik[3][0][2]*
      ikcnkt[5][2][0])+((Cik[3][0][0]*ikcnkt[5][0][0])+(Cik[3][0][1]*
      ikcnkt[5][1][0]))))-(mk[0]*((com[1]*com[1])+(com[2]*com[2]))));
    icm[0][1] = ((mk[0]*(com[0]*com[1]))+(((Cik[3][0][2]*ikcnkt[5][2][1])+((
      Cik[3][0][0]*ikcnkt[5][0][1])+(Cik[3][0][1]*ikcnkt[5][1][1])))-(mk[0]*(
      q[0]*q[1]))));
    icm[0][2] = ((mk[0]*(com[0]*com[2]))+(((Cik[3][0][2]*ikcnkt[5][2][2])+((
      Cik[3][0][0]*ikcnkt[5][0][2])+(Cik[3][0][1]*ikcnkt[5][1][2])))-(mk[0]*(
      q[0]*q[2]))));
    icm[1][0] = icm[0][1];
    icm[1][1] = (((mk[0]*((q[0]*q[0])+(q[2]*q[2])))+((Cik[3][1][2]*
      ikcnkt[5][2][1])+((Cik[3][1][0]*ikcnkt[5][0][1])+(Cik[3][1][1]*
      ikcnkt[5][1][1]))))-(mk[0]*((com[0]*com[0])+(com[2]*com[2]))));
    icm[1][2] = ((mk[0]*(com[1]*com[2]))+(((Cik[3][1][2]*ikcnkt[5][2][2])+((
      Cik[3][1][0]*ikcnkt[5][0][2])+(Cik[3][1][1]*ikcnkt[5][1][2])))-(mk[0]*(
      q[1]*q[2]))));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    icm[2][2] = (((mk[0]*((q[0]*q[0])+(q[1]*q[1])))+((Cik[3][2][2]*
      ikcnkt[5][2][2])+((Cik[3][2][0]*ikcnkt[5][0][2])+(Cik[3][2][1]*
      ikcnkt[5][1][2]))))-(mk[0]*((com[0]*com[0])+(com[1]*com[1]))));
/*
 Used 0.00 seconds CPU time,
 3584000 additional bytes of memory.
 Equations contain   30 adds/subtracts/negates
                     57 multiplies
                      0 divides
                     22 assignments
*/
}

void alien_pos(int body,
    double pt[3],
    double loc[3])
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (alien_chkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(21,23);
        return;
    }
    if (body  ==  -1) {
        loc[0] = pt[0];
        loc[1] = pt[1];
        loc[2] = pt[2];
    } else {
        pv[0] = rnb[body][0]+pt[0]*cnb[body][0][0]+pt[1]*cnb[body][0][1]+pt[2]*
          cnb[body][0][2];
        pv[1] = rnb[body][1]+pt[0]*cnb[body][1][0]+pt[1]*cnb[body][1][1]+pt[2]*
          cnb[body][1][2];
        pv[2] = rnb[body][2]+pt[0]*cnb[body][2][0]+pt[1]*cnb[body][2][1]+pt[2]*
          cnb[body][2][2];
        loc[0] = pv[0];
        loc[1] = pv[1];
        loc[2] = pv[2];
    }
}

void alien_vel(int body,
    double pt[3],
    double velo[3])
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (alien_chkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(22,23);
        return;
    }
    if (body  ==  -1) {
        velo[0] = 0.;
        velo[1] = 0.;
        velo[2] = 0.;
    } else {
        pv[0] = wb[body][1]*pt[2]-wb[body][2]*pt[1];
        pv[1] = wb[body][2]*pt[0]-wb[body][0]*pt[2];
        pv[2] = wb[body][0]*pt[1]-wb[body][1]*pt[0];
        velo[0] = vnb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2]
          *cnb[body][0][2];
        velo[1] = vnb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2]
          *cnb[body][1][2];
        velo[2] = vnb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2]
          *cnb[body][2][2];
    }
}

void alien_orient(int body,
    double dircos[3][3])
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (alien_chkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(23,23);
        return;
    }
    if (body == -1) {
        dircos[0][0] = 1.;
        dircos[0][1] = 0.;
        dircos[0][2] = 0.;
        dircos[1][0] = 0.;
        dircos[1][1] = 1.;
        dircos[1][2] = 0.;
        dircos[2][0] = 0.;
        dircos[2][1] = 0.;
        dircos[2][2] = 1.;
    } else {
        dircos[0][0] = cnb[body][0][0];
        dircos[0][1] = cnb[body][0][1];
        dircos[0][2] = cnb[body][0][2];
        dircos[1][0] = cnb[body][1][0];
        dircos[1][1] = cnb[body][1][1];
        dircos[1][2] = cnb[body][1][2];
        dircos[2][0] = cnb[body][2][0];
        dircos[2][1] = cnb[body][2][1];
        dircos[2][2] = cnb[body][2][2];
    }
}

void alien_angvel(int body,
    double avel[3])
{
/*
Return angular velocity of the body.

*/

    if (alien_chkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(24,23);
        return;
    }
    if (body == -1) {
        avel[0] = 0.;
        avel[1] = 0.;
        avel[2] = 0.;
    } else {
        avel[0] = wb[body][0];
        avel[1] = wb[body][1];
        avel[2] = wb[body][2];
    }
}

void alien_trans(int frbod,
    double ivec[3],
    int tobod,
    double ovec[3])
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (alien_chkbnum(25,frbod) != 0) {
        return;
    }
    if (alien_chkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(25,23);
        return;
    }
    if (frbod == tobod) {
        alien_vcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        alien_vcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        alien_vcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[frbod][0][0]+pv[1]*cnb[frbod][0][1]+pv[2]*cnb[frbod
          ][0][2];
        ovec[1] = pv[0]*cnb[frbod][1][0]+pv[1]*cnb[frbod][1][1]+pv[2]*cnb[frbod
          ][1][2];
        ovec[2] = pv[0]*cnb[frbod][2][0]+pv[1]*cnb[frbod][2][1]+pv[2]*cnb[frbod
          ][2][2];
        return;
    }
    pv[0] = ivec[0]*cnb[frbod][0][0]+ivec[1]*cnb[frbod][0][1]+ivec[2]*cnb[frbod
      ][0][2];
    pv[1] = ivec[0]*cnb[frbod][1][0]+ivec[1]*cnb[frbod][1][1]+ivec[2]*cnb[frbod
      ][1][2];
    pv[2] = ivec[0]*cnb[frbod][2][0]+ivec[1]*cnb[frbod][2][1]+ivec[2]*cnb[frbod
      ][2][2];
    ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod][2][
      0];
    ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod][2][
      1];
    ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod][2][
      2];
}

void alien_rel2cart(int coord,
    int body,
    double point[3],
    double linchg[3],
    double rotchg[3])
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 5)) {
        alien_seterr(59,45);
        return;
    }
    if (alien_chkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        alien_seterr(59,23);
        return;
    }
    gnd = -1;
    if (body == gnd) {
        x = -1;
    } else {
        x = firstq[body]+njntdof[body]-1;
    }
    if (x < coord) {
        alien_vset(0.,0.,0.,linchg);
        alien_vset(0.,0.,0.,rotchg);
        return;
    }
    alien_dovpk();
    for (i = 0; i < 3; i++) {
        rotchg[i] = Wpk[coord][x][i];
        lin[i] = Vpk[coord][x][i];
    }
    if (body == gnd) {
        alien_vcopy(point,pv);
    } else {
        pv[0] = rcom[body][0]+point[0];
        pv[1] = rcom[body][1]+point[1];
        pv[2] = rcom[body][2]+point[2];
    }
    alien_vcross(rotchg,pv,linchg);
    alien_vadd(linchg,lin,linchg);
}

void alien_acc(int body,
    double pt[3],
    double accel[3])
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (alien_chkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        alien_seterr(32,24);
        return;
    }
    if (body  ==  -1) {
        accel[0] = 0.;
        accel[1] = 0.;
        accel[2] = 0.;
    } else {
        pv[0] = pt[0]*dyad[body][0][0]+pt[1]*dyad[body][0][1]+pt[2]*dyad[body][0
          ][2];
        pv[1] = pt[0]*dyad[body][1][0]+pt[1]*dyad[body][1][1]+pt[2]*dyad[body][1
          ][2];
        pv[2] = pt[0]*dyad[body][2][0]+pt[1]*dyad[body][2][1]+pt[2]*dyad[body][2
          ][2];
        accel[0] = anb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2
          ]*cnb[body][0][2];
        accel[1] = anb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2
          ]*cnb[body][1][2];
        accel[2] = anb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2
          ]*cnb[body][2][2];
    }
}

void alien_angacc(int body,
    double aacc[3])
{
/*
Return angular acceleration of the body.

*/

    if (alien_chkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        alien_seterr(33,24);
        return;
    }
    if (body == -1) {
        aacc[0] = 0.;
        aacc[1] = 0.;
        aacc[2] = 0.;
    } else {
        aacc[0] = onb[body][0];
        aacc[1] = onb[body][1];
        aacc[2] = onb[body][2];
    }
}

void alien_grav(double gravin[3])
{

    alien_seterr(1,19);
    roustate = 0;
}

void alien_mass(int body,
    double massin)
{

    if (alien_chkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        alien_seterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        alien_seterr(2,19);
    }
    roustate = 0;
}

void alien_iner(int body,
    double inerin[3][3])
{
    int anyques;

    if (alien_chkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        alien_seterr(3,15);
        return;
    }
    anyques = 0;
    if (ikq[body][0][0]  !=  0) {
        ik[body][0][0] = inerin[0][0];
        ikq[body][0][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][1]  !=  0) {
        ik[body][0][1] = inerin[0][1];
        ikq[body][0][1] = 3;
        ik[body][1][0] = inerin[0][1];
        ikq[body][1][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][2]  !=  0) {
        ik[body][0][2] = inerin[0][2];
        ikq[body][0][2] = 3;
        ik[body][2][0] = inerin[0][2];
        ikq[body][2][0] = 3;
        anyques = 1;
    }
    if (ikq[body][1][1]  !=  0) {
        ik[body][1][1] = inerin[1][1];
        ikq[body][1][1] = 3;
        anyques = 1;
    }
    if (ikq[body][1][2]  !=  0) {
        ik[body][1][2] = inerin[1][2];
        ikq[body][1][2] = 3;
        ik[body][2][1] = inerin[1][2];
        ikq[body][2][1] = 3;
        anyques = 1;
    }
    if (ikq[body][2][2]  !=  0) {
        ik[body][2][2] = inerin[2][2];
        ikq[body][2][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        alien_seterr(3,19);
    }
    roustate = 0;
}

void alien_btj(int joint,
    double btjin[3])
{
    int anyques;

    if (alien_chkjnum(4,joint) != 0) {
        return;
    }
    anyques = 0;
    if (rkq[joint][0]  !=  0) {
        rk[joint][0] = btjin[0];
        rkq[joint][0] = 3;
        anyques = 1;
    }
    if (rkq[joint][1]  !=  0) {
        rk[joint][1] = btjin[1];
        rkq[joint][1] = 3;
        anyques = 1;
    }
    if (rkq[joint][2]  !=  0) {
        rk[joint][2] = btjin[2];
        rkq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        alien_seterr(4,19);
    }
    roustate = 0;
}

void alien_itj(int joint,
    double itjin[3])
{
    int anyques;

    if (alien_chkjnum(5,joint) != 0) {
        return;
    }
    anyques = 0;
    if (riq[joint][0]  !=  0) {
        ri[joint][0] = itjin[0];
        riq[joint][0] = 3;
        anyques = 1;
    }
    if (riq[joint][1]  !=  0) {
        ri[joint][1] = itjin[1];
        riq[joint][1] = 3;
        anyques = 1;
    }
    if (riq[joint][2]  !=  0) {
        ri[joint][2] = itjin[2];
        riq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        alien_seterr(5,19);
    }
    roustate = 0;
}

void alien_pin(int joint,
    int pinno,
    double pinin[3])
{
    int anyques,offs;

    if (alien_chkjpin(6,joint,pinno) != 0) {
        return;
    }
    anyques = 0;
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    if (pinq[offs][0]  !=  0) {
        pin[offs][0] = pinin[0];
        pinq[offs][0] = 3;
        anyques = 1;
    }
    if (pinq[offs][1]  !=  0) {
        pin[offs][1] = pinin[1];
        pinq[offs][1] = 3;
        anyques = 1;
    }
    if (pinq[offs][2]  !=  0) {
        pin[offs][2] = pinin[2];
        pinq[offs][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        alien_seterr(6,19);
    }
    roustate = 0;
}

void alien_pres(int joint,
    int axis,
    int presin)
{
    int anyques;

    if (alien_chkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        alien_seterr(37,20);
    }
    anyques = 0;
    if (presq[alien_indx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[alien_indx(joint,axis)] = 1.;
        } else {
            pres[alien_indx(joint,axis)] = 0.;
        }
        presq[alien_indx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        alien_seterr(37,19);
    }
    wwflg = 0;
}

void alien_conschg(void)
{

    wwflg = 0;
}

void alien_stab(double velin,
    double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void alien_getgrav(double gravout[3])
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void alien_getmass(int body,
    double *massout)
{

    if (alien_chkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        alien_seterr(40,15);
        return;
    }
    *massout = mk[body];
}

void alien_getiner(int body,
    double inerout[3][3])
{

    if (alien_chkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        alien_seterr(41,15);
        return;
    }
    inerout[0][0] = ik[body][0][0];
    inerout[0][1] = ik[body][0][1];
    inerout[0][2] = ik[body][0][2];
    inerout[1][0] = ik[body][1][0];
    inerout[1][1] = ik[body][1][1];
    inerout[1][2] = ik[body][1][2];
    inerout[2][0] = ik[body][2][0];
    inerout[2][1] = ik[body][2][1];
    inerout[2][2] = ik[body][2][2];
}

void alien_getbtj(int joint,
    double btjout[3])
{

    if (alien_chkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void alien_getitj(int joint,
    double itjout[3])
{

    if (alien_chkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void alien_getpin(int joint,
    int pinno,
    double pinout[3])
{
    int offs;

    if (alien_chkjpin(44,joint,pinno) != 0) {
        return;
    }
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    pinout[0] = pin[offs][0];
    pinout[1] = pin[offs][1];
    pinout[2] = pin[offs][2];
}

void alien_getpres(int joint,
    int axis,
    int *presout)
{

    if (alien_chkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[alien_indx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

void alien_getstab(double *velout,
    double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void alien_info(int info[50])
{

    info[0] = ground;
    info[1] = nbod;
    info[2] = ndof;
    info[3] = ncons;
    info[4] = nloop;
    info[5] = nldof;
    info[6] = nloopc;
    info[7] = nball;
    info[8] = nlball;
    info[9] = npres;
    info[10] = nuser;
    info[11] = 0;
/* info entries from 12-49 are reserved */
}

void alien_jnt(int joint,
    int info[50],
    int tran[6])
{
    int i,offs;

    if (alien_chkjnum(48,joint) != 0) {
        return;
    }
    info[0] = jtype[joint];
    info[1] = 0;
    offs = 0;
    info[2] = inb[joint];
    info[3] = outb[joint];
    info[4] = njntdof[joint];
    info[5] = njntc[joint];
    info[6] = njntp[joint];
    info[7] = firstq[joint];
    info[8] = ballq[joint];
    info[9] = firstm[joint];
    info[10] = firstp[joint];
/* info entries from 11-49 are reserved */

    for (i = 0; i <= 5; i++) {
        if (i  <  njntdof[joint]) {
            tran[i] = trans[offs+firstq[joint]+i];
        } else {
            tran[i] = -1;
        }
    }
}

void alien_cons(int consno,
    int info[50])
{

    if (alien_chkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}

void alien_gentime(int *gentm)
{

    *gentm = 213312;
}
/*
Done. CPU seconds used: 0.03  Memory used: 21213184 bytes.
Equation complexity:
  sdstate:    38 adds    73 multiplies     4 divides    83 assignments
  sdderiv:   116 adds   143 multiplies     6 divides   343 assignments
  sdresid:    58 adds    42 multiplies     0 divides   100 assignments
  sdreac:     85 adds    28 multiplies     0 divides    87 assignments
  sdmom:      23 adds    34 multiplies     0 divides    13 assignments
  sdsys:      30 adds    57 multiplies     0 divides    22 assignments
*/
