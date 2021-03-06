/* Copyright (c) 1988-96, B-Core (UK) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

#include <Xm/XmAll.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>

#define SC_BUT_NAME_MAX   100
#define SC_BUT_ACT_MAX    150
#define SC_CHECKED_OUT  0
#define SC_CHECKED_IN   1
#define SC_UNCHANGED    2

#define MAX_SRCName           75
#define MAX_CFGName           75

#include "BMotif_defs.h"

#include "BMotif_BaseParameters.h"

/* */
#include "BMotif_detect.h"

#include "CFG_DEP_BASE/CDE/C/CfgDepBase.h"

#include "CFG_DEP_BASE/CDE/C/file_dump.h"
#include "CFG_DEP_BASE/CDE/C/CfgDepCtx.h"
#include "CFG_DEP_BASE/CDE/C/CfgDepBaseCtx.h"
#include "CFG_DEP_BASE/CDE/C/Scalar_TYPE.h"
#include "CFG_DEP_BASE/CDE/C/Bool_TYPE.h"
#include "CFG_DEP_BASE/CDE/C/String_TYPE.h"
#include "CFG_DEP_BASE/CDE/C/basic_io.h"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_file_dump.h"

#include "CFG_DEP_BASE/CDE/C/Abs2Conc_ffnc_ctx.h"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_seq_ctx.h"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_set_ctx.h"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_str_ctx.h"
#include "CFG_DEP_BASE/CDE/C/Construct_ffnc_ctx.h"
#include "CFG_DEP_BASE/CDE/C/GENState_ffnc_ctx.h"
#include "CFG_DEP_BASE/CDE/C/MRIState_ffnc_ctx.h"
#include "CFG_DEP_BASE/CDE/C/Seqstr_ffnc_ctx.h"
#include "CFG_DEP_BASE/CDE/C/String_ffnc_ctx.h"

#include "../C/BToolkitlm_globals.h"

#include "../C/BToolkitd_ClientServer/CDE/C/BToolkitd_Client_Client.h"


/***
ClientSocket.c
***/
extern int hi_l;
extern int hi_m;
extern int hi_h;
extern char pid_id_file [];

#include "CFG_DEP_BASE/CDE/C/CfgDepCtx.h"



#define print_debug(m) \
  if ( is_debug ) \
      printf ( "\n    BMotif: debug trace %4d\n", m );

#define HERE(s) \
  printf ( s "\n");

#define storeStartClock \
  start_c = clock()

#define elapsedClock \
   clock() - start_c

#include "BMotif_version.h"

#ifdef BTOOLKIT_FLAG

#include "BMotif_help.h"

#endif

#ifdef BTOOLKIT_FLAG

extern int brz;

extern int started_from_cd;

extern FILE * bstdout;


#define alloc_minimum                1500

#define alloc_init                 500000

#define init_alloc_topup          2000000
#define alloc_topup               2500000


#define compact_cut_off          30000000

extern int * mmts;
extern int max_mem;

extern int BOOSTER_link;


/* from trmmch.c */

#define redirect_trm(fstr) \
    bstdout = fopen ( fstr, "w" ); \
    if ( bstdout == NULL ) { \
      fprintf ( stderr, "\n\n             Can't open %s for writing\n\n", fstr ); \
      exit___ ( 1 ); \
    }

#define reappend_trm(fstr) \
    bstdout = fopen ( fstr, "a" ); \
    if ( bstdout == NULL ) { \
      fprintf ( stderr, "\n\n             Can't open %s for appending\n\n", fstr ); \
      exit___ ( 1 ); \
    }

#define reset_trm \
    if ( fclose ( bstdout ) != 0 ) { \
      fprintf ( stderr, "\n\n             Can't close menu window\n\n" ); \
      exit___ ( 1 ); \
    } \
    bstdout = stdout;

#endif

/***
defined in CfgDepCtx.h:

ext:

#define mch         1
#define ref         2
#define imp         3
#define bse         4
#define itf         5
#define enm         6
#define doc         7
#define ops         8
#define mch_prf     9
#define ref_prf    10
#define imp_prf    11
#define map        12
#define mth        13

type:

#define usr 1
#define lib 2
#define bse_gen 3
#define enm_gen 4
#define itf_gen 5
#define prf_gen 6
#define usr_vhdl 7
#define gen_vhdl 8
#define lib_vhdl 9
***/

#ifdef BTOOLKIT_FLAG
extern Pixel lab_col_f [];
extern Pixel lab_col_b [];

extern Pixmap lab_col_pixmap []; /* */
#endif

/*******************************************************************************/


#define print_XmNtraversalOn_value(ss,ww) \
{ \
  Boolean bb; \
  XmNavigationType nt; \
  XtVaGetValues ( ww, XmNtraversalOn, &bb, NULL ); \
  if   ( bb == True ) printf ( "%s XmNtraversalOn is True ", ss ); \
  else                printf ( "%s XmNtraversalOn is False ", ss ); \
  XtVaGetValues ( ww, XmNnavigationType, &nt, NULL ); \
  if      ( nt == XmTAB_GROUP ) printf ( " XmTAB_GROUP\n" ); \
  else if ( nt == XmNONE )      printf ( " XmNONE\n" ); \
  else                          printf ( " Xm???\n" ); \
}

/*
#define print_tac_info(s) \
printf ( "\n+++++++++++++++++++ %s ++++++++++++++++++++", s ); \
printf ( "\n node %d end_of_tac_prf %d new_tac_prf %d tac_ptr_prf %d\n from_applicable_rr %d\n", run_man_prf_i, end_of_tac_prf, new_tac_prf, tac_ptr_prf, from_applicable_rr ); \
printf ( "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
*/


#ifdef WWW_VERSION

extern char strip_arr [];
extern int strip_arr_tot;

#define WWW_Err \
     WWWConstructsCycleCheck ( 1 ); \
     Popup_Err ( 0, "Option not available in WWW Demonstration Release" )

#endif /* WWW_VERSION */


#define chk_rep(x,y) \
      if ( ! x ) { \
        BT_base_err_exit ( y ); \
      }


#define PrintBase \
{ \
  int bb, obj; \
 \
  first_MRIState ( &bb, &obj ); \
  while ( bb ) { \
    print_BaseObj_MRIState ( obj ); \
    next_MRIState ( &bb, &obj, bb, obj ); \
  } \
 \
  first_GENState ( &bb, &obj ); \
  while ( bb ) { \
    print_BaseObj_GENState ( obj ); \
    next_GENState ( &bb, &obj, bb, obj ); \
  } \
 \
  first_Seqstr ( &bb, &obj ); \
  while ( bb ) { \
    print_BaseObj_Seqstr ( obj ); \
    next_Seqstr ( &bb, &obj, bb, obj ); \
  } \
 \
  first_String ( &bb, &obj ); \
  while ( bb ) { \
    print_BaseObj_String ( obj ); \
    next_String ( &bb, &obj, bb, obj ); \
  } \
 \
  first_Abs2Conc ( &bb, &obj ); \
  while ( bb ) { \
    print_BaseObj_Abs2Conc ( obj ); \
    next_Abs2Conc ( &bb, &obj, bb, obj ); \
  } \
 \
  print_Globals_CfgDepBase(); \
 \
  first_Construct ( &bb, &obj ); \
  while ( bb ) { \
    print_BaseObj_Construct ( obj ); \
    next_Construct ( &bb, &obj, bb, obj ); \
  } \
}

#define Info_40_Upgrade(n) \
{ \
  printf ( "    --------------------- %d ----------------\n", n ); \
  printf ( "\n" ); \
  printf ( "   %6d %6d         Construct\n", (Construct_ssize_fnc_obj - Construct_sold_fnc_obj), Construct_ffnc_objP3 ); \
  printf ( "   %6d %6d         Abs2Conc\n", (Abs2Conc_ssize_fnc_obj - Abs2Conc_sold_fnc_obj), Abs2Conc_ffnc_objP3 ); \
  printf ( "   %6d %6d         MRIState\n", (MRIState_ssize_fnc_obj - MRIState_sold_fnc_obj), MRIState_ffnc_objP3 ); \
  printf ( "   %6d %6d         GENState\n", (GENState_ssize_fnc_obj - GENState_sold_fnc_obj), GENState_ffnc_objP3 ); \
  printf ( "   %6d %6d %6d  STR_OBJ\n", CfgDepBase_ssiz_len_str_obj-1-CfgDepBase_ssiz_old_str_obj, CfgDepBase_str_objP1, CfgDepBase_tot_str_obj ); \
  printf ( "   %6d %6d %6d  SEQ_OBJ\n", CfgDepBase_ssiz_len_seq_obj-1-CfgDepBase_ssiz_old_seq_obj, CfgDepBase_seq_objP2, CfgDepBase_tot_seq_obj ); \
  printf ( "   %6d %6d %6d  SET_OBJ\n", CfgDepBase_ssiz_len_set_obj-1-CfgDepBase_ssiz_old_set_obj, CfgDepBase_set_objP2, CfgDepBase_tot_set_obj ); \
  printf ( "   %6d %6d         Seqstr\n", (Seqstr_ssize_fnc_obj - Seqstr_sold_fnc_obj), Seqstr_ffnc_objP3 ); \
  printf ( "   %6d %6d         String\n", (String_ssize_fnc_obj - String_sold_fnc_obj), String_ffnc_objP3 ); \
  printf ( "    ----------------------------------------\n" ); \
  fflush ( stdout ); \
}


/********
BEESRC stuff
********/
int read_frmfunc_str_buf();
void kil_from_btoolkit();
void mod_name_fil_from_btoolkit ();
int eql_frm_from_btoolkit ();
void psh_from_btoolkit ();



/**************************************************
        "GlobalDefs.src"
***************************************************/

