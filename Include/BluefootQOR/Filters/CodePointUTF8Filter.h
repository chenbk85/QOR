//CodePointUTF8Filter.h

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

#ifndef BLUEFOOT_FILTERS_CODEPOINTUTF8_H_3
#define BLUEFOOT_FILTERS_CODEPOINTUTF8_H_3

//Defines a filter encoding Unicode code points into UTF-8
//This filter can be operated in both Push and Pull modes

#include "BluefootQOR/BfFilter.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CCodePointUTF8Filter : public nsBluefoot::CBFFilter
	{
	public:

		CCodePointUTF8Filter();
		virtual ~CCodePointUTF8Filter();
		CCodePointUTF8Filter( const CCodePointUTF8Filter& src );
		CCodePointUTF8Filter& operator = ( const CCodePointUTF8Filter& src );
		virtual bool Read( unsigned long& ulUnitsRead , unsigned long ulUnitsToRead = 1 );
		virtual bool Write( unsigned long& ulUnitsWritten, unsigned long ulUnitsToWrite = 1 );
		virtual CBFBuffer* GetSourceBuffer( void );

	private:

		unsigned long ProcessCodePointToUTF8Buffer( unsigned long ulUnit, unsigned int* pCodePointBuffer );

		CByteStreamBuffer m_SourceBuffer;
	};

}//nsBluefoot

#endif//BLUEFOOT_FILTERS_CODEPOINTUTF8_H_3