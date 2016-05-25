//LocalSecAuth.cpp

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

#include "WinQAPI/AdvAPI32.h"
#include "ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaAddAccountRights( LSA_HANDLE PolicyHandle, PSID AccountSid, ::PLSA_UNICODE_STRING UserRights, ULONG CountOfRights )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaAddAccountRights" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaAddAccountRights );
		Status = Call< NTSTATUS, LSA_HANDLE, PSID, ::PLSA_UNICODE_STRING, ULONG >( pFunc, PolicyHandle, AccountSid, UserRights, CountOfRights );
#	else
		QOR_PP_UNREF4( PolicyHandle, AccountSid, UserRights, CountOfRights );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaAddAccountRights"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaClose( LSA_HANDLE ObjectHandle )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaClose" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaClose );
		Status = Call< NTSTATUS, LSA_HANDLE >( pFunc, ObjectHandle );
#	else
		QOR_PP_UNREF( ObjectHandle );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaClose"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaCreateTrustedDomainEx( LSA_HANDLE PolicyHandle, 
									  PTRUSTED_DOMAIN_INFORMATION_EX TrustedDomainInformation, 
									  PTRUSTED_DOMAIN_AUTH_INFORMATION AuthenticationInformation, 
									  ACCESS_MASK DesiredAccess, PLSA_HANDLE TrustedDomainHandle )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaCreateTrustedDomainEx" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaCreateTrustedDomainEx );
		Status = Call< NTSTATUS, LSA_HANDLE, PTRUSTED_DOMAIN_INFORMATION_EX, PTRUSTED_DOMAIN_AUTH_INFORMATION, 
			ACCESS_MASK, PLSA_HANDLE >( pFunc, PolicyHandle, TrustedDomainInformation, AuthenticationInformation,
			DesiredAccess, TrustedDomainHandle );
#	else
		QOR_PP_UNREF4( PolicyHandle, TrustedDomainInformation, AuthenticationInformation, DesiredAccess );
		QOR_PP_UNREF( TrustedDomainHandle );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaCreateTrustedDomainEx"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaDeleteTrustedDomain( LSA_HANDLE PolicyHandle, PSID TrustedDomainSid )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaDeleteTrustedDomain" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaDeleteTrustedDomain );
		Status = Call< NTSTATUS, LSA_HANDLE, PSID >( pFunc, PolicyHandle, TrustedDomainSid );
#	else
		QOR_PP_UNREF( PolicyHandle );
		QOR_PP_UNREF( TrustedDomainSid );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaDeleteTrustedDomain"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaEnumerateAccountRights( LSA_HANDLE PolicyHandle, PSID AccountSid, ::PLSA_UNICODE_STRING *UserRights,
									   PULONG CountOfRights )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaEnumerateAccountRights" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaEnumerateAccountRights );
		Status = Call< NTSTATUS, LSA_HANDLE, PSID, ::PLSA_UNICODE_STRING*, PULONG >( pFunc, PolicyHandle, AccountSid, UserRights, CountOfRights );
#	else
		QOR_PP_UNREF4( PolicyHandle, AccountSid, UserRights, CountOfRights );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaEnumerateAccountRights"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaEnumerateAccountsWithUserRight( LSA_HANDLE PolicyHandle, ::PLSA_UNICODE_STRING UserRights, 
											   PVOID* EnumerationBuffer, PULONG CountReturned )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaEnumerateAccountsWithUserRight" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaEnumerateAccountsWithUserRight );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PLSA_UNICODE_STRING, PVOID*, PULONG >( pFunc, 
			PolicyHandle, UserRights, EnumerationBuffer, CountReturned );
