//FunctionContext.h

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

#ifndef WINQAPI_FCONTEXT_H_1
#define WINQAPI_FCONTEXT_H_1

#include "CodeQOR/Text/CodeString.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"

#if	( __QOR_FUNCTION_CONTEXT_TRACKING == __QCS_YES_ )

#	ifdef __INTELLISENSE__ //fool the fool that is intellisense
#		define _FCONTEXT( _X ) nsWinQAPI::CFunctionContext _FContext_ ( nsCodeQOR::CObjectContextBase( this ), __FUNCSIG__, __FILE__, __LINE__ )
#		define _SFCONTEXT( _X ) nsWinQAPI::CFunctionContext _FContext_ ( __FUNCSIG__, __FILE__, __LINE__ )
#	else
#		define _FCONTEXT( _X ) nsWinQAPI::CFunctionContext _FContext_ ( nsCodeQOR::CObjectContextBase( this ), _X, __FILE__, __LINE__ )
#		define _SFCONTEXT( _X ) nsWinQAPI::CFunctionContext _FContext_ ( _X, __FILE__, __LINE__ )
#	endif

#	if	( __QCMP_SUPPORTS__FUNCSIG__ == __QCS_YES_ )
#		define _WINQ_FCONTEXT( _X ) _FCONTEXT( __QCMP_FUNCSIG__( _X ) )
#		define _WINQ_SFCONTEXT( _X ) _SFCONTEXT( __QCMP_FUNCSIG__( _X ) )
#	else
#		define _WINQ_FCONTEXT( _X ) _FCONTEXT( _X )
#		define _WINQ_SFCONTEXT( _X ) _SFCONTEXT( _X )
#	endif//( __QCMP_SUPPORTS__FUNCSIG__ == __QCS_YES_ )

#else//!( __QOR_FUNCTION_CONTEXT_TRACKING == __QCS_YES_ )

#	define _WINQ_FCONTEXT( _X )
#	define _WINQ_SFCONTEXT( _X )

#endif//( __QOR_FUNCTION_CONTEXT_TRACKING == __QCS_YES_ )

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQAPI ) CFunctionContext : public nsCodeQOR::CFunctionContextBase
	{

	public:

		CFunctionContext( const char* szFuncName, const char* szFile, unsigned int uiLine );
		CFunctionContext( nsCodeQOR::CObjectContextBase ObjContext, const char* szFuncName, const char* szFile, unsigned int uiLine );
		virtual ~CFunctionContext();
		unsigned long LastOSError();

	protected:
		
		unsigned long m_dwLastOSError;

	private:

		CFunctionContext( const CFunctionContext& src );//Copy ctor not to be implemented
		CFunctionContext& operator=( CFunctionContext& src );//Assignment op not to be implemented

	};
	
}//nsWinQAPI

#endif//WINQAPI_FCONTEXT_H_1