#define BT_EDT             1
#define BT_TYP             2
#define BT_GBMI            3
#define BT_DMU             4
#define BT_ANL             5
#define BT_ANM             6
#define BT_POG             7
#define BT_AUP             8
#define BT_INP             9
/*
#define BT_RMK            10
*/
#define BT_NEW            11
#define BT_RMV            12
#define BT_SRC            13
#define BT_RST            14
#define BT_STA            15
/* #define BT_SEL            16 */
#define BT_EDT_ANL_POG    17
#define BT_EDT_ANL        18
#define BT_EDT_ANL_TYP    19
#define BT_EDT_ANL_ANM    20
#define BT_SHW            21
#define BT_EDT_GBM        22
#define BT_OPN            23
#define BT_CMT_CSTR       24
#define BT_CLO            25
#define BT_PRV            26
#define BT_GEN            27
#define BT_OPN_HLP        28
#define BT_OPN_PAL        29
#define BT_CLO_HLP        30
#define BT_CLO_PAL        31
#define BT_TRN            32
#define BT_RMV_LEV        33
#define BT_MAIN           34
/*
#define BT_EDT_ANM_THY    35
*/
#define BT_LIB            36
#define BT_TRL            37
#define BT_LNK            38
#define BT_ENUM           39
#define BT_RMV_SGL        40
#define BT_SRC_SGL        41
#define BT_RUN            42
#define BT_EDT_ENUM       43
#define BT_RNM            44
#define BT_SHELL          45
#define BT_AUP_MAT_RMK    46
#define BT_ENV            47
#define BT_CMT_EDT        48
#define BT_UTILS          49
#define BT_RFRSH          50
/*
#define BT_RMK_NO_CHK     51
*/
#define BT_FRC_RMK        52
#define BT_SAF_SVE        53
/*
#define BT_FIND           54
*/
#define BT_NML            55
#define BT_EDT_NML        56
#define BT_EDT_NML_POG    57
#define BT_EDT_NML_ANM    58
#define BT_CIO            59
#define BT_EDT_CIO        60
#define BT_LIB_FRC        61
#define BT_EDT_NML_ANMT   62
#define BT_SRC_FRC        63
#define BT_CLO_ALL_EDT    64
#define BT_REM_UNU_LIB    65
#define BT_EXP            66
#define BT_TLIB           67
#define BT_DOC            68
#define BT_RSTD           69
#define BT_RSTC           70
#define BT_ENUM_NML       71
#define BT_GBO            72
#define BT_EDT_GBO        73
#define BT_PFP            74
#define BT_PNP            75
#define BT_PUP            76
#define BT_UAP            77
#define BT_TLIB_FRC       78
#define BT_PEXP           79
#define BT_PFP_RMK        80
#define BT_GCBO           81
#define BT_GCBMC          82
#define BT_EDT_GCBO       83
#define BT_EDT_GCBMC      84
#define BT_CRE_SLIB       85
#define BT_GBMI_REM       86
#define BT_LP             87
#define BT_MOTIF_INIT     88
#define BT_MOTIF_QUIT     89
#define BT_RSTP           90
#define BT_SET_FLAGS      91
#define BT_FIND_MOTIF     92

#define BT_MOTIF_ERR_NO_BERR  94
#define BT_CMT_NEW_MCH        95
#define BT_CMT_NEW_REF        96
#define BT_CMT_NEW_REF_ANL    97
#define BT_CMT_NEW_IMP        98

#define BT_CMT_NEW_BASE      100
#define BT_CMT_NEW_ENUM      101
#define BT_CMT_NEW_ENUM_ANL  102
#define BT_CMT_NEW_ITF       103
#define BT_CMT_NEW_ITF_ANL   104
#define BT_CMT_NEW_DOC       105
#define BT_CMT_NEW_DOC_CFG   106
#define BT_CMT_EDT_MOTIF     107
#define BT_CLO_M             108
#define BT_SGL_STA           109
#define BT_CK_PARSE          110
#define BT_RM_ALL_JOBS       111
#define BT_CNT_MINI_REMK     112
#define BT_CMT_OPEN_CSTR     113
#define BT_CMT_LIB_CSTR      114
#define BT_NML_WITH_ENV      115
#define BT_TLIB_WITH_ENV     116
#define BT_LIB_FRC_WITH_ENV  117
#define BT_DMU_WITH_ENV      118
#define BT_DOC_WITH_ENV      119
#define BT_POG_WITH_ENV      120
#define BT_AUP_WITH_ENV      121
#define BT_REF_ANL_WITH_ENV  122
#define BT_IMP_ANL_WITH_ENV  123
#define BT_ITF_ANL_WITH_ENV  124
#define BT_CMT_GEN_CSTR      125
#define BT_CMT_OPEN_GEN_CSTR 126
#define BT_GBO_WITH_ENV      127
#define BT_GBMI_WITH_ENV     128
#define BT_ENUM_ANL_WITH_ENV 129
#define BT_ENUM_WITH_ENV     130
#define BT_CIO_WITH_ENV      131
#define BT_TRL_WITH_IPT_SEES 132
#define BT_SKIP              133
#define BT_LNK_WITH_IPT      134
#define BT_FIND_WITH_ENV     135
#define BT_ANM_WITH_ENV      136
#define BT_PFP_WITH_ENV      137
#define BT_DOC_CFG_WITH_ENV  138
#define BT_DMU_RMK           139
#define BT_CIOM              140
#define BT_CIOM_WITH_ENV     141
#define BT_CIO_CIOM          142
#define BT_ANM_FINI          143
#define BT_NML_PRIORITY      144
#define BT_NOOP              145
#define BT_SUB_LIB_FRC       146
/* #define BT_RST_MAIN          147 */
#define BT_ENUM_DELAY        148
#define BT_DMU_PARSE_ERR     149
#define BT_LST_FLG           150
#define BT_NML_TRL           151
#define BT_BSEL              152
/*
#define BT_EXE_BGD           153
*/
#define BT_NOTPARSE          154
#define BT_CDG               155
#define BT_XTM_BGD           156  /* hard-wired */
#define BT_PASP_FIN          157
#define BT_PASP_SLIB_HTX     158
#define BT_CMT_NEW_MCH_VHDL  159
#define BT_CMT_NEW_REF_VHDL  160
#define BT_CMT_NEW_IMP_VHDL  161
#define BT_CMT_OPEN_VHDL_CSTR 162
#define BT_CMT_VHDL_CSTR     163
#define BT_TRL_VHDL_WITH_IPT_SEES 164
#define BT_CMT_NEW_ENM_VHDL  165
#define BT_ENUM_VHDL_WITH_ENV 166
#define BT_VHDL_LIB_FRC_WITH_ENV 167
#define BT_VHDL_LIB_FRC       168
#define BT_CMT_VHDL_LIB_CSTR  169
#define BT_SUB_VHDL_LIB_FRC   170
#define BT_CMT_NEW_CM_CFG_VHDL 171
#define BT_NEW_DIR            172
#define BT_CK_PARSE_BCOM      173
#define BT_BCOM_NOTPARSE      174
#define BT_VHDL_SLIB_HTX      175
#define BT_CRE_VHDL_SLIB_1    176
#define BT_CRE_VHDL_SLIB_2    177
#define BT_VHDL_SYTX          178
#define BT_PASP_SYTX          179
#define BT_BTL_INI            180
#define BT_BTL_RUN            181
#define BT_INP_ASK_FINI       182
#define BT_BTL_AUP_INI        183
#define BT_BTL_AUP            184
#define BT_BTL_AUP_INI_FIRST  185
#define BT_BTL_FINI           186
#define BT_PFP_BTL            187
#define BT_PFP_RMK_BTL        188
#define BT_PFP_WITH_ENV_BTL   189
#define BT_PNP_BTL            190
#define BT_CRE_HTML_WITH_ENV  191
#define BT_CRE_HTML           192
#define BT_IN_LINED_OPS       193
#define BT_PROB_BINARY        194
/* above also appears in BSession.c */
#define BT_CHK_FOR_OPS        195
#define BT_QUERY_LNK          196
#define BT_ANM_EXE_STEP_WITH_ENV 197
#define BT_ANM_EXE_AUTO_WITH_ENV 198
#define BT_ANM_EXE_STEP       199
#define BT_ANM_EXE_AUTO       200
#define BT_ANM_EXE_STEP_FINI  201
#define BT_ANM_EXE_AUTO_FINI  202
#define BT_ANM_EMPTY_SCRIPT   203
#define BT_MOTIF_PANIC_QUIT   204
#define BT_BTL_RLD_REQ        205
#define BT_BTL_RLD_FINI       206
#define BT_PRINT_IN_LINED_OP  207
#define BT_PRINT_EXTERN       208
#define BT_CRE_PASP_SLIB      209

/**************************************************
        global 
***************************************************/
#ifdef BTOOLKIT_FLAG

extern size_t editorsCount;
extern char* editors[];

extern textWidgetXeditor* constructEditors[];
extern textWidgetXeditor* proofMethodEditors[];


extern size_t browsersCount;
extern char* browsers[];

extern textWidgetXbrowser* htmlBrowsers[];

#endif

/**************************************************
        global definitions
***************************************************/

#define MAX_ANM_MULTI_INPUT_FLD 250

#define Anm_Multi_Input_fld_is_num 1
#define Anm_Multi_Input_fld_is_str 2
#define Anm_Multi_Input_fld_is_chr 3
#define Anm_Multi_Input_fld_is_bts 4
#define Anm_Multi_Input_fld_is_enm 5
#define Anm_Multi_Input_fld_unknwn 6

#define MAX_RADIO_BUT     15
#define MAX_RADIO_BUT_STR 75

extern char radio_labels [] [ MAX_RADIO_BUT_STR ];

#define CFG_DIR            1
#define POB_DIR            2


