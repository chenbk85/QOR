//WinQLWindowLayoutModel.cpp

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

//Model for Window layout

#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: this stored in members for later usage" )
#include "WinQL/GUI/VisualModels/WindowLayoutModel.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	
	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CWindowLayoutModel );
	
	//--------------------------------------------------------------------------------
	//default construct
	CWindowLayoutModel::CWindowLayoutModel( CModel* pContainer ) : CPropertySet( pContainer )
	,	m_XPos(		this, _TXT( "XPos" ).str()	, 0 )
	,	m_YPos(		this, _TXT( "YPos" ).str()	, 0 )
	,	m_Width(	this, _TXT( "Width" ).str()	, 0 )
	,	m_Height(	this, _TXT( "Height" ).str()	, 0 )
	{
	}

	//--------------------------------------------------------------------------------
	CWindowLayoutModel::~CWindowLayoutModel()
	{
	}

	//--------------------------------------------------------------------------------
	//Copy construct
	CWindowLayoutModel::CWindowLayoutModel( const CWindowLayoutModel& src ) : CPropertySet( src )
	,	m_XPos( this, src.m_XPos )
	,	m_YPos( this, src.m_YPos )
	,	m_Width( this, src.m_Width )
	,	m_Height( this, src.m_Height )
	{
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CWindowLayoutModel::CWindowLayoutModel( nsMammut::CPropertySet& src ) : CPropertySet( src )
	,	m_XPos( this, src[ _TXT( "XPos" ).str() ]->As< nsMammut::CProperty< unsigned long > >() )
	,	m_YPos( this, src[ _TXT( "YPos" ).str() ]->As< nsMammut::CProperty< unsigned long > >() )
	,	m_Width( this, src[ _TXT( "Width" ).str() ]->As< nsMammut::CProperty< unsigned long > >() )
	,	m_Height( this, src[ _TXT( "Height" ).str() ]->As< nsMammut::CProperty< unsigned long > >() )
	{
	}

	//--------------------------------------------------------------------------------
	//assign from another CWindowLayoutModel
	CWindowLayoutModel& CWindowLayoutModel::operator = ( const CWindowLayoutModel& src )
	{
		if( &src != this )
		{
			m_XPos = src.m_XPos;
			m_YPos = src.m_YPos;
			m_Width = src.m_Width;
			m_Height = src.m_Height;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CWindowLayoutModel& CWindowLayoutModel::operator = ( const nsMammut::CPropertySet& src )
	{
		if( &src != this )
		{
			m_XPos = src[ _TXT( "XPos" ).str() ]->As< nsMammut::CProperty< unsigned long > >();
			m_YPos = src[ _TXT( "YPos" ).str() ]->As< nsMammut::CProperty< unsigned long > >();
			m_Width = src[ _TXT( "Width" ).str() ]->As< nsMammut::CProperty< unsigned long > >();
			m_Height = src[ _TXT( "Height" ).str() ]->As< nsMammut::CProperty< unsigned long > >();
		}
		return *this;
	}

}//nsWin32
