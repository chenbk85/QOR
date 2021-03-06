//DateTimePicker.h

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

//WinQL Date Time Picker Common Control Window

#ifndef WINQL_GUI_WND_CCTRL_DTP_H_3
#define WINQL_GUI_WND_CCTRL_DTP_H_3

#include "WinQL/GUI/Views/WindowView.h"
#include "MammutQOR/Model.h"
#include "WinQL/GUI/Windows/WinCtrlWindow.h"
#include "WinQL/GUI/WindowFactory.h"
#include "WinQL/GUI/CommonCtrl.h"
#include "WinQL/System/Clock/WinQLTime.h"
#include "WinQL/Application/Graphics/WinQLFont.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CDateTimePickerClass : public CWindowClass
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDateTimePickerClass );

		CDateTimePickerClass();
		virtual ~CDateTimePickerClass();
		virtual bool Preregistered();
		const TCHAR* Name();

	private:

		CCommonCtrl m_ComCtrl32;

		CDateTimePickerClass( const CDateTimePickerClass& );
		CDateTimePickerClass& operator = ( const CDateTimePickerClass& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CDateTimePicker : public CWinCtrlWindow
	{
	public:

		//--------------------------------------------------------------------------------
		typedef struct tagDATETIMEPICKERINFO
		{
			unsigned long cbSize;
			RECT rcCheck;
			unsigned long stateCheck;
			RECT rcButton;
			unsigned long stateButton;
			CWindowHandle::refType hwndEdit;
			CWindowHandle::refType hwndUD;
			CWindowHandle::refType hwndDropDown;
		} DATETIMEPICKERINFO, *LPDATETIMEPICKERINFO;

		//--------------------------------------------------------------------------------
		typedef struct tagNMDATETIMECHANGE : public NotificationMessageHeader
		{
			//NMHDR       nmhdr;
			unsigned long       dwFlags;    // GDT_VALID or GDT_NONE
			SystemTime  st;         // valid iff dwFlags==GDT_VALID
		} NMDATETIMECHANGE, *LPNMDATETIMECHANGE;

		//--------------------------------------------------------------------------------
		struct NMDATETIMEFORMAT : public NotificationMessageHeader
		{
			//NMHDR nmhdr;
			const TCHAR* pszFormat;   // format substring
			SystemTime st;       // current systemtime
			const TCHAR* pszDisplay;  // string to display
			TCHAR szDisplay[ 64 ]; // buffer pszDisplay originally points at
		};

		//--------------------------------------------------------------------------------
		struct NMDATETIMEFORMATQUERY : public NotificationMessageHeader
		{
			//NMHDR nmhdr;
			const TCHAR* pszFormat; // format substring
			SIZE szMax;        // max bounding rectangle app will use for this format string
		};

		//--------------------------------------------------------------------------------
		struct NMDATETIMESTRING : public NotificationMessageHeader
		{
			//NMHDR      nmhdr;
			const TCHAR*    pszUserString;  // string user entered
			SystemTime st;             // app fills this in
			unsigned long      dwFlags;        // GDT_VALID or GDT_NONE
		};

		//--------------------------------------------------------------------------------
		struct NMDATETIMEWMKEYDOWN : public NotificationMessageHeader
		{
			//NMHDR      nmhdr;
			int        nVirtKey;  // virtual key code of WM_KEYDOWN which MODIFIES an X field
			const TCHAR*    pszFormat; // format substring
			SystemTime st;        // current systemtime, app should modify based on key
		};

		//Notifications

		__QCMP_STATIC_CONSTANT( int, DTN_FIRST2          = (0U-753U) );
		__QCMP_STATIC_CONSTANT( int, DTN_DATETIMECHANGE  = (DTN_FIRST2 - 6) );// the systemtime has changed, -759
		__QCMP_STATIC_CONSTANT( int, DTN_USERSTRINGA		= (DTN_FIRST2 - 5) );// the user has entered a string, -758
		__QCMP_STATIC_CONSTANT( int, DTN_WMKEYDOWNA		= (DTN_FIRST2 - 4) );// modify keydown on app format field (X), , -757
		__QCMP_STATIC_CONSTANT( int, DTN_FORMATA			= (DTN_FIRST2 - 3) );// query display for app format field (X), -756
		__QCMP_STATIC_CONSTANT( int, DTN_FORMATQUERYA	= (DTN_FIRST2 - 2) );// query formatting info for app format field (X), -755
		__QCMP_STATIC_CONSTANT( int, DTN_DROPDOWN		= (DTN_FIRST2 - 1) );// MonthCal has dropped down, -754
		__QCMP_STATIC_CONSTANT( int, DTN_CLOSEUP			= DTN_FIRST2 );// MonthCal is popping up, -753

		__QCMP_STATIC_CONSTANT( int, DTN_FIRST           = (0U-740U)       );// datetimepick
		__QCMP_STATIC_CONSTANT( int, DTN_LAST            = (0U-745U)       );// DTN_FIRST - 5
		__QCMP_STATIC_CONSTANT( int, DTN_USERSTRINGW		= (DTN_FIRST - 5) );// -745
		__QCMP_STATIC_CONSTANT( int, DTN_WMKEYDOWNW		= (DTN_FIRST - 4) );// -744
		__QCMP_STATIC_CONSTANT( int, DTN_FORMATW			= (DTN_FIRST - 3) );// -743
		__QCMP_STATIC_CONSTANT( int, DTN_FORMATQUERYW	= (DTN_FIRST - 2) );// -742

#ifdef UNICODE
#	define DTN_FORMAT			DTN_FORMATW
#	define DTN_FORMATQUERY      DTN_FORMATQUERYW
#	define DTN_USERSTRING       DTN_USERSTRINGW
#	define DTN_WMKEYDOWN           DTN_WMKEYDOWNW
#else
#	define DTN_FORMAT			DTN_FORMATA
#	define DTN_FORMATQUERY      DTN_FORMATQUERYA
#	define DTN_USERSTRING       DTN_USERSTRINGA
#	define DTN_WMKEYDOWN           DTN_WMKEYDOWNA
#endif

		//Messages

		__QCMP_STATIC_CONSTANT( int, DTM_FIRST			= 0x1000 );
		__QCMP_STATIC_CONSTANT( int, DTM_GETSYSTEMTIME   = ( DTM_FIRST + 1) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETSYSTEMTIME   = ( DTM_FIRST + 2) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETRANGE = ( DTM_FIRST + 3) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETRANGE = ( DTM_FIRST + 4) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETFORMATA = ( DTM_FIRST + 5) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETFORMATW = ( DTM_FIRST + 50) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETMCCOLOR    = ( DTM_FIRST + 6) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETMCCOLOR    = ( DTM_FIRST + 7) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETMONTHCAL   = ( DTM_FIRST + 8) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETMCFONT     = ( DTM_FIRST + 9) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETMCFONT     = ( DTM_FIRST + 10) );
		__QCMP_STATIC_CONSTANT( int, DTM_SETMCSTYLE    = ( DTM_FIRST + 11) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETMCSTYLE    = ( DTM_FIRST + 12) );
		__QCMP_STATIC_CONSTANT( int, DTM_CLOSEMONTHCAL = ( DTM_FIRST + 13) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETDATETIMEPICKERINFO = ( DTM_FIRST + 14) );
		__QCMP_STATIC_CONSTANT( int, DTM_GETIDEALSIZE = ( DTM_FIRST + 15) );

#ifdef UNICODE
#	define DTM_SETFORMAT       DTM_SETFORMATW
#else
#	define DTM_SETFORMAT       DTM_SETFORMATA
#endif

		__QOR_DECLARE_OCLASS_ID( CDateTimePicker );

		CDateTimePicker();
		~CDateTimePicker();			
		long OnNotify( NotificationMessageHeader* pHdr );

		virtual void OnCloseUp( NotificationMessageHeader* pHdr );
		virtual void OnDateTimeChange( LPNMDATETIMECHANGE pHdr );
		virtual void OnDropDown( NotificationMessageHeader* pHdr );
		virtual void OnFormat( NMDATETIMEFORMAT* pHdr );
		virtual void OnFormatQuery( NMDATETIMEFORMATQUERY* pHdr );
		virtual void OnUserString( NMDATETIMESTRING* pHdr );
		virtual void OnKeyDown( NMDATETIMEWMKEYDOWN* pHdr );
		virtual void OnKillFocus( NotificationMessageHeader* pHdr );
		virtual void OnSetFocus( NotificationMessageHeader* pHdr );

		void CloseMonthCal();
		void GetInfo( DATETIMEPICKERINFO& Info );
		void GetIdealSize( SIZE& IdealSize );
		long GetMonthCalColour( int iColour );
		CFont::refType GetMonthCalFont();
		long GetMonthCalStyle();
		COSWindow::refType GetMonthCal();
		long GetRange( SystemTime* pTimeRange );
		long GetSystemTime( SystemTime& SysTime );
		bool SetFormat( const TCHAR* strFormat );
		long SetMonthCalColour( int iColour, unsigned long clr );
		void SetMonthCalFont( CFont& Font, bool bRedraw );
		bool SetRange( unsigned long dwFlags, SystemTime* pTimeRange );
		bool SetSystemTime( unsigned long dwFlags, SystemTime& Time );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CDateTimePickerFactory : public CWindowFactory
	{
	public:

		__QCMP_STATIC_CONSTANT( int, DTS_UPDOWN          = 0x0001 );// use UPDOWN instead of MONTHCAL
		__QCMP_STATIC_CONSTANT( int, DTS_SHOWNONE        = 0x0002 );// allow a NONE selection
		__QCMP_STATIC_CONSTANT( int, DTS_SHORTDATEFORMAT = 0x0000 );// use the short date format (app must forward WM_WININICHANGE messages)
		__QCMP_STATIC_CONSTANT( int, DTS_LONGDATEFORMAT  = 0x0004 );// use the long date format (app must forward WM_WININICHANGE messages)
#if		(_WIN32_IE >= 0x500)
		__QCMP_STATIC_CONSTANT( int, DTS_SHORTDATECENTURYFORMAT = 0x000C );// short date format with century (app must forward WM_WININICHANGE messages)
#endif//(_WIN32_IE >= 0x500)
		__QCMP_STATIC_CONSTANT( int, DTS_TIMEFORMAT      = 0x0009 );// use the time format (app must forward WM_WININICHANGE messages)
		__QCMP_STATIC_CONSTANT( int, DTS_APPCANPARSE     = 0x0010 );// allow user entered strings (app MUST respond to DTN_USERSTRING)
		__QCMP_STATIC_CONSTANT( int, DTS_RIGHTALIGN      = 0x0020 );// right-align popup instead of left-align it

		__QOR_DECLARE_OCLASS_ID( CDateTimePickerFactory );

		CDateTimePickerFactory();
		virtual ~CDateTimePickerFactory();
		virtual CDateTimePicker* Create();
		bool GetUpDown();
		void SetUpDown( bool bFlag );
		bool GetShowNone();
		void SetShowNone( bool bFlag );
		bool GetShortDateFormat();
		void SetShortDateFormat( bool bFlag );
		bool GetLongDateFormat();
		void SetLongDateFormat( bool bFlag );
		bool GetShortDateCenturyFormat();
		void SetShortDateCenturyFormat( bool bFlag );
		bool GetTimeFormat();
		void SetTimeFormat( bool bFlag );
		bool GetAppCanParse();
		void SetAppCanParse( bool bFlag );
		bool GetRightAlign();
		void SetRightAlign( bool bFlag );
 
	private:

		CDateTimePickerFactory( const CDateTimePickerFactory& );
		CDateTimePickerFactory& operator = ( const CDateTimePickerFactory& );
	};

}//nsWin32

#endif//WINQL_GUI_WND_CCTRL_DTP_H_3
