//WinQLGlobalAtoms.h

// Copyright Querysoft Limited 2015
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

//Win32 Global Atoms interface

#ifndef WINQL_GLOBALATOMS_H_3
#define WINQL_GLOBALATOMS_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/CodeServices/WinQLSharedRef.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CGlobalAtom
	{
		friend class CGlobalAtomTable;

	public:

		typedef nsCodeQOR::CTLRef< CGlobalAtom > refType;

		__QOR_DECLARE_OCLASS_ID( CGlobalAtom );

		CGlobalAtom( const CTString& strName, bool bUseExisting = false );
		~CGlobalAtom();

		CTString GetName( void );

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this, false );
		}

		CGlobalAtom& operator = ( const CGlobalAtom& );

	protected:

		CGlobalAtom( const CGlobalAtom& src );
		CGlobalAtom( unsigned short );

		unsigned short m_usAtom;

	private:

		CGlobalAtom();
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CGlobalAtomTable
	{

		QOR_PP_WINQL_SHARED;

	public:
		
		typedef CSharedRef< CGlobalAtomTable > refType;

		__QOR_DECLARE_OCLASS_ID( CGlobalAtomTable );

		CGlobalAtomTable();
		~CGlobalAtomTable();
		CGlobalAtom Add ( const TCHAR* lpString );
		void Delete ( CGlobalAtom& Atom );
		CGlobalAtom Find ( const TCHAR* lpString );
		unsigned int GetName ( const CGlobalAtom& Atom, TCHAR* lpBuffer, int nSize );

		refType Ref( void );

	private:

		CGlobalAtomTable( const CGlobalAtomTable& );
		CGlobalAtomTable& operator = ( const CGlobalAtomTable& );
	};

	CGlobalAtom::refType CreateGlobalAtom( const CTString& strName );

}//nsWin32

#endif//WINQL_GLOBALATOMS_H_3
