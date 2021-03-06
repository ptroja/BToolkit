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
#include "Bit_TYPE.h"
#include "Bit_TYPE_Ops.h"

void
#ifdef _BT_ANSIC
MSK_BTS( int *s, int m, int n )
#else
MSK_BTS( s, m, n )
int *s, m, n;
#endif
{
	int i,v;
	i = n-m+1;
	v = 0;
	while( i>0 ){
		v = 2*v+1;
		i = i-1;
	};
	*(s) = v<<(32-n);
}


void
#ifdef _BT_ANSIC
VMS_BTS( int *s, int b, int m, int n )
#else
VMS_BTS( s, b, m, n )
int *s, b, m, n;
#endif
{
	int i,v;
	i = n-m+1;
	v = 0;
	while( i>0 ){
		v = 2*v+1;
		i = i-1;
	};
	*(s) = ((b&(v<<(32-n)))>>(32-n));
}


void
#ifdef _BT_ANSIC
MMS_BTS( int *s, int b, int m, int n, int w )
#else
MMS_BTS( s, b, m, n, w )
int *s, b, m, n, w;
#endif
{
	int i,v;
	i = n-m+1;
	v = 0;
	while( i>0 ){
		v = 2*v+1;
		i = i-1;
	};
	*(s) = (~(v<<(32-n))&b)|((w&v)<<(32-n));
}


void
#ifdef _BT_ANSIC
VAL_BTS( int *s, int b, int n)
#else
VAL_BTS( s, b, n)
int *s, b, n;
#endif
{
	VMS_BTS(s,b,n,n);
}


void
#ifdef _BT_ANSIC
STO_BTS( int *s, int b, int n, int w )
#else
STO_BTS( s, b, n, w )
int *s, b, n;
#endif
{
	MMS_BTS(s,b,n,n,w);
}

