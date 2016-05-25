//WinQLInfo.cpp

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

#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/System/Info/WinQLInfo.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CSystemInfo );
	__QOR_IMPLEMENT_OCLASS_LUID( CSystemInfo::CParameters );

	//--------------------------------------------------------------------------------
	CSystemInfo::CSystemInfo() : m_bAcquiredVersion( false )
	{
		_WINQ_FCONTEXT( "CSystemInfo::CSystemInfo" );
	}

	//--------------------------------------------------------------------------------
	CSystemInfo::CSystemInfo( const CSystemInfo& src ) : m_bAcquiredVersion( src.m_bAcquiredVersion )
	{
		_WINQ_FCONTEXT( "CSystemInfo::CSystemInfo" );
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CSystemInfo& CSystemInfo::operator = ( const CSystemInfo& src )
	{
		_WINQ_FCONTEXT( "CSystemInfo::operator =" );

		if( &src != this )
		{
			m_bWin9x = src.m_bWin9x;
			m_dwMajorVersion = src.m_dwMajorVersion;
			m_dwMinorVersion = src.m_dwMinorVersion;
			m_dwBuild = src.m_dwBuild;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CSystemInfo::~CSystemInfo()
	{
		_WINQ_FCONTEXT( "CSystemInfo::~CSystemInfo" );
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::IsWindows98orME()
	{
		_WINQ_FCONTEXT( "CSystemInfo::IsWindows98orME" );
		bool bResult = false;
		__QOR_PROTECT
		{
			if( !m_bAcquiredVersion )
			{
				AcquireVersion();
			}

			bResult = m_bWin9x && ( m_dwBuild == 0 ) && ( m_dwMajorVersion == 4 ) && ( m_dwMinorVersion > 0 );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSystemInfo::GetMajorVersion()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetMajorVersion" );
		__QOR_PROTECT
		{
			if( !m_bAcquiredVersion )
			{
				AcquireVersion();
			}
		}__QOR_ENDPROTECT
		return m_dwMajorVersion;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSystemInfo::GetMinorVersion()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetMinorVersion" );
		__QOR_PROTECT
		{
			if( !m_bAcquiredVersion )
			{
				AcquireVersion();
			}
		}__QOR_ENDPROTECT
		return m_dwMinorVersion;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSystemInfo::GetBuild()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetBuild" );
		__QOR_PROTECT
		{
			if( !m_bAcquiredVersion )
			{
				AcquireVersion();
			}
		}__QOR_ENDPROTECT
		return m_dwBuild;
	}

	//--------------------------------------------------------------------------------
	unsigned int CSystemInfo::GetOSVerNumber()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetOSVerNumber" );
		unsigned int uiVersion = 0;
		__QOR_PROTECT
		{
			uiVersion = GetBuild() & 0x07fff;
		}__QOR_ENDPROTECT
		return uiVersion;
	}

	//--------------------------------------------------------------------------------
	CSystemInfo::CParameters& CSystemInfo::Parameters()
	{
		_WINQ_FCONTEXT( "CSystemInfo::Parameters" );
		return m_Parameters;
	}

	//--------------------------------------------------------------------------------
	//Converts a DNS - style host name to a NetBIOS - style computer name.
	CTString CSystemInfo::DnsHostnameToComputerName( const TCHAR* Hostname )
	{
		_WINQ_FCONTEXT( "CSystemInfo::DnsHostnameToComputerName" );
		CTString strComputerName;
		__QOR_PROTECT
		{
			unsigned long ulSize = nsWin32::Max_ComputerName_Length + 1;
			m_Win32SysInfo.DnsHostnameToComputerNameT( Hostname, strComputerName.GetBufferSetLength( static_cast< unsigned short >( ulSize ) ), &ulSize );
		}__QOR_ENDPROTECT
		return strComputerName;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< byte > CSystemInfo::EnumSystemFirmwareTables( unsigned long FirmwareTableProviderSignature, unsigned int& uiByteCount )
	{
		_WINQ_FCONTEXT( "CSystemInfo::EnumSystemFirmwareTables" );
		nsCodeQOR::CTLRef< byte > Result;
		__QOR_PROTECT
		{
			unsigned int uiBufferSizeNeeded = m_Win32SysInfo.EnumSystemFirmwareTables( FirmwareTableProviderSignature, 0, 0 );
			void* pFirmwareTableBuffer = new unsigned char[ uiBufferSizeNeeded ];
			uiByteCount = m_Win32SysInfo.EnumSystemFirmwareTables( FirmwareTableProviderSignature, pFirmwareTableBuffer, uiBufferSizeNeeded );
			Result = nsCodeQOR::CTLRef< byte >( reinterpret_cast< byte* >( pFirmwareTableBuffer ), true );
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< byte > CSystemInfo::EnumSystemFirmwareTablesFIRM( unsigned int& uiByteCount )
	{
		_WINQ_FCONTEXT( "CSystemInfo::EnumSystemFirmwareTablesFIRM" );
		nsCodeQOR::CTLRef< byte > Result;
		__QOR_PROTECT
		{
			unsigned long ulFIRM = 0x46000000 | 0x00490000 | 0x00005200 | 0x0000004D; //FIRM
			unsigned int uiBufferSizeNeededFIRM = m_Win32SysInfo.EnumSystemFirmwareTables( ulFIRM, 0, 0 );
			void* pFirmwareTableBuffer = new unsigned char[ uiBufferSizeNeededFIRM ];
			uiByteCount = m_Win32SysInfo.EnumSystemFirmwareTables( ulFIRM, pFirmwareTableBuffer, uiBufferSizeNeededFIRM );
			Result = nsCodeQOR::CTLRef< byte >( reinterpret_cast< byte* >(pFirmwareTableBuffer), true );
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< unsigned long > CSystemInfo::EnumSystemFirmwareTablesACPI( unsigned int& uiTableCount )
	{
		_WINQ_FCONTEXT( "CSystemInfo::EnumSystemFirmwareTablesACPI" );
		nsCodeQOR::CTLRef< unsigned long > Result;
		__QOR_PROTECT
		{
			unsigned long ulACPI = 0x41000000 | 0x00430000 | 0x00005000 | 0x00000049; //ACPI
			unsigned int uiBufferSizeNeededACPI = m_Win32SysInfo.EnumSystemFirmwareTables( ulACPI, 0, 0 );
			void* pFirmwareTableBuffer = new unsigned char[ uiBufferSizeNeededACPI ];
			uiTableCount = m_Win32SysInfo.EnumSystemFirmwareTables( ulACPI, pFirmwareTableBuffer, uiBufferSizeNeededACPI ) / sizeof( unsigned long );
			Result = nsCodeQOR::CTLRef< unsigned long >( reinterpret_cast< unsigned long* >( pFirmwareTableBuffer ), true );
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< byte > CSystemInfo::EnumSystemFirmwareTablesRSMB( unsigned int& uiByteCount )
	{
		_WINQ_FCONTEXT( "CSystemInfo::EnumSystemFirmwareTablesRSMB" );
		nsCodeQOR::CTLRef< byte > Result;
		__QOR_PROTECT
		{
			unsigned long ulRSMB = 0x52000000 | 0x00530000 | 0x00004D00 | 0x00000042; //RSMB
			unsigned int uiBufferSizeNeededRSMB = m_Win32SysInfo.EnumSystemFirmwareTables( ulRSMB, 0, 0 );
			void* pFirmwareTableBuffer = new unsigned char[ uiBufferSizeNeededRSMB ];
			uiByteCount = m_Win32SysInfo.EnumSystemFirmwareTables( ulRSMB, pFirmwareTableBuffer, uiBufferSizeNeededRSMB );
			Result = nsCodeQOR::CTLRef< byte >( reinterpret_cast< byte* >( pFirmwareTableBuffer ), true );
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::ExpandEnvironmentStrings( const TCHAR* lpSrc )
	{
		_WINQ_FCONTEXT( "CSystemInfo::ExpandEnvironmentStrings" );
		CTString strExpandedString;
		__QOR_PROTECT
		{
			unsigned long ulCharCount = 0;
			ulCharCount = m_Win32SysInfo.ExpandEnvironmentStringsT( lpSrc, 0, ulCharCount );
			ulCharCount = m_Win32SysInfo.ExpandEnvironmentStringsT( lpSrc, strExpandedString.GetBufferSetLength( static_cast< unsigned short >( ulCharCount ) + 1 ), ulCharCount );
		}__QOR_ENDPROTECT
		return strExpandedString;
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::GetComputerName()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetComputerName" );
		bool bResult = false;
		CTString strComputerName;
		unsigned long ulSize = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetComputerNameT( 0, &ulSize );
			bResult = m_Win32SysInfo.GetComputerNameT( strComputerName.GetBufferSetLength( static_cast< unsigned short >( ulSize ) ), &ulSize );
			strComputerName.ReleaseBuffer();
		}__QOR_ENDPROTECT
		return strComputerName;
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::GetComputerNameEx( eComputerNameFormat NameType )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetComputerNameEx" );
		bool bResult = false;
		CTString strComputerName;
		unsigned long ulSize = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetComputerNameExT( NameType, 0, &ulSize );
			bResult = m_Win32SysInfo.GetComputerNameExT( NameType, strComputerName.GetBufferSetLength( static_cast< unsigned short >( ulSize ) ), &ulSize );
			strComputerName.ReleaseBuffer();
		}__QOR_ENDPROTECT
		return strComputerName;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSystemInfo::GetFirmwareEnvironmentVariable( const TCHAR* lpName, const TCHAR* lpGuid, void* pBuffer, unsigned long nSize )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetFirmwareEnvironmentVariable" );
		unsigned long ulResult = 0;
		__QOR_PROTECT
		{
			ulResult = m_Win32SysInfo.GetFirmwareEnvironmentVariableT( lpName, lpGuid, pBuffer, nSize );
		}__QOR_ENDPROTECT
		return ulResult;
	}

	//--------------------------------------------------------------------------------
	void CSystemInfo::GetNativeSystemInfo( SystemInfo* pSystemInfo )
	{			
		_WINQ_FCONTEXT( "CSystemInfo::GetNativeSystemInfo" );
		__QOR_PROTECT
		{
			if( pSystemInfo )
			{
				m_Win32SysInfo.GetNativeSystemInfo( pSystemInfo );
			}
			else
			{
				//TODO: Raise NULL pointer error
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	eProductType CSystemInfo::GetProductInfo( unsigned long dwOSMajorVersion, unsigned long dwOSMinorVersion, unsigned long dwSpMajorVersion, unsigned long dwSpMinorVersion )
	{			
		_WINQ_FCONTEXT( "CSystemInfo::GetProductInfo" );
		unsigned long ulReturnedProductType;
		__QOR_PROTECT
		{			
			m_Win32SysInfo.GetProductInfo( dwOSMajorVersion, dwOSMinorVersion, dwSpMajorVersion, dwSpMinorVersion, &ulReturnedProductType );
		}__QOR_ENDPROTECT
		return static_cast< eProductType >( ulReturnedProductType );
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::GetSystemDirectory()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetSystemDirectory" );
		CTString strSystemDirectory;
		__QOR_PROTECT
		{
			strSystemDirectory = m_Win32SysInfo.GetSystemDirectoryT();			
		}__QOR_ENDPROTECT
		return strSystemDirectory;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< byte > CSystemInfo::GetSystemFirmwareTable( unsigned long FirmwareTableProviderSignature, unsigned long FirmwareTableID, unsigned int& uiByteCount  )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetSystemFirmwareTable" );
		nsCodeQOR::CTLRef< byte > Result;
		__QOR_PROTECT
		{
			uiByteCount = 0;
			uiByteCount = m_Win32SysInfo.GetSystemFirmwareTable( FirmwareTableProviderSignature, FirmwareTableID, 0, uiByteCount );
			byte* pFirmwareTableBuffer = new byte[ uiByteCount ];
			uiByteCount = m_Win32SysInfo.GetSystemFirmwareTable( FirmwareTableProviderSignature, FirmwareTableID, pFirmwareTableBuffer, uiByteCount ); 
			Result = nsCodeQOR::CTLRef< byte >( pFirmwareTableBuffer, true );
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	void CSystemInfo::GetSystemInfo( SystemInfo* lpSystemInfo )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetSystemInfo" );
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetSystemInfo( lpSystemInfo );
		}__QOR_ENDPROTECT
	}

	//------------------------------------------------------------------------------
	void CSystemInfo::GetSystemRegistryQuota( unsigned long& ulQuotaAllowed, unsigned long& ulQuotaUsed )
	{			
		_WINQ_FCONTEXT( "CSystemInfo::GetSystemRegistryQuota" );
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetSystemRegistryQuota( &ulQuotaAllowed, &ulQuotaUsed );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::GetSystemWindowsDirectory()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetSystemWindowsDirectory" );
		return m_Win32SysInfo.GetSystemWindowsDirectoryT();
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::GetSystemWow64Directory()
	{			
		_WINQ_FCONTEXT( "CSystemInfo::GetSystemWow64Directory" );
		return m_Win32SysInfo.GetSystemWow64DirectoryT();
	}

	//--------------------------------------------------------------------------------
	unsigned long CSystemInfo::GetVersion(void)
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetVersion" );
		unsigned long ulResult = 0;
		__QOR_PROTECT
		{
			ulResult = m_Win32SysInfo.GetVersion();
		}__QOR_ENDPROTECT
		return ulResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::GetVersionExT( OSVersionInfo* lpVersionInfo )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetVersionExT" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32SysInfo.GetVersionExT( lpVersionInfo );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::GetWindowsDirectory()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetWindowsDirectory" );
		return m_Win32SysInfo.GetWindowsDirectoryT();
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::IsProcessorFeaturePresent( nsWin32::eProcessorFeature ProcessorFeature )
	{
		_WINQ_FCONTEXT( "CSystemInfo::IsProcessorFeaturePresent" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32SysInfo.IsProcessorFeaturePresent( ProcessorFeature );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::SetComputerName( const TCHAR* lpComputerName )
	{
		_WINQ_FCONTEXT( "CSystemInfo::SetComputerName" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32SysInfo.SetComputerNameT( lpComputerName );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::SetComputerNameEx( eComputerNameFormat NameType, const TCHAR* lpBuffer )
	{			
		_WINQ_FCONTEXT( "CSystemInfo::SetComputerNameEx" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32SysInfo.SetComputerNameExT( NameType, lpBuffer );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::SetFirmwareEnvironmentVariable( const TCHAR* lpName, const TCHAR* lpGuid, void* pBuffer, unsigned long nSize )
	{
		_WINQ_FCONTEXT( "CSystemInfo::SetFirmwareEnvironmentVariable" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32SysInfo.SetFirmwareEnvironmentVariableT( lpName, lpGuid, pBuffer, nSize );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemInfo::VerifyVersionInfo( OSVersionInfoEx& VersionInfo, unsigned long ulTypeMask, Cmp_unsigned_long_long ullConditionMask )
	{
		_WINQ_FCONTEXT( "CSystemInfo::VerifyVersionInfo" );
		bool bResult = false;
		__QOR_PROTECT
		{
			VersionInfo.dwOSVersionInfoSize = sizeof( OSVersionInfoEx );
			bResult = m_Win32SysInfo.VerifyVersionInfoT( &VersionInfo, ulTypeMask, ullConditionMask );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	Cmp_unsigned_long_long CSystemInfo::VerSetConditionMask( Cmp_unsigned_long_long ullConditionMask, unsigned long ulTypeBitMask, unsigned char ucConditionMask )
	{			
		_WINQ_FCONTEXT( "CSystemInfo::VerSetConditionMask" );
		Cmp_unsigned_long_long ullResult = 0;
		__QOR_PROTECT
		{
			ullResult = m_Win32SysInfo.VerSetConditionMask( ullConditionMask, ulTypeBitMask, ucConditionMask );
		}__QOR_ENDPROTECT
		return ullResult;
	}

	//--------------------------------------------------------------------------------
	CTString CSystemInfo::EnumerateLocalComputerNames( eComputerNameType NameType, unsigned long ulFlags, unsigned long& ulNameCount, unsigned int& uiCharCount )
	{			
		_WINQ_FCONTEXT( "CSystemInfo::EnumerateLocalComputerNames" );
		CTString strNames;		
		__QOR_PROTECT
		{
				m_Win32SysInfo.EnumerateLocalComputerNames( NameType, ulFlags, 0, uiCharCount );
				ulNameCount = m_Win32SysInfo.EnumerateLocalComputerNames( NameType, ulFlags, strNames.GetBufferSetLength( static_cast< unsigned short >( uiCharCount ) ), uiCharCount );
		}__QOR_ENDPROTECT
		return strNames;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< SystemLogicalProcessorInformation > CSystemInfo::GetLogicalProcessorInformation( unsigned int& uiCount )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetLogicalProcessorInformation" );
		nsCodeQOR::CTLRef< SystemLogicalProcessorInformation > Ref;
		__QOR_PROTECT
		{
			uiCount = 0;
			Ref = m_Win32SysInfo.GetLogicalProcessorInformation( uiCount );
		}__QOR_ENDPROTECT
		return Ref;
	}

	//--------------------------------------------------------------------------------
	Cmp_unsigned_long_long CSystemInfo::GetNumaAvailableMemoryNode( Cmp_unsigned__int8 uiNode )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetNumaAvailableMemoryNode" );
		Cmp_unsigned_long_long Result = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetNumaAvailableMemoryNode( uiNode, &Result );
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSystemInfo::GetNumaHighestNodeNumber()
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetNumaHighestNodeNumber" );
		unsigned long ulResult = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetNumaHighestNodeNumber( &ulResult );
		}__QOR_ENDPROTECT
		return ulResult;
	}

	//--------------------------------------------------------------------------------
	Cmp_unsigned_long_long CSystemInfo::GetNumaNodeProcessorMask( Cmp_unsigned__int8 uiNode )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetNumaNodeProcessorMask" );
		Cmp_unsigned_long_long ulResult = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetNumaNodeProcessorMask( uiNode, &ulResult );
		}__QOR_ENDPROTECT
		return ulResult;
	}

	//--------------------------------------------------------------------------------
	Cmp_unsigned__int8 CSystemInfo::GetNumaProcessorNode( Cmp_unsigned__int8 uiProcessor )
	{
		_WINQ_FCONTEXT( "CSystemInfo::GetNumaProcessorNode" );
		Cmp_unsigned__int8 uiResult = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetNumaProcessorNode( uiProcessor, &uiResult );
		}__QOR_ENDPROTECT
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	Cmp_unsigned__int8 CSystemInfo::GetNumaProximityNode( unsigned long ProximityId )
	{		
		_WINQ_FCONTEXT( "CSystemInfo::GetNumaProximityNode" );
		Cmp_unsigned__int8 uiResult = 0;
		__QOR_PROTECT
		{
			m_Win32SysInfo.GetNumaProximityNode( ProximityId, &uiResult );
		}__QOR_ENDPROTECT
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	void CSystemInfo::AcquireVersion( void )
	{
		_WINQ_FCONTEXT( "CSystemInfo::AcquireVersion" );

		__QOR_PROTECT
		{
			unsigned long dwPackedVersion = m_Win32SysInfo.GetVersion();
						
			// Get the Windows version.
			m_dwMajorVersion = (unsigned long)(LoByte(LoWord(dwPackedVersion)));
			m_dwMinorVersion = (unsigned long)(HiByte(LoWord(dwPackedVersion)));

			// Get the build number.
			if ( dwPackedVersion < 0x80000000 )
			{
				m_bWin9x = false;
				m_dwBuild = (unsigned long)(HiWord(dwPackedVersion));
			}
			else // Windows Me/98/95
			{
				m_bWin9x = true;
				m_dwBuild = 0;
			}

			m_bAcquiredVersion = true;
		}__QOR_ENDPROTECT
	}

}//nsWin32