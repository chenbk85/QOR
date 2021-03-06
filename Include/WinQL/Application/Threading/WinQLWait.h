//WinQLWait.h

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

#ifndef WINQL_CS_WAIT_H_3
#define WINQL_CS_WAIT_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Macros/codingmacros.h"
#include "WinQL/WinQL.h"
#include "WinQL/CodeServices/Handles/WinQLSyncHandle.h"

//------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CUser32;
}

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	typedef void ( __QCMP_STDCALLCONVENTION *WAITORTIMERCALLBACK ) ( void* , unsigned char );

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CWaitHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CWaitHelper );

		CWaitHelper();
		CWaitHelper( const CWaitHelper& );
		CWaitHelper& operator = ( const CWaitHelper& );
		~CWaitHelper();
		bool RegisterWaitForSingleObject( void** phNewWaitObject, CSyncHandle& Object, nsWin32::WAITORTIMERCALLBACK Callback, void* Context, unsigned long dwMilliseconds, unsigned long dwFlags );
		unsigned long SignalObjectAndWait( CSyncHandle& hObjectToSignal, CSyncHandle& hObjectToWaitOn, unsigned long dwMilliseconds, bool bAlertable );
		bool UnregisterWait( void* WaitHandle );
		bool UnregisterWaitEx( void* WaitHandle, void* CompletionEvent );
		unsigned long WaitForMultipleObjects( CSyncHandleSet& Handles, bool bWaitAll, unsigned long dwMilliseconds );
		unsigned long WaitForMultipleObjectsEx( CSyncHandleSet& Handles, bool bWaitAll, unsigned long dwMilliseconds, bool bAlertable );
		unsigned long WaitForSingleObject( CSyncHandle& Handle, unsigned long dwMilliseconds );
		unsigned long WaitForSingleObjectEx( CSyncHandle& Handle, unsigned long dwMilliseconds, bool bAlertable );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CMsgWaitHelper
	{
	public:
			
		__QOR_DECLARE_OCLASS_ID( CMsgWaitHelper );

		CMsgWaitHelper();
		virtual ~CMsgWaitHelper();
		unsigned long Wait( CSyncHandleSet& Handles, bool bWaitAll, unsigned long dwMilliseconds, unsigned long dwWakeMask );
		unsigned long WaitEx( CSyncHandleSet& Handles, unsigned long dwMilliseconds, unsigned long dwWakeMask, unsigned long dwFlags );

	private:

		nsWinQAPI::CUser32& m_Library;

		__QCS_DECLARE_NONCOPYABLE( CMsgWaitHelper );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CRegisteredWait
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CRegisteredWait );

		CRegisteredWait( CSyncHandle& Object, unsigned long dwMilliseconds, unsigned long dwFlags, void* pCompletionEvent = 0, bool* pResult = 0 );
		virtual ~CRegisteredWait();

		void SetCompletionEvent( void* pCompletionEvent );

	protected:
			
		static CWaitHelper s_WaitHelper;
		void* m_pWaitHandle;
		bool m_bRegistered;
		void* m_pCompletionEvent;
		bool* m_pResult;

		virtual void InstanceCallback( unsigned char ucData );

	private:

		static void __stdcall StaticCallback( void* pData1 , unsigned char ucData2 );

		//Not to be implemented
		CRegisteredWait();
		CRegisteredWait( const CRegisteredWait& );
		CRegisteredWait& operator = ( const CRegisteredWait& );
	};

}//nsWin32

#endif//WINQL_CS_WAIT_H_3