#define OK_BUTTON          1
#define CANCEL_BUTTON      2
#define HELP_BUTTON        3
#define FILTER_BUTTON      4
#define ALL_BUTTON         5
#define NONE_BUTTON        6


#define BT_QUIT_M              999000
  /* exit! */


#define BT_MINI_RMK_M          999007
  /* LoadBcjm & Popup_MiniRemake */

/*
efine BT_ANM_THY_CLO_M       999008
  /? Popup_CloseAnimThyFile ?/
*/

/* #define BT_ANM_INI_STATE_M     999009 */
  /* Popup_IniAnim */

/*
#define BT_ANM_MINI_RMK_EDT_THY_M      999010
  /? Popup_AnimMiniRemake_EditThyFile ?/
/? Mini-remake/Edit theory file ?/
*/

#define BT_CMT_NOT_PARSE_M    999012
  /* Popup_CmtNotParse */

#define BT_PROMPT_CFM_M       999013
  /* Popup_ConfirmDialog */



#define BT_GET_STRING_M       999015
  /* Popup_PromptDialog */

#define BT_GET_LIST_M         999016
  /* Popup_Sel_Dialog */

#define BT_GET_ONE_M          999017
  /* Popup_SelOne_Dialog */

#define BT_EDT_PROCD_M        999018
  /* Popup_Edt_Proceed */

#define BT_ERR_M              999019
  /* Error_From_B */




#define BT_CURR_ENV_M         999024

#define BT_TEXT_M             999025
  /* ProcessAndDisplayCurrWinText () */

#define BT_RMV_EDT_M          999026
  /* Popup_RemoveEditedFile */

#define BT_RECT_FAULT_M       999027
  /* Popup_Err */

#define BT_GET_L_ONE_M        999028
  /* Popup_SelLargeOne_Dialog */

#define BT_POB_RHL_M          999029
  /* Ipr */

#define BT_POB_RH__M          999030
  /* Ipr */

#define BT_POB_R_L_M          999031
  /* Ipr */

#define BT_POB_R___M          999032
  /* Ipr */

#define BT_LEM_RHR_M          999033
  /* Ipr */

#define BT_LEM_R_R_M          999034
  /* Ipr */

#define BT_LEM__HR_M          999035
  /* Ipr */

#define BT_LEM___R_M          999036
  /* Ipr */



#define BT_ANM_PRCD_M         999039
  /* Animate () */

#define BT_ANM_DISP_OP_M      999040
  /* Animate () */

#define BT_ANM_GET_OP_M       999041
  /* Animate_Ops () */


#define BT_LEM____RLD_FAIL_M  999043
  /* Ipr */



#define BT_GET_CHOICE_M       999046
  /* Popup_SelChoice_Dialog () */

#define BT_PARSE_M            999047

#define BT_REC_LISTS_M        999048
  /* LoadBSelRecLists */

#define BT_CIO_RMK_M          999049

#define BT_TRL_M              999050

#define BT_LNK_M              999051

#define BT_PFP_M              999052

#define BT_CRE_SLIB_M         999053
  /* Popup_creSLIB */

#define BT_CRE_SLIB_FINI_M    999054
  /* Popup_creSLIB_FINI */

#define BT_DMU_M              999055

#define BT_INTERIM_COMP_JOBS_M 999056
  /* Interim_Load_Completed_Jobs */

#define BT_CRE_SLIB_INI_M      999057
  /* Popup_creSLIB_INI */

#define BT_INTERRUPT_M         999058
  /* interrupt from bplatform! */

#define BT_ANM_UTILS_M         999059

#define BT_MAIN_ENV_M          999060

/*
#define BT_ANM_MINI_RMK_ONLY_THY_M  999061
  /? Popup_AnimMiniRemakeThyOnly ?/
     /? Edit theory file ?/
*/

/*
#define BT_EXPORT_TLIB_DONE    999062
  /? construct successfullt exported to TLIB ?/
*/

#define BT_DMU_PRASE_ERROR_M   999063
  /* annotation error */

#define BT_INI_M               999064
  /* pwd parse info from Toolkit1 */

#define BT_ENV_M               999065
/* load_env request */

/*
#define BT_EXE_BGD_M           999066
/! return from EXE_BGD !/
*/

#define BT_CANT_DISCH_GOAL_M   999067

#define BT_XTM_BGD_M           999068
/* return from EXE_XTM */

#define BT_DSP_FILE_M          999069
/* display file */

#define BT_XTERM_REQD_M        999070
/* throw up an XTerm */

#define BT_PMD_INCL_M          999071
/* provide Provers Inclusion PMD string */

#define BT_POSTFIX_M           999072
/* _ to ; */

#define BT_BCATL_M             999073
/* performs bcatl - removes .| and " */

#define BT_TEXT_FROM_BCOM_M    999074
  /* ProcessAndDisplayCurrWinTextBcom () */

#define BT_ADD_UND_M           999075
/* _ appended */

#define BT_SPLIT_AT_FIRST_UND_M 999076

#define BT_NEW_DIR_M           999077

#define BT_BCOM_PARSE_M        999078

#define BT_CRE_VHDL_SLIB_1_M   999079

#define BT_CRE_VHDL_SLIB_2_M   999080

#define BT_BITSTR2SET_M        999081

#define BT_SPLIT_AT_SECOND_UND_M 999082

#define BT_BTL_M               999083

#define BT_INP_ASK_FINI_M      999084

#define BT_BTL_AUP_M           999085

#define BT_PFP_BTL_M           999086

#define BT_PNP_BTL_M           999087

#define BT_IPR_HYP_M           999088

#define BT_IPR_THY_M           999089

#define BT_IPR_RUL_M           999090

#define BT_IPR_RUL_RANGE_M     999091




#define BT_ANM_PRCD_FALSE_M    999094
  /* Animate () */

#define BT_EDT_ANM_THY_M       999095

#define BT_MINOR_ERR_M         999096


#define BT_FILE_PARSE_NEW_M    999098

#define BT_CHK_MCH_NAME_PARSES_M 999099

#define BT_CRE_HTML_RETURN_M   999100

#define BT_LEM_RHR_NOT_PARSE_M 999101

#define BT_IN_LINED_OPS_M      999102

/* #define BT_C_PRE_PROCESS_M     999103 */

#define BT_CHK_FOR_OPS_M       999104

#define BT_ANM_MULTI_INP_M     999105

#define BT_ANM_DSP_1_M         999106

#define BT_ANM_DSP_2_M         999107

#define BT_ANM_DSP_3_M         999108

#define BT_MULTI_ERR_STR_M     999109

#define BT_ANM_OK_CONT_M       999110

#define BT_IPT_CLOSURE_M       999111

#define BT_IPT_DSGN_CHK_M      999112

#define BT_DUP_IPT_CHK_M       999113

#define BT_QUERY_LNK_M         999114

#define BT_PROB_BINARY_M       999115

#define BT_ANM_GET_EXE_STEP_M  999116

#define BT_ANM_EXE_STEP_FINI_M 999117

#define BT_ANM_EXE_AUTO_FINI_M 999118

#define BT_ANM_EMPTY_SCRIPT_M  999119

#define BT_PASP_APP_UNDERSC_M  999120

#define BT_PASP_MULTI_INP_M    999121

#define BT_INFO_DONT_WAIT_M    999122

#define BT_BTL_RLD_M           999123

#define BT_PRINT_IN_LINED_OP_M 999124

#define BT_PRINT_EXTERN_M      999125



extern int primary_string_len;




#define sel_arr_MAX       MAX_NUM_CONSTRUCTS + 2
#define sel_str_len_MAX   5001

#define MAIN_HELP              1
#define PALETTE_HELP           2
#define DIALOG_HELP            3
#define DIFF_HELP              4


#define off               0
#define run_hyp_no_lem    1
#define run_hyp_lem       2
#define run_no_hyp_no_lem 3
#define run_no_hyp_lem    4

#define run_hyp_rld       1
#define run_no_hyp_rld    2


#define allowable_dim_x 12
#define allowable_dim_y 25

/**************************************************
          global data
***************************************************/


#ifdef BTOOLKIT_FLAG

extern int SourceControl_Initialised;

extern int CfgDepBase_is_Restored;

extern struct SourceControlStruct * SC_0;

extern Widget SC_dialog;
extern Widget SC_setup_dialog;

#define sc_state_w 0
#define sc_state_r 1

extern int max_fwd_ctr_auto_prf;


#define Sensitized    FrameSensitized == True
#define DeSensitized  FrameSensitized == False

extern int total_edits;

extern XtIntervalId SRC_watch_id;
#define long_SRC_watch_cycle   3000
#define short_SRC_watch_cycle  2000
extern long unsigned SRC_watch_cycle;
#endif

extern int OR_sym;

extern char multi_err_str [];

extern char post_process_xterm_text [];

extern time_t start_t, end_t, start_c, end_c;

extern int top_level_dep_cstr;

extern int report_parse_errors;

#ifdef BTOOLKIT_FLAG

extern Dimension wm_width, wm_height;

extern Widget display_main_menu_dialog, display_a_theory_dialog,
              display_a_rule_dialog,    prove_rule_dialog;

extern Position  anm_ops_x, anm_ops_y;
extern Dimension anm_ops_h, anm_ops_w;

extern Position last_browse_x, last_browse_y;

extern int display_unproved_btl_flag, display_unproved_ipr_flag;

#endif

extern int upgrade3T04_flag;
#define upgrade3T04_reset        1
#define upgrade3T04_reset_remake 2


extern int anm_invariant_flag;

extern int tmp_from_btoolkit;

#define MAX_FIFO_WRITE_BUF   250000
extern char fifo_write_buf [];

#if ( defined  ( BTOOLKIT_FLAG ) ||  defined  ( BTOOLM_FLAG ) )

extern Widget global_widget, global_widget1;