#	else
		QOR_PP_UNREF4( PolicyHandle, UserRights, EnumerationBuffer, CountReturned );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaEnumerateAccountsWithUserRight"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaEnumerateTrustedDomains( LSA_HANDLE PolicyHandle, PLSA_ENUMERATION_HANDLE EnumerationContext, 
										PVOID* Buffer, ULONG PreferedMaximumLength, PULONG CountReturned )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaEnumerateTrustedDomains" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaEnumerateTrustedDomains );
		Status = Call< NTSTATUS, LSA_HANDLE, PLSA_ENUMERATION_HANDLE, PVOID*, ULONG, PULONG>( pFunc, 
			PolicyHandle, EnumerationContext, Buffer, PreferedMaximumLength, CountReturned );
#	else
		QOR_PP_UNREF4( PolicyHandle, EnumerationContext, Buffer, PreferedMaximumLength );
		QOR_PP_UNREF( CountReturned );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaEnumerateTrustedDomains"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaEnumerateTrustedDomainsEx( LSA_HANDLE PolicyHandle, PLSA_ENUMERATION_HANDLE EnumerationContext,
										  PVOID* Buffer, ULONG PreferredMaximumLength, PULONG CountReturned )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaEnumerateTrustedDomainsEx" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaEnumerateTrustedDomainsEx );
		Status = Call< NTSTATUS, LSA_HANDLE, PLSA_ENUMERATION_HANDLE, PVOID*, ULONG, PULONG >( pFunc, 
			PolicyHandle, EnumerationContext, Buffer, PreferredMaximumLength, CountReturned );
#	else
		QOR_PP_UNREF4( PolicyHandle, EnumerationContext, Buffer, PreferredMaximumLength );
		QOR_PP_UNREF( CountReturned );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaEnumerateTrustedDomainsEx"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaFreeMemory( PVOID Buffer )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaFreeMemory" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaFreeMemory );
		Status = Call< NTSTATUS, PVOID >( pFunc, Buffer );
#	else
		QOR_PP_UNREF( Buffer );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaFreeMemory"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaLookupNames( LSA_HANDLE PolicyHandle, ULONG Count, ::PLSA_UNICODE_STRING Names, 
							::PLSA_REFERENCED_DOMAIN_LIST* ReferencedDomains, ::PLSA_TRANSLATED_SID* Sids )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaLookupNames" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaLookupNames );
		Status = Call< NTSTATUS, LSA_HANDLE, ULONG, ::PLSA_UNICODE_STRING, ::PLSA_REFERENCED_DOMAIN_LIST*, 
			::PLSA_TRANSLATED_SID* >( pFunc, PolicyHandle, Count, Names, ReferencedDomains, Sids );
#	else
		QOR_PP_UNREF4( PolicyHandle, Count, Names, ReferencedDomains );
		QOR_PP_UNREF( Sids );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaLookupNames"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaLookupNames2( LSA_HANDLE PolicyHandle, ULONG Flags, ULONG Count, ::PLSA_UNICODE_STRING Names,
							 ::PLSA_REFERENCED_DOMAIN_LIST* ReferencedDomains, ::PLSA_TRANSLATED_SID2* Sids )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaLookupNames2" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaLookupNames2 );
		Status = Call< NTSTATUS, LSA_HANDLE, ULONG, ULONG, ::PLSA_UNICODE_STRING, ::PLSA_REFERENCED_DOMAIN_LIST*, 
			::PLSA_TRANSLATED_SID2* >( pFunc, PolicyHandle, Flags, Count, Names, ReferencedDomains, Sids );
#	else
		QOR_PP_UNREF4( PolicyHandle, Flags, Count, Names );
		QOR_PP_UNREF( ReferencedDomains );
		QOR_PP_UNREF( Sids );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaLookupNames2"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS WINAPI CAdvAPI32::LsaLookupPrivilegeValue( LSA_HANDLE PolicyHandle, ::PUNICODE_STRING Name, ::PLUID Value )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaLookupPrivilegeValue" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaLookupPrivilegeValue );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PUNICODE_STRING, ::PLUID >( pFunc, PolicyHandle, Name, Value );
