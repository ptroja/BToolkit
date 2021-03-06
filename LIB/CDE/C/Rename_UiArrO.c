/* Copyright (c) 1985-2012, B-Core (UK) Ltd
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
#include "Rename_UiArrO.h"

#include "Rename_C_UiArr.h"
#include "Rename_M_Byt.h"
#include "Rename_O_BiArr.h"

#include "Bool_TYPE.h"
#include "PASP_TYPE.h"

void
INI_Rename_UiArrO(void)
{
  INI_Rename_C_UiArr();
  INI_Rename_M_Byt();
  INI_Rename_O_BiArr();
  Rename_M_STO(0);
}

void
Rename_UiAO_OBJ_FUL(int *_bb)
{
  int obj;
  Rename_M_VAL(&obj);
  if ( obj == Rename_UiArrOP1 ) {
    *_bb = TRUE;
  }
  else {
    *_bb = FALSE;
  }
}

void
Rename_UiAO_XST(int *_bb,int _pp)
{
  int tok,xx,yy;
  Rename_M_VAL(&tok);
  BGE(&xx,_pp,1);
  BLE(&yy,_pp,tok);
  if ( xx == TRUE && yy == TRUE ) {
    *_bb = TRUE;
  }
  else {
    *_bb = FALSE;
  }
}

void
Rename_UiAO_INI(void)
{
  Rename_M_STO(0);
}

void
Rename_UiAO_CRE(int *_bb,int *_pp)
{
  int tt,tok;
  Rename_M_VAL(&tt);
  if ( tt < Rename_UiArrOP1 ) {
    BINC(&tok,tt);
    Rename_M_STO(tok);
    Rename_O_STO(tok,1);
    *_pp = tok;
    *_bb = TRUE;
  }
  else {
    *_bb = FALSE;
    *_pp = 0;
  }
}

void
Rename_UiAO_VAL(int *_vv,int _pp,int _ii)
{
  int seg,idx;
  BDEC(&seg,_pp);
  UMUL(&idx,seg,Rename_UiArrOP2);
  UADD(&idx,idx,_ii);
  Rename_C_VAL(_vv,idx);
}

void
Rename_UiAO_NXT(int *_nn,int _pp)
{
  Rename_O_VAL(_nn,_pp);
}

void
Rename_UiAO_EQL(int *_bb,int _ss,int _tt)
{
  int idx,offset,seg,top,xidx,xoffset,xseg,v1,v2,pp,qq;
  BDEC(&seg,_ss);
  UMUL(&offset,Rename_UiArrOP2,seg);
  UINC(&idx,offset);
  UADD(&top,offset,Rename_UiArrOP2);
  BDEC(&xseg,_tt);
  UMUL(&xoffset,Rename_UiArrOP2,xseg);
  UINC(&xidx,xoffset);
  pp = TRUE;
  while ( pp == TRUE ) {
    Rename_C_VAL(&v1,idx);
    Rename_C_VAL(&v2,xidx);
    UINC(&idx,idx);
    UINC(&xidx,xidx);
    ULE(&pp,idx,top);
    BEQ(&qq,v1,v2);
    if ( pp == TRUE && qq == TRUE ) {
      pp = TRUE;
    }
    else {
      pp = FALSE;
    }
  };
  Rename_O_STO(_ss,1);
  Rename_O_STO(_tt,1);
  *_bb = qq;
}

void
Rename_UiAO_STO(int _pp,int _ii,int _vv)
{
  int nx,offset,seg,index;
  BDEC(&seg,_pp);
  UMUL(&offset,Rename_UiArrOP2,seg);
  UADD(&index,offset,_ii);
  Rename_C_STO(index,_vv);
  if ( _ii < Rename_UiArrOP2 ) {
    UINC(&nx,_ii);
    Rename_O_STO(_pp,nx);
  }
  else {
    Rename_O_STO(_pp,1);
  }
}

void
Rename_UiAO_STO_NXT(int _pp,int _vv)
{
  int nx,offset,seg,index,ii;
  BDEC(&seg,_pp);
  UMUL(&offset,Rename_UiArrOP2,seg);
  Rename_O_VAL(&ii,_pp);
  UADD(&index,offset,ii);
  Rename_C_STO(index,_vv);
  if ( ii < Rename_UiArrOP2 ) {
    UINC(&nx,ii);
    Rename_O_STO(_pp,nx);
  }
  else {
    Rename_O_STO(_pp,1);
  }
}

void
Rename_UiAO_CPY(int _pp,int _qq)
{
  int idx,offset,seg,top,xidx,xoffset,xseg,vv;
  BDEC(&seg,_pp);
  UMUL(&offset,Rename_UiArrOP2,seg);
  UINC(&idx,offset);
  UADD(&top,offset,Rename_UiArrOP2);
  BDEC(&xseg,_qq);
  UMUL(&xoffset,Rename_UiArrOP2,xseg);
  UINC(&xidx,xoffset);
  while ( idx <= top ) {
    Rename_C_VAL(&vv,idx);
    Rename_C_STO(xidx,vv);
    UINC(&idx,idx);
    UINC(&xidx,xidx);
  };
  Rename_O_STO(_pp,1);
  Rename_O_STO(_qq,1);
}

void
Rename_UiAO_FILL(int _pp,int _vv)
{
  int seg,ii,top;
  BDEC(&seg,_pp);
  UMUL(&ii,seg,Rename_UiArrOP2);
  UADD(&top,ii,Rename_UiArrOP2);
  while ( ii != top ) {
    UINC(&ii,ii);
    Rename_C_STO(ii,_vv);
  };
  Rename_O_STO(_pp,1);
}

