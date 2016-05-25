//Storage.h

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

#ifndef WINQL_COM_STORAGE_H_3
#define WINQL_COM_STORAGE_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/Definitions/Interfaces.h"
#include "WinQL/COM/ILockBytesOnHGlobal.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CPropertySetStorageClient : CComPtr< IPropertySetStorage >
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CPropertySetStorageClient );

		CPropertySetStorageClient( IStorage* pStorage );
		virtual ~CPropertySetStorageClient();			

	private:

		CPropertySetStorageClient();
		CPropertySetStorageClient( const CPropertySetStorageClient& );
		CPropertySetStorageClient& operator = ( const CPropertySetStorageClient& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CPropertyStorageClient : public CComPtr< IPropertyStorage >
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CPropertyStorageClient );

		CPropertyStorageClient( IUnknown* pUnk, const GUID& fmtid, const GUID* pclsid, unsigned long grfFlags, unsigned long dwReserved );
		CPropertyStorageClient( IUnknown* pUnk, const GUID& fmtid, unsigned long grfFlags, unsigned long dwReserved );

	private:

		CPropertyStorageClient();
		CPropertyStorageClient( const CPropertyStorageClient& );
		CPropertyStorageClient& operator = ( const CPropertyStorageClient& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CStorageClient : public CComPtr< IStorage >
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CStorageClient );

		CStorageClient();
		CStorageClient( IFillLockBytes* ppflb, unsigned long grfmode, unsigned long asyncFlags );
		CStorageClient( const wchar_t* pwcsName, IStorage* pstgPriority, unsigned long grfMode, wchar_t** snbExclude, unsigned long reserved );
		CStorageClient( ILockBytes* plkbyt,	IStorage* pStgPriority, unsigned long grfMode, wchar_t** snbExclude, unsigned long reserved );
		CStorageClient( ILockBytes* plkbyt, unsigned long grfMode );
		CStorageClient( const wchar_t* pwcsName, unsigned long grfMode );
		virtual ~CStorageClient();

		long OleCreateFromFile( const GUID& rclsid, const wchar_t* lpszFileName, const GUID& riid, unsigned long renderopt, FormatEtc* lpFormatEtc, IOleClientSite* pClientSite, void** ppvObj );
		long OleCreateFromFileEx( const GUID& rclsid, const wchar_t* lpszFileName, const GUID& riid, unsigned long dwFlags, unsigned long renderopt, unsigned long cFormats, unsigned long* rgAdvf, FormatEtc* rgFormatEtc, IAdviseSink* lpAdviseSink, unsigned long* rgdwConnection, IOleClientSite* pClientSite, void** ppvObj );
		long OleCreateLink( IMoniker* pmkLinkSrc, const GUID& riid, unsigned long renderopt, FormatEtc* lpFormatEtc, IOleClientSite* pClientSite, void** ppvObj	);
		long OleCreateLinkEx( IMoniker* pmkLinkSrc, const GUID& riid, unsigned long dwFlags, unsigned long renderopt, unsigned long cFormats, unsigned long* rgAdvf, FormatEtc* rgFormatEtc, IAdviseSink* lpAdviseSink, unsigned long* rgdwConnection, IOleClientSite* pClientSite, void** ppvObj );
		long OleCreateLinkToFile( const wchar_t* lpszFileName, const GUID& riid, unsigned long renderopt, FormatEtc* lpFormatEtc, IOleClientSite* pClientSite, void** ppvObj );
		long OleCreateLinkToFileEx( const wchar_t* lpszFileName, const GUID& riid, unsigned long dwFlags, unsigned long renderopt, unsigned long cFormats, unsigned long* rgAdvf, FormatEtc* rgFormatEtc, IAdviseSink* lpAdviseSink, unsigned long* rgdwConnection, IOleClientSite* pClientSite, void** ppvObj );
		long OleDoAutoConvert( GUID* pClsidNew );
		long OleLoad( const GUID& riid, IOleClientSite* pClientSite, void** ppvObj );
		long SaveFromIPersistStorage( IPersistStorage* pPS, bool bSameAsLoad );
		long GetConvertStg( void );
		long SetConvertStg( bool bConvert );
		long ReadClassStg( GUID* pclsid );
		long WriteClassStg( const GUID& rclsid );
		long ReadFmtUserTypeStg( CLIPFORMAT* pcf, wchar_t** ppszUserType );
		long WriteFmtUserTypeStg( CLIPFORMAT cf, wchar_t** pszUserType );

	private:

		CStorageClient( const CStorageClient& );
		CStorageClient& operator = ( const CStorageClient& );
	};

}//nsWin32

#endif//WINQL_COM_STORAGE_H_3
