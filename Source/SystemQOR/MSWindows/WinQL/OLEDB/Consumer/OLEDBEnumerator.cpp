//OLEDBEnumerator.cpp

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

#include "WinQL/OLEDB/Consumer/OLEDBEnumerator.h"
#include "WinQL/OLEDB/DBPropSet.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	const GUID CLSID_OLEDB_ENUMERATOR = { 0xc8b522d0L,0x5cf3,0x11ce,{ 0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d } };
	const GUID DBPROPSET_ROWSET = { 0xc8b522be,0x5cf3,0x11ce,{ 0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d } };
	const GUID DBPROPSET_DBINIT = { 0xc8b522bc,0x5cf3,0x11ce,{ 0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d } };

	const DBID DB_NULLID = { { 0x00000000L,0x0000,0x0000,{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 } }, 0, (wchar_t*)0 };

	const GUID IDBInitialize::_IID =		{ 0x0c733a8b, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID ISourcesRowset::_IID =		{ 0x0c733a1e, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID IRowset::_IID =				{ 0x0c733a7c, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID IDBProperties::_IID =		{ 0x0c733a8a, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID ISessionProperties::_IID =	{ 0x0c733a85, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID ICommandProperties::_IID =	{ 0x0c733a79, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID IRowsetInfo::_IID =			{ 0x0c733a55, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID IAccessor::_IID =			{ 0x0c733a8c, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };
	const GUID IColumnsInfo::_IID =			{ 0x0c733a11, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d };

	__QOR_IMPLEMENT_OCLASS_LUID( COLEDBEnumerator );

	//--------------------------------------------------------------------------------
	COLEDBEnumerator::COLEDBEnumerator()
	{
		_WINQ_FCONTEXT( "COLEDBEnumerator::COLEDBEnumerator" );	

		const unsigned long cProperties = 2;
		DBPROP rgProperties[ cProperties ];
		DBPROPSET rgPropSets[ 1 ];

		CComPtr< IDBInitialize > pIDBInitialize;
		long hr = nsWinQAPI::COLE32::Instance().CoCreateInstance( reinterpret_cast< const ::IID& >( CLSID_OLEDB_ENUMERATOR ), 0, CLSCTX_INPROC_SERVER, reinterpret_cast< const ::IID& >( IUnknown_IID ), reinterpret_cast< void** >( &m_p ) );

		if( hr == S_OK )
		{
			hr = m_p->QueryInterface( IDBInitialize_IID, reinterpret_cast< void** >( &pIDBInitialize ) );
			if( hr == S_OK && !pIDBInitialize.IsNull() )
			{
				hr = DoInitialize();

				if( hr == S_OK )
				{
					AddRowsetProperties( rgPropSets, cProperties, rgProperties );

					CComPtr< ISourcesRowset > pISourcesRowset;
					hr = m_p->QueryInterface( ISourcesRowset_IID, reinterpret_cast<void**>( &pISourcesRowset ) );

					if( hr == S_OK )
					{
						CComPtr< IUnknown > pIRowset;
						hr = pISourcesRowset->GetSourcesRowset( 0, IRowset_IID, 1, rgPropSets, &pIRowset );
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	long COLEDBEnumerator::DoInitialize( void )
	{
		long hr = S_OK;
		return hr;
	}

	//--------------------------------------------------------------------------------
	COLEDBEnumerator::~COLEDBEnumerator()
	{
		_WINQ_FCONTEXT( "COLEDBEnumerator::~COLEDBEnumerator" );
	}

	//--------------------------------------------------------------------------------
	void COLEDBEnumerator::AddRowsetProperties( DBPROPSET* pPropSet, unsigned long cProperties, DBPROP* rgProperties )
	{
		pPropSet->cProperties = cProperties;
		pPropSet->rgProperties = rgProperties;
		pPropSet->guidPropertySet = DBPROPSET_ROWSET;

		AddProperty( &rgProperties[ 0 ], DBPROP_CANFETCHBACKWARDS );
		AddProperty( &rgProperties[ 1 ], DBPROP_IRowsetLocate );
	}

	//--------------------------------------------------------------------------------
	void COLEDBEnumerator::AddProperty( DBPROP* pProp, unsigned long dwPropertyID, unsigned short vtType, long lValue, DBPROPOPTIONS dwOptions )
	{
		// Set up the property structure.
		pProp->dwPropertyID = dwPropertyID;
		pProp->dwOptions = dwOptions;
		pProp->dwStatus = DBPROPSTATUS_OK;
		pProp->colid = DB_NULLID;
		pProp->vValue.vt = vtType;

		// Since VARIANT data is a union, we can place the value in any
		// member (except for VT_DECIMAL, which is a union with the whole
		// VARIANT structure -- but we know we're not passing VT_DECIMAL).
		pProp->vValue.lVal = lValue;
	}

	//--------------------------------------------------------------------------------
	// This function gets the BOOL value for the specified property and returns the result in *pbValue.
	long GetProperty( IUnknown* pIUnknown, const GUID& riid, unsigned long dwPropertyID, const GUID& guidPropertySet, int* pbValue )
	{
		long hr;
		unsigned long rgPropertyIDs[ 1 ];
		DBPROPIDSET rgPropertyIDSets[ 1 ];

		CDBPropSetArray PropertySets;
		//unsigned long cPropSets = 0;
		//CDBPropSet* rgPropSets = NULL;

		CComPtr<IDBProperties>        pIDBProperties;
		CComPtr<ISessionProperties>   pISesProps;
		CComPtr<ICommandProperties>   pICmdProps;
		CComPtr<IRowsetInfo>          pIRowsetInfo;

		// Initialize the output value
		*pbValue = FALSE;

		// Set up the property ID array
		rgPropertyIDs[ 0 ] = dwPropertyID;

		// Set up the Property ID Set
		rgPropertyIDSets[ 0 ].rgPropertyIDs = rgPropertyIDs;
		rgPropertyIDSets[ 0 ].cPropertyIDs = 1;
		rgPropertyIDSets[ 0 ].guidPropertySet = guidPropertySet;

		// Get the property value for this property from the provider, but
		// don't try to display extended error information, since this may
		// not be a supported property. A failure is, in fact, expected if
		// the property is not supported.
		// See IDBProperties, ISessionProperties, ICommandProperties,
		// and IRowsetInfo
		if( riid == IDBProperties_IID )
		{
			hr = pIUnknown->QueryInterface( IDBProperties_IID, (void**)&pIDBProperties );
			hr = pIDBProperties->GetProperties( 1, rgPropertyIDSets, PropertySets.pCount(), PropertySets.pptr() );
		}
		else if( riid == ISessionProperties_IID )
		{
			hr = pIUnknown->QueryInterface( ISessionProperties_IID, (void**)&pISesProps );
			hr = pISesProps->GetProperties( 1, rgPropertyIDSets, PropertySets.pCount(), PropertySets.pptr() );
		}
		else if( riid == ICommandProperties_IID )
		{
			hr = pIUnknown->QueryInterface( ICommandProperties_IID, (void**)&pICmdProps );
			hr = pICmdProps->GetProperties( 1, rgPropertyIDSets, PropertySets.pCount(), PropertySets.pptr() );
		}
		else
		{
			hr = pIUnknown->QueryInterface( IRowsetInfo_IID, (void**)&pIRowsetInfo );
			hr = pIRowsetInfo->GetProperties( 1, rgPropertyIDSets, PropertySets.pCount(), PropertySets.pptr() );
		}

		// Return the value for this property to the caller if
		// it's a VT_BOOL type value, as expected.
		if( V_VT( &(PropertySets.ptr()[ 0 ].rgProperties[ 0 ].vValue) ) == VT_BOOL )
		{
			*pbValue = V_BOOL( &(PropertySets.ptr()[ 0 ].rgProperties[ 0 ].vValue ) );
		}

		return hr;
	}

	/////////////////////////////////////////////////////////////////

	// mySetupBindings
	// Summary of Routines
	//
	// This function takes an IUnknown pointer from a rowset object
	// and creates a bindings array that describes how we want the
	// data we fetch from the rowset to be laid out in memory. It
	// also calculates the total size of a row so that we can use
	// this to allocate memory for the rows that we will fetch
	// later.
	//
	// For each column in the rowset, there will be a corresponding
	// element in the bindings array that describes how the
	// provider should transfer the data, including length and
	// status, for that column. This element also specifies the data
	// type that the provider should return the column as. We will
	// bind all columns as DBTYPE_WSTR, with a few exceptions
	// detailed below, as providers are required to support the
	// conversion of their column data to this type in the vast
	// majority of cases. The exception to our binding as
	// DBTYPE_WSTR is if the native column data type is
	// DBTYPE_IUNKNOWN or if the user has requested that BLOB
	// columns be bound as ISequentialStream objects, in which case
	// we will bind those columns as ISequentialStream objects.
	//
	/////////////////////////////////////////////////////////////////
	long mySetupBindings( IUnknown* pUnkRowset, unsigned long* pcBindings, DBBINDING** prgBindings, unsigned long* pcbRowSize )
	{
		long hr;
		unsigned long	cColumns;
		DBCOLUMNINFO*   rgColumnInfo = NULL;
		wchar_t*           pStringBuffer = NULL;
		CComPtr<IColumnsInfo>   pIColumnsInfo;

		unsigned long	iCol;
		unsigned long	dwOffset = 0;
		DBBINDING*      rgBindings = NULL;

		unsigned long cStorageObjs = 0;
		int fMultipleObjs = FALSE;

		// Obtain the column information for the rowset; from this, we can
		// find out the following information that we need to construct the
		// bindings array:
		// - the number of columns
		// - the ordinal of each column
		// - the precision and scale of numeric columns
		// - the OLE DB data type of the column
		// See IColumnsInfo
		hr = pUnkRowset->QueryInterface( IColumnsInfo_IID, reinterpret_cast<void**>( &pIColumnsInfo ) ) );
		hr = pIColumnsInfo->GetColumnInfo( &cColumns, &rgColumnInfo, &pStringBuffer );

		// Allocate memory for the bindings array; there is a one-to-one mapping between the columns returned from GetColumnInfo and our bindings.
		rgBindings = (DBBINDING*)CoTaskMemAlloc( cColumns * sizeof( DBBINDING ) );		
		memset( rgBindings, 0, cColumns * sizeof( DBBINDING ) );

		// Determine if the rowset supports multiple storage object bindings.
		// If it does not, we will bind only the first BLOB column or IUnknown
		// column as an ISequentialStream object, and we will bind the rest as
		// DBTYPE_WSTR.
		// See ISequentialStream
		GetProperty( pUnkRowset, IRowset_IID, DBPROP_MULTIPLESTORAGEOBJECTS, DBPROPSET_ROWSET, &fMultipleObjs );

		// Construct the binding array element for each column.
		for( iCol = 0; iCol < cColumns; iCol++ ) 
		{
			// This binding applies to the ordinal of this column.
			rgBindings[ iCol ].iOrdinal = rgColumnInfo[ iCol ].iOrdinal;

			// We are asking the provider to give us the data for this column
			// (DBPART_VALUE), the length of that data (DBPART_LENGTH), and
			// the status of the column (DBPART_STATUS).
			rgBindings[ iCol ].dwPart = DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;

			// The following values are the offsets to the status, length, and
			// data value that the provider will fill with the appropriate
			// values when we fetch data later. When we fetch data, we will
			// pass a pointer to a buffer that the provider will copy column
			// data to, in accordance with the binding we have provided for
			// that column; these are offsets into that future buffer.
			rgBindings[ iCol ].obStatus = dwOffset;
			rgBindings[ iCol ].obLength = dwOffset + sizeof( DBSTATUS );
			rgBindings[ iCol ].obValue = dwOffset + sizeof( DBSTATUS ) + sizeof( unsigned long );

			// Any memory allocated for the data value will be owned by us, the
			// client. Note that no data will be allocated in this case, as the
			// DBTYPE_WSTR bindings we are using will tell the provider to
			// simply copy data directly into our provided buffer.
			rgBindings[ iCol ].dwMemOwner = DBMEMOWNER_CLIENTOWNED;

			// This is not a parameter binding.
			rgBindings[ iCol ].eParamIO = DBPARAMIO_NOTPARAM;

			// We want to use the precision and scale of the column.
			rgBindings[ iCol ].bPrecision = rgColumnInfo[ iCol ].bPrecision;
			rgBindings[ iCol ].bScale = rgColumnInfo[ iCol ].bScale;

			// Bind this column as DBTYPE_WSTR, which tells the provider to
			// copy a Unicode string representation of the data into our
			// buffer, converting from the native type if necessary.
			rgBindings[ iCol ].wType = DBTYPE_WSTR;

			// Initially, we set the length for this data in our buffer to 0;
			// the correct value for this will be calculated directly below.
			rgBindings[ iCol ].cbMaxLen = 0;

			// Determine the maximum number of bytes required in our buffer to
			// contain the Unicode string representation of the provider's
			// native data type, including room for the NULL-termination
			// character.
			switch( rgColumnInfo[ iCol ].wType ) 
			{
			case DBTYPE_NULL:
			case DBTYPE_EMPTY:
			case DBTYPE_I1:
			case DBTYPE_I2:
			case DBTYPE_I4:
			case DBTYPE_UI1:
			case DBTYPE_UI2:
			case DBTYPE_UI4:
			case DBTYPE_R4:
			case DBTYPE_BOOL:
			case DBTYPE_I8:
			case DBTYPE_UI8:
			case DBTYPE_R8:
			case DBTYPE_CY:
			case DBTYPE_ERROR:
				// When the above types are converted to a string, they
				// will all fit into 25 characters, so use that plus space
				// for the NULL terminator.
				rgBindings[ iCol ].cbMaxLen = ( 25 + 1 ) * sizeof( WCHAR );
				break;
			case DBTYPE_DECIMAL:
			case DBTYPE_NUMERIC:
			case DBTYPE_DATE:
			case DBTYPE_DBDATE:
			case DBTYPE_DBTIMESTAMP:
			case DBTYPE_GUID:
				// Converted to a string, the above types will all fit into
				// 50 characters, so use that plus space for the terminator.
				rgBindings[ iCol ].cbMaxLen = ( 50 + 1 ) * sizeof( WCHAR );
				break;
			case DBTYPE_BYTES:
				// In converting DBTYPE_BYTES to a string, each byte
				// becomes two characters (e.g. 0xFF -> "FF"), so we
				// will use double the maximum size of the column plus
				// include space for the NULL terminator.
				rgBindings[ iCol ].cbMaxLen =
					( rgColumnInfo[ iCol ].ulColumnSize * 2 + 1 ) * sizeof( WCHAR );
				break;
			case DBTYPE_STR:
			case DBTYPE_WSTR:
			case DBTYPE_BSTR:
				// Going from a string to our string representation,
				// we can just take the maximum size of the column,
				// a count of characters, and include space for the
				// terminator, which is not included in the column size.
				rgBindings[ iCol ].cbMaxLen =
					( rgColumnInfo[ iCol ].ulColumnSize + 1 ) * sizeof( WCHAR );
				break;

			default:
				// For any other type, we will simply use our maximum
				// column buffer size, since the display size of these
				// columns may be variable (e.g. DBTYPE_VARIANT) or
				// unknown (e.g. provider-specific types).
				rgBindings[ iCol ].cbMaxLen = MAX_COL_SIZE;
				break;
			};

			// If the provider's native data type for this column is
			// DBTYPE_IUNKNOWN or this is a BLOB column and the user
			// has requested that we bind BLOB columns as ISequentialStream
			// objects, bind this column as an ISequentialStream object if
			// the provider supports our creating another ISequentialStream
			// binding.
			if( ( rgColumnInfo[ iCol ].wType == DBTYPE_IUNKNOWN || ( ( rgColumnInfo[ iCol ].dwFlags & DBCOLUMNFLAGS_ISLONG ) && ( g_dwFlags & USE_ISEQSTREAM ) ) ) && ( fMultipleObjs || !cStorageObjs ) )
			{
				// To create an ISequentialStream object, we will
				// bind this column as DBTYPE_IUNKNOWN to indicate
				// that we are requesting this column as an object.
				rgBindings[ iCol ].wType = DBTYPE_IUNKNOWN;

				// We want to allocate enough space in our buffer for the
				// ISequentialStream pointer we will obtain from the provider.
				rgBindings[ iCol ].cbMaxLen = sizeof( ISequentialStream * );

				// To specify the type of object that we want from the
				// provider, we need to create a DBOBJECT structure and
				// place it in our binding for this column.
				rgBindings[ iCol ].pObject = (DBOBJECT *)CoTaskMemAlloc( sizeof( DBOBJECT ) );

				// Direct the provider to create an ISequentialStream
				// object over the data for this column.
				rgBindings[ iCol ].pObject->iid = IID_ISequentialStream;

				// We want read access on the ISequentialStream
				// object that the provider will create for us.
				rgBindings[ iCol ].pObject->dwFlags = STGM_READ;

				// Keep track of the number of storage objects
				// (ISequentialStream is a storage interface) that we have
				// requested, so that we can avoid requesting multiple storage
				// objects from a provider that supports only a single storage
				// object in our bindings.
				cStorageObjs++;
			}

			// Ensure that the bound maximum length is no more than the
			// maximum column size in bytes that we've defined.
			rgBindings[ iCol ].cbMaxLen = min( rgBindings[ iCol ].cbMaxLen, MAX_COL_SIZE );

			// Update the offset past the end of this column's data so that the
			// next column will begin in the correct place in the buffer.
			dwOffset = rgBindings[ iCol ].cbMaxLen + rgBindings[ iCol ].obValue;

			// Ensure that the data for the next column will be correctly
			// aligned for all platforms, or if we're done with columns,
			// that if we allocate space for multiple rows that the data
			// for every row is correctly aligned.
			dwOffset = ROUNDUP( dwOffset );
		}

		// Return the row size (the current dwOffset is the size of the row),
		// the count of bindings, and the bindings array to the caller.
		*pcbRowSize = dwOffset;
		*pcBindings = cColumns;
		*prgBindings = rgBindings;

	CLEANUP:
		CoTaskMemFree( rgColumnInfo );
		CoTaskMemFree( pStringBuffer );
		if( pIColumnsInfo )
			pIColumnsInfo->Release();
		return hr;
	}

	//--------------------------------------------------------------------------------
	long myCreateAccessor( IUnknown* pUnkRowset, Cmp_ulong_ptr* phAccessor, unsigned long* pcBindings, DBBINDING** prgBindings, unsigned long* pcbRowSize )
	{
		long hr;
		CComPtr< IAccessor > pIAccessor;

		// An accessor is basically a handle to a collection of bindings.
		// To create the accessor, we need to first create an array of
		// bindings for the columns in the rowset.
		hr = mySetupBindings( pUnkRowset, pcBindings, prgBindings, pcbRowSize );

		// Now that we have an array of bindings, tell the provider to
		// create the accessor for those bindings. We get back a handle
		// to this accessor, which we will use when fetching data.
		// See IAccessor
		hr = pUnkRowset->QueryInterface( IAccessor_IID, (void**)&pIAccessor );
		hr = pIAccessor->CreateAccessor( DBACCESSOR_ROWDATA, *pcBindings, *prgBindings, 0, phAccessor, 0 );

		return hr;
	}

	//--------------------------------------------------------------------------------
	long myDisplayRowset( IUnknown* pUnkRowset, const wchar_t* pwszColToReturn, unsigned long cchBuffer, wchar_t* pwszBuffer )
	{
		long			hr;
		IRowset*		pIRowset = NULL;
		unsigned long   cBindings;
		DBBINDING*		rgBindings = NULL;
		Cmp_ulong_ptr   hAccessor = 0x00;
		unsigned long	cbRowSize;
		void*			pData = NULL;
		ULONG*			rgDispSize = NULL;
		unsigned long   cRowsObtained;
		Cmp_ulong_ptr*	rghRows = NULL;
		unsigned long	iRow;
		long			cRows = 10;//MAX_ROWS;
		long			iRetCol = -1;
		int				fCanFetchBackwards;
		unsigned long	iIndex;
		void*			pCurData;

		// Obtain the IRowset interface for use in fetching rows and data.  See IRowset
		hr = pUnkRowset->QueryInterface( IRowset_IID, (void**)&pIRowset );

		// Determine whether this rowset supports fetching data backwards
		// we use this to determine whether the rowset can support moving to the previous set of rows, described in more detail below
		GetProperty( pUnkRowset, IRowset_IID, DBPROP_CANFETCHBACKWARDS, DBPROPSET_ROWSET, &fCanFetchBackwards );

		// If the caller wants us to return the data for a particular column from a
		// user-selected row, we need to turn the column name into a column ordinal.
		//if( pwszColToReturn )
			//CHECK_HR( hr = myFindColumn( pUnkRowset, pwszColToReturn, &iRetCol ) );

		// Create an accessor. An accessor is basically a handle to a
		// collection of bindings that describes to the provider how to
		// copy (and convert, if necessary) column data into our buffer.
		// The accessor that this creates will bind all columns either as
		// DBTYPE_WSTR (a Unicode string) or as an ISequentialStream object
		// (used for BLOB data). This will also give us the size of the
		// row buffer that the accessor describes to the provider.
		hr = myCreateAccessor( pUnkRowset, &hAccessor, &cBindings, &rgBindings, &cbRowSize ) );

		// Allocate enough memory to hold cRows rows of data; this is
		// where the actual row data from the provider will be placed.
		pData = CoTaskMemAlloc( cbRowSize * MAX_ROWS );
		//CHECK_MEMORY( hr, pData );

		// Allocate memory for an array that we will use to calculate the
		// maximum display size used by each column in the current set of rows.
		rgDispSize = (ULONG *)CoTaskMemAlloc( cBindings * sizeof( ULONG ) );
		//CHECK_MEMORY( hr, rgDispSize );

		// In this loop, we perform the following process:
		// - reset the maximum display size array
		// - try to get cRows row handles from the provider
		// - these handles are then used to actually get the row data from the
		//    provider copied into our allocated buffer
		// - calculate the maximum display size for each column
		// - release the row handles to the rows we obtained
		// - display the column names for the rowset
		// - display the row data for the rows that we fetched
		// - get user input
		// - free the provider-allocated row handle array
		// - repeat unless the user has chosen to quit or has selected a row
		while( hr == S_OK ) 
		{
			// Clear the maximum display size array.
			memset( rgDispSize, 0, cBindings * sizeof( ULONG ) );

			// Attempt to get cRows row handles from the provider.
			hr = pIRowset->GetNextRows( DB_NULL_HCHAPTER,   // hChapter
				0,   // lOffset
				cRows,   // cRows
				&cRowsObtained,   // pcRowsObtained
				&rghRows );   // prghRows

								// Loop over the row handles obtained from GetNextRows,
								// actually fetching the data for these rows into our buffer.
			for( iRow = 0; iRow < cRowsObtained; iRow++ ) 
			{
				// Find the location in our buffer where we want to place
				// the data for this row. Note that if we fetched rows
				// backwards (cRows < 0), the row handles obtained from the
				// provider are reversed from the order in which we want to
				// actually display the data on the screen, so we will
				// account for this. This ensures that the resulting order
				// of row data in the pData buffer matches the order we
				// wish to use to display the data.
				iIndex = cRows > 0 ? iRow : cRowsObtained - iRow - 1;
				pCurData = (BYTE*)pData + ( cbRowSize * iIndex );

				// Get the data for this row handle. The provider will copy
				// (and convert, if necessary) the data for each of the
				// columns that are described in our Aaccessor into the given
				// buffer (pCurData).
				hr = pIRowset->GetData( rghRows[ iRow ],   // hRow
					hAccessor,   // hAccessor
					pCurData );   // pData

									// Update the maximum display size array, accounting for this row.
				hr = myUpdateDisplaySize( cBindings, rgBindings, pCurData, rgDispSize );
			}

			// If we obtained rows, release the row handles for the retrieved
			// rows and display the names of the rowset columns before we
			// display the data.
			if( cRowsObtained ) 
			{
				// Release the row handles that we obtained.
				hr = pIRowset->ReleaseRows(
					cRowsObtained,                        // cRows
					rghRows,                              // rghRows
					NULL,                                 // rgRowOptions
					NULL,                                 // rgRefCounts
					NULL                                  // rgRowStatus
					);

				// Display the names of the rowset columns.
				hr = myDisplayColumnNames( pIRowset, rgDispSize );
			}

			// For each row that we obtained the data for, display this data.
			for( iRow = 0; iRow < cRowsObtained; iRow++ ) 
			{
				// Get a pointer to the data for this row.
				pCurData = (BYTE*)pData + ( cbRowSize* iRow );

				// And display the row data.
				hr = myDisplayRow( iRow, cBindings, rgBindings, pCurData, rgDispSize );
			}

			// Allow the user to navigate the rowset. This displays the
			// appropriate prompts, gets the user's input, may call
			// IRowset::RestartPosition, and may copy data from a selected row
			// to the selection buffer, if so directed. This will return S_OK
			// if the user asked for more rows, S_FALSE if the user selected a
			// row, or E_FAIL if the user quits.
			hr = myInteractWithRowset(
				pIRowset,                // IRowset pointer, for RestartPosition
				&cRows,                  // updated with fetch direction value
				cRowsObtained,           // to indicate selection range
				fCanFetchBackwards,      // whether [P]revious is supported
				pData,                   // data pointer for copying selection
				cbRowSize,               // size of rows for copying selection
				iRetCol >= 0 ?           // bindings for the selection column,
				&rgBindings[ iRetCol ] : NULL,   // or NULL if no selection column
				cchBuffer,                // size of the selection buffer
				pwszBuffer );             // pointer to the selection buffer

										  // Since we are allowing the provider to allocate the memory for
										  // the row handle array, we will free this memory and reset the
										  // pointer to NULL. If this is not NULL on the next call to
										  // GetNextRows, the provider will assume that it points to an
										  // allocated array of the required size (which may not be the case
										  // if we obtained less than cRows rows from this last call to
										  // GetNextRows).
			CoTaskMemFree( rghRows );
			rghRows = NULL;
		}

	CLEANUP:
		myFreeBindings( cBindings, rgBindings );
		CoTaskMemFree( rgDispSize );
		CoTaskMemFree( pData );
		if( pIRowset )
			pIRowset->Release();
		return hr;
	}

}//nsWin32