extern char nodename [];
extern char platform [];
extern int platform_ident;
#define platform_ident_SunOS      1
#define platform_ident_Solaris    2
#define platform_ident_OSF1       3
#define platform_ident_Linux      4
#define platform_ident_AIX        5
#define platform_ident_HP_UX      6
extern const char *platform_types[];

extern int auto_reset_and_remake;
extern int auto_timer;
extern int is_debug;
extern int auto_reset;


extern int up_and_running;
extern int interrupt_option;
extern int file_parses;
extern int xterm_is_up;
extern int terminal_option;
extern int obj_to_display;
extern int row_to_display;
extern int current_pmd_ps;
extern int global_pmd_ps;
extern int anm_exe_ps;
extern int sc_ps;
extern int btl_rule;
extern char xterm_title [];

#endif

#ifdef BTOOLKIT_FLAG
#define MAX_buf 75000
#else
#define MAX_buf 5000
#endif /* BTOOLKIT_FLAG */
extern char buf [];

#define MaxProofSteps 1000
extern int CopyProofTreeLookUp [] [ MaxProofSteps ];
extern int CopyProofTreeLookUpTot;

extern int run_button_pressed;
extern int node_to_be_displayed_as_last;
extern int node_to_undo_to;
extern int last_goal_displayed_frm;
extern int backtrack_attempted;
extern int backtrack_succeeded;
extern int another_backtrack_required;

#define proof_ini_horiz       5
#define proof_ini_vert        5
#define proof_header_height  35
extern int half_proof_goal_height;
extern int proof_horiz_offset;
extern int proof_vert_offset;
extern int proof_extra_lines_offset;
extern int goal_rule_vert_diff;

extern char SwitchBTPXDED0 [];
extern char SwitchBTPXDED1 [];
extern char SwitchBTPXDED2 [];

extern int first_switch_thy, last_switch_thy;
extern int first_switchBTP_thy, last_switchBTP_thy;
extern int first_btl_thy_to_display, last_btl_thy_to_display;
extern int btl_users_thy, fwd_btl_users_thy;
extern int users_thy, fwd_users_thy;
extern int last_btl_fwd_thy, last_rewrite_thy, last_lib_thy;
extern int max_btl_thy_len;
extern int orig_btl_proved;
#define orig_btl_proved_arr_MAX 1000
extern int orig_btl_proved_arr [ orig_btl_proved_arr_MAX + 1 ];
extern int orig_btl_pmd_rule;
#define orig_btl_pmd_rule_arr_MAX 1000
extern int orig_btl_pmd_rule_arr [];
#define btl_pob_thy_MAX 100
extern int btl_fwd_thy_depth [];
extern int forward_reasoning_depth;


extern int unwanted_seq;
extern int btool_proofs_committed;

extern int btl_fwd_tac_depth;
extern int feql_val;

/***
     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
     THESE MUST AGREE WITH REASONING_DEPTH_n_Tac in Globals.src
     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
***/

/*
#define REASONING_DEPTH_0_Tac \
  "(ExpandHypX; PropertiesX; FwdUsersTheory; FwdBToolUsersTheory; FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB)~"

#define REASONING_DEPTH_1_Tac \
  "(ExpandHypX; PropertiesX; FwdUsersTheory; FwdBToolUsersTheory; FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X)~"

#define REASONING_DEPTH_2_Tac \
  "(ExpandHypX; PropertiesX; FwdUsersTheory; FwdBToolUsersTheory; FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X; FwdContra2X; FwdPredicate2X; FwdNotEqual2X; FwdEqual2X; FwdFunction2X; FwdRelation2X; FwdSequence2X; FwdInNat2X; FwdInSet2X; FwdInclusion2X; FwdNotInSet2X; FwdLessThanOrEqual2X; FwdLessThan2X)~"

#define REASONING_DEPTH_0_FEQL_Tac \
  "(ExpandHypX; PropertiesX; FwdUsersTheory; FwdBToolUsersTheory; FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FEQL)~"

#define REASONING_DEPTH_1_FEQL_Tac \
  "(ExpandHypX; PropertiesX; FwdUsersTheory; FwdBToolUsersTheory; FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X; FEQL)~"

#define REASONING_DEPTH_2_FEQL_Tac \
  "(ExpandHypX; PropertiesX; FwdUsersTheory; FwdBToolUsersTheory; FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X; FwdContra2X; FwdPredicate2X; FwdNotEqual2X; FwdEqual2X; FwdFunction2X; FwdRelation2X; FwdSequence2X; FwdInNat2X; FwdInSet2X; FwdInclusion2X; FwdNotInSet2X; FwdLessThanOrEqual2X; FwdLessThan2X; FEQL)~"
*/


#define REASONING_DEPTH_0_Tac \
  "FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB"

#define REASONING_DEPTH_1_Tac \
  "FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X"

#define REASONING_DEPTH_2_Tac \
  "FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X; FwdContra2X; FwdPredicate2X; FwdNotEqual2X; FwdEqual2X; FwdFunction2X; FwdRelation2X; FwdSequence2X; FwdInNat2X; FwdInSet2X; FwdInclusion2X; FwdNotInSet2X; FwdLessThanOrEqual2X; FwdLessThan2X"

#define REASONING_DEPTH_0_FEQL_Tac \
  "FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FEQL"

#define REASONING_DEPTH_1_FEQL_Tac \
  "FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X; FEQL"

#define REASONING_DEPTH_2_FEQL_Tac \
  "FwdPredicate0X; FwdEqual0X; FwdContra0X; ARI; SUB; FwdContra1X; FwdPredicate1X; FwdNotEqual1X; FwdEqual1X; FwdFunction1X; FwdRelation1X; FwdSequence1X; FwdInNat1X; FwdInSet1X; FwdInclusion1X; FwdNotInSet1X; FwdLessThanOrEqual1X; FwdLessThan1X; FwdContra2X; FwdPredicate2X; FwdNotEqual2X; FwdEqual2X; FwdFunction2X; FwdRelation2X; FwdSequence2X; FwdInNat2X; FwdInSet2X; FwdInclusion2X; FwdNotInSet2X; FwdLessThanOrEqual2X; FwdLessThan2X; FEQL"



extern char *btl_fwd_tac[];

extern pid_t pid;

extern int cs_nn, cs_rr;
extern char serv_addr [];
extern FILE * Bfile;
extern int port;

#ifdef COUNT_VERSION

extern int cs_nn, cs_rr;
extern char serv_addr [];
extern int port;
extern int COUNT_25_flag;
extern int COUNT_25_msg;

#endif /* COUNT_VERSION */

#ifdef WWW_VERSION

extern int cs_nn, cs_rr;
extern char serv_addr [];
extern int port;
extern int COUNT_25_flag;
extern int COUNT_25_msg;

#define max_num_usr_constr     50
extern int num_usr_constructs;
extern int constr_anl_len [];
extern int constr_pob_len [];
extern char constr_nme [] [ 50 ];

#endif /* WWW_VERSION */

#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Widget temp_widget, temp_dialog;
extern int temp_level;

#endif


/***********
current object curr_obj
***********/
extern int curr_obj;
extern int anm_thy_obj;

/***********
multi-click interval
***********/
extern int mc_interval;


/***********
!!!!!!!!!!
***********/
extern int option;
extern int not_parse_option;
extern int commit_aborted;

extern int translating_pre_MInterface;

#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Widget cd_dialog;

#endif

extern int ITF_Intro_basic_io;
extern int ITF_Intro_basic_io_obj;
extern int ITF_Intro_basic_io_ps;

extern int close_all_count;
extern int close_all_quit_count;
extern int commit_all_count;
extern int commit_all_remake_count;
extern int remove_count;

extern int dont_destroy_display;

extern int init_option;

extern int bell_option;


extern int widget1_built;

#define commit_type_maths         0
#define commit_type_annot         1
#define commit_type_assumed_annot 2
#define commit_type_ws            3


extern int Popup_Sel_flag;
#define commit_all_edit_selection         4
#define interprover_selection             5
/*
#define open_selection                    7
*/
#define introduce_SRC_selection           8
#define introduce_SLIB_selection          9
#define introduce_TLIB_selection         10
#define remove_selection                 11
#define ref_anl_selection                12
#define imp_anl_selection                13
#define itf_anl_selection                14
#define enm_anl_selection                15
#define ppf_selection                    16
#define creSLIB_selection                17
#define creTLIB_selection                18
#define doc_anl_selection                19
#define commit_all_remake_edit_selection 20
#define browse_design_selection_top_win  21
#define browse_spec_selection_top_win    22
#define browse_design_selection          23
#define browse_spec_selection            24
#define rename_selection                 25
#define close_all_edit_selection         26
#define remake_jobs_selection            27
#define remake_constructs_selection      28
#define browse_selection                 29
#define rsl_selection                    30
#define browse_pmd_selection             31
#define introduce_VHDL_SLIB_selection    32
#define introduce_cfg_CM_selection       33
#define rem_VHDLSLIB_selection           34
#define cre_VHDLSLIB_selection_no_code   35
#define cre_VHDLSLIB_selection_code      36
#define remSLIB_selection                37
#define remTLIB_selection                38
#define btool_pmd_rule_selection         39
#define ipr_thy_range_selection          40
#define update_from_SRC_sel              41
#define animator_utilities_sel           42
#define save_anm_output_sel              43
#define save_anm_animate_sel             44
#define anm_clean_files_sel              45
#define anm_exe_step                     46
#define anm_exe_auto                     47
#define edit_anm_exe_sel                 48
#define edit_anm_exe_new_from_old_sel    49
#define browse_out_selection             50
#define edit_anm_thy_sel                 51
#define source_control_sel               52
#define save_vhdl_slib_selection         53
#define load_vhdl_slib_selection         54
#define analyse_generate_jobs_selection  55
#define checkout_VHDLSLIB_selection      56
#define crePASPSLIB_selection            57


