//ExtendPropertySheetImpl.cpp

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

//Base class implementation for MMC snapin ExtendPropertySheetImpl

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/COM/MMC/ExtendPropertySheetImpl.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_COMCLASS_ID( CExtendPropertySheetImpl, IExtendPropertySheet );

	//--------------------------------------------------------------------------------
	CExtendPropertySheetImpl::CExtendPropertySheetImpl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase< IExtendPropertySheet >( pImpl )
	{
		_WINQ_FCONTEXT( "CExtendPropertySheetImpl::CExtendPropertySheetImpl" );
		RegisterInterface( dynamic_cast< IExtendPropertySheet* >( this ) );
	}

	//--------------------------------------------------------------------------------
	CExtendPropertySheetImpl::~CExtendPropertySheetImpl()
	{
		_WINQ_FCONTEXT( "CExtendPropertySheetImpl::~CExtendPropertySheetImpl" );
	}

	//--------------------------------------------------------------------------------
    long CExtendPropertySheetImpl::CreatePropertyPages( IPropertySheetCallback* lpProvider, Cmp_long_ptr handle, IDataObject* lpIDataObject )
	{
		_WINQ_FCONTEXT( "CExtendPropertySheetImpl::CreatePropertyPages" );
		return E_NOTIMPL;
	}

	//--------------------------------------------------------------------------------
    long CExtendPropertySheetImpl::QueryPagesFor( IDataObject* lpDataObject )
	{
		_WINQ_FCONTEXT( "CExtendPropertySheetImpl::QueryPagesFor" );
		return E_NOTIMPL;
	}

	
	__QOR_IMPLEMENT_COMCLASS_ID( CExtendPropertySheet2Impl, IExtendPropertySheet2 );

	//--------------------------------------------------------------------------------
	CExtendPropertySheet2Impl::CExtendPropertySheet2Impl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase< IExtendPropertySheet2, CExtendPropertySheetImpl >( pImpl )
	{
		_WINQ_FCONTEXT( "CExtendPropertySheet2Impl::CExtendPropertySheet2Impl" );
		RegisterInterface( dynamic_cast< IExtendPropertySheet2* >( this ) );
	}

	//--------------------------------------------------------------------------------
	CExtendPropertySheet2Impl::~CExtendPropertySheet2Impl()
	{
		_WINQ_FCONTEXT( "CExtendPropertySheet2Impl::~CExtendPropertySheet2Impl" );
	}

	//--------------------------------------------------------------------------------
	long CExtendPropertySheet2Impl::GetWatermarks( IDataObject* lpIDataObject, void** lphWatermark, void** lphHeader, void** lphPalette, int* bStretch)
	{
		_WINQ_FCONTEXT( "CExtendPropertySheet2Impl::GetWatermarks" );
		return E_NOTIMPL;
	}

}//nsWin32