#	else
		QOR_PP_UNREF( PolicyHandle );
		QOR_PP_UNREF( Name );
		QOR_PP_UNREF( Value );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaLookupPrivilegeValue"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaLookupSids( LSA_HANDLE PolicyHandle, ULONG Count, PSID* Sids, 
						   ::PLSA_REFERENCED_DOMAIN_LIST* ReferencedDomains, ::PLSA_TRANSLATED_NAME* Names )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaLookupSids" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaLookupSids );
		Status = Call< NTSTATUS, LSA_HANDLE, ULONG, PSID*, ::PLSA_REFERENCED_DOMAIN_LIST*, ::PLSA_TRANSLATED_NAME* >(
			pFunc, PolicyHandle, Count, Sids, ReferencedDomains, Names );
#	else
		QOR_PP_UNREF4( PolicyHandle, Count, Sids, ReferencedDomains );
		QOR_PP_UNREF( Names );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaLookupSids"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	ULONG CAdvAPI32::LsaNtStatusToWinError( NTSTATUS Status )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaNtStatusToWinError" );
		CCheckReturn< ULONG, CTCheckFailureValue< ULONG, ERROR_MR_MID_NOT_FOUND > >::TType ulResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaNtStatusToWinError );
		ulResult = Call< ULONG, NTSTATUS >( pFunc, Status );
#	else
		QOR_PP_UNREF( Status );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaNtStatusToWinError"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return ulResult;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaOpenPolicy( ::PLSA_UNICODE_STRING SystemName, ::PLSA_OBJECT_ATTRIBUTES ObjectAttributes, 
						   ACCESS_MASK DesiredAccess, PLSA_HANDLE PolicyHandle )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaOpenPolicy" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS, nsCodeQOR::CError::ERR_LVL_CONTINUE, API_RETURNED_NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaOpenPolicy );
		Status = Call< NTSTATUS, ::PLSA_UNICODE_STRING, ::PLSA_OBJECT_ATTRIBUTES, ::ACCESS_MASK, PLSA_HANDLE >( pFunc, SystemName, ObjectAttributes, DesiredAccess, PolicyHandle );
#	else
		QOR_PP_UNREF4( SystemName, ObjectAttributes, DesiredAccess, PolicyHandle );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaOpenPolicy"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaOpenTrustedDomainByName( LSA_HANDLE PolicyHandle, ::PLSA_UNICODE_STRING TrustedDomainName,
										ACCESS_MASK DesiredAccess, PLSA_HANDLE TrustedDomainHandle )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaOpenTrustedDomainByName" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaOpenTrustedDomainByName );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PLSA_UNICODE_STRING, ACCESS_MASK, PLSA_HANDLE >( pFunc, PolicyHandle,
			TrustedDomainName, DesiredAccess, TrustedDomainHandle );
#	else
		QOR_PP_UNREF4( PolicyHandle, TrustedDomainName, DesiredAccess, TrustedDomainHandle );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaOpenTrustedDomainByName"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaQueryTrustedDomainInfo( LSA_HANDLE PolicyHandle, PSID TrustedDomainSid, 
									   ::TRUSTED_INFORMATION_CLASS InformationClass, PVOID* Buffer )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaQueryTrustedDomainInfo" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaQueryTrustedDomainInfo );
		Status = Call< NTSTATUS, LSA_HANDLE, PSID, ::TRUSTED_INFORMATION_CLASS, PVOID* >( pFunc, PolicyHandle,
			TrustedDomainSid, InformationClass, Buffer );
#	else
		QOR_PP_UNREF4( PolicyHandle, TrustedDomainSid, InformationClass, Buffer );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaQueryTrustedDomainInfo"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaQueryTrustedDomainInfoByName( LSA_HANDLE PolicyHandle, ::PLSA_UNICODE_STRING TrustedDomainName,
											 ::TRUSTED_INFORMATION_CLASS InformationClass, PVOID* Buffer )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaQueryTrustedDomainInfoByName" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaQueryTrustedDomainInfoByName );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PLSA_UNICODE_STRING, ::TRUSTED_INFORMATION_CLASS, PVOID* >( pFunc, 
			PolicyHandle, TrustedDomainName, InformationClass, Buffer );
