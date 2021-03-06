//LibraryLoader.h

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

//Posum Library Loader

#ifndef POSUMQOR_LIBRARYLOADER_H_3
#define POSUMQOR_LIBRARYLOADER_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "PosumQOR/SharedLibrary.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{

	class __QOR_INTERFACE( __POSUMQOR ) CString;
	class __QOR_INTERFACE( __POSUMQOR ) CPath;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __POSUMQOR ) CLibraryLoader
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CLibraryLoader );

		CLibraryLoader();
		virtual ~CLibraryLoader();
		
		virtual int Close( CSharedLibrary* pLibrary );
		virtual CString Error( void );
		virtual CSharedLibrary* Open( CPath& Path, int iMode );
		virtual void* Symbol( CSharedLibrary*, const char* szSym );//TODO Posum::TChar*

	protected:

		CLibraryLoader( CLibraryLoader* pImpl );
		CLibraryLoader* PImpl( void );

	private:

		CLibraryLoader* m_pImpl;

		CLibraryLoader( const CLibraryLoader& );
		CLibraryLoader& operator = ( const CLibraryLoader& );
	};

}//nsPosum

#endif//POSUMQOR_LIBRARYLOADER_H_3

/*
__QOR_INTERFACE( __CQOR ) int dlclose( void* );
__QOR_INTERFACE( __CQOR ) char* dlerror( void );
__QOR_INTERFACE( __CQOR ) void* dlopen( const char*, int );
__QOR_INTERFACE( __CQOR ) void* dlsym( void* __QCMP_RESTRICT, const char* __QCMP_RESTRICT );
*/