extern int Popup_Selection_Sel_flag;
#define cd_Selection_sel         1


extern int Commit_All_type;
#define Commit_All_not_remake       0
#define Commit_All_remake_all       1
#define Commit_All_remake_construct 2



extern const char *EnvString[];
#define EnvString_tot 5

#define env_str_anm_num   EnvString_tot
#define env_str_ipr_num   EnvString_tot + 1
#define env_str_btl_num   EnvString_tot + 2


#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Widget env_lab [];

#endif

#define main_env        0
#define provers_env     1
#define generators_env  2
#define translators_env 3
#define documents_env   4
#define vhdl_env        5
#define ipr_pob_env     6
#define ipr_lem_env     7
#define btl_env         8
#define anm_env         9

extern int curr_env;


/***********
client data
***********/

#define c_arr_MAX  2500
extern int c_arr [];

extern int global_file_diff_but;


extern const char *lab_types[];

extern const char *extens[];

extern const char *DIRS[];
#define dir_len         11


#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern TopBarMenuItem Overview_menu [];


extern const char *PaletteN_pal[];

extern TopBarMenuItem PaletteN_menu [];

extern TopBarMenuItem Browse_menu [];

extern TopBarMenuItem Remake_menu [];


extern TopBarMenuItem IntroduceNew_menu [];

extern TopBarMenuItem Introduce_menu [];

extern TopBarMenuItem Utilities_menu [];

extern TopBarMenuItem Optional_Utilities_menu [];

extern TopBarMenuItem Construct_menu [];

extern TopBarMenuItem Interrupt_menu [];

#endif  /* #if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */


/***
interrupts
***/
extern struct sigaction act1, act2, act3;

extern int anm_thy_ps;

#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern XmStringCharSet charset;

extern XtAppContext app;

extern Widget top_level,          main_form,            top_bar;

extern Widget main_form_pane;
#define     top_frame_form_min        /* 245 */ 165
#define  bottom_frame_form_min         75
extern Dimension bottom_frame_form_height;

extern Widget top_frame_form,    bottom_frame_form,
              B_button,          B_label,
              bot_display_frame,
              ipr_text_dialog,   anm_text_dialog,
              ipr_text_form,     anm_text_form,
              main_text,         ipr_text,             anm_text,        curr_text,
              ipr_hyp_dialog,    ipr_hyp_dialog_text,  ipr_hyp_sch_dialog [],
              constructs_frame,  constructs_form,
              main_row_scroll,     provers_row_scroll,  generators_row_scroll,
              translators_row_scroll, documents_row_scroll,
              main_row_form,     provers_row_form,  generators_row_form,
              translators_row_form, documents_row_form,
              /* */ information_label,
              constructs_scroll, constructs_rc, ipr_label,
              ipr_sel_rc,
                                 sub_frame1,           sub_text1,
                                 sub_frame2,           sub_text2,
                                 sub_frame3,           sub_text3,
                                 sub_dummy,
              InterruptPullDown,
              OptionsPullDown,   InterruptPullDown,    BrowsePullDown,
              UtilsPullDown,     RemakePullDown,       ConstructPullDown,
              IntroducePullDown, HelpPullDown,
              Utils_Options_PullDown, Utils_Options_PullDown_PushButtons [];

extern Widget TRBut [];

#endif

#define MAX_str_buf 74995
extern char str_buf [];
extern int str_buf_i;
extern int tmp_btool_ipr_thy;

extern const char *proved_label[];

extern const char *proved_class[];

extern char prev_thy [];
extern int  prev_rule;

extern int ipr_hyp_dialog_up, ipr_hyp_sch_dialog_up [];

extern int Ipr_Prf_Level_dialog_isdplayed;
extern int Ipr_Prf_Option;
extern char hyp_search_string [];

#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Widget command_bar_rc,
              help_main_lab,
              main_lab_form,  provers_lab_form, 
              generators_lab_form,  translators_lab_form,
              documents_lab_form, cmt_documents_lab, dmu_lab, shw_lab,
              prt_lab, doc_rst_lab,
              sts_lab, rst_lab, edt_documents_lab,
              cmt_main_lab, cmt_provers_lab, cmt_generators_lab, cmt_translators_lab,
              edt_main_lab, edt_provers_lab, edt_generators_lab, edt_translators_lab,
              anl_lab,  pog_lab,  anm_lab, pmd_lab,
              prv_lab,
              rsl_lab,
              ppf_lab, sup_lab,  lvl_lab, pob_lab, tot_lab,
              gbo_lab,  gbm_lab,  enm_lab, itf_lab, gen_rst_lab,
              trl_lab,  lnk_lab, exe_lab, trl_rst_lab;

extern Widget ipr_ops_dialog;

extern Widget anm_ops_dialog;

extern int anm_ops_option;

extern Widget htx_curr_form, htx_curr_form_lab,
              htx_B_logo,
              htx_label, htx_prev_but, htx_done_but, htx_help_but,
              htx_spec_but, htx_design_but, htx_save_but, 
              htx_dialog, htx_frame, htx_form, htx_scroll, htx_scroll_form,
              htx_down_arw, htx_up_arw,
              curr_htx, curr_htx_frame, curr_htx_inner_frame, curr_htx_but,
              curr_htx_rc, curr_htx_form, curr_htx_dialog,
              ipts_htx_rc, sees_htx_rc;

extern int htx_dialog_is_up;

extern Pixmap B_framed_pixmap_gray94, B_framed_pixmap_inverse, B_topbar_pixmap, red_pixmap, green_pixmap, blue_pixmap,
              inapplicable_pixmap,tab_pixmap, tabgrey_pixmap, B_downarrow_pixmap,
              htx_pixmap_right, htx_pixmap_left, htx_pixmap_left_big;

extern Dimension HtxDialog_x;
extern Dimension HtxDialog_y;

/* cells & blocks */
#define MAX_Browser       40
/* rows */
#define MAX_Design_Spec   40

#define MAX_a2c_htx   MAX_Browser
#define MAX_sees_htx  50
#define MAX_ipts_htx  50

extern Widget curr_htx_a2c_frame [], curr_htx_a2c [];
extern int  curr_htx_a2c_tot;
extern int  curr_htx_a2c_open_idx;

extern Widget sees_htx_rc_sub [],
              sees_htx_a2c_frame [] [ MAX_a2c_htx ],
              sees_htx_a2c [] [ MAX_a2c_htx ];

extern int    sees_htx_a2c_Total, sees_htx_a2c_tot [];

extern Widget ipts_htx_rc_sub [],
              ipts_htx_a2c_frame [] [ MAX_a2c_htx ],
              ipts_htx_a2c [] [ MAX_a2c_htx ];

extern Widget left_big_arr_htx [] [ MAX_a2c_htx ];

extern int    ipts_htx_a2c_Total, ipts_htx_a2c_tot [];

#define MAX_htx_curr_obj 50
extern int htx_curr_obj [];
extern int htx_curr_obj_ptr;

extern int htx_offset;
extern int tot_htx_constructs, tot_htx_blocks, tot_htx_rows;

#define MAX_D_row     MAX_Design_Spec
#define MAX_D_block   MAX_Browser
#define MAX_D_cell    MAX_Browser

extern int D_arr        [] [ MAX_D_block ] [ MAX_D_cell ];
extern int D_block_tot  [] [ MAX_D_block ];
extern int D_node       [] [ MAX_D_block ];
extern int D_frame      [] [ MAX_D_block ];
extern int D_sticky     [] [ MAX_D_block ];

extern int D_cell;
extern int D_block [];

extern int D_arr_load_err;

extern int initial_reattachment;


/***
used in display
***/
extern int HtmlMasterFileChanged;
extern int DisplayChanged;

extern Display *display;

extern Screen * proof_screen;

#endif /* #if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */

extern char * primary_string;
extern char * secondary_string;
extern char * additional_string;

extern char SRCName    [];
extern char CFGName    [];

extern char   sel_str_arr [] [ sel_str_len_MAX ];
extern char   rmk_str_arr [] [ sel_str_len_MAX ];
extern int    sel_obj_arr [];
extern short  sel_arr_tog [];

#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Widget sel_arr_but [];

#endif

extern int    sel_arr_tot;


extern int hid_LIB_flag;
extern int hid_gen_flag;


/***
Options
***/
#define hid_LIB_Option_num              1 
#define hid_gen_Option_num              2
#define Remake_pog_Option_num           3
#define Remake_apr_Option_num           4
#define Remake_ppf_Option_num           5
#define Remake_dmu_Option_num           6
#define Remake_trl_Option_num           7 
#define Remake_lnk_Option_num           8
#define Remake_itf_Option_num           9
#define Preserve_Editor_Option_num     10 
#define Interface_Option_num           11
#define Interface_Option_Motif    0
#define Interface_Option_NonMotif 1
#define Ipr_Prf_Level_num            12
#define DMU_Labels_Option_num          13 
#define DMU_ClIndex_Option_num         14 
#define DMU_CoIndex_Option_num         15 
#define DMU_GIndex_Option_num          16 
#define Prog_Language_Option_num       17
#define Prog_Language_Option_ANSI_C 0
#define Prog_Language_Option_C      1
#define Prog_Language_Option_PLX    2
#define Prog_Language_Option_CICS   3
#define Prog_Language_Option_PASP   4
#define DMU_Language_Option_num        18 
/* leave the above for now */
#define DMU_Language_Option_LaTeX2e 0
#define DMU_Language_Option_LaTeX   1
#define DMU_Language_Option_GML     2
#define Point_Size_Option_num          19
#define DMU_eps_Option_num             20
/* leave the above for now */

