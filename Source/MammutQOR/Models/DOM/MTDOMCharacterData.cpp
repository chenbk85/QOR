//MTDOMCharacterData.cpp

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

#include "MammutQOR/Models/DOM/MTDOMCharacterData.h"

#define ATT_DATA _TXT( "Data" )

//------------------------------------------------------------------------------
namespace nsMammut
{
	//------------------------------------------------------------------------------
	CCharacterData::CCharacterData(CModel* pContainer) : CDOMNode(pContainer)
	, m_Data(this, ATT_DATA)
	{
	}

	//------------------------------------------------------------------------------
	CCharacterData::CCharacterData(const CCharacterData& src) : CDOMNode(src)
	, m_Data(this, src.m_Data)
	{
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CCharacterData::CCharacterData(CPropertySet& src) : CDOMNode(src)
	, m_Data(this, ATT_DATA, src[ATT_DATA])
	{
	}

	//------------------------------------------------------------------------------
	CCharacterData::~CCharacterData()
	{
	}

	//------------------------------------------------------------------------------
	CCharacterData& CCharacterData::operator = (const CCharacterData& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_Data = src.m_Data;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CCharacterData& CCharacterData::operator = (CPropertySet& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_Data = src[ATT_DATA];
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	bool CCharacterData::operator == (const CCharacterData& src)
	{
		return &(const_cast< CCharacterData& >(src)) == this ? true : false;
	}

	//------------------------------------------------------------------------------
	unsigned long CCharacterData::Length(void)
	{
		return m_Data.Value().Len();
	}

	//------------------------------------------------------------------------------
	CDOMString CCharacterData::SubStringData(unsigned long ulOffset, unsigned long ulCount)
	{
		return m_Data.Value().Mid( ulOffset, ulCount );
	}

	//------------------------------------------------------------------------------
	void CCharacterData::AppendData( CDOMString& arg )
	{
		m_Data.Value().Append( arg );
	}

	//------------------------------------------------------------------------------
	void CCharacterData::InsertData( unsigned long ulOffset, CDOMString& arg )
	{
		m_Data.Value().Insert( ulOffset, arg );
	}

	//------------------------------------------------------------------------------
	void CCharacterData::DeleteData( unsigned long ulOffset, unsigned long ulCount )
	{
		m_Data.Value().Remove( ulOffset, ulCount );
	}

	//------------------------------------------------------------------------------
	void CCharacterData::ReplaceData( unsigned long ulOffset, unsigned long ulCount, CDOMString& arg )
	{
		m_Data.Value().Replace( ulOffset, ulCount, arg );
	}

	//------------------------------------------------------------------------------
	bool CCharacterData::HasChildNodes( void )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	bool CCharacterData::ValidChildType( CMUint16 NodeType )
	{
		return false;
	}

}//nsMammut
