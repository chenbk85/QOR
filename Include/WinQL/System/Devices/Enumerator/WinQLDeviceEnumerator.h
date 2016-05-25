//WinQLDeviceEnumerator.h

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

//Win32 Device Enumerator

#ifndef WINQL_DEVICEENUMERATOR_H_3
#define WINQL_DEVICEENUMERATOR_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/CodeServices/Handles/WinQLHandle.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceInfoSet.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstance.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CSetupAPI;
}//nsWinQAPI

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceEnumerator
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDeviceEnumerator );

		typedef nsCodeQOR::CTLRef< CDeviceEnumerator > refType;

		CDeviceEnumerator( CTString& strEnumID );
		virtual ~CDeviceEnumerator();

		CTString ID( void );
		unsigned int Enumerate( void );

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this );
		}

		nsCodeQOR::CTArray< CDeviceInstance*, CWinQLPolicy >& Instances( void );

	private:

		nsWinQAPI::CSetupAPI& m_Library;
		CTString m_strID;							//Symbolic name or GUID as string
		CDeviceInfoSet::refType m_InfoSet;
		SP_DevInfo_Data m_DevInfo;
		nsCodeQOR::CTArray< CDeviceInstance*, CWinQLPolicy > m_ArrayDeviceInstances;
		bool m_bEnumerated;
		
		CDeviceEnumerator();//not to be implemented
		CDeviceEnumerator( const CDeviceEnumerator& src );
		CDeviceEnumerator& operator = ( const CDeviceEnumerator& src );
	};


}//nsWin32

#endif//WINQL_DEVICEENUMERATOR_H_3