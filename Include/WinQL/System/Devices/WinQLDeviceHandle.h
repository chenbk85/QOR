//WinQLDeviceHandle.h

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

//Win32 Device Handle

#ifndef WINQL_DEVICEHANDLE_H_1
#define WINQL_DEVICEHANDLE_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/CodeServices/Handles/WinQLHandle.h"
#include "WinQL/Application/Threading/WinQLThreadAffinity.h"
#include "WinQL/CodeServices/Handles/WinQLHandleMap.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	class __QOR_INTERFACE( __WINQL ) CDeviceHandle;

	//typedef nsWin32::CTHandleMap< nsCodeQOR::CTCRef< CDeviceHandle >, CDeviceHandle > CDeviceHandleMap;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceHandle : public CHandle
	{
		QOR_PP_WINQL_THREAD_ATTACHED;

	public:

		typedef nsCodeQOR::CTCRef< CDeviceHandle > refType;

		__QOR_DECLARE_OCLASS_ID( CDeviceHandle );

		CDeviceHandle();
		CDeviceHandle( void* h );
		CDeviceHandle( const CDeviceHandle& src );
		CDeviceHandle& operator = ( const CDeviceHandle& src );
		virtual ~CDeviceHandle();

		void* Use( void );

		unsigned long AddRef( void ) const ;
		unsigned long Release( void );

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this );
		}

	protected:

		void Init( void );																		//
		void Uninit( void );																	//

	private:

		mutable unsigned long m_ulRefCount;//TODO: Should be an atmoic value		
	};

}//nsWin32

#endif//WINQL_DEVICEHANDLE_H_1