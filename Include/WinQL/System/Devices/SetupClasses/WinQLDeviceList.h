//WinQLDeviceList.h

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

//Win32 Device List

#ifndef WINQL_DEVICELIST_H_3
#define WINQL_DEVICELIST_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Data.h"
#include "WinQL/Definitions/IO.h"
#include "WinQL/System/Devices/WinQLDevice.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstance.h"
#include "WinQL/System/Devices/WinQLDeviceHandle.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/Application/Threading/WinQLThreadAffinity.h"
#include "WinQL/CodeServices/WinQLSharedRef.h"
#include "WinQL/CodeServices/Handles/WinQLHandleMap.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceInfoSet.h"
#include "AppocritaQOR/Controller.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceList
	{

	public:

		__QOR_DECLARE_OCLASS_ID( CDeviceList );
		
		CDeviceList( nsCodeQOR::mxGUID* pGuid = 0, COSWindow* pWindow = 0, const mxTCHAR* szMachineName = 0 );		
		//CDeviceList( CDeviceListModel& DeviceListModel, nsAppocrita::CController* pParent = 0  );		
		CDeviceList( const CDeviceList& src );		
		~CDeviceList();

		unsigned long Size( void );

		CDeviceInstance::refType operator[]( unsigned long ulIndex );

	private:

		CDeviceInfoSet::refType m_InfoSet;
		
		nsWinQAPI::CSetupAPI& m_Library;

		bool EnumDevice( unsigned int& uiIndex, nsCodeQOR::mxGUID* );
		bool AddDevice( SP_DevInfo_Data& DevInfo, unsigned int uiIndex );

		CDeviceList& operator = ( const CDeviceList& src  );	//no assignment
	};

}//nsWin32

#endif//WINQL_DEVICELIST_H_3