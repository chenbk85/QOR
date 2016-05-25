//iconv.h

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
//iconv.h

#ifndef	QOR_ICONV_H_3
#define QOR_ICONV_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(iconv)

typedef nsPlatform::iconv_t iconv_t;

#if		(!__QCMP_FEATURE_PREDEFINESSIZE_T)
typedef nsPlatform::size_t size_t;
#endif//(!__QCMP_FEATURE_PREDEFINESSIZE_T)

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) iconv_t iconv_open( const char*, const char* );
    __QOR_INTERFACE( __CQOR ) size_t iconv( iconv_t, char** __QCMP_RESTRICT, size_t* __QCMP_RESTRICT, char** __QCMP_RESTRICT, size_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int iconv_close( iconv_t );

__QCMP_ENDLINKAGE_C

#endif//QOR_ICONV_H_3
