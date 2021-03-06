//BfBuffer.cpp

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

//Implementation of Bluefoot buffer class

#include "BluefootQOR/BfBuffer.h"
#include <string.h>

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	CBFBuffer::CBFBuffer( unsigned long ulUnitSize, unsigned long ulItemCount ) : m_ulUnitSize( ulUnitSize )
	{
		SetCapacity( ulItemCount );
	}

	//------------------------------------------------------------------------------
	CBFBuffer::CBFBuffer( const CBFBuffer& src )
	{
		*this = src;
	}

	//------------------------------------------------------------------------------
	CBFBuffer::~CBFBuffer()
	{
		SetCapacity( 0 );
	}

	//------------------------------------------------------------------------------
	CBFBuffer& CBFBuffer::operator = ( const CBFBuffer& src )
	{
		if( &src != this )
		{
			SetCapacity( src.Capacity() );
		}
		return *this;
	}
		
	//------------------------------------------------------------------------------
	void CBFBuffer::SetCapacity( unsigned long ulItemCount )
	{
		m_ulAllocationCount = ulItemCount;
		m_uiReadBegin = 0;
		m_uiReadEnd = 0;
		m_uiWriteBegin = 0;
		m_uiWriteEnd = 0;
	}

	//------------------------------------------------------------------------------
	unsigned long CBFBuffer::Capacity( void ) const
	{
		return m_ulAllocationCount;
	}

	//------------------------------------------------------------------------------
	unsigned long CBFBuffer::ReadAcknowledge( unsigned long& ulItemCount )
	{
		if( ulItemCount > ( m_uiReadEnd - m_uiReadBegin ) )
		{
			ulItemCount = static_cast< unsigned long >( m_uiReadEnd - m_uiReadBegin );
		}

		m_uiReadBegin += ulItemCount;
		return ReadCapacity();
	}

	//------------------------------------------------------------------------------
	unsigned long CBFBuffer::ReadReject( unsigned long& ulItemCount )
	{
		if( ulItemCount > ( m_uiReadEnd - m_uiReadBegin ) )
		{
			ulItemCount = static_cast< unsigned long >( m_uiReadEnd - m_uiReadBegin );
		}

		m_uiReadEnd -= ulItemCount;
		return ReadCapacity();
	}

	//------------------------------------------------------------------------------
	unsigned long CBFBuffer::WriteAcknowledge( unsigned long& ulItemCount )
	{
		if( ulItemCount >( m_uiWriteEnd - m_uiWriteBegin ) )
		{
			ulItemCount = static_cast< unsigned long >( m_uiWriteEnd - m_uiWriteBegin );
		}

		m_uiWriteBegin += ulItemCount;
		return WriteCapacity();
	}

	//------------------------------------------------------------------------------
	unsigned long CBFBuffer::GetUnitSize( void )
	{
		return m_ulUnitSize;
	}

}//nsBluefoot

