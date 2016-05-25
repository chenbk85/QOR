//TLSDyn.c

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "../SystemQOR/MSWindows/WinCmpSupQORVC/include/PE/Sections.h"

#define DLL_THREAD_ATTACH    2

typedef void ( __cdecl *_PVFV )( void );
typedef void ( __stdcall  *fpImage_TLS_Callback ) ( void* DllHandle, unsigned long Reason, void* Reserved );

static _CRTALLOC(".CRT$XDA") _PVFV __xd_a = 0;
static _CRTALLOC(".CRT$XDZ") _PVFV __xd_z = 0;

//--------------------------------------------------------------------------------
void __stdcall __dyn_tls_init( void* hDllHandle, unsigned long dwReason, void* lpreserved )
{
    _PVFV* pfunc;

    if( dwReason != DLL_THREAD_ATTACH ) 
	{
        return ;
    }
    
    for ( pfunc = &__xd_a + 1; pfunc != &__xd_z; ++pfunc ) 
	{
		__try
		{
			if ( *pfunc != 0 ) 
			{
				( *pfunc )();
			}
		}
		__finally
		{
			//TODO: Possibly report throwing initialiser
		}
    }
    return ;
}


fpImage_TLS_Callback __dyn_tls_init_callback = __dyn_tls_init;

static _CRTALLOC(".CRT$XLC") fpImage_TLS_Callback __xl_c = __dyn_tls_init;

//__QCMP_ENDLINKAGE_C
