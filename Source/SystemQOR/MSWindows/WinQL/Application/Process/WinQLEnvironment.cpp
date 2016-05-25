//WinQLEnvironment.cpp

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
#include <string.h>
#include <errno.h>
#include "WinQL/Application/ErrorSystem/WinQLDOSError.h"
#include "WinQL/Application/Process/WinQLProcess.h"
#include "WinQL/CodeServices/Locale/WinQLLocale.h"
#include "WinQL/Application/Process/WinQLEnvironment.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	CEnvironment::CEnvironment() : m_bInitialised( false )
	{
	}

	//--------------------------------------------------------------------------------
	void CEnvironment::Init()
	{
		/*Init for IO
GetStartupInfo
Allocate IO info structs 'file blocks'
process inherited file handle information
Set up Std Handles if not inherited
SetHandleCount = 32

Get Environment string
Get command Line in ASCII and UNICODE

Init Multibyte character Table

setenvp (_tsetenvp)

44 strings!
*/
		int numstrings = 0;             // number of environment strings
		int cchars = 0;
		void* pRawASCIIEnv = GetStringsA();
		char* p = (char*)pRawASCIIEnv;
		char** env;						// traversal pointer

		if( p != 0 )
		{
			while( *p != '\0' ) 
			{
				// don't count "=..." type
				if( *p != '=' )
				{
					++numstrings;
				}
				p += strlen( p ) + 1;
			}

			// need pointer for each string, plus one null ptr at end
			if( ( m_apAEnvironment = env = (char**) new char*[ numstrings + 1 ] ) == 0 )
			{
				return;
			}
			
			for ( p = (char*)pRawASCIIEnv; *p != '\0' ; p += cchars )
			{
				cchars = (int)strlen( p ) + 1;
				// don't copy "=..." type
				if( *p != '=' ) 
				{
					if( ( *env = new char[ cchars ] ) == 0 )
					{
						delete [] m_apAEnvironment;
						m_apAEnvironment = NULL;
						return;
					}

					char* pTemp = strncpy( *env, p, cchars );
					//_ERRCHECK(_tcscpy_s(*env, cchars, p));
					env++;
				}
			}

			delete [] pRawASCIIEnv;
			pRawASCIIEnv = 0;			

			// and a final NULL pointer
			*env = NULL;
			m_bInitialised = true;
		}
	}

	//--------------------------------------------------------------------------------
	const wchar_t* CEnvironment::GetVarValue( const wchar_t* /*wszVar*/ )
	{
		//TODO:
		const wchar_t* wszResult = 0;
		return wszResult;
	}

	//--------------------------------------------------------------------------------
	void* CEnvironment::GetStringsA()
	{
		static int f_use = 0;
		wchar_t* wEnv = NULL;
		wchar_t* wTmp;
		char* aEnv = NULL;
		char* aTmp;
		int nSizeW;
		int nSizeA;

		// Look for 'preferred' flavor. Otherwise use available flavor.
		// Must actually call the function to ensure it's not a stub.

		if( 0 == f_use )
		{
			if( 0 != ( wEnv = (wchar_t*)( nsWinQAPI::CKernel32::GetEnvironmentStringsW() ) ) )
			{
				f_use = use_w;
			}
			else if ( nsWinQAPI::CKernel32::GetLastError() == ERROR_CALL_NOT_IMPLEMENTED )
			{
				f_use = use_a;
			}
		}

		// Use "W" version

		if( use_w == f_use )
		{
			// obtain wide environment block
			if( 0 == wEnv && ( 0 == ( wEnv = (wchar_t*)( nsWinQAPI::CKernel32::GetEnvironmentStringsW() ) ) ) )
			{
				return 0;
			}

			// look for double null that indicates end of block
			wTmp = wEnv;
			while( *wTmp != L'\0' ) 
			{
				if( *++wTmp == L'\0' )
				{
					wTmp++;
				}
			}

			// calculate total size of block, including all nulls
			nSizeW = (int)(wTmp - wEnv + 1);

			// find out how much space needed for multi-byte environment
			CCodePage AnsiCP( CCodePage::ACP );
			nSizeA = AnsiCP.WideCharToMultiByte( 0, wEnv, nSizeW, NULL, 0, NULL, NULL );

			// allocate space for multi-byte string
			if( ( nSizeA == 0) || ( ( aEnv = new char[ nSizeA ] ) == 0 ) )
			{
				nsWinQAPI::CKernel32::FreeEnvironmentStringsW( wEnv );
				{
					return 0;
				}
			}

			// do the conversion
			if ( !AnsiCP.WideCharToMultiByte( 0, wEnv, nSizeW, aEnv, nSizeA, 0, 0 ) )
			{
				delete [] aEnv;
				aEnv = 0;
			}

			nsWinQAPI::CKernel32::FreeEnvironmentStringsW( wEnv );
			return aEnv;
		}

		// Use "A" version

		if( use_a == f_use || f_use == 0 )
		{
			if( ( 0 == aEnv ) && ( 0 == ( aEnv = (char*)( nsWinQAPI::CKernel32::GetEnvironmentStringsA() ) ) ) )
			{
				return 0;
			}

			// determine how big a buffer is needed

			aTmp = aEnv;

			while ( *aTmp != '\0' ) 
			{
				if ( *++aTmp == '\0' )
				{
					aTmp++;
				}
			}

			nSizeA = (int)( aTmp - aEnv + 1 );

			if( 0 == ( aTmp = new char[ nSizeA ] ) )
			{
				nsWinQAPI::CKernel32::FreeEnvironmentStringsA( aEnv );
				return 0;
			}

			memcpy( aTmp, aEnv, nSizeA );

			nsWinQAPI::CKernel32::FreeEnvironmentStringsA( aEnv );

			return aTmp;
		}

		return 0;
	}

	//--------------------------------------------------------------------------------
	const char* CEnvironment::GetVarValue( const char* szVar )
	{
		const char* szResult = 0;
		char** pszSearch = m_apAEnvironment;
		int iLength = 0;

		if( m_bInitialised && szVar != 0 && pszSearch != 0 )
		{
			iLength = strlen( szVar );

			while( *pszSearch )
			{
				if( strlen( *pszSearch ) > iLength && ( *( *pszSearch + iLength ) == '=' ) && ( strnicoll( *pszSearch, szVar, iLength ) == 0 ) )
				{
					/* internal consistency check: the environment string should never use a buffer bigger than _MAX_ENV
					* see also SDK function SetEnvironmentVariable
					*/
					//_ASSERTE(_tcsnlen(*pszSearch + iLength + 1, _MAX_ENV) < _MAX_ENV);

					szResult = ( *pszSearch + iLength + 1 );
					break;
				}

				pszSearch++;
			}					
		}

		return szResult;
	}

	//--------------------------------------------------------------------------------
	int CEnvironment::cenvarg ( const char* const *argv, const char* const *envp, char** argblk, char** envblk, const char* name )
	{
		const char* const *vp;
		unsigned tmp;
		char* cptr;
		unsigned arg_len;
		unsigned env_len;
		int cfi_len;            // counts the number of file handles in CFI
		int retval = 0;

		// * Null environment pointer "envp" means use global variable, "_environ"
				 
		int cwd_start;
		int cwd_end;            /* length of "cwd" strings in environment */

		char envpfx[] = "SystemRoot";
		char* envbuf = NULL;
		int envsize = 0;
		int defined = 0;

		/*
			* Allocate space for command line string
			*  tmp counts the number of bytes in the command line string
			*      including spaces between arguments
			*  An empty string is special -- 2 bytes
			*/

		for( vp = argv, tmp = 2; *vp; tmp += (unsigned int)strlen( *vp++ ) + 1 ) ;

		arg_len = tmp;

		//Allocate space for the command line plus 2 null bytes

		if( ( *argblk = new char[ tmp ] ) == 0 )
		{
			*envblk = NULL;
			errno = ENOMEM;
			nsWin32::CDOSError::Set( nsWin32::CDOSError::E_nomem );
			return( -1 );
		}

	//	//_ERRCHECK_EINVAL(_tdupenv_s_crt(&envbuf, NULL, envpfx))
	//	if ( dupenv_s( &envbuf, 0, envpfx ) != 0)
	//	{
	//		retval = -1;
	//		goto error;
	//	}

	//	envsize = (int)strlen(envpfx) + 2;
	//	if( envbuf != 0 )
	//	{
	//		envsize += (int)strlen( envbuf );
	//	}

	//	/* Allocate space for environment strings
	//	 *  tmp counts the number of bytes in the environment strings
	//	 *      including nulls between strings
	//	 *  Also add "_C_FILE_INFO=" string
	//	 */
	//	if( envp )
	//	{
	//		for( vp = envp, tmp = 2; *vp; tmp += (unsigned int)strlen( *vp++ ) + 1 ) ;
	//	}

	//	//The _osfile and _osfhnd arrays are passed as binary data in dospawn.c
	//	
	//	cfi_len = 0;    /* no _C_FILE_INFO */

	//	if( !envp )
	//	{
	//		*envblk = 0;
	//	}
	//	else 
	//	{
	//		/*
	//		 * Now that we've decided to pass our own environment block,
	//		 * compute the size of the "current directory" strings to
	//		 * propagate to the new environment.
	//		 */

	//		//search for the first one
	//		
	//		for( cwd_start = 0; *m_apAEnvironment[ cwd_start ] != '\0' && *m_apAEnvironment[ cwd_start ] != '=' ; cwd_start += (int)strlen( m_apAEnvironment[ cwd_start ] ) + 1 )
	//		{
	//		}

	//		// find the total size of all contiguous ones
	//		cwd_end = cwd_start;
	//		while( *m_apAEnvironment[ cwd_end + 0 ] == '=' && *m_apAEnvironment[ cwd_end + 1 ] != '\0' &&
	//			*m_apAEnvironment[ cwd_end + 2] == ':' && *m_apAEnvironment[ cwd_end + 3 ] == '=' )
	//		{
	//			cwd_end += 4 + (int)strlen( m_apAEnvironment[ cwd_end + 4 ] ) + 1;
	//		}
	//		
	//		tmp += cwd_end - cwd_start;

	//		//Allocate space for the environment strings plus extra null byte			
	//		env_len = tmp;

	//		//Check if SystemRoot is already defined in environment provided
	//		
	//		for( vp = envp; *vp; vp++ ) 
	//		{
	//			if( strnicmp( *vp, envpfx, strlen( envpfx ) ) == 0 ) 
	//			{
	//				defined = 1;
	//				break;
	//			}
	//		}

	//		if( !defined )
	//		{
	//			tmp += envsize;
	//		}

	//		if( !( *envblk = new char[ tmp ] ) )
	//		{
	//			delete [] *argblk;
	//			*argblk = 0;
	//			errno = ENOMEM;
	//			nsWin32::CDOSError::Set( nsWin32::CDOSError:: E_nomem );
	//			retval = -1;
	//			goto done;
	//		}
	//	}

	//	/* Build the command line by concatenating the argument strings
	//		 * with spaces between, and two null bytes at the end.
	//		 * NOTE: The argv[0] argument is followed by a null.
	//		 */

	//	cptr = *argblk;
	//	vp = argv;

	//	if( !*vp )       // Empty argument list ?
	//	{
	//		++cptr;		// just two null bytes
	//	}
	//	else 
	//	{          // argv[0] must be followed by a null
	//		strcpy( cptr/*, arg_len - (cptr - *argblk)*/, *vp );
	//		//_ERRCHECK(_tcscpy_s(cptr, arg_len - (cptr - *argblk), *vp));
	//		cptr += (int)strlen( *vp++ ) + 1;
	//	}

	//	while( *vp ) 
	//	{
	//		strcpy( cptr/*, arg_len - (cptr - *argblk)*/, *vp );
	//		//_ERRCHECK(_tcscpy_s(cptr, arg_len - (cptr - *argblk), *vp));
	//		cptr += (int)strlen( *vp++ );
	//		*cptr++ = ' ';
	//	}

	//	*cptr = cptr[ -1 ] = '\0'; /* remove extra blank, add double null */

	//	/* Build the environment block by concatenating the environment
	//	 * strings with nulls between and two null bytes at the end
	//	*/

	//	cptr = *envblk;

	//	if( envp != NULL ) 
	//	{
	//		//Copy the "cwd" strings to the new environment.
	//		
	//		memcpy( cptr, &m_apAEnvironment[ cwd_start ], ( cwd_end - cwd_start ) * sizeof(char) );
	//		cptr += cwd_end - cwd_start;

	//		//Copy the environment strings from "envp".
	//		
	//		vp = envp;
	//		while( *vp ) 
	//		{
	//			strcpy( cptr/*, env_len - (cptr - *envblk)*/, *vp );
	//			//_ERRCHECK(_tcscpy_s(cptr, env_len - (cptr - *envblk), *vp));
	//			cptr += 1 + (int)strlen(*vp++);
	//		}

	//		if( !defined ) 
	//		{
	//			//Copy SystemRoot to the new environment.
	//			
	//			strcpy( cptr/*, envsize*/, envpfx);
	//			//_ERRCHECK(_tcscpy_s(cptr, envsize, envpfx));
	//			strcat( cptr/*, envsize*/, "=" );
	//			//_ERRCHECK(_tcscat_s(cptr, envsize, _T("=")));
	//			if( envbuf != 0 )
	//			{
	//				strcat( cptr/*, envsize*/, envbuf );
	//				//_ERRCHECK(_tcscat_s(cptr, envsize, envbuf));
	//			}
	//			cptr += envsize;
	//		}
	//	}

	//	if( cptr != 0 ) 
	//	{
	//		if( cptr == *envblk ) 
	//		{
	//			//Empty environment block ... this requires two nulls.
	//			*cptr++ = '\0';
	//		}
	//		
	//		//Extra null terminates the segment
	//		
	//		*cptr = '\0';
	//	}

	//	goto done;

	//error:

	//	delete [] *argblk;
	//	*argblk = 0;
	//	*envblk = 0;

	//done:

	//	if( envbuf )
	//	{
	//		delete [] envbuf;
	//	}

		return retval;
	}

	//--------------------------------------------------------------------------------
	intptr_t CEnvironment::Spawn( int mode, const char* name, char* cmdblk, char* envblk )
	{
		char syncexec, asyncresult, background;
		char* CommandLine;
		STARTUPINFO StartupInfo;
		ProcessInformation ProcessInformation;
		int CreateProcessStatus;
		unsigned long dosretval;                // OS return value
		unsigned long exitcode;
		intptr_t retval = 0;
		unsigned long fdwCreate = 0;            // flags for CreateProcess
		int i;
	//	ioinfo *pio;
	//	char *posfile;
	//	UNALIGNED intptr_t *posfhnd;
	//	int nh;                         // number of file handles to be passed to the child

	//	// translate input mode value to individual flags
	//	syncexec = asyncresult = background = 0;

	//	switch (mode) 
	//	{
	//	case CRemoteProcess::_P_WAIT:    syncexec = 1;    break;  // synchronous execution
	//	case 2: /* _P_OVERLAY */
	//	case CRemoteProcess::_P_NOWAITO: break;                 // asynchronous execution
	//	case CRemoteProcess::_P_NOWAIT:  asyncresult=1; break;  // asynch + remember result
	//	case CRemoteProcess::_P_DETACH:  background=1;  break;  // detached in null scrn grp
	//	default:
	//		_doserrno = 0;              /* not a Dos error */
	//		_VALIDATE_RETURN(("invalid mode", 0), EINVAL, -1);
	//	}

	//	/* Loop over null separated arguments, and replace null separators
	//	 * with spaces to turn it back into a single null terminated
	//	 * command line.
	//	 */
	//	CommandLine = cmdblk;
	//	while( *cmdblk ) 
	//	{
	//		while( *cmdblk ) 
	//		{
	//			cmdblk++;
	//		}

	//		//If not last argument, turn null separator into a space.
	//		
	//		if( cmdblk[ 1 ] != '\0' ) 
	//		{
	//			*cmdblk++ = ' ';
	//		}
	//	}

	//	memset( &StartupInfo, 0, sizeof( StartupInfo ) );
	//	StartupInfo.cb = sizeof( StartupInfo );

	//	for ( nh = _nhandle ; nh && !_osfile( nh - 1 ) ; nh-- ) ;

	//	if( nh < 0 || nh >= ( ( USHRT_MAX - sizeof(int) ) / ( sizeof(char) + sizeof(intptr_t) ) ) )
	//	{
	//		errno = ENOMEM;
	//		return -1;
	//	}

	//	StartupInfo.cbReserved2 = (unsigned short)( sizeof(int) + ( nh * ( sizeof(char) + sizeof(intptr_t) ) ) );

	//	StartupInfo.lpReserved2 = new BYTE[ StartupInfo.cbReserved2 ];

	//	if( !StartupInfo.lpReserved2 )
	//	{
	//		errno = ENOMEM;
	//		return -1;
	//	}

	//	*( (UNALIGNED int *)( StartupInfo.lpReserved2 ) ) = nh;

	//	posfile = (char *)( StartupInfo.lpReserved2 + sizeof(int) );
	//	posfhnd = (UNALIGNED intptr_t *)( StartupInfo.lpReserved2 + sizeof(int) + ( nh * sizeof(char) ) );

	//	for ( i = 0;
	//#pragma warning(suppress: 22009) /* Here prefast is very confused by this nh */
	//		i < nh ;
	//		i++, posfile++, posfhnd++ )
	//	{
	//		pio = _pioinfo(i);
	//		if( ( pio->osfile & FNOINHERIT) == 0 ) 
	//		{
	//				*posfile = pio->osfile;
	//				*posfhnd = pio->osfhnd;
	//		}
	//		else 
	//		{
	//			*posfile = 0;
	//			*posfhnd = (intptr_t)Invalid_Handle_Value;
	//		}
	//	}

	//	/* if the child process is detached, it cannot access the console, so
	//	 * we must nuke the information passed for the first three handles.
	//	 */
	//	if ( background ) 
	//	{
	//		for ( i = 0, posfile = (char *)(StartupInfo.lpReserved2 + sizeof( int )),
	//				  posfhnd = (UNALIGNED intptr_t *)(StartupInfo.lpReserved2 + sizeof( int ) + (nh * sizeof( char ))) ;
	//				  i < __min( nh, 3 ) ; i++, posfile++, posfhnd++ )
	//		{
	//				*posfile = 0;
	//				*posfhnd = (intptr_t)Invalid_Handle_Value;
	//		}

	//		fdwCreate |= DETACHED_PROCESS;
	//	}

	//	// errno is set to something non-zero if there are some errors in the spawning
	//		 
	//	_doserrno = 0;

	//	CreateProcessStatus = CreateProcess( (LPTSTR)name, CommandLine, 0, 0, TRUE, fdwCreate, envblk, 0,
	//											 &StartupInfo, &ProcessInformation );

	//	dosretval = GetLastError();
	//	delete [] StartupInfo.lpReserved2;

	//	if( !CreateProcessStatus ) 
	//	{
	//		_dosmaperr(dosretval);
	//		return -1;
	//	}

	//	if( mode == 2 /* _P_OVERLAY */) 
	//	{
	//			/* destroy ourselves */
	//			_exit(0);
	//	}
	//	else if ( mode == CRemoteProcess::_P_WAIT ) 
	//	{
	//		WaitForSingleObject(ProcessInformation.hProcess, (unsigned long)(-1L));

	//			/* return termination code and exit code -- note we return
	//			   the full exit code */
	//		GetExitCodeProcess(ProcessInformation.hProcess, &exitcode);

	//		retval = (intptr_t)(int)exitcode;

	//		CloseHandle(ProcessInformation.hProcess);
	//	}
	//	else if ( mode == CRemoteProcess::_P_DETACH ) 
	//	{
	//		/* like totally detached asynchronous spawn, dude,
	//		   close process handle, return 0 for success */
	//		CloseHandle(ProcessInformation.hProcess);
	//		retval = (intptr_t)0;
	//	}
	//	else 
	//	{
	//		// asynchronous spawn -- return PID
	//		retval = (intptr_t)ProcessInformation.hProcess;
	//	}

	//	CloseHandle( ProcessInformation.hThread );
		return retval;
	}

}//nsWin32
