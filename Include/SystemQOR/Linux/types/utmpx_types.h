//utmpx_types.h

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


#ifndef SYSTEMQOR_LIN_TYPES_UTMPXTYPES_H_3
#define SYSTEMQOR_LIN_TYPES_UTMPXTYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_pid_t
#define __NEED_time_t
#define __NEED_suseconds_t
#define __NEED_struct_timeval

#include QOR_SYS_ARCHHEADER(alltypes.h)

//------------------------------------------------------------------------------
namespace nsLinux
{
	//------------------------------------------------------------------------------
	struct utmpx
	{
		short ut_type;
		pid_t ut_pid;
		char ut_line[32];
		char ut_id[4];
		char ut_user[32];
		char ut_host[256];
		struct 
		{
			short __e_termination;
			short __e_exit;
		} ut_exit;
		long ut_session;
		timeval ut_tv;
		unsigned ut_addr_v6[4];
		char __unused[20];
	};

}//nsLinux

#if defined(_BSD_SOURCE) | defined(_GNU_SOURCE)
#	define e_exit __e_exit
#	define e_termination __e_termination
#endif

#define EMPTY           0
#define RUN_LVL         1
#define BOOT_TIME       2
#define NEW_TIME        3
#define OLD_TIME        4
#define INIT_PROCESS    5
#define LOGIN_PROCESS   6
#define USER_PROCESS    7
#define DEAD_PROCESS    8

#endif//SYSTEMQOR_LIN_TYPES_UTMPXTYPES_H_3
