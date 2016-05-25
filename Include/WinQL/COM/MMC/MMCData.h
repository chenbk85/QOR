//MMCData.h

// Copyright Querysoft Limited 2013, 2015
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

//Data structures for use with the Microsoft Management Console

#ifndef WINQLCOM_MMC_DATA_H_3
#define WINQLCOM_MMC_DATA_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQL/Definitions/Data.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	struct SColumnSetID 
	{
		unsigned long dwFlags;
		unsigned long cBytes;
		byte  id[1];
	};

	//--------------------------------------------------------------------------------
	struct MMC_COLUMN_DATA 
	{
		int					nColIndex;
		unsigned long		dwFlags;
		int					nWidth;
		Cmp_ulong_ptr		ulReserved;
	};

	//--------------------------------------------------------------------------------
	struct MMC_COLUMN_SET_DATA 
	{
		int					cbSize;
		int					nNumCols;
		MMC_COLUMN_DATA*	pColData;
	};

	//--------------------------------------------------------------------------------
	struct MMC_SORT_DATA 
	{
		int				nColIndex;
		unsigned long	dwSortOptions;
		Cmp_ulong_ptr	ulReserved;
	};

	//--------------------------------------------------------------------------------
	struct MMC_SORT_SET_DATA 
	{
		int				cbSize;
		int				nNumItems;
		MMC_SORT_DATA*	pSortData;
	};

	//--------------------------------------------------------------------------------
	struct CONTEXTMENUITEM
	{
		wchar_t* strName;
		wchar_t* strStatusBarText;
		long lCommandID;
		long lInsertionPointID;
		long fFlags;
		long fSpecialFlags;
	};

	//--------------------------------------------------------------------------------
	struct CONTEXTMENUITEM2
	{
		wchar_t* strName;
		wchar_t* strStatusBarText;
		long lCommandID;
		long lInsertionPointID;
		long fFlags;
		long fSpecialFlags;
		wchar_t* strLanguageIndependentName;
	};

	//--------------------------------------------------------------------------------
	enum MMC_CONTROL_TYPE
	{
		TOOLBAR	= 0,
		MENUBUTTON	= ( TOOLBAR + 1 ) ,
		COMBOBOXBAR	= ( MENUBUTTON + 1 ) 
	};

	//--------------------------------------------------------------------------------
	enum IconIdentifier
    {
        Icon_None	= 0,
        Icon_Error	= 32513,
        Icon_Question	= 32514,
        Icon_Warning	= 32515,
        Icon_Information	= 32516,
        Icon_First	= Icon_Error,
        Icon_Last	= Icon_Information
    };

	/*
	//--------------------------------------------------------------------------------
	struct RESULTDATAITEM
	{
		unsigned long mask;
		int bScopeItem;
		Cmp_long_ptr itemID;
		int nIndex;
		int nCol;
		wchar_t* str;
		int nImage;
		unsigned int nState;
		Cmp_long_ptr lParam;
		int iIndent;
	};
	*/

	//--------------------------------------------------------------------------------
	enum MMC_RESULT_VIEW_STYLE      
	{                                        
		MMC_SINGLESEL           = 0x0001,    
		MMC_SHOWSELALWAYS       = 0x0002,    
		MMC_NOSORTHEADER        = 0x0004,        
		MMC_ENSUREFOCUSVISIBLE  = 0x0008,     
	};

	//--------------------------------------------------------------------------------
	enum MMC_ACTION_TYPE
	{
		MMC_ACTION_UNINITIALIZED	= -1,
		MMC_ACTION_ID	= ( MMC_ACTION_UNINITIALIZED + 1 ) ,
		MMC_ACTION_LINK	= ( MMC_ACTION_ID + 1 ) ,
		MMC_ACTION_SCRIPT	= ( MMC_ACTION_LINK + 1 ) 
	};

	//--------------------------------------------------------------------------------
	struct MMC_TASK_DISPLAY_SYMBOL
	{
		wchar_t* szFontFamilyName;
		wchar_t* szURLtoEOT;
		wchar_t* szSymbolString;
	};

	//--------------------------------------------------------------------------------
	struct MMC_TASK_DISPLAY_BITMAP
	{
		wchar_t* szMouseOverBitmap;
		wchar_t* szMouseOffBitmap;
	};

	//--------------------------------------------------------------------------------
	enum MMC_TASK_DISPLAY_TYPE
	{
		MMC_TASK_DISPLAY_UNINITIALIZED	= 0,
		MMC_TASK_DISPLAY_TYPE_SYMBOL	= ( MMC_TASK_DISPLAY_UNINITIALIZED + 1 ) ,
		MMC_TASK_DISPLAY_TYPE_VANILLA_GIF	= ( MMC_TASK_DISPLAY_TYPE_SYMBOL + 1 ) ,
		MMC_TASK_DISPLAY_TYPE_CHOCOLATE_GIF	= ( MMC_TASK_DISPLAY_TYPE_VANILLA_GIF + 1 ) ,
		MMC_TASK_DISPLAY_TYPE_BITMAP	= ( MMC_TASK_DISPLAY_TYPE_CHOCOLATE_GIF + 1 ) 
	};

	//--------------------------------------------------------------------------------
	struct MMC_TASK_DISPLAY_OBJECT
	{
		MMC_TASK_DISPLAY_TYPE eDisplayType;
		union 
		{
			MMC_TASK_DISPLAY_BITMAP uBitmap;
			MMC_TASK_DISPLAY_SYMBOL uSymbol;
		};
	};

	//--------------------------------------------------------------------------------
	struct MMC_TASK
	{
		MMC_TASK_DISPLAY_OBJECT sDisplayObject;
		wchar_t* szText;
		wchar_t* szHelpString;
		MMC_ACTION_TYPE eActionType;
		union 
		{
			Cmp_long_ptr nCommandID;
			wchar_t* szActionURL;
			wchar_t* szScript;
		};
	};

	//--------------------------------------------------------------------------------
	struct MMC_LISTPAD_INFO
	{
		wchar_t* szTitle;
		wchar_t* szButtonText;
		Cmp_long_ptr nCommandID;
	};

	//--------------------------------------------------------------------------------
	struct RDITEMHDR
	{
		unsigned long dwFlags;
		Cmp_long_ptr cookie;
		Cmp_long_ptr lpReserved;
	};

	//--------------------------------------------------------------------------------
	struct RDCOMPARE
	{
		unsigned long cbSize;
		unsigned long dwFlags;
		int nColumn;
		Cmp_long_ptr lUserParam;
		RDITEMHDR* prdch1;
		RDITEMHDR* prdch2;
	};

	//--------------------------------------------------------------------------------
	struct RESULTFINDINFO
	{
		wchar_t* psz;
		int nStart;
		unsigned long dwOptions;
	};

	//--------------------------------------------------------------------------------
	enum
	{
		MMC_VIEW_OPTIONS_NONE							= 0,
		MMC_VIEW_OPTIONS_NOLISTVIEWS					= 0x1,
		MMC_VIEW_OPTIONS_MULTISELECT					= 0x2,
		MMC_VIEW_OPTIONS_OWNERDATALIST					= 0x4,
		MMC_VIEW_OPTIONS_FILTERED						= 0x8,
		MMC_VIEW_OPTIONS_CREATENEW						= 0x10,
		MMC_VIEW_OPTIONS_USEFONTLINKING					= 0x20,
		MMC_VIEW_OPTIONS_EXCLUDE_SCOPE_ITEMS_FROM_LIST	= 0x40,
		MMC_VIEW_OPTIONS_LEXICAL_SORT					= 0x80,
	};

	//--------------------------------------------------------------------------------
	enum
	{
		RDI_STR				= 0x2,
		RDI_IMAGE			= 0x4,
		RDI_STATE			= 0x8,
		RDI_PARAM			= 0x10,
		RDI_INDEX			= 0x20,
		RDI_INDENT			= 0x40,
	};

	//--------------------------------------------------------------------------------
	enum
	{
		SDI_STR				= 0x2,
		SDI_IMAGE			= 0x4,
		SDI_OPENIMAGE		= 0x8,
		SDI_STATE			= 0x10,
		SDI_PARAM			= 0x20,
		SDI_CHILDREN		= 0x40,
		SDI_PARENT			= 0,
		SDI_PREVIOUS		= 0x10000000,
		SDI_NEXT			= 0x20000000,
		SDI_FIRST			= 0x08000000,
	};

	__QCMP_STATIC_CONSTANT( IDataObject*, DOBJ_NULL				= (IDataObject*)0 );
	__QCMP_STATIC_CONSTANT( IDataObject*, DOBJ_CUSTOMOCX		= (IDataObject*)-1 );
	__QCMP_STATIC_CONSTANT( IDataObject*, DOBJ_CUSTOMWEB		= (IDataObject*)-2 );
	__QCMP_STATIC_CONSTANT( IDataObject*, DOBJ_NOCONSOLE		= (IDataObject*)-3 );

	__QCMP_STATIC_CONSTANT( int, SPECIAL_DOBJ_MIN				= -10 );
	__QCMP_STATIC_CONSTANT( int, SPECIAL_DOBJ_MAX				= 0 );

}//nsWin32

#endif//WINQLCOM_MMC_DATA_H_3