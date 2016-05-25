//BootStrap.h

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

#ifndef WINUSREXEBOOT_BOOTSTRAP_H_1
#define WINUSREXEBOOT_BOOTSTRAP_H_1

#include "WinQL/Bootstrap/WinQLProcessBootstrap.h"
#include "CodeQOR/Text/TExtString.h"
/*
For Windows there are 4 possible low level entry point names and 4 possible application code entry point names
These depend on the combination of UNICODE vs ANSI and GUI vs CONSOLE builds

ANSI | CONSOLE		-> mainCRTStartup		- main
ANSI | GUI			-> WinMainCRTStartup	- WinMain
UNICODE | CONSOLE	-> wmainCRTStartup		- wmain
UNICODE | GUI		-> wWinMainCRTStartup	- wWinMain

The low level entry point gets mapped to _tMainCRTStartup below so we have exactly one place where where execution begins
The application code entry point gets mapped to _tWinMain or _tmain for GUI or CONSOLE apps which have very different signatures

Three names get defined:
	_tMainCRTStartup, _tWinMain, _tmain
The framework implements _tMainCRTStartup and the application must implement either _tWinMain for GUI or _tmain for CONSOLE applications
*/

#if		( __QOR_UNICODE )
#	ifdef _WINDOWS
#		define _tMainCRTStartup wWinMainCRTStartup
#	else
#		define _tMainCRTStartup wmainCRTStartup
#	endif
#	define _tWinMain		wWinMain
#	define _tmain			wmain
#else
#	ifdef _WINDOWS
#		define _tMainCRTStartup WinMainCRTStartup
#	else
#		define _tMainCRTStartup mainCRTStartup
#	endif
#	define _tWinMain		WinMain
#	define _tmain			main
#endif//( __QOR_UNICODE )

__QCMP_STARTLINKAGE_C
extern int __cdecl _tMainCRTStartup( void );
__QCMP_ENDLINKAGE_C

//--------------------------------------------------------------------------------
//This class exists as a container for the parts of the Windows Process startup and shutdown that must be in the main executable binary module 
//These things cannot be in WinQL because it's packaged as a shared library.
class CBootStrap : public nsWin32::CProcessBootStrap
{
public:

	//These reserve space in the binary image of the executable for static initializers

	// C initializers
#	pragma __QCMP_DATA_SEGMENT(".CRT$XIA")
static __attribute__((section (".CRT$XIA" ))) InitFunc CInit_a[];
#	pragma __QCMP_DATA_SEGMENT(".CRT$XIZ")
static __attribute__((section (".CRT$XIZ" ))) InitFunc CInit_z[] ;

	// C++ initializers
#	pragma __QCMP_DATA_SEGMENT(".CRT$XCA")
static __attribute__((section (".CRT$XCA" ))) InitFunc CppInit_a[];
#	pragma __QCMP_DATA_SEGMENT(".CRT$XCZ")
static __attribute__((section (".CRT$XCZ" ))) InitFunc CppInit_z[];

#	pragma __QCMP_DATA_SEGMENT()

	CBootStrap();				//Bootstrap construction sets up the framework
	~CBootStrap();
	
	int Execute( void );		//Execute the bootstrap and hence the application

};

extern ::CBootStrap* g_pBootStrap; //The module global pointer to the per module BootStrap

#endif//WINUSREXEBOOT_BOOTSTRAP_H_1
