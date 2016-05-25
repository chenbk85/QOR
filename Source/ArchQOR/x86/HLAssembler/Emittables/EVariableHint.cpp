//EVariableHint.cpp

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
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

//Implements an x86 variable hint emittable

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )

#include "ArchQOR/x86/HLAssembler/Emittables/EVariableHint.h"
#include "ArchQOR/x86/HLAssembler/x86HLAContext.h"
#include "ArchQOR/x86/HLAssembler/HLAssembler.h"
#include <assert.h>

//------------------------------------------------------------------------------
namespace nsArch
{
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		CEVariableHint::CEVariableHint( nsArch::CHighLevelAssemblerBase* c, VarData* vdata, Cmp_unsigned__int32 hintId, Cmp_unsigned__int32 hintValue ) __QCMP_THROW : CEmittable( c, EMITTABLE_VARIABLE_HINT ),
		m_pVdata( vdata ),
		m_uiHintId( hintId ),
		m_uiHintValue( hintValue )
		{
			assert( m_pVdata != 0 );
		}

		//------------------------------------------------------------------------------
		CEVariableHint::~CEVariableHint() __QCMP_THROW
		{
		}

		//------------------------------------------------------------------------------
		void CEVariableHint::prepare( CHLAssemblerContextBase& hlac ) __QCMP_THROW
		{
			Cx86HLAContext& cc = dynamic_cast< Cx86HLAContext& >( hlac );
			m_uiOffset = cc.GetCurrentOffset();

			// First emittable (begin of variable scope).
			if( m_pVdata->firstEmittable == 0 )
			{
				m_pVdata->firstEmittable = this;
			}

			CEmittable* oldLast = m_pVdata->lastEmittable;

			// Last emittable (end of variable scope).
			m_pVdata->lastEmittable = this;

			switch( m_uiHintId )
			{
			case VARIABLE_HINT_ALLOC:
			case VARIABLE_HINT_SPILL:
			case VARIABLE_HINT_SAVE:
			{
				if( !cc._isActive( m_pVdata ) )
				{
					cc._addActive( m_pVdata );
				}
			}
			break;
			case VARIABLE_HINT_SAVE_AND_UNUSE:
			{
				if( !cc._isActive( m_pVdata ) ) 
				{
					cc._addActive( m_pVdata );
				}
			}
			break;
			case VARIABLE_HINT_UNUSE:
			{
				if( oldLast )
				{
					oldLast->tryUnuseVar( m_pVdata );
				}
			}
			break;
			}
		}

		//------------------------------------------------------------------------------
		nsArch::CEmittable* CEVariableHint::translate( CHLAssemblerContextBase& hlac ) __QCMP_THROW
		{
			Cx86HLAContext& cc = dynamic_cast< Cx86HLAContext& >( hlac );

			switch( m_uiHintId )
			{
			case VARIABLE_HINT_ALLOC:
				cc.allocVar( m_pVdata, m_uiHintValue, VARIABLE_ALLOC_READ );
				break;
			case VARIABLE_HINT_SPILL:
				{
					if( m_pVdata->state == VARIABLE_STATE_REGISTER )
					{
						cc.spillVar( m_pVdata );
					}
				}
				break;
			case VARIABLE_HINT_SAVE:
			case VARIABLE_HINT_SAVE_AND_UNUSE:
				{
					if( m_pVdata->state == VARIABLE_STATE_REGISTER && m_pVdata->changed )
					{
						cc.emitSaveVar( m_pVdata, m_pVdata->registerIndex );
						m_pVdata->changed = false;
					}
					if( m_uiHintId == VARIABLE_HINT_SAVE_AND_UNUSE )
					{
						//goto unuse;
						cc.unuseVar( m_pVdata, VARIABLE_STATE_UNUSED );
						return translated();
					}
					break;
				}
			case VARIABLE_HINT_UNUSE:
		//unuse:
				cc.unuseVar( m_pVdata, VARIABLE_STATE_UNUSED );
				//goto end;
				return translated();
			}

			cc._unuseVarOnEndOfScope( this, m_pVdata );

		//end:
			return translated();
		}

		//------------------------------------------------------------------------------
		int CEVariableHint::getMaxSize() const __QCMP_THROW
		{
			// Variable hint is NOP, but it can generate other emittables which can do something.
			return 0;
		}

	}//nsx86
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )