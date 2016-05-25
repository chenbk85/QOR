//kErrorHandling

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

#include "WinQAPI/Kernel32.h"
#include "../SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	BOOL CKernel32::Beep( DWORD dwFreq, DWORD dwDuration )
	{
		_WINQ_SFCONTEXT( "CKernel32::Beep" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult = ::Beep( dwFreq, dwDuration );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	USHORT CKernel32::RtlCaptureStackBackTrace( ULONG FramesToSkip, ULONG FramesToCapture, void** BackTrace, PULONG BackTraceHash )
	{
		_WINQ_SFCONTEXT( "CKernel32::RtlCaptureStackBackTrace" );
		USHORT usResult = 0;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "RtlCaptureStackBackTrace" ), 0 ));
#else
#	if ( _WIN32_WINNT > 0x0501 )
		usResult = ::CaptureStackBackTrace( FramesToSkip, FramesToCapture, BackTrace, BackTraceHash );
#	else
		QOR_PP_UNREF4( BackTraceHash, BackTrace, FramesToCapture, FramesToSkip );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "RtlCaptureStackBackTrace" ), _T( "Windows XP" ), 0 ));
#	endif
#endif
		return usResult;
	}

	//--------------------------------------------------------------------------------
	void CKernel32::FatalAppExit( UINT uAction, LPCTSTR lpMessageText )
	{
		_WINQ_SFCONTEXT( "CKernel32::FatalAppExit" );
		::FatalAppExit( uAction, lpMessageText );
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::FormatMessage( DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPTSTR lpBuffer, DWORD nSize, va_list* Arguments )
	{
		_WINQ_SFCONTEXT( "CKernel32::FormatMessage" );
		CCheckReturn< DWORD, CCheckNonZero< DWORD > >::TType dwResult = ::FormatMessage( dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments );
		return dwResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetErrorMode(void)
	{
		_WINQ_SFCONTEXT( "CKernel32::GetErrorMode" );
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "GetErrorMode" ), 0 ));
		return 0;
#else
#	if ( _WIN32_WINNT >= 0x0600 )
		return ::GetErrorMode();
#	else
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "GetErrorMode" ), _T( "Windows Vista" ), 0 ));
		return 0;
#	endif
#endif
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::GetLastError(void)
	{
		return ::GetLastError();
	}

	//--------------------------------------------------------------------------------
	//Client Requires Windows XP 64-Bit Edition Version 2003.
	//Server Requires 64-bit edition of Windows Server 2003.
	void* CKernel32::RtlLookupFunctionEntry( ULONGLONG ControlPC, PULONGLONG ImageBase, PUNWIND_HISTORY_TABLE TargetGp )
	{
		_WINQ_SFCONTEXT( "CKernel32::RtlLookupFunctionEntry" );
		void* pResult = 0;
#	if ( _WIN32_WINNT >= 0x0501 && defined( _WIN64 ) )
		pResult = ::RtlLookupFunctionEntry( ControlPC, ImageBase, TargetGp );
#	else
		QOR_PP_UNREF3( TargetGp, ImageBase, ControlPC );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "RtlLookupFunctionEntry" ), _T( "Windows XP 64 bit edition" ), 0 ));
#	endif
		return pResult;
	}

	//--------------------------------------------------------------------------------
	//Client Requires Windows XP 64-Bit Edition Version 2003.
	//Server Requires 64-bit edition of Windows Server 2003.
	void* CKernel32::RtlPcToFileHeader( void* PcValue, void** BaseOfImage )
	{
		_WINQ_SFCONTEXT( "CKernel32::RtlPcToFileHeader" );
		void* pResult = 0;
#	if ( _WIN32_WINNT >= 0x0502 && defined( _WIN64 ) )
		pResult = ::RtlPcToFileHeader( PcValue, BaseOfImage );
#	else
		QOR_PP_UNREF2( BaseOfImage, PcValue );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "RtlPcToFileHeader" ), _T( "Windows Server 2003 64-Bit edition " ), 0 ));
