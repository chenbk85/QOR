//pthread.h

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

///POSIX threads interface

#ifndef QOR_PTHREAD_H_3
#define QOR_PTHREAD_H_3

#include <sched.h>
#include <semaphore.h>
#include <time.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(pthread)

typedef nsPlatform::pthread_attr_t pthread_attr_t;
typedef nsPlatform::pthread_barrier_t pthread_barrier_t;
typedef nsPlatform::pthread_barrierattr_t pthread_barrierattr_t;
typedef nsPlatform::pthread_cond_t pthread_cond_t;
typedef nsPlatform::pthread_condattr_t pthread_condattr_t;
typedef nsPlatform::pthread_key_t pthread_key_t;
typedef nsPlatform::pthread_mutex_t pthread_mutex_t;
typedef nsPlatform::pthread_mutexattr_t pthread_mutexattr_t;
typedef nsPlatform::pthread_once_t pthread_once_t;
typedef nsPlatform::pthread_rwlock_t pthread_rwlock_t;
typedef nsPlatform::pthread_rwlockattr_t pthread_rwlockattr_t;
typedef nsPlatform::pthread_spinlock_t pthread_spinlock_t;
typedef nsPlatform::pthread_t pthread_t;
typedef nsPlatform::sem_t sem_t;
typedef nsPlatform::sched_param sched_param;

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) int   pthread_atfork( void (*)(void), void (*)(void), void(*)(void) );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_destroy( ::pthread_attr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getdetachstate( const ::pthread_attr_t*, int* );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getguardsize( const ::pthread_attr_t* __QCMP_RESTRICT, size_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getinheritsched( const ::pthread_attr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    //__QOR_INTERFACE( __CQOR ) int   pthread_attr_getschedparam( const ::pthread_attr_t* __QCMP_RESTRICT, sched_param* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getschedpolicy( const ::pthread_attr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getscope( const ::pthread_attr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getstack( const ::pthread_attr_t* __QCMP_RESTRICT, void** __QCMP_RESTRICT, size_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getstackaddr( const ::pthread_attr_t* __QCMP_RESTRICT, void** __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_getstacksize( const ::pthread_attr_t* __QCMP_RESTRICT, size_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_init( ::pthread_attr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setdetachstate( ::pthread_attr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setguardsize( ::pthread_attr_t*, size_t );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setinheritsched( ::pthread_attr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setschedparam( ::pthread_attr_t* __QCMP_RESTRICT, const ::sched_param* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setschedpolicy( ::pthread_attr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setscope( ::pthread_attr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setstack( ::pthread_attr_t*, void*, size_t );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setstackaddr( ::pthread_attr_t*, void* );
    __QOR_INTERFACE( __CQOR ) int   pthread_attr_setstacksize( ::pthread_attr_t*, size_t );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrier_destroy( ::pthread_barrier_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrier_init( ::pthread_barrier_t* __QCMP_RESTRICT, const ::pthread_barrierattr_t* __QCMP_RESTRICT, unsigned );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrier_wait( ::pthread_barrier_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrierattr_destroy( ::pthread_barrierattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrierattr_getpshared( const ::pthread_barrierattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrierattr_init( ::pthread_barrierattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_barrierattr_setpshared( ::pthread_barrierattr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_cancel( ::pthread_t );
    //__QOR_INTERFACE( __CQOR ) void  pthread_cleanup_push( void (*)(void *), void * );
    //__QOR_INTERFACE( __CQOR ) void  pthread_cleanup_pop( int );
    __QOR_INTERFACE( __CQOR ) int   pthread_cond_broadcast( ::pthread_cond_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_cond_destroy( ::pthread_cond_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_cond_init( ::pthread_cond_t* __QCMP_RESTRICT, const ::pthread_condattr_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_cond_signal( ::pthread_cond_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_cond_timedwait( ::pthread_cond_t* __QCMP_RESTRICT, ::pthread_mutex_t* __QCMP_RESTRICT, const ::timespec* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_cond_wait( ::pthread_cond_t* __QCMP_RESTRICT, ::pthread_mutex_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_condattr_destroy( ::pthread_condattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_condattr_getclock( const ::pthread_condattr_t* __QCMP_RESTRICT, ::clockid_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_condattr_getpshared( const ::pthread_condattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_condattr_init( ::pthread_condattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_condattr_setclock( ::pthread_condattr_t*, ::clockid_t );
    __QOR_INTERFACE( __CQOR ) int   pthread_condattr_setpshared( ::pthread_condattr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_create( ::pthread_t* __QCMP_RESTRICT, const ::pthread_attr_t* __QCMP_RESTRICT, void *(*)(void *), void* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_detach( ::pthread_t );
    __QOR_INTERFACE( __CQOR ) int   pthread_equal( ::pthread_t, ::pthread_t );
    __QOR_INTERFACE( __CQOR ) void  pthread_exit( void* );
    __QOR_INTERFACE( __CQOR ) int   pthread_getconcurrency( void );
    __QOR_INTERFACE( __CQOR ) int   pthread_getcpuclockid( ::pthread_t, ::clockid_t* );
    //__QOR_INTERFACE( __CQOR ) int   pthread_getschedparam( ::pthread_t, int* __QCMP_RESTRICT, sched_param* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) void* pthread_getspecific( ::pthread_key_t );
    __QOR_INTERFACE( __CQOR ) int   pthread_join( ::pthread_t, void** );
    __QOR_INTERFACE( __CQOR ) int   pthread_key_create( ::pthread_key_t*, void (*)(void *) );
    __QOR_INTERFACE( __CQOR ) int   pthread_key_delete( ::pthread_key_t );
	__QOR_INTERFACE( __CQOR ) int   pthread_mutex_consistent( ::pthread_mutex_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_destroy( ::pthread_mutex_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_getprioceiling( const ::pthread_mutex_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_init( ::pthread_mutex_t* __QCMP_RESTRICT, const ::pthread_mutexattr_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_lock( ::pthread_mutex_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_setprioceiling( ::pthread_mutex_t* __QCMP_RESTRICT, int, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_timedlock( ::pthread_mutex_t*, const ::timespec* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_trylock( ::pthread_mutex_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutex_unlock( ::pthread_mutex_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_destroy( ::pthread_mutexattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_getprioceiling( const ::pthread_mutexattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_getprotocol( const ::pthread_mutexattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_getpshared( const ::pthread_mutexattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_getrobust( const ::pthread_mutexattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_gettype( const ::pthread_mutexattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_init( ::pthread_mutexattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_setprioceiling( ::pthread_mutexattr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_setprotocol( ::pthread_mutexattr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_setpshared( ::pthread_mutexattr_t*, int );
	__QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_setrobust( ::pthread_mutexattr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_mutexattr_settype( ::pthread_mutexattr_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_once( ::pthread_once_t*, void (*)(void) );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_destroy( ::pthread_rwlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_init( ::pthread_rwlock_t* __QCMP_RESTRICT, const ::pthread_rwlockattr_t* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_rdlock( ::pthread_rwlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_timedrdlock( ::pthread_rwlock_t* __QCMP_RESTRICT, const ::timespec* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_timedwrlock( ::pthread_rwlock_t* __QCMP_RESTRICT, const ::timespec* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_tryrdlock( ::pthread_rwlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_trywrlock( ::pthread_rwlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_unlock( ::pthread_rwlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlock_wrlock( ::pthread_rwlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlockattr_destroy( ::pthread_rwlockattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlockattr_getpshared( const ::pthread_rwlockattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlockattr_init( ::pthread_rwlockattr_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_rwlockattr_setpshared( ::pthread_rwlockattr_t*, int );
    __QOR_INTERFACE( __CQOR ) ::pthread_t pthread_self( void );
    __QOR_INTERFACE( __CQOR ) int   pthread_setcancelstate( int, int* );
    __QOR_INTERFACE( __CQOR ) int   pthread_setcanceltype( int, int* );
    __QOR_INTERFACE( __CQOR ) int   pthread_setconcurrency( int );
    __QOR_INTERFACE( __CQOR ) int   pthread_setschedparam( ::pthread_t, int, const ::sched_param* );
    __QOR_INTERFACE( __CQOR ) int   pthread_setschedprio( ::pthread_t, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_setspecific( ::pthread_key_t, const void* );
    __QOR_INTERFACE( __CQOR ) int   pthread_spin_destroy( ::pthread_spinlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_spin_init( ::pthread_spinlock_t*, int );
    __QOR_INTERFACE( __CQOR ) int   pthread_spin_lock( ::pthread_spinlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_spin_trylock( ::pthread_spinlock_t* );
    __QOR_INTERFACE( __CQOR ) int   pthread_spin_unlock( ::pthread_spinlock_t* );
    __QOR_INTERFACE( __CQOR ) void  pthread_testcancel( void );

__QCMP_ENDLINKAGE_C

#endif//QOR_PTHREAD_H_3