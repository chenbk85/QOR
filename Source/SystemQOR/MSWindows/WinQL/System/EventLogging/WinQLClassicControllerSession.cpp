//WinQLClassicControllerSession.cpp

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

#include "WinQL/System/EventLogging/WinQLClassicControllerSession.h"
#include "WinQAPI/AdvAPI32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	CClassicEventControllerSession::CClassicEventControllerSession( CTString& LogFilePath, CTString& LogSessionName, const GUID& SessionGuid, const GUID& ProviderGuid ) 
		: m_AdvAPI32Library( CAdvAPI32::Instance() ), m_LogFilePath( LogFilePath ), m_LogSessionName( LogSessionName ), m_SessionGuid( SessionGuid ), m_ProviderGuid( ProviderGuid )
	{
		m_ulStatus = ERROR_SUCCESS;
		m_SessionHandle = 0;
		m_pSessionProperties = 0;
		m_BufferSize = 0;
		m_bTrace = true;

		// Allocate memory for the session properties. The memory must
		// be large enough to include the log file name and session name,
		// which get appended to the end of the session properties structure.
    
		m_BufferSize = sizeof( Event_Trace_Properties ) + ( m_LogFilePath.Len() * sizeof( mxTCHAR ) ) + ( m_LogSessionName.Len() * sizeof( mxTCHAR ) );
		m_pSessionProperties = reinterpret_cast< Event_Trace_Properties* >( malloc( m_BufferSize ) );

		if( 0 == m_pSessionProperties )
		{
			//TODO: Raise Error wprintf(L"Unable to allocate %d bytes for properties structure.\n", BufferSize);
			return;
		}
    
		// Set the session properties. You only append the log file name
		// to the properties structure; the StartTrace function appends
		// the session name for you.

		ZeroMemory( m_pSessionProperties, m_BufferSize );
		m_pSessionProperties->Wnode.BufferSize = m_BufferSize;
		m_pSessionProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
		m_pSessionProperties->Wnode.ClientContext = 1; //QPC clock resolution
		m_pSessionProperties->Wnode.Guid = m_SessionGuid; 
		m_pSessionProperties->LogFileMode = Event_Trace_File_Mode_Circular | Event_Trace_Use_Paged_Memory;
		m_pSessionProperties->MaximumFileSize = 5;  // 5 MB
		m_pSessionProperties->LoggerNameOffset = sizeof( Event_Trace_Properties );
		m_pSessionProperties->LogFileNameOffset = sizeof( Event_Trace_Properties ) + ( m_LogSessionName.Len() * sizeof( mxTCHAR ) ); 

		memcpy( ( m_pSessionProperties + m_pSessionProperties->LogFileNameOffset ), m_LogFilePath.GetBuffer(), ( m_LogFilePath.Len() * sizeof( mxTCHAR ) ) );

		// Create the trace session.
		m_ulStatus = m_AdvAPI32Library.StartTrace( (PTRACEHANDLE)&m_SessionHandle, m_LogSessionName.GetBuffer(), reinterpret_cast< ::PEVENT_TRACE_PROPERTIES >( m_pSessionProperties ) );
		if( ERROR_SUCCESS != m_ulStatus )
		{
			//TODO: Raise Error wprintf(L"StartTrace() failed with %lu\n", status);
			return;
		}

		// Enable the providers that you want to log events to your session.

		m_ulStatus = m_AdvAPI32Library.EnableTrace( m_bTrace, 0, Trace_Level_Information, (LPCGUID)&m_ProviderGuid, m_SessionHandle );

		if( ERROR_SUCCESS != m_ulStatus )
		{
			//TODO: Raise Error wprintf(L"EnableTrace() failed with %lu\n", status);
			m_bTrace = false;
			return;
		}

	}

	//--------------------------------------------------------------------------------
	CClassicEventControllerSession::~CClassicEventControllerSession()
	{
		if( m_SessionHandle )
		{
			if( m_bTrace )
			{
				m_ulStatus = m_AdvAPI32Library.EnableTrace( false, 0, 0, (LPCGUID)&m_ProviderGuid, m_SessionHandle );
			}

			m_ulStatus = m_AdvAPI32Library.ControlTrace( m_SessionHandle, m_LogSessionName.GetBuffer(), reinterpret_cast< ::PEVENT_TRACE_PROPERTIES >( m_pSessionProperties ), Event_Trace_Control_Stop );

			if( ERROR_SUCCESS != m_ulStatus )
			{
				//TODO: Raise Error
			}
		}

		if( m_pSessionProperties )
		{
			free( m_pSessionProperties );
		}
	}

}//nsWin32
