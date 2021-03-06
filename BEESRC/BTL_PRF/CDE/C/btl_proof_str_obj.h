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
extern int btl_proof_str_objP1;
extern int btl_proof_str_objP2;
extern int btl_proof_tot_str_obj;

extern int btl_proof_adr_str_obj[];
extern int btl_proof_ssiz_adr_str_obj;

extern int btl_proof_len_str_obj[];
extern int btl_proof_ssiz_len_str_obj;

extern int btl_proof_old_str_obj[];
extern int btl_proof_ssiz_old_str_obj;

extern char btl_proof_array_str_obj[];


#define btl_proof_MEM_FUL_STR_OBJ(bb) \
{*(bb) = ((btl_proof_tot_str_obj == 0)!=0);}

#define btl_proof_OBJ_FUL_STR_OBJ(bb)     \
{*(bb) = ((btl_proof_ssiz_len_str_obj-1-btl_proof_ssiz_old_str_obj == btl_proof_str_objP1)!=0);}

#define btl_proof_FRE_MEM_STR_OBJ(nn) \
{*(nn) =  btl_proof_tot_str_obj;}

#define btl_proof_FRE_OBJ_STR_OBJ(nn)     \
{*(nn) = (btl_proof_str_objP1-btl_proof_ssiz_len_str_obj+1+btl_proof_ssiz_old_str_obj);}

#define btl_proof_ANY_STR_OBJ(nn)  \
{*(nn) = 1;}

#define btl_proof_XST_IDX_STR_OBJ(bb,pp,ii)   \
{*(bb) = ((ii>0) && (ii <= btl_proof_len_str_obj[pp]))!=0;}

#define btl_proof_CLR_STR_OBJ(ss) \
{btl_proof_tot_str_obj = btl_proof_tot_str_obj+btl_proof_len_str_obj[ss]; \
 btl_proof_len_str_obj[ss] = 0;}

#define btl_proof_KIL_STR_OBJ(pp) \
{btl_proof_CLR_STR_OBJ(pp); \
 btl_proof_ssiz_old_str_obj=btl_proof_ssiz_old_str_obj+1; \
 btl_proof_old_str_obj[btl_proof_ssiz_old_str_obj]=pp;}

#define btl_proof_STO_STR_OBJ(ss,ii,vv)  \
{btl_proof_array_str_obj[ii+btl_proof_adr_str_obj[ss]] = vv;}

#define btl_proof_VAL_STR_OBJ(vv,ss,ii)  \
{*(vv) = btl_proof_array_str_obj[ii+btl_proof_adr_str_obj[ss]];}

#define btl_proof_POP_STR_OBJ(pp)        \
{btl_proof_len_str_obj[pp] = btl_proof_len_str_obj[pp]-1; \
 btl_proof_tot_str_obj = btl_proof_tot_str_obj+1;}

#define btl_proof_KEP_STR_OBJ(pp,ii)      \
{btl_proof_tot_str_obj = btl_proof_tot_str_obj+btl_proof_len_str_obj[pp]-(ii); \
 btl_proof_len_str_obj[pp] = ii;}

#define btl_proof_LEN_STR_OBJ(nn,pp)     \
{*(nn) = btl_proof_len_str_obj[pp];}

#define btl_proof_EMP_STR_OBJ(bb,pp)   \
{*(bb) = (btl_proof_len_str_obj[pp]==0)!=0;}

#define btl_proof_REL_BUF_STR_OBJ() {}






