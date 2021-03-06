//FunctionContextBase.cpp

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

//Implements a base Function Context object

#include "CompilerQOR.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/Modules/ProcessBase.h"
#include "SystemQOR/SharedBootStrap.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{

	bool CFunctionContextBase::s_bTraceCalls = true;

	//--------------------------------------------------------------------------------
	CCleanupBase::CCleanupBase()
	{
	}

	//--------------------------------------------------------------------------------
	CCleanupBase::~CCleanupBase()
	{
	}

	//--------------------------------------------------------------------------------
	void CCleanupBase::Cleanup()
	{
	}

	//--------------------------------------------------------------------------------
	//A function context is being created
	//These should only ever be created on the stack
	CFunctionContextBase::CFunctionContextBase( const char* szFuncName, const char* szFile, unsigned int uiLine ) : m_szFuncName( szFuncName ), m_szFile( szFile )
	{
		m_uiLocked = 0;
		m_iTraceDepth = 0;
		m_szFile = szFile;
		m_pParent = 0;
		m_pThread = 0;
		m_uiLine = uiLine;
		Init();
	}

	//--------------------------------------------------------------------------------
	CFunctionContextBase::CFunctionContextBase( CObjectContextBase ObjContext, const char* szFuncName, const char* szFile, unsigned int uiLine ) : m_ObjContext( ObjContext )
	{
		m_uiLocked = 0;
		m_iTraceDepth = 0;
		m_szFuncName = szFuncName;
		m_szFile = szFile;
		m_pParent = 0;
		m_pThread = 0;
		m_uiLine = uiLine;
		Init();
	}

	//--------------------------------------------------------------------------------
	bool CFunctionContextBase::Locked()
	{
		return m_uiLocked > 0;
	}

	//--------------------------------------------------------------------------------
	unsigned int CFunctionContextBase::Lock()
	{
		return ++m_uiLocked;
	}

	//--------------------------------------------------------------------------------
	unsigned int CFunctionContextBase::Unlock()
	{
		return m_uiLocked--;
	}

	//--------------------------------------------------------------------------------
	bool CFunctionContextBase::Trace( bool bNewTrace )
	{
		bool bTrace = s_bTraceCalls;
		s_bTraceCalls = bNewTrace;
		return bTrace;
	}

	//--------------------------------------------------------------------------------
	bool CFunctionContextBase::Booted( bool bBooted )
	{
		return g_pBootStrap && g_pBootStrap->Booted();
	}

	//--------------------------------------------------------------------------------
	CCallContextBase* CFunctionContextBase::CallContext( void )
	{
		return &m_CallContext;
	}

	//--------------------------------------------------------------------------------
	void CFunctionContextBase::Name( const char** ppName )
	{
		if( ppName != 0 )
		{
			*ppName = m_szFuncName;
		}
	}

	//--------------------------------------------------------------------------------
	void CFunctionContextBase::Init()
	{
		if( nsCodeQOR::CFunctionContextBase::Booted( false ) )
		{
			m_uiLocked++;
			m_iTraceDepth = 0;
			m_pThread = CThreadContextBase::GetCurrent();
			if( m_pThread )
			{
				m_pParent = m_pThread->RegisterFunctionContext( this );
			}

			if( m_pParent )
			{
				m_uiLocked += m_pParent->m_uiLocked;//Lock cannot be less than parent lock				
				if( !m_pParent->Locked() )
				{
					m_iTraceDepth = m_pParent->m_iTraceDepth + 1;
					if( m_pParent->CallContext() )
					{
						m_pParent->CallContext()->CallMade( this );//Tell calling context we have reached sub function body
					}
				}
			}
			m_uiLocked--;
		}
	}

	//--------------------------------------------------------------------------------
	const char* CFunctionContextBase::File()
	{
		return m_szFile;
	}

    //--------------------------------------------------------------------------------
    unsigned int CFunctionContextBase::Line()
    {
        return m_uiLine;
    }

	//--------------------------------------------------------------------------------
	CFunctionContextBase* CFunctionContextBase::GetParent()
	{
		return m_pParent;
	}

	//--------------------------------------------------------------------------------
	void CFunctionContextBase::SetParent( CFunctionContextBase* pParent )
	{
		m_pParent = pParent;
	}

	//--------------------------------------------------------------------------------
	CFunctionContextBase::CFunctionContextBase()
	{
		m_uiLocked = 0;
		m_iTraceDepth = 0;
		m_szFuncName = 0;
		m_szFile = 0;
		m_pParent = 0;
		Init();
	}

	//--------------------------------------------------------------------------------
	void CFunctionContextBase::Cleanup()
	{
		while( m_Cleanups.GetCount() > 0 )
		{
			CCleanupBase* pCleanup = m_Cleanups.Behead();
			if( pCleanup != 0 )
			{
				pCleanup->Cleanup();
			}
			delete pCleanup;
		}
	}

	//--------------------------------------------------------------------------------
	int& CFunctionContextBase::TraceDepth()
	{
		return m_iTraceDepth;
	}

	//--------------------------------------------------------------------------------
	CFunctionContextBase::~CFunctionContextBase()
	{
		if( nsCodeQOR::CFunctionContextBase::Booted( false ) )
		{
		    m_uiLocked++;
			if( m_pParent )
			{
				m_uiLocked -= m_pParent->m_uiLocked;//remove parent lock level
				if(!m_pParent->Locked() && m_pParent->CallContext() )
				{
					m_pParent->CallContext()->CallCompleted();//Tell call context we have completed sub function body
					Lock();
					m_pParent->CallContext()->Cleanup();
					Unlock();
				}
			}

			if( m_pThread )
			{
				m_pThread->UnregisterFunctionContext( this, m_pParent );
			}
			m_uiLocked--;
		}
	}

	//--------------------------------------------------------------------------------
	const char* CFunctionContextBase::Name( void )
	{
		return m_szFuncName;
	}

	//--------------------------------------------------------------------------------
	CObjectContextBase CFunctionContextBase::ObjectContext()
	{
		return m_ObjContext;
	}

	//--------------------------------------------------------------------------------
	CObjectContextBase* CFunctionContextBase::ObjectContextPointer()
	{
		return &m_ObjContext;
	}

	//--------------------------------------------------------------------------------
	CFunctionContextBase* CFunctionContextBase::GetCurrent()
	{
		CProcessBase* pProcess = CProcessBase::ThisProcess();
		CThreadContextBase* pThread = 0;
		if( pProcess != 0 )
		{
			pThread = pProcess->ThreadContext();
		}

		CFunctionContextBase* pFunctionContext = 0;
		if( pThread != 0 )
		{
			pFunctionContext = pThread->FunctionContext();
		}
		return pFunctionContext;
	}

}//nsCodeQOR
