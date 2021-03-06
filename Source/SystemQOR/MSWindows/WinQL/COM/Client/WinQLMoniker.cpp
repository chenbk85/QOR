//WinQLMoniker.cpp

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
#include "WinQL/COM/Moniker.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_OCLASS_LUID( CMoniker );
	__QOR_IMPLEMENT_OCLASS_LUID( CAntiMoniker );
	__QOR_IMPLEMENT_OCLASS_LUID( CClassMoniker );
	__QOR_IMPLEMENT_OCLASS_LUID( CFileMoniker );
	__QOR_IMPLEMENT_OCLASS_LUID( CItemMoniker );
	__QOR_IMPLEMENT_OCLASS_LUID( CObjRefMoniker );
	__QOR_IMPLEMENT_OCLASS_LUID( CPointerMoniker );

	//--------------------------------------------------------------------------------
	CMoniker::CMoniker()
	{
		_WINQ_FCONTEXT( "CMoniker::CMoniker" );
	}

	//--------------------------------------------------------------------------------
	CMoniker::CMoniker( IBindCtx* pbctx, const wchar_t* szUserName, unsigned long* pchEaten )
	{
		_WINQ_FCONTEXT( "CMoniker::CMoniker" );
		m_lStatus = m_Library.MkParseDisplayName( reinterpret_cast< LPBC >( pbctx ), szUserName, pchEaten, reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CMoniker::CMoniker( void* pFirst, void* pRest )
	{
		_WINQ_FCONTEXT( "CMoniker::CMoniker" );
		m_lStatus = m_Library.CreateGenericComposite( reinterpret_cast< LPMONIKER >( pFirst ), reinterpret_cast< LPMONIKER >( pRest ), reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CMoniker::~CMoniker()
	{
		_WINQ_FCONTEXT( "CMoniker::~CMoniker" );
	}

	//--------------------------------------------------------------------------------
	long CMoniker::Bind( unsigned long grfOpt, const GUID& iidResult, void** ppvResult )
	{
		_WINQ_FCONTEXT( "CMoniker::Bind" );
		return m_Library.BindMoniker( reinterpret_cast< LPMONIKER >( m_p ), grfOpt, reinterpret_cast< REFIID >( iidResult ), ppvResult );
	}

	//--------------------------------------------------------------------------------
	CAntiMoniker::CAntiMoniker() : CMoniker()
	{
		_WINQ_FCONTEXT( "CAntiMoniker::CAntiMoniker" );
		m_lStatus = m_Library.CreateAntiMoniker( reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CAntiMoniker::~CAntiMoniker()
	{
		_WINQ_FCONTEXT( "CAntiMoniker::~CAntiMoniker" );
	}
		
		
	//--------------------------------------------------------------------------------
	CClassMoniker::CClassMoniker( const nsWin32::GUID& rclsid ) : CMoniker()
	{
		_WINQ_FCONTEXT( "CClassMoniker::CClassMoniker" );
		m_lStatus = m_Library.CreateClassMoniker( reinterpret_cast< const ::IID& >( rclsid ), reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CClassMoniker::~CClassMoniker()
	{
		_WINQ_FCONTEXT( "CClassMoniker::~CClassMoniker" );
	}

		
	//--------------------------------------------------------------------------------
	CFileMoniker::CFileMoniker( const wchar_t* lpszPathName ) : CMoniker()
	{
		_WINQ_FCONTEXT( "CFileMoniker::CFileMoniker" );
		m_lStatus = m_Library.CreateFileMoniker( lpszPathName, reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CFileMoniker::~CFileMoniker()
	{
		_WINQ_FCONTEXT( "CFileMoniker::~CFileMoniker" );
	}

	//--------------------------------------------------------------------------------
	CItemMoniker::CItemMoniker( const wchar_t* lpszDelim, const wchar_t* lpszItem )
	{
		_WINQ_FCONTEXT( "CItemMoniker::CItemMoniker" );
		m_lStatus = m_Library.CreateItemMoniker( lpszDelim, lpszItem, reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CItemMoniker::~CItemMoniker()
	{
		_WINQ_FCONTEXT( "CItemMoniker::~CItemMoniker" );
	}

	//--------------------------------------------------------------------------------
	CObjRefMoniker::CObjRefMoniker( void* punk )
	{
		_WINQ_FCONTEXT( "CObjRefMoniker::CObjRefMoniker" );
		m_lStatus = m_Library.CreateObjrefMoniker( reinterpret_cast< LPUNKNOWN >( punk ), reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CObjRefMoniker::~CObjRefMoniker()
	{
		_WINQ_FCONTEXT( "CObjRefMoniker::~CObjRefMoniker" );
	}

	//--------------------------------------------------------------------------------
	CPointerMoniker::CPointerMoniker( void* punk )
	{
		_WINQ_FCONTEXT( "CPointerMoniker::CPointerMoniker" );
		m_lStatus = m_Library.CreatePointerMoniker( reinterpret_cast< LPUNKNOWN >( punk ), reinterpret_cast< LPMONIKER* >( &m_p ) );
	}

	//--------------------------------------------------------------------------------
	CPointerMoniker::~CPointerMoniker()
	{
		_WINQ_FCONTEXT( "CPointerMoniker::~CPointerMoniker" );
	}

}//nsWin32

