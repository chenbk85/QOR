//locale_types.h

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

//Win32 specific definitions associated with locale

#ifndef WIN32_LOCALE_TYPES_H_3
#define WIN32_LOCALE_TYPES_H_3

#include "CompilerQOR.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//class __WINQL_INTERFACE CThreadLocaleInfo;

	//--------------------------------------------------------------------------------
	typedef struct tagLC_ID 
	{
			unsigned short wLanguage;
			unsigned short wCountry;
			unsigned short wCodePage;
	} LC_ID, *LPLC_ID;

	// Locale categories
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryAll =		0/*CLocale::LCALL*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryCollate =	1/*CLocale::LCCOLLATE*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryCType =		2/*CLocale::LCCTYPE*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryMessages =	3/*CLocale::LCMESSAGES*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryMonetary =	4/*CLocale::LCMONETARY*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryNumeric =	5/*CLocale::LCNUMERIC*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryTime =		6/*CLocale::LCTIME*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryMin =		0/*LocaleCategoryAll*/ );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryMax =		6/*LocaleCategoryTime*/ );

	__QCMP_STATIC_CONSTANT( int, LocaleCategoryCollateMask =			0x0001 );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryCTypeMask =				0x0002 );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryMessagesMask =			0x0004 );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryMonetaryMask =			0x0008 );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryNumericMask =			0x0010 );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryTimeMask =				0x0020 );
	__QCMP_STATIC_CONSTANT( int, LocaleCategoryAllMask =				0x003F );

	//--------------------------------------------------------------------------------
	struct lconv 
	{
		char *decimal_point;
		char *thousands_sep;
		char *grouping;
		char *int_curr_symbol;
		char *currency_symbol;
		char *mon_decimal_point;
		char *mon_thousands_sep;
		char *mon_grouping;
		char *positive_sign;
		char *negative_sign;
		char int_frac_digits;
		char frac_digits;
		char p_cs_precedes;
		char p_sep_by_space;
		char n_cs_precedes;
		char n_sep_by_space;
		char p_sign_posn;
		char n_sign_posn;
	};
	
	typedef void* locale_t;//TODO: replace this with proper definition

}//nsWin32

#endif//WIN32_LOCALE_TYPES_H_3
