//BfXmlContentHandler.h

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

// SAX handler class

#ifndef BLUEFOOT_XML_SAX_CONTENTHANDLER_H_3
#define BLUEFOOT_XML_SAX_CONTENTHANDLER_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CompilerQOR.h"
#include "CodeQOR/Text/TString.h"
#include <list>

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlLocator;
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlAttributes;

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlContentHandler
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CXmlContentHandler );

		CXmlContentHandler();
		virtual ~CXmlContentHandler();
		virtual void SetDocumentLocator( CXmlLocator* locator );
		virtual bool StartDocument();
		virtual bool EndDocument();
		virtual bool StartPrefixMapping( const nsCodeQOR::CUCS2String& prefix, const nsCodeQOR::CUCS2String& uri );
		virtual bool EndPrefixMapping( const nsCodeQOR::CUCS2String& prefix );
		virtual bool StartElement( const nsCodeQOR::CUCS2String& namespaceURI, const nsCodeQOR::CUCS2String& localName, const nsCodeQOR::CUCS2String& qName, const CXmlAttributes& atts );
		virtual bool EndElement( const nsCodeQOR::CUCS2String& namespaceURI, const nsCodeQOR::CUCS2String& localName, const nsCodeQOR::CUCS2String& qName);
		virtual bool Characters( const nsCodeQOR::CUCS2String& ch );
		virtual bool IgnorableWhitespace( const nsCodeQOR::CUCS2String& ch );
		virtual bool ProcessingInstruction( const nsCodeQOR::CUCS2String& target, const nsCodeQOR::CUCS2String& data );
		virtual bool SkippedEntity( const nsCodeQOR::CUCS2String& name );
		virtual nsCodeQOR::CString ErrorString() const;
	};

}//nsBluefoot

#endif//BLUEFOOT_XML_SAX_CONTENTHANDLER_H_3
