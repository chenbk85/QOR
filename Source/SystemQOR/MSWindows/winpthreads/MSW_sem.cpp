//MSW_sem.cpp

/*
   Copyright (c) 2011 mingw-w64 project

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

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

#include "SystemQOR.h"

#if		(QOR_SYS_OS == QOR_SYS_MSW)

#include <errno.h>
#include <stdio.h>
#include <semaphore.h>
#include "SystemQOR/MSWindows/types/pthread_types.h"
#include "SystemQOR/MSWindows/MSW_pthread.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/thread.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/misc.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/mutex.h"
#include "semaphore.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/mutex.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/ref.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/spinlock.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	int do_sema_b_wait_intern( void* sema, int nointerrupt, unsigned long timeout );

	//--------------------------------------------------------------------------------
	static int sem_result (int res)
	{
		if (res != 0) 
		{
			errno = res;
			return -1;
		}
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_init( sem_t* sem, int pshared, unsigned int value )
	{
		_sem_t* sv;

		if( !sem || value > (unsigned int)SEM_VALUE_MAX )
		{
			return sem_result( EINVAL );
		}

		if( pshared != PTHREAD_PROCESS_PRIVATE )
		{
			return sem_result( EPERM );
		}

		if( !( sv = (_sem_t*) calloc( 1, sizeof( *sv ) ) ) )
		{
			return sem_result( ENOMEM );
		}

		sv->value = value;
		if( pthread_mutex_init( &sv->vlock, NULL ) != 0 )
		{
			free( sv );
			return sem_result( ENOSPC );
		}

		sv->s = new nsWin32::CSemaphore( NULL, 0, SEM_VALUE_MAX, NULL, 0, nsWin32::Standard_Rights_All | nsWin32::Semaphore_Modify_State );
		/*
		if (() == NULL)
		{
		pthread_mutex_destroy (&sv->vlock);
		free (sv);
		return sem_result (ENOSPC);
		}
		*/

		sv->valid = LIFE_SEM;
		*sem = (sem_t)sv;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_destroy( sem_t* sem )
	{
	  int r;
	  _sem_t *sv = NULL;

	  if (!sem || (sv = (_sem_t*)*sem) == NULL)
		return sem_result (EINVAL);
	  if ((r = pthread_mutex_lock (&sv->vlock)) != 0)
		return sem_result (r);

	  if (sv->value < 0)
		{
		  pthread_mutex_unlock (&sv->vlock);
		  return sem_result (EBUSY);
		}

		delete sv->s;
		/*
		if( !CloseHandle( sv->s ) )
		{
			pthread_mutex_unlock( &sv->vlock );
			return sem_result( EINVAL);
		}
		*/

		nsWin32::CThreadHelper ThreadHelper;
	  *sem = NULL;
	  sv->value = SEM_VALUE_MAX;
	  pthread_mutex_unlock(&sv->vlock);
	  ThreadHelper.Sleep( 0 );
	  while( pthread_mutex_destroy( &sv->vlock ) == EBUSY )
	  {
		ThreadHelper.Sleep( 0 );
	  }
	  sv->valid = DEAD_SEM;
	  free (sv);
	  return 0;
	}

	//--------------------------------------------------------------------------------
	static int sem_std_enter( sem_t* sem, _sem_t** svp, int do_test )
	{
		int r;
		_sem_t* sv;

		if( do_test )
		{
			pthread_testcancel();
		}

		if( !sem )
		{
			return sem_result( EINVAL );
		}

		sv = (_sem_t*)*sem;
		if( sv == NULL )
		{
			return sem_result( EINVAL );
		}

		if( ( r = pthread_mutex_lock( &sv->vlock ) ) != 0 )
		{
			return sem_result( r );
		}

		if( *sem == NULL )
		{
			pthread_mutex_unlock( &sv->vlock );
			return sem_result( EINVAL );
		}
		*svp = sv;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_trywait( sem_t* sem )
	{
		_sem_t *sv;

		if( sem_std_enter( sem, &sv, 0 ) != 0 )
		{
			return -1;
		}
		if( sv->value <= 0 )
		{
			pthread_mutex_unlock( &sv->vlock );
			return sem_result( EAGAIN );
		}
		sv->value--;
		pthread_mutex_unlock ( &sv->vlock );

		return 0;
	}

	//--------------------------------------------------------------------------------
	struct sSemTimedWait
	{
		sem_t* p;
		int* ret;
	};

	//--------------------------------------------------------------------------------
	static void clean_wait_sem( void* s )
	{
	  struct sSemTimedWait *p = (struct sSemTimedWait *) s;
	  _sem_t *sv = NULL;

	  if (sem_std_enter (p->p, &sv, 0) != 0)
		return;

	  nsWin32::CInterlockedHelper InterlockedHelper;
	  nsWin32::CWaitHelper WaitHelper;
	  if( WaitHelper.WaitForSingleObject( sv->s->Handle(), 0 ) != nsWin32::Wait_Object_0 )
	  {
		InterlockedHelper.Increment( &sv->value );
	  }
	  else if (p->ret)
	  {
		p->ret[0] = 0;
	  }
	  pthread_mutex_unlock (&sv->vlock);
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_wait( sem_t* sem )
	{
	  long cur_v;
	  int ret = 0;
	  _sem_t *sv;
	  void* semh;
	  struct sSemTimedWait arg;

	  if (sem_std_enter (sem, &sv, 1) != 0)
		return -1;

	  arg.ret = NULL;
	  arg.p = sem;
	  m_InterlockedHelper.Decrement (&sv->value);
	  cur_v = sv->value;
	  semh = sv->s;
	  pthread_mutex_unlock (&sv->vlock);

	  if (cur_v >= 0)
		return 0;
	  else
		{
		  cleanup_push (clean_wait_sem, (void *) &arg);
		  ret = do_sema_b_wait_intern (semh, 2, nsWin32::Infinite );
		  cleanup_pop (ret);
		  if (ret == EINVAL)
			ret = 0;
		}

	  if (!ret)
		return 0;

	  return sem_result (ret);
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_timedwait( sem_t* sem, const timespec* t )
	{
	  int cur_v, ret = 0;
	  unsigned long dwr;
	  void* semh;
	  _sem_t *sv;
	  struct sSemTimedWait arg;

	  if (!t)
		return sem_wait (sem);
	  dwr = dwMilliSecs( Cpthread::rel_time_in_ms( t ) );

	  if (sem_std_enter (sem, &sv, 1) != 0)
		return -1;

	  arg.ret = &ret;
	  arg.p = sem;
	  m_InterlockedHelper.Decrement( &sv->value );
	  cur_v = sv->value;
	  semh = sv->s;
	  pthread_mutex_unlock(&sv->vlock);

	  if (cur_v >= 0)
		return 0;
	  else
		{
		  cleanup_push (clean_wait_sem, (void *) &arg);
		  ret = do_sema_b_wait_intern (semh, 2, dwr);
		  cleanup_pop (ret);
		  if (ret == EINVAL)
			ret = 0;
		}

	  if (!ret)
		return 0;
	  return sem_result (ret);
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_post( sem_t* sem )
	{
		_sem_t* sv;;

		if( sem_std_enter( sem, &sv, 0 ) != 0 )
		{
			return -1;
		}

		if( sv->value >= SEM_VALUE_MAX )
		{
			pthread_mutex_unlock( &sv->vlock );
			return sem_result( ERANGE );
		}

		m_InterlockedHelper.Increment( &sv->value );
		if (sv->value > 0 || sv->s->Release( 1, NULL) )
		{
			pthread_mutex_unlock (&sv->vlock);
			return 0;
		}
		m_InterlockedHelper.Decrement( &sv->value );
		pthread_mutex_unlock (&sv->vlock);

		return sem_result (EINVAL);
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_post_multiple( sem_t* sem, int count )
	{
		int waiters_count;
		_sem_t* sv;;

		if( count <= 0 )
		{
			return sem_result( EINVAL );
		}

		if( sem_std_enter( sem, &sv, 0 ) != 0 )
		{
			return -1;
		}

		if( sv->value > ( SEM_VALUE_MAX - count ) )
		{
			pthread_mutex_unlock( &sv->vlock );
			return sem_result( ERANGE );
		}

		waiters_count = -sv->value;
		sv->value += count;
		/*InterlockedExchangeAdd((long*)&sv->value, (long) count);*/
		if( waiters_count <= 0 || sv->s->Release( ( waiters_count < count ? waiters_count : count ), NULL ) )
		{
			pthread_mutex_unlock( &sv->vlock );
			return 0;
		}
		/*InterlockedExchangeAdd((long*)&sv->value, -((long) count));*/
		sv->value -= count;
		pthread_mutex_unlock( &sv->vlock );
		return sem_result( EINVAL );
	}
	
	//--------------------------------------------------------------------------------
	sem_t* Cpthread::sem_open( const char*, int oflag/*, mode_t, unsigned int*/ )
	{
		sem_result (ENOSYS);
		return NULL;
	}
	
	//--------------------------------------------------------------------------------
	int Cpthread::sem_close( sem_t* sem )
	{
		return sem_result( ENOSYS );
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_unlink( const char* name )
	{
		return sem_result( ENOSYS );
	}

	//--------------------------------------------------------------------------------
	int Cpthread::sem_getvalue( sem_t* sem, int* sval )
	{
		_sem_t *sv;
		int r;

		if( !sval )
		{
			return sem_result (EINVAL);
		}

		if( !sem || ( sv = (_sem_t *)(*sem) ) == NULL )
		{
			return sem_result( EINVAL );
		}

		if( ( r = pthread_mutex_lock( &sv->vlock ) ) != 0 )
		{
			return sem_result(r);
		}

		if( *sem == NULL )
		{
			pthread_mutex_unlock( &sv->vlock );
			return sem_result( EINVAL );
		}

		*sval = (int) sv->value;
		pthread_mutex_unlock( &sv->vlock );
		return 0;  
	}

}//nsWin32

#endif//(QOR_SYS_OS == QOR_SYS_MSW)