//SAN_stdio.cpp

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

#include "SystemQOR.h"

#if		( QOR_SYS_OS == QOR_SYS_SANOS )

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "SystemQOR/SanOS/SAN_stdio.h"
#include "SanQL/SanQL.h"
//#include "SanQL/CodeServices/ErrorSystem/Error.h"
//#include "SanQL/CodeServices/String.h"

//--------------------------------------------------------------------------------
namespace nsSanOS
{
	__QOR_IMPLEMENT_OCLASS_LUID( Cstdio );

	//--------------------------------------------------------------------------------
	Cstdio::Cstdio()
	{
		//_WINQ_FCONTEXT( "Cstdio::Cstdio" );
	}

	//--------------------------------------------------------------------------------
	Cstdio::~Cstdio()
	{
		//_WINQ_FCONTEXT( "Cstdio::~Cstdio" );
	}

	//--------------------------------------------------------------------------------
	int Cstdio::fflush( FILE* stream )
	{
		//_WINQ_FCONTEXT( "Cstdio::fflush" );
		int iResult = 0;
		//__QOR_PROTECT
		//{
			//nsPosum::CStream Stream( stream );
			iResult = 0;//Stream.Flush();
		//}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int Cstdio::fputc( int c, FILE* stream )
	{
		//_WINQ_FCONTEXT( "Cstdio::fputc" );
		int iResult = 0;
		//__QOR_PROTECT
		//{
			//nsPosum::CStream Stream( stream );
			iResult = 0;//Stream.PutC( c );
		//}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	//fputs
	int Cstdio::fputs( const char* s, FILE* stream )
	{
		//_WINQ_FCONTEXT( "Cstdio::fputs" );
		int iResult = 0;
		//__QOR_PROTECT
		//{
			//nsPosum::CStream Stream( stream );
			iResult = 0;//Stream.PutS( s );
		//}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	size_t Cstdio::fwrite( const void* ptr, size_t size, size_t nmemb, FILE* stream )
	{
		//_WINQ_FCONTEXT( "Cstdio::fwrite" );
		size_t Result = 0;
		//__QOR_PROTECT
		//{
			//nsPosum::CStream Stream( stream );
			Result = 0;//Stream.Write( ptr, size, nmemb );
		//}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	int Cstdio::getchar( void )
	{
		//_WINQ_FCONTEXT( "Cstdio::getchar" );
		int iResult = 0;
		//__QOR_PROTECT
		//{
			//::nsPosum::CStream Stream( 0 );
			iResult = 0;//Stream.GetC();
		//}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int Cstdio::printf( const char* format, va_list vargs )
	{
		//_WINQ_FCONTEXT( "Cstdio::printf" );
		int iResult = 0;

		if( format == 0 )
		{
			errno = EINVAL;
			iResult = -1;
		}
		else
		{
			//::nsPosum::CStream Stream( 1 );
			iResult = 0;//Stream.PrintF( format, vargs );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int Cstdio::putchar( int c )
	{
		//_WINQ_FCONTEXT( "Cstdio::putchar" );
		int iResult = 0;
		//__QOR_PROTECT
		//{
			//::nsPosum::CStream Stream( 1 );
			iResult = 0;//Stream.PutC( c );	
		//}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	//puts
	int Cstdio::puts( const char* s )
	{
		//_WINQ_FCONTEXT( "Cstdio::puts" );
		int iResult = 0;
		//__QOR_PROTECT
		//{
			//::nsPosum::CStream Stream( 1 );
			iResult = 0;//Stream.PutS( s );
		//}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int Cstdio::sprintf( char* s, const char* format, va_list vargs )
	{
		//_WINQ_FCONTEXT( "Cstdio::sprintf" );
		//nsWin32::CStringHelper StringHelper;
		//return StringHelper.wvsprintfA( s, format, vargs );
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cstdio::vfprintf( FILE* stream, const char* format, va_list vargs )
	{
		//_WINQ_FCONTEXT( "Cstdio::vfprintf" );
		return 0;//fprintf( stream, format, vargs );
	}

	//--------------------------------------------------------------------------------
	int Cstdio::vprintf(const char* format, va_list vargs )
	{
		//_WINQ_FCONTEXT( "Cstdio::vprintf" );
		return 0;//printf( format, vargs );
	}

}//nsSanOS

#endif//(QOR_SYS_OS == QOR_SYS_SANOS)