#	endif
		return pResult;
	}

	//--------------------------------------------------------------------------------
	void CKernel32::RtlUnwind( void* TargetFrame, void* TargetIp, ::PEXCEPTION_RECORD ExceptionRecord, void* ReturnValue )
	{
#ifndef	__MINGW32__ //No exception stuff with MinGW yet
		_WINQ_USESAPI( RtlUnwind );
		voidCall< void*, void*, ::PEXCEPTION_RECORD, void* >( pFunc, TargetFrame, TargetIp, ExceptionRecord, ReturnValue );
#endif
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::SetErrorMode( UINT uMode )
	{
		_WINQ_SFCONTEXT( "CKernel32::SetErrorMode" );
		return ::SetErrorMode( uMode );
	}

	//--------------------------------------------------------------------------------
	void CKernel32::SetLastError( DWORD dwErrCode )
	{
		_WINQ_SFCONTEXT( "CKernel32::SetLastError" );
		::SetLastError( dwErrCode );
	}

	//--------------------------------------------------------------------------------
	HRESULT CKernel32::WerGetFlags( HANDLE hProcess, PDWORD pdwFlags )
	{
		_WINQ_SFCONTEXT( "CKernel32::WerGetFlags" );
		CCheckReturn< HRESULT, CSuccessCheck< > >::TType hr;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "WerGetFlags" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP1 )
		hr = ::WerGetFlags( hProcess, pdwFlags );
#	else
		QOR_PP_UNREF2( pdwFlags, hProcess );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WerGetFlags" ), _T( "Windows Vista Service Pack 1" ), 0 ));
#	endif
#endif
		return hr;
	}

	//--------------------------------------------------------------------------------
	HRESULT CKernel32::WerRegisterFile( PCWSTR pwzFile, ::WER_REGISTER_FILE_TYPE regFileType, DWORD dwFlags )
	{
		_WINQ_SFCONTEXT( "CKernel32::WerRegisterFile" );
		CCheckReturn< HRESULT, CSuccessCheck< > >::TType hr;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "WerRegisterFile" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP1 )
		hr = ::WerRegisterFile( pwzFile, regFileType, dwFlags );
#	else
		QOR_PP_UNREF3( dwFlags, regFileType, pwzFile );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WerRegisterFile" ), _T( "Windows Vista Service Pack 1" ), 0 ));
#	endif
#endif
		return hr;
	}

	//--------------------------------------------------------------------------------
	HRESULT CKernel32::WerRegisterMemoryBlock( void* pvAddress, DWORD dwSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::WerRegisterMemoryBlock" );
		CCheckReturn< HRESULT, CSuccessCheck< > >::TType hr;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "WerRegisterMemoryBlock" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP1 )
		hr = ::WerRegisterMemoryBlock( pvAddress, dwSize );
#	else
		QOR_PP_UNREF2( dwSize, pvAddress );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WerRegisterMemoryBlock" ), _T( "Windows Vista Service Pack 1" ), 0 ));
#	endif
#endif
		return hr;
	}

	//--------------------------------------------------------------------------------
	HRESULT CKernel32::WerSetFlags( DWORD dwFlags )
	{
		_WINQ_SFCONTEXT( "CKernel32::WerSetFlags" );
		CCheckReturn< HRESULT, CSuccessCheck< > >::TType hr;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "WerSetFlags" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP1 )
		hr = ::WerSetFlags( dwFlags );
#	else
		QOR_PP_UNREF( dwFlags );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WerSetFlags" ), _T( "Windows Vista Service Pack 1" ), 0 ));
#	endif
#endif
		return hr;
	}

	//--------------------------------------------------------------------------------
	HRESULT CKernel32::WerUnregisterFile( PCWSTR pwzFilePath )
	{
		_WINQ_SFCONTEXT( "CKernel32::WerUnregisterFile" );
		CCheckReturn< HRESULT, CSuccessCheck< > >::TType hr;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "WerUnregisterFile" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP1 )
		hr = ::WerUnregisterFile( pwzFilePath );
#	else
		QOR_PP_UNREF( pwzFilePath );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WerUnregisterFile" ), _T( "Windows Vista Service Pack 1" ), 0 ));
#	endif
#endif
		return hr;
	}

	//--------------------------------------------------------------------------------
	HRESULT CKernel32::WerUnregisterMemoryBlock( void* pvAddress )
	{
		_WINQ_SFCONTEXT( "CKernel32::WerUnregisterMemoryBlock" );
		CCheckReturn< HRESULT, CSuccessCheck< > >::TType hr;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "WerUnregisterMemoryBlock" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP1 )
		hr = ::WerUnregisterMemoryBlock( pvAddress );
#	else
		QOR_PP_UNREF( pvAddress );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WerUnregisterMemoryBlock" ), _T( "Windows Vista Service Pack 1" ), 0 ));
#	endif
#endif
		return hr;
	}

}//nsWinQAPI