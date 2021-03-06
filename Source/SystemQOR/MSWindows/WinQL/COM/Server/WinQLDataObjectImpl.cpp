//WinQLDataObjectImpl.cpp

// Copyright Querysoft Limited 2013, 2015
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

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/COM/DataObjectImpl.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_COMCLASS_ID( CDataObjectImpl, IDataObject );

	//--------------------------------------------------------------------------------
	CDataObjectImpl::CDataObjectImpl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase< IDataObject >( pImpl )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::CDataObjectImpl" );
		RegisterInterface( dynamic_cast< IDataObject* >( this ) );
	}

	//--------------------------------------------------------------------------------
	CDataObjectImpl::~CDataObjectImpl()
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::~CDataObjectImpl" );
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::OleSetClipboard( void )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::OleSetClipboard" );
		long lResult = -1;
		__QOR_PROTECT
		{
			IDataObject* pDataObject = dynamic_cast< IDataObject* >( this );
			lResult = m_Library.OleSetClipboard( reinterpret_cast< ::LPDATAOBJECT >( pDataObject ) );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::OleFlushClipboard( void )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::OleFlushClipboard" );
		long lResult = -1;
		__QOR_PROTECT
		{
			lResult = m_Library.OleFlushClipboard();
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::OleIsCurrentClipboard( void )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::OleIsCurrentClipboard" );
		long lResult = -1;
		__QOR_PROTECT
		{
			IDataObject* pDataObject = dynamic_cast< IDataObject* >( this );
			lResult = m_Library.OleIsCurrentClipboard( reinterpret_cast< ::LPDATAOBJECT >( pDataObject ) );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::GetData( FormatEtc* pFormatEtcIn, StgMedium* pmedium )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::GetData" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::GetDataHere( FormatEtc* pFormatEtc, StgMedium* pmedium )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::GetDataHere" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::QueryGetData( FormatEtc* pFormatEtc )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::QueryGetData" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::GetCanonicalFormatEtc( FormatEtc* pformatectIn, FormatEtc* pFormatEtcOut )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::GetCanonicalFormatEtc" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::SetData( FormatEtc* pFormatEtc, StgMedium* pmedium, int fRelease )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::SetData" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::EnumFormatEtc( unsigned long ulDirection, IEnumFORMATETC** ppenumFormatEtc )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::EnumFormatEtc" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::DAdvise( FormatEtc* pFormatEtc, unsigned long advf, IAdviseSink* pAdvSink, unsigned long* pdwConnection )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::DAdvise" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::DUnadvise( unsigned long dwConnection )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::DUnadvise" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDataObjectImpl::EnumDAdvise( IEnumSTATDATA** ppenumAdvise )
	{
		_WINQ_FCONTEXT( "CDataObjectImpl::EnumDAdvise" );
		long lResult = E_NOTIMPL;
		return lResult;
	}

}//nsWin32

