//MPropertyIterator.cpp

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

#include "MammutQOR.h"
#include "MammutQOR/Model/MPropertyIterator.h"
#include "MammutQOR/Model/MPropertySet.h"

//------------------------------------------------------------------------------
namespace nsMammut
{

	//------------------------------------------------------------------------------
	CPropertyIterator::CPropertyIterator( CPropertySet& Container, CModel::iterator::CModelNode __p ) __QCMP_THROW : CModel::iterator( __p ), m_Container( Container ), m_ulIndex( 0 ), m_pProperty( 0 )
	{
		AcquireProperty();
	}

	//------------------------------------------------------------------------------
	CPropertyIterator::CPropertyIterator( CPropertySet& Container ) : m_Container( Container ), m_ulIndex( 0 ), m_pProperty( 0 )
	{
		AcquireProperty();
	}

	//------------------------------------------------------------------------------
	CPropertyIterator::CPropertyIterator( const CPropertyIterator& src ) : m_Container( src.m_Container ), m_ulIndex( src.m_ulIndex ), m_pProperty( 0 )
	{
		AcquireProperty();
	}

	//------------------------------------------------------------------------------
	bool CPropertyIterator::operator == ( const CPropertyIterator& cmp )
	{
		return ( ( &m_Container == &cmp.m_Container ) && ( m_ulIndex == cmp.m_ulIndex ) && ( m_pProperty == cmp.m_pProperty ) ) ? true : false;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator& CPropertyIterator::operator = ( const CPropertyIterator& src )
	{
		m_ulIndex = src.m_ulIndex;
		AcquireProperty();
		return *this;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator::~CPropertyIterator()
	{
		if( m_pProperty )
		{
			m_pProperty->Unlock();
		}
		m_pProperty = 0;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator::operator CPropertyBase*()
	{
		return m_pProperty;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator& CPropertyIterator::operator +( unsigned long uiStep )
	{
		m_ulIndex += uiStep;
		AcquireProperty();
		return *this;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator& CPropertyIterator::operator ++( void )
	{
		m_ulIndex++;
		AcquireProperty();
		return *this;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator& CPropertyIterator::operator -( unsigned long uiStep )
	{
		m_ulIndex -= uiStep;
		AcquireProperty();
		return *this;
	}

	//------------------------------------------------------------------------------
	CPropertyIterator& CPropertyIterator::operator --( void )
	{
		if( m_ulIndex > 0 )
		{
			--m_ulIndex;
			AcquireProperty();
		}
		return *this;
	}

//protected:

	//------------------------------------------------------------------------------
	void CPropertyIterator::AcquireProperty( void )
	{
		if( m_pProperty )
		{
			m_pProperty->Unlock();
		}
		m_pProperty = dynamic_cast< CPropertyBase* >( (m_Container.operator[]( m_ulIndex ).operator nsMammut::CModelItem *() ) );
		if( m_pProperty )
		{
			m_pProperty->Lock();
		}
	}

}//nsMammut