#define Option_21                      21
#define Option_22                      22
#define Option_23                      23
#define Option_24                      24
#define Option_25                      25
#define Option_25_Max         25
#define Option_2324_Max       750
#define check_iterations        2

#define Base_Seqstr_tok_num            26
#define POG_Option_num                 27
#define Hypertext_text_num             28 
#define Bell_Option_num                29
#define Bell_Option_on        1
#define Bell_Option_off       0
#define Teamlib_Option_num             30
#define Provers_max_fwd_Option_num     31
#define VHDL_SLIB__Option_num          32

#define get_dep_cstr_num               75



/*** ADD ADD TO THIS LIST - DON'T INSERT */

#define editor_str_num                  1
#define pmd_editor_str_num              2
#define htx_viewer_str_num              3
#define cc_compiler_str_num             4
#define cc_link_lib_str_num             5
#define cc_Xlink_lib_str_num            6
#define dvi_screen_str_num              7
#define dvi_print_str_num               8
/* #define teamlib_str_num                 9 */
#define provers_str_num                10
#define shell_str_num                  11
#define optional_utility1_str_num      12
#define optional_utility2_str_num      13
#define optional_utility3_str_num      14
#define optional_utility4_str_num      15
#define optional_utility5_str_num      16
#define source_control_str_num         17
#define latex_declaration_str_num      18
#define latex_exec_name_str_num        19
#define vhdl_ulib_str_num              20

/*** ADD ADD TO THIS LIST - DON'T INSERT */




extern const char *options[];

/* moved to BMotif_version.h
extern char *cpyrt[];
*/

extern char BKIT_path [];
extern char cur_dir [];

#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Pixel gray94, gray64, gray39, red, blue, black,
             user_lab_col_f,      user_lab_col_b,
             lib_lab_col_f,       lib_lab_col_b,
             gen_lab_col_f,       gen_lab_col_b,
             user_vhdl_lab_col_f, user_vhdl_lab_col_b,
             gen_vhdl_lab_col_f,  gen_vhdl_lab_col_b,
             lib_vhdl_lab_col_f,  lib_vhdl_lab_col_b,
             inapplicable_lab_col,      main_text_col,
             option_set_col,      option_not_set_col,
             Prompt_bck_col,      Prompt_top_col,  Prompt_bot_col,
             Browse_bck_col,      Browse_top_col,  Browse_bot_col,  
             Prompt_text_bck_col, Browse_text_bck_col,
             Prompt_but_lab_col,  Browse_but_lab_col,
             Prompt_bck_col,
             Env_lab_active,      Env_lab_passive;

/* extern Pixel but_xpm; */

extern int rewrite_prompt;


/**************************************************
               interrupts etc
***************************************************/

#define from_InvokeB                      0
#define from_CheckFileParses              1
#define from_new_dir                      11

#define from_Popup_Err_CB            12
#define from_Popup_Capacity_Err_CB   13

extern int go_flag;
extern int ReturnFromB_option;

extern void   interrupt_SIGUSR1 ();
extern void   interrupt_SIGUSR2 ();
extern void   interrupt_CRASH ();
extern XtIntervalId InvokeBLogoFlashTimer_id;
extern int          InvokeBLogoFlashTimer_flag;
/* #define InvokeBLogoFlashTimer_delay_ini ( long unsigned ) 5000 */
#define InvokeBLogoFlashTimer_delay_ini ( long unsigned ) 1000
#define InvokeBLogoFlashTimer_delay_on  ( long unsigned ) 1500
#define InvokeBLogoFlashTimer_delay_off ( long unsigned )  750
extern XtTimerCallbackProc Process_interrupt_SIGUSR1 ();
extern XtTimerCallbackProc Process_interrupt_SIGUSR2 ();
extern XtTimerCallbackProc Process_interrupt_CRASH ();
extern XtTimerCallbackProc Process_SetInvokeBLogoFlashTimer ();
extern void   process_XTerm_IfReq ();
extern void   ReturnFromB ();
extern void   DisplayXTermText ();
extern void   KillXTerm ();
extern void   CreateXTerm ();
extern void   file_error ();
extern int    Is_Trl ();
extern int    Is_LibOrEnm ();
extern int    HasImp ();
extern void   Retrieve_String ();

/**************************************************
     internal procedures
***************************************************/

extern char * GetName ();
extern char * GetShortName ();
extern void   ProcessInterProverRuleSelection ();
extern void   ProcessInterProverRuleRange ();
extern void   B_info_CB ();
extern void   Popup_SelPMDRules_Dialog ();
extern void   IprReasoningDepth_CB ();
extern void   env_lab_CB ();
extern void   NEW_Dialog_RadioBox_CB ();
extern void   NEW_Dialog_RadioBox_EditedFileExists_CB ();
extern void   GetColours ();
extern int    FormulaParses ();
extern int    FileParses ();
XtCallbackProc Popup_Help_CB ();
extern void   Cre_Anm_Multi_Input_Form ();
extern int    RestoreRecordedProofs ();
extern Widget CreHighlightedButton ();
extern void   btl_proofprint ();
extern void   motif_init ();
extern void   load_toolkit15_po_dot_src ();
extern void   DisplayMainMenu ();
extern void   DisplayMainTopWin ();
extern void   DestroyAllIprHypDialogs ();
extern void   Popup_AnmTextDialog ();
extern void   Popup_IprTextDialog ();
extern void   ProcessAndDestroy_AnmTextDialog ();
extern void   ProcessAndDestroy_IprTextDialog ();
extern void   AutoRemakeFini ();
extern void   Pre_ChangeToNewDirectory ();
extern void   SaveCurrentOptions ();
extern void   SaveCurrentOptions_Proceed ();
extern void   RestoreDefaultOptions ();
extern void   RestoreDefaultOptions_Proceed ();
extern void   SetTitle ();
extern void   display_non_parse_text ();
extern void   Popup_Info ();
extern void   Popup_Capacity_Err ();
extern void   execute ();
extern void   WriteBtlb ();
extern void   WriteBplf ();
extern void   WriteBdmf ();
extern void   WriteBpog ();
extern void   PreRename ();
extern void   Rename ();
extern void   CheckBaseUnderscore ();
extern void   LoadBSelRecLists ();
extern void   Remove_non_doc_gset1 ();
extern void   RemoveCodeFiles ();
extern void   RecompileLibCodeFiles ();
extern void   RemoveSinglePOBFiles ();
extern void   RemoveUnusedLibFiles ();
extern void   RemoveTexFiles ();
extern void   CopySRCCFG ();
extern void   CopyCFGSRC ();
extern void   CheckUnanalyse ();
extern void   CheckUndoc ();
extern void   CheckUngen ();
extern void   Popup_LIBRenamePromptDialog ();
extern void   Popup_Quit ();
extern void   Popup_ResetAll ();
extern void   Popup_ProversMenu ();
extern void   ResetAll_CB ();
extern void   LoadBufObjExe ();
extern void   LoadBcjm ();
#define dont_display_env 0
#define display_env      1
extern void   GetObjFromNameExt ();
extern void   GetPrfObjFromNameExtLevel ();
extern void   GetExtNumFromString ();
extern void   GetNameFromString ();
extern void   GetMchRefImp_MchArr_numFromName ();
extern void   DeCommentFile ();
extern void   PrintNum ();
extern void   CreNumInBuf ();
extern void   CreNumFromBuf ();
extern int    FileDifference ();
extern void   MainWinDisp_status ();
extern void   MainWinDisp_type ();
extern void   MainWinDisp_mri ();
extern void   MainWinDisp_spec_ref_imp_by ();
extern void   MainWinDisp_nat ();
extern void   MainWinDisp_gset ();
extern void   MainWinDispCode_gset ();
extern void   Cat_gset_tcp ();
extern void   ProcessCompletedJobs  ();
extern void   PreOpenConstruct ();
extern void   ModifyGlobalPMDOpenFromBed ();
extern void   ModifyCurrentPMDOpenFromBed ();
extern void   CloseAllOpenFilesNext ();
extern void   CommitAllOpenEditedFilesNext ();
extern void   CommitAll_Remake_OpenEditedFilesNext ();
extern void   RemoveNext ();
extern void   RemoveLevel ();

extern void   CheckAnmThyFileParses ();
extern void   CheckAnmThyFileParses_contd ();
extern void   CheckFileParses ();
extern void   CheckFileParses_contd ();
extern void   CheckFileParses_ContinueLoop ();
extern int    DetermineCommitType ();
extern void   PreCommitMathsEdits ();
extern void   CommitMathsEdits ();
extern void   PreCommitAnnotationEdits ();
extern void   CommitAnnotationEdits ();
extern void   CommitWhitespaceEdits ();
extern void   file_ed_radiobox_contd ();
extern void   ITF_ed_radiobox_contd ();
extern void   mini_remake_radiobox_contd ();

extern int committed;

extern void   ResetConstruct ();
extern void   Load_SRC_CFG_Names ();
extern void   Pre_Itf ();
extern void   Pre_Trl ();
extern void   Pre_Lnk ();

extern void   Pre_ExportTLIB ();
extern void   Sub_Rec_Trl_In_gseq ();
extern void   Rec_Trl_In_gseq ();
extern char * DropFinalDir ();
extern void   LoadWritableDirInto_sel_strs ();
extern void   LoadOpenConstructsInto_sel_strs ();
extern void   LoadOpenEditedConstructsInto_sel_strs ();
extern void   LoadCre_VHDSLIB_ableInto_sel_strs ();
extern void   LoadAnlMchInto_sel_strs ();
extern void   LoadAnlConstructsInto_sel_strs ();
extern void   LoadRefImpAnlIntroducableInto_sel_strs ();

