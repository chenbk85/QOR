//WinQLStringServices.h

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

//Win32 Code Services String class

#ifndef WINQL_STRING_H_3
#define WINQL_STRING_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "CodeQOR/Macros/codingmacros.h"
#include "WinQL/Definitions/Handles.h"
#include "WinQL/Application/I18n/WinQLI18n.h"
#include <stdarg.h>

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CUser32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CBaseStringHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CBaseStringHelper );

		__QCMP_STATIC_CONSTANT( unsigned int, CTType1 = 0x00000001 );// ctype 1 information
		__QCMP_STATIC_CONSTANT( unsigned int, CTType2 = 0x00000002 );// ctype 2 information
		__QCMP_STATIC_CONSTANT( unsigned int, CTType3 = 0x00000004 );// ctype 3 information

		CBaseStringHelper();
		virtual ~CBaseStringHelper();
		int CompareStringEx( const wchar_t* lpLocaleName, unsigned long dwCmpFlags, const wchar_t* lpString1, int cchCount1, const wchar_t* lpString2, int cchCount2, nsWin32::NLSVersionInfo* lpVersionInformation, void* lpReserved, Cmp_long_ptr lParam );
		int CompareStringT( unsigned long Locale, unsigned long dwCmpFlags, const TCHAR* lpString1, int cchCount1, const TCHAR* lpString2, int cchCount2 );
		int CompareStringA( unsigned long Locale, unsigned long dwCmpFlags, const char* lpString1, int cchCount1, const char* lpString2, int cchCount2 );
		int CompareStringW( unsigned long Locale, unsigned long dwCmpFlags, const wchar_t* lpString1, int cchCount1, const wchar_t* lpString2, int cchCount2 );
		int FoldStringT( unsigned long dwMapFlags, const TCHAR* lpSrcStr, int cchSrc, TCHAR* lpDestStr, int cchDest );
		bool GetStringTypeA( unsigned long Locale, unsigned long dwInfoType, const char* lpSrcStr, int cchSrc, unsigned short* lpCharType );
		bool GetStringTypeExT( unsigned long Locale, unsigned long dwInfoType, const TCHAR* lpSrcStr, int cchSrc, unsigned short* lpCharType );
		bool GetStringTypeW( unsigned long dwInfoType, const wchar_t* lpSrcStr, int cchSrc, unsigned short* lpCharType );
		bool IsDBCSLeadByte( unsigned char TestChar );
		bool IsDBCSLeadByteEx( unsigned int CodePage, unsigned char TestChar );
		int MultiByteToWideChar( unsigned int CodePage, unsigned long dwFlags, const char* lpMultiByteStr, int cbMultiByte, wchar_t* lpWideCharStr, int cchWideChar );
		int WideCharToMultiByte( unsigned int uiCodePage, unsigned long dwFlags, const wchar_t* lpWideCharStr, int cchWideChar, char* lpMultiByteStr, int cbMultiByte, const char* lpDefaultChar, int* lpUsedDefaultChar );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CStringHelper : public CBaseStringHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CStringHelper );

		CStringHelper();
		virtual ~CStringHelper();
		char* CharLowerA( char* lpsz );
		wchar_t* CharLowerW( wchar_t* lpwsz );
		unsigned long CharLowerBuffA( char* lpsz, unsigned long cchLength );
		unsigned long CharLowerBuffW( wchar_t* lpwsz, unsigned long cchLength );
		TCHAR* CharNextT( const TCHAR* lpsz );
		char* CharNextExA( unsigned short CodePage, const char* lpCurrentChar, unsigned long dwFlags );
		TCHAR* CharPrevT( const TCHAR* lpszStart, const TCHAR* lpszCurrent );
		char* CharPrevExA( unsigned short CodePage, const char* lpStart, const char* lpCurrentChar, unsigned long dwFlags );
		bool CharToOemT( const TCHAR* lpszSrc, char* lpszDst );
		bool CharToOemBuffA( const char* lpszSrc, char* lpszDst, unsigned long cchDstLength );
		bool CharToOemBuffW( const wchar_t* lpwszSrc, char* lpszDst, unsigned long cchDstLength );
		TCHAR* CharUpperT( TCHAR* lpsz );
		unsigned long CharUpperBuffA( char* lpsz, unsigned long cchLength );
		unsigned long CharUpperBuffW( wchar_t* lpwsz, unsigned long cchLength );
		bool IsCharAlphaT( TCHAR ch );
		bool IsCharAlphaNumericT( TCHAR ch );
		bool IsCharLowerT( TCHAR ch );
		bool IsCharUpperT( TCHAR ch );
		int LoadStringT( InstanceHandle hInstance, unsigned int uID, TCHAR* lpBuffer, int nBufferMax );
		int LoadStringA( InstanceHandle hInstance, unsigned int uID, char* lpBuffer, int nBufferMax );
		int LoadStringW( InstanceHandle hInstance, unsigned int uID, wchar_t* lpBuffer, int nBufferMax );
		bool OemToCharT( const char* lpszSrc, TCHAR* lpszDst );
		bool OemToCharBuffA( const char* lpszSrc, char* lpszDst, unsigned long cchDstLength );
		bool OemToCharBuffW( const wchar_t* lpwszSrc, wchar_t* lpwszDst, unsigned long cchDstLength );
		int wvsprintfA( char* lpOutput, const char* lpFmt, va_list arglist );
		int wvsprintfW( wchar_t* lpOutput, const wchar_t* lpFmt, va_list arglist );

	private:

		nsWinQAPI::CUser32& m_User32Library;

		__QCS_DECLARE_NONASSIGNABLE( CStringHelper );
	};

}//nsWin32

#endif//WINQL_STRING_H_3