//WinQLMessageIndicator.h

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

//Win32 Message Indicator Device

#ifndef WINQL_DEVICE_MESSAGEINDICATOR_H_3
#define WINQL_DEVICE_MESSAGEINDICATOR_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterface.h"
#include "WinQL/System/Devices/WinQLIODevice.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CMessageIndicator : public CDeviceInterface
	{
	public:

		typedef nsCodeQOR::CTLRef< CMessageIndicator > refType;

		__QOR_DECLARE_OCLASS_ID( CMessageIndicator );

		static nsCodeQOR::CTExternalRegEntry< CMessageIndicator > RegEntry;

		CMessageIndicator();
		virtual ~CMessageIndicator();
		

	private:

		CMessageIndicator( const CMessageIndicator& src );
		CMessageIndicator& operator = ( const CMessageIndicator& src );
		
	};

}//nsWin32

#endif//WINQL_DEVICE_MESSAGEINDICATOR_H_3



/*
// Message indicator class driver functions
//
#define IOCTL_SET_SYS_MESSAGE_INDICATOR     \
        CTL_CODE(FILE_DEVICE_BATTERY, 0x70, METHOD_BUFFERED, FILE_WRITE_ACCESS)
*/

//m_pIODevice->Control( __WINQL_DEVICE_CONTROL_CODE( File_Device_Battery, Set_Message_Indicator/*0x70*/, Method_Buffered, File_Write_Access ), 0, 0, 0, 0, &ulOut, 0 );

/*
	//--------------------------------------------------------------------------------
	bool CPowerHelper::SetMessageWaitingIndicator( CDeviceHandle& hIndicator, unsigned long cmsg )
	{
		_WINQ_FCONTEXT( "CPowerHelper::SetMessageWaitingIndicator" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::SetMessageWaitingIndicator( hIndicator.Use(), cmsg ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CMessageWaitingIndicator::CMessageWaitingIndicator() : 
		m_MessageWaitingDevice( _TXT( "\\\\.\\MessageIndicator" ), Generic_Write, File_Share_Write, 0, Open_Existing, 0, 0 )
	{
	}

	//--------------------------------------------------------------------------------
	CMessageWaitingIndicator::~CMessageWaitingIndicator()
	{
	}

	//--------------------------------------------------------------------------------
	bool CMessageWaitingIndicator::Set( unsigned long cmsg )
	{
		bool bResult = false;
		bResult = m_Win32PowerHelper.SetMessageWaitingIndicator( m_MessageWaitingDevice.Handle(), cmsg );
		return bResult;
	}
*/
/*
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CMessageWaitingIndicator
	{
	public:

		CMessageWaitingIndicator();
		~CMessageWaitingIndicator();
		bool Set( unsigned long cmsg );

	protected:

		nsWin32::CPowerHelper m_Win32PowerHelper;
		nsWin32::CFile m_MessageWaitingDevice;
	};
*/