extern void   LoadNonOpsConstructsInto_sel_strs ();
extern void   LoadCreSLIBableInto_sel_strs ();
extern void   LoadITFableMchInto_sel_strs ();
extern void   LoadVHDLSLIBInto_sel_strs ();
extern void   LoadIntroducableInto_sel_strs ();
extern void   LoadRemovableInto_sel_strs ();
extern void   LoadRenamableInto_sel_strs ();
extern void   LoadBrowsableInto_sel_str ();
extern void   ProcessAnalyse ();
extern void   ProcessDocument ();
extern void   RemakeSelections ();


#endif  /* #if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */


/**************************************************
     socket procedures & data
***************************************************/

#define FIFO_FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
extern int fifo_write_ptr, fifo_read_ptr;

extern char fifo_file_2m [];
extern char fifo_file_2b [];

/***/
extern void fifo_read ();
extern void fifo_write ();
#define Read_FIFO  fifo_read
#define Write_FIFO fifo_write
/***/

/***
extern void fifo_read_non_fifo ();
extern void fifo_write_non_fifo ();
#define Read_FIFO  fifo_read_non_fifo
#define Write_FIFO fifo_write_non_fifo
***/

/**************************************************
     i/o procedures
***************************************************/

extern void   main_continue();

extern void   AbortedMsg ();
extern void   AbortedMsgCode ();
extern void   AbortedMsgFile ();
extern void   Save_CfgDepBase ();
extern void   Restore_CfgDepBase ();
extern void   Save_n_CfgDepBase ();
extern void   Restore_n_CfgDepBase ();
extern void   BT_crash_err_exit ();
extern void   BT_err_exit ();
extern void   BT_base_err_exit ();
extern void   BT_system_exit ();


extern void LoadLIBInto_sel_strs ();
extern void LoadFileIntoBuf ();
extern void Sort_sel_strs_from_second ();

extern void   Cre_tcp_env ();
extern void   Cre_fifo_write_buf_cmd_env ();
extern void   Cre_fifo_write_buf_cmd_num ();
#define Cre_fifo_write_buf_cmd_0(n) Cre_fifo_write_buf_cmd_num (n,0)
extern void   InvokeB ();
extern void WriteBplatformSocket ();
extern void ReadBplatformSocket ();
#define without_XTerm 0
#define with_XTerm    1
extern void   GetBsel ();
extern void   GetBsel_NLallowed ();



/**************************************************
     Utilities
***************************************************/

extern void remove_my_zombie_pid ();
extern void remove_all_zombie_pid ();
extern int ClientSocketNUM ();

#ifdef COUNT_VERSION

/*extern void ClientSocketNUM ();*/
extern void COUNTCheckIsBad ();

#endif /* COUNT_VERSION */

#ifdef WWW_VERSION

/*extern void ClientSocketNUM ();*/
extern void COUNTCheckIsBad ();
extern void WWWConstructsCycleCheck ();

#endif /* WWW_VERSION */

extern void ResetWaitingOption ();
extern int waiting_option;
extern int second_visit;
extern int SelOne_flagged;


#if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

extern Pixel  GetPixel ();
extern void   AddHelpButton ();

extern Widget AddPOBLabel ();
extern Widget DisplayConstructPOB ();

extern void DoesntWorkYet ();

extern void RemoveTopCurrText ();
extern void DisplayCurrWinText ();
extern XmTextPosition main_text_posn, ipr_text_posn, anm_text_posn, curr_text_posn;

#define remake_all_constructs 0
#define remake_construct      1
extern void Pre_Remake ();
#define dry_run      0
#define not_dry_run  1
extern void Remake ();
extern void Remake_Proceed ();
extern void CommitAll_CB ();
extern void CommitAll_Remake_CB ();
extern void CloseAll_CB ();
extern void CloseAllPriorCD ();
extern void ChangeDirectoryNewDir ();
extern void ChangeDirectoryExistingDir ();
extern void Hypertext_CB ();

extern void IPRButton_CB ();

extern XtCallbackProc CentreWidgetRelMainWin_CB  ();
extern XtCallbackProc PositionWidgetRightMainWin_CB  ();
extern XtCallbackProc PositionWidgetRelMainWin_CB  ();
extern XtCallbackProc IprPositionSearchedHyp_CB ();

extern void Desensitize ();
extern void DesLSTBut();

/**********************************************
        TopBar call backs
**********************************************/

XtCallbackProc TopBar_Introduce_CB ();
XtCallbackProc TopBar_Browse_CB ();
extern void TopBar_Palette_CB ();
XtCallbackProc TopBar_Options_CB ();
XtCallbackProc TopBar_Help_CB ();
extern Widget Cre_Help_Pulldown ();
XtCallbackProc Top_Bar_Interrupt_CB ();

/**************************************************
     Main Window
***************************************************/

extern void Cre_MainWindow ();


/**************************************************
     Overview
***************************************************/
extern void SaveBrowse ();
extern void BuildDisplayFromD_arr ();
extern void CentreAllBlocksUnderArrows ();
extern void GetTopImpNode ();
extern void GetTopSpecNode ();
extern void DisplayTopNode ();
extern void ManageOverviewAndPosition ();
extern void Load_DarrFromImpNode ();
extern void Load_DarrFromSpecNode ();
extern void inc_htx_curr_obj ();
extern void dec_htx_curr_obj ();

extern void init_htx_curr_obj ();
extern void Cre_HtxDialog ();
extern void Popup_HtxDialog ();
extern void htx_spec_but_CB ();
extern void htx_design_but_CB ();
extern void htx_done_but_CB ();
extern void htx_prev_but_CB ();
extern void htx_help_but_CB ();
extern void DestroyDisplayedBrowse ();
extern void PositioNonOverviewBrowse ();
extern void BuildCurrBrowse ();
extern void cre_curr_sees_ipts_htx_rc ();
extern void cre_curr_sees_ipts_htx_a2c ();
extern void curr_htx_CB ();
extern void curr_htx_a2c_CB ();
extern void cre_curr_htx_a2c ();
extern void sees_htx_a2c_CB ();
extern void cre_sees_htx_a2c ();
extern void ipts_htx_a2c_CB ();
extern void cre_ipts_htx_a2c ();


/**************************************************
     Quit, Help, Palette, Interrupt & Options callbacks
***************************************************/

extern void Quit_CB ();
extern void Kill_bplatform_and_exit ();
extern void Help_CB ();
extern void Popup_Interrupt ();
extern void Popdown_Interrupt ();


/*****************************************************
******************************************************
                  Animator
******************************************************
*****************************************************/

extern void Animate_Ops ();
extern void Animate ();



/*****************************************************
******************************************************
                  InterProver
******************************************************
*****************************************************/

extern void Ipr ();
extern void Ipr_Sel_Ops ();



/*****************************************************
******************************************************
                           Quit Editor Dialog
*****************************************************
****************************************************/

extern void QuitEditor_Popup_CB ();
extern void Check_QuitEditor_Popup ();
extern void OpenQuit ();

/*****************************************************
******************************************************
                  error dialogs
******************************************************
*****************************************************/

extern void Popup_Err_CB ();
extern void Popup_Minor_Err_CB ();
extern void Popup_CapacityErr_CB ();

extern void Popup_Parse_Err ();
extern void Popup_Err ();
extern void Popup_Minor_Err ();
extern void Popup_Minor_Err_DisplayAtTop  ();


/*****************************************************
******************************************************
                  radiobox dialogs
******************************************************
*****************************************************/

/*******************************
 radiobox dialog callbacks
*******************************/

extern int errorbox_flag;

/***
main_form userData values (radiobox_flag)
***/
extern int radiobox_flag;
#define open_radiobox                     4
#define close_radiobox                    5
#define mini_remake_radiobox              6
#define file_ed_NML_radiobox              7
/* #define close_quit_radiobox               8 */
#define close_all_radiobox                9
#define commit_all_radiobox              10
#define commit_but_radiobox              11
#define commitD_but_radiobox             12
#define remove_radiobox                  13
#define file_ed_POG_radiobox             16
#define rst_cst_but_radiobox             18
#define file_ed_DOC_radiobox             19
#define file_ed_DMU_radiobox             20
#define file_ed_GBO_radiobox             21
#define commit_all_remake_radiobox       22
#define continue_remake_radiobox         23
/*
#define anim_mini_rmk_edit_thy_radiobox  24
*/
#define close_anm_thy_file               25
#define remake_radiobox                  26
#define remake_all_or_construct_radiobox 27
#define browser_radiobox                 28
#define save_browse_radiobox             29
#define file_ed_ITF_radiobox             30
#define file_ed_ENM_radiobox             31
#define close_pmd_file                   32
/*
#define anim_mini_rmk_only_edit_thy_radiobox 33
*/
#define save_options_radiobox            34
#define restore_options_radiobox         35
#define pasp_fin_radiobox                36
#define new_dev_dir_radiobox             39
#define rem_VHDLSLIB_radiobox            40
#define cre_VHDLSLIB_code_radiobox       41
#define commit_btool_radiobox            42
#define commit_ipr_radiobox              43
#define three_provers_radiobox           44
#define rem_SLIB_radiobox                45
#define edit_pmd_radiobox                46
#define cre_new_dir_dev_radiobox         47
#define update_from_src_radiobox         48
#define six_animators_radiobox           49
#define close_anm_exe_file               50
#define source_control_setup_radiobox    51
#define source_control_edit_radiobox     52
#define source_control_radiobox          53