#	else
		QOR_PP_UNREF4( PolicyHandle, TrustedDomainName, InformationClass, Buffer );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaQueryTrustedDomainInfoByName"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaRemoveAccountRights( LSA_HANDLE PolicyHandle, PSID AccountSid, BOOLEAN AllRights, 
									::PLSA_UNICODE_STRING UserRights, ULONG CountOfRights )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaRemoveAccountRights" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaRemoveAccountRights );
		Status = Call< NTSTATUS, LSA_HANDLE, PSID, BOOLEAN, ::PLSA_UNICODE_STRING, ULONG >( pFunc, PolicyHandle,
			AccountSid, AllRights, UserRights, CountOfRights );
#	else
		QOR_PP_UNREF4( PolicyHandle,	AccountSid, AllRights, UserRights );
		QOR_PP_UNREF( CountOfRights );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaRemoveAccountRights"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaRetrievePrivateData( LSA_HANDLE PolicyHandle, ::PLSA_UNICODE_STRING KeyName, 
									::PLSA_UNICODE_STRING* PrivateData )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaRetrievePrivateData" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaRetrievePrivateData );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PLSA_UNICODE_STRING, ::PLSA_UNICODE_STRING* >( pFunc, PolicyHandle, KeyName, PrivateData );
#	else
		QOR_PP_UNREF( PolicyHandle );
		QOR_PP_UNREF( KeyName );
		QOR_PP_UNREF( PrivateData );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaRetrievePrivateData"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaSetTrustedDomainInfoByName( LSA_HANDLE PolicyHandle, ::PLSA_UNICODE_STRING TrustedDomainName, 
										   ::TRUSTED_INFORMATION_CLASS InformationClass, PVOID Buffer )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaSetTrustedDomainInfoByName" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaSetTrustedDomainInfoByName );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PLSA_UNICODE_STRING, ::TRUSTED_INFORMATION_CLASS, PVOID >( pFunc, 
			PolicyHandle, TrustedDomainName, InformationClass, Buffer );
#	else
		QOR_PP_UNREF4( PolicyHandle, TrustedDomainName, InformationClass, Buffer );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaSetTrustedDomainInfoByName"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaSetTrustedDomainInformation( LSA_HANDLE PolicyHandle, PSID TrustedDomainSid, 
											::TRUSTED_INFORMATION_CLASS InformationClass, PVOID Buffer )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaSetTrustedDomainInformation" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaSetTrustedDomainInformation );
		Status = Call< NTSTATUS, LSA_HANDLE, PSID, ::TRUSTED_INFORMATION_CLASS, PVOID >( pFunc, PolicyHandle, TrustedDomainSid, InformationClass, Buffer );
#	else
		QOR_PP_UNREF4( PolicyHandle, TrustedDomainSid, InformationClass, Buffer );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaSetTrustedDomainInformation"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

	//------------------------------------------------------------------------------
	NTSTATUS CAdvAPI32::LsaStorePrivateData( LSA_HANDLE PolicyHandle, ::PLSA_UNICODE_STRING KeyName, 
								 ::PLSA_UNICODE_STRING PrivateData )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LsaStorePrivateData" );
		CCheckReturn< NTSTATUS, CTSuccessCheck< NTSTATUS > >::TType Status;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( LsaStorePrivateData );
		Status = Call< NTSTATUS, LSA_HANDLE, ::PLSA_UNICODE_STRING, ::PLSA_UNICODE_STRING >( pFunc, PolicyHandle, KeyName, PrivateData );
#	else
		QOR_PP_UNREF( PolicyHandle );
		QOR_PP_UNREF( KeyName );
		QOR_PP_UNREF( PrivateData );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LsaStorePrivateData"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return Status;
	}

}//nsWinQAPI
