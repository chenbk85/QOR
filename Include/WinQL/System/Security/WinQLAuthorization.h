//WinQLAuthorization.h

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

//Win32 Security Authorization

#ifndef WINQL_SECURITY_AUTHORZTN_H_3
#define WINQL_SECURITY_AUTHORZTN_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Macros/codingmacros.h"
#include "WinQL/Definitions/Security.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CAdvAPI32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSIDIdentifierAuthority : public nsWin32::SID_IDENTIFIER_AUTHORITY
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSIDIdentifierAuthority );

		CSIDIdentifierAuthority();
		~CSIDIdentifierAuthority();

	private:

		CSIDIdentifierAuthority( const CSIDIdentifierAuthority& );
		CSIDIdentifierAuthority& operator = ( const CSIDIdentifierAuthority& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSID
	{
		friend class CWindowsAccountDomainSID;

	public:

		__QOR_DECLARE_OCLASS_ID( CSID );

		CSID( void* pSid );
		CSID( const TCHAR* lpSystemName, const TCHAR* lpAccountName, nsWin32::PSID_NAME_USE peUse );
		CSID( nsWin32::PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, unsigned char nSubAuthorityCount, unsigned long dwSubAuthority0, unsigned long dwSubAuthority1 = 0, unsigned long dwSubAuthority2 = 0, unsigned long dwSubAuthority3 = 0, unsigned long dwSubAuthority4 = 0, unsigned long dwSubAuthority5 = 0, unsigned long dwSubAuthority6 = 0, unsigned long dwSubAuthority7 = 0 );
		CSID( const TCHAR* StrSID );
		CSID( const CSID& Src );
		CSID( nsWin32::WELL_KNOWN_SID_TYPE WellKnownSidType, void* DomainSid = 0 );
		CSID& operator = ( void* pSid );
		virtual ~CSID();
		bool mxConvertSidToStringSid( TCHAR** StringSid ) const;
		bool DomainEqual( CSID& CompareSID );
		bool PrefixEqual( CSID& CompareSID );
		bool operator == ( CSID& CompareSID );
		unsigned long Length( void );
		CSIDIdentifierAuthority* GetIdentifierAuthority( void );
		static unsigned long GetLengthRequired( unsigned char nSubAuthorityCount );
		unsigned long* GetSubAuthority( unsigned long nSubAuthority );
		unsigned char* GetSubAuthorityCount( void );
		bool IsValid( void );
		bool IsWellKnown( nsWin32::WELL_KNOWN_SID_TYPE WellKnownSidType );
		bool LookupAccount( const TCHAR* lpSystemName, TCHAR* lpName, unsigned long* cchName, TCHAR* lpReferencedDomainName, unsigned long* cchReferencedDomainName, nsWin32::PSID_NAME_USE peUse );
		void* Data( void ) const;

	protected:

		void* m_pSID;				
				
		CSID();//Default constructor only accesible by derived classes
		bool Initialize( CSIDIdentifierAuthority* pIdentifierAuthority, unsigned char nSubAuthorityCount );

	private:
				
		nsWinQAPI::CAdvAPI32& m_AdvAPI32Library;
		bool m_bFreeSid;
		bool m_bLocalFree;
		bool m_bHeapFree;

		__QCS_DECLARE_NONASSIGNABLE( CSID );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CWindowsAccountDomainSID : public CSID
	{
	public:
	
		__QOR_DECLARE_OCLASS_ID( CSID );

		CWindowsAccountDomainSID( CSID* pSID );
		virtual ~CWindowsAccountDomainSID();

		__QCS_DECLARE_NONCOPYABLE( CWindowsAccountDomainSID );
	};

}//nsWin32

#endif//WINQL_SECURITY_AUTHORZTN_H_3