extern int confirm_flag;
#define commitD_but_confirm         commitD_but_radiobox
#define commit_but_confirm          commit_but_radiobox
#define rst_cst_but_confirm         rst_cst_but_radiobox
#define close_confirm               close_radiobox
#define close_all_confirm           close_all_radiobox
#define commit_all_confirm          commit_all_radiobox
#define update_from_src_confirm     update_from_src_radiobox
#define commit_all_remake_confirm   commit_all_remake_radiobox
#define continue_remake_confirm     continue_remake_radiobox
#define remove_confirm              remove_radiobox
#define save_browse_confirm         save_browse_radiobox
#define remake_confirm              remake_radiobox
#define save_options_confirm        save_options_radiobox
#define restore_options_confirm     restore_options_radiobox
#define new_dev_dir_confirm         new_dev_dir_radiobox
#define rem_SLIB_confirm            rem_SLIB_radiobox
#define cre_new_dir_dev_confirm     cre_new_dir_dev_radiobox
#define pasp_fin_confirm            pasp_fin_radiobox
#define rem_VHDLSLIB_confirm        rem_VHDLSLIB_radiobox
#define reload_PMD_confirm          10001
#define commit_doc_rst_but_confirm  10002
#define rst_cde_but_confirm         10003
#define VHDL_rst_cde_but_confirm    10004
#define rsl_selection_confirm       rsl_selection
#define cre_VHDLSLIB_selection_no_code_confirm 10005
#define cre_VHDLSLIB_selection_code_confirm    10006



extern void   Dialog_RadioBox_CB ();
extern void   Dialog_RadioBox_EditedFileExists_CB ();
extern void   Dialog_RadioBox_Ipr_Prf_Level_CB ();

extern void   ShowFileDiff ();

extern void   Popup_Help_OK_CB ();

extern void   Popup_EditedFileExists_Dialog_CB ();
extern void   Popup_RadioBox_Dialog_CB ();

extern void Popup_SavePromptDialog ();
extern void Popup_SavePromptDialog_CB ();
extern void Popup_FindPromptDialog ();
extern void Popup_FindPromptDialog_CB ();
extern void Popup_RenamePromptDialog ();
extern void Popup_RenamePromptDialog_CB ();
extern void Popup_IntroduceNewNamePromptDialog ();
extern void Popup_IntroduceNewNamePromptDialog_CB ();
extern void Popup_SaveBrowseDialog ();
extern void Popup_ThreeProvers ();
extern void Popup_EditPmd ();


/*******************************
 RadioBox dialog construction
*******************************/
#define Make_RadioBox_Dialog_Declarations \
 \
  static Widget dialog = ( Widget ) 0; \
  static Widget dialog_form, \
                radio_box, radio_box_frame, \
                B_logo, \
                sep, \
                och_o, och_c, och_h, och_form, \
                label; \
 \
  static struct help_struct       help_data; \
 \
  static struct ok_cancel_but_struct ok_but_data; \
  static struct ok_cancel_but_struct cancel_but_data; \
 \
  static Atom WM_DELETE_WINDOW



/*
#define Manage_RadioBox_Dialog \
 \
  XtVaSetValues ( och_o, \
      XmNshowAsDefault,          True, \
      NULL ); \
 \
  XtManageChild ( B_logo ); \
  XtManageChild ( label ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( radio_box_frame ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_c );  \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )
*/

#define Manage_RadioBox_Dialog \
  XtManageChild ( B_logo ); \
  XtManageChild ( label ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( radio_box_frame ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_c );  \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )

/*
#define Manage_RadioBox_Dialog_NoCancel \
 \
  XtVaSetValues ( och_o, \
      XmNshowAsDefault,          True, \
      NULL ); \
 \
  XtManageChild ( B_logo ); \
  XtManageChild ( label ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( radio_box_frame ); \
  XtManageChild ( och_o ); \
  XtUnmanageChild ( och_c ); \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )
*/

#define Manage_RadioBox_Dialog_NoCancel \
  XtManageChild ( B_logo ); \
  XtManageChild ( label ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( radio_box_frame ); \
  XtManageChild ( och_o ); \
  XtUnmanageChild ( och_c ); \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )


extern void Cre_RadioBox_Dialog ();
extern void Re_Cre_RadioBox_Dialog ();

/*******************************
 the RadioBox dialogs
*******************************/

extern void Popup_creVHDLSLIB_code ();
extern void Popup_creSLIB ();
extern void Popup_CloseEditedFile ();
extern void Popup_CloseEditedProofFile ();
extern void Popup_CloseEditedFileQuit ();
extern void Popup_OpenEditedFile ();
extern void Popup_OpenEditedProofFile ();
extern void Popup_OpenProofFile ();
extern void Popup_MiniRemake ();
extern void Popup_ClosePMDFile ();
extern void Popup_CloseAnimThyFile ();
extern void Popup_IniAnim ();
extern void Popup_AnimMiniRemake_EditThyFile ();
extern void Popup_AnimMiniRemakeThyOnly ();
extern void Popup_CmtNotParse ();

extern void Popup_Edt_Proceed ();
extern void Popup_RemoveEditedFile ();


/*****************************************************
******************************************************
                   prompt dialogs
******************************************************
*****************************************************/

/*******************************
 prompt dialog callbacks
*******************************/

extern void   Popup_InformationDialog_CB ();
extern void   Popup_PromptDialog_CB ();
extern void   Popup_PromptDialogHelp_CB ();
extern void   Popup_GetStringDialogHelp_CB ();
extern void   Popup_GetStringDialog_CB ();

/*******************************
 radiobox dialog construction
*******************************/

extern Widget Cre_Information_Dialog ();
extern Widget Cre_Prompt_Dialog ();
extern Widget Cre_NoCancel_Prompt_Dialog ();

/*******************************
 the prompt dialogs
*******************************/

extern void Popup_InformationDialog ();
extern void Popup_PromptDialog ();
extern void Popup_NoCancel_PromptDialog ();
extern void Popup_GetStringDialog ();


/*****************************************************
******************************************************
                   question dialogs
******************************************************
*****************************************************/

/*******************************
 question dialog callbacks
*******************************/

extern void Popup_ConfirmDialog_CB ();
extern void Popup_QuestionHelp_CB ();

/*******************************
 the question dialogs
*******************************/

extern void Popup_ConfirmDialog ();




/*****************************************************
******************************************************
                   selection dialogs
******************************************************
*****************************************************/

/*******************************
 Sel dialog callbacks
*******************************/

extern void   Dialog_Sel_RadioBox_CB ();
extern void   Popup_Sel_Dialog_CB ();
extern void   Popup_Selection_Sel_Dialog_CB ();
extern void   Popup_Selection_Sel_Text_Dialog_CB ();
extern void   ToggleBox_CB ();
extern void   SelectionToggleBox_CB ();
extern int    ToggleBox_check_toggles ();
extern int    ToggleBox_check_toggles_no_sel_str ();


/*******************************
 Sel dialog construction
*******************************/
#define Make_Sel_Dialog_Declarations \
 \
  static Widget dialog = ( Widget ) 0; \
  static Widget dialog_form, \
                radio_box_scroll, radio_box, \
                B_logo, \
                sep, \
                och_form, och_o, och_c, och_h, och_a, och_n, \
                label; \
 \
  static struct help_struct help_data; \
 \
  static Atom WM_DELETE_WINDOW


/*
#define Manage_Sel_Dialog \
 \
  XtVaSetValues ( och_o, \
      XmNshowAsDefault,          True, \
      NULL ); \
 \
  XtManageChild ( label ); \
  XtManageChild ( radio_box_scroll ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( B_logo ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_c );  \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )
*/

#define Manage_Sel_Dialog \
  XtManageChild ( label ); \
  XtManageChild ( radio_box_scroll ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( B_logo ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_c );  \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )


#define SelLarge_flag_EXTRA 2
#define SelLarge_flag_YES   1
#define SelLarge_flag_NO    0
extern void Cre_Selection_Sel_Dialog ();
extern void Cre_Sel_Dialog ();

#define SelOne_flagged_YES 1
#define SelOne_flagged_NO  0
#define GetBsel_NLallowed_flag_YES   1
#define GetBsel_NLallowed_flag_NO    0
#define GetBsel_flag_YES 1
#define GetBsel_flag_NO  0
extern void Re_Cre_Sel_Dialog ();


#define Make_Selection_Sel_Dialog_Declarations \
 \
  static Widget dialog = ( Widget ) 0; \
  static Widget dialog_form, \
                radio_box_scroll, radio_box, \
                B_logo, \
                sep, \
                och_form, och_o, och_f, och_c, och_h, \
                label, \
                sel_label, sel_text; \
 \
  static struct help_struct help_data; \
 \
  static Atom WM_DELETE_WINDOW


/*
#define Manage_Selection_Sel_Dialog \
 \
  XtVaSetValues ( och_o, \
      XmNshowAsDefault,          True, \
      NULL ); \
 \
  XtManageChild ( B_logo ); \
  XtManageChild ( label ); \
  XtManageChild ( sep ); \
  XtManageChild ( sel_text ); \
  XtManageChild ( sel_label ); \
  XtManageChild ( radio_box_scroll ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_f ); \
  XtManageChild ( och_c );  \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( dialog_form ); \
  XtPopup ( dialog, XtGrabNone ); \
  XmUpdateDisplay ( dialog )
*/

#define Manage_Selection_Sel_Dialog \
  XtManageChild ( B_logo ); \
  XtManageChild ( label ); \
  XtManageChild ( sep ); \
  XtManageChild ( sel_text ); \
  XtManageChild ( sel_label ); \
  XtManageChild ( radio_box_scroll ); \
  XtManageChild ( radio_box ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_f ); \
  XtManageChild ( och_c );  \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( dialog_form ); \
  XtPopup ( dialog, XtGrabNone ); \
  XmUpdateDisplay ( dialog )

extern void Re_Cre_Selection_Sel_Dialog ();



/*******************************
 the Sel dialogs
*******************************/

extern void Popup_Sel_Dialog ();
extern void Popup_SelLarge_Dialog ();
extern void Popup_SelOne_Dialog ();
extern void Popup_SelChoice_Dialog ();
extern void Popup_SelLargeOne_Dialog ();
extern void Popup_Selection_Sel_Dialog ();

#endif  /* #if ( defined  ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */
