//MMReg.h

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

#ifndef ARCH_X86PC_ASSEMBLERMMREG_H_2
#define ARCH_X86PC_ASSEMBLERMMREG_H_2

#include "BaseReg.h"

//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{
	//------------------------------------------------------------------------------
	// 64-bit MMX register.
	class __QOR_INTERFACE( __ARCHQOR ) CMMReg : public CBaseReg
	{
	public:

        virtual ~CMMReg() __QCMP_THROW;
		CMMReg() __QCMP_THROW;
		CMMReg( const CMMReg& other ) __QCMP_THROW;
		CMMReg( const nsCodeQOR::_DontInitialize& dontInitialize ) __QCMP_THROW;
		CMMReg( const nsCodeQOR::_Initialize&, Cmp_unsigned__int32 code ) __QCMP_THROW;
		CMMReg& operator = ( const CMMReg& other ) __QCMP_THROW;
		bool operator == ( const CMMReg& other ) const __QCMP_THROW;
		bool operator != ( const CMMReg& other ) const __QCMP_THROW;
		virtual COperand* Clone( CZone& zone ) const;
	};

	//------------------------------------------------------------------------------
	// Get MMX (MM) register.
	static inline CMMReg mm( Cmp_unsigned__int32 index ) __QCMP_THROW
	{
		return CMMReg( nsCodeQOR::_Initialize(), static_cast< Cmp_unsigned__int32 >( index | REG_TYPE_MM ) );
	}

	//------------------------------------------------------------------------------
	// Structure used for MMX specific data (64-bit). This structure can be used to load / store data from / to MMX register.
	union __QCMP_LOCAL MMData
	{
		//------------------------------------------------------------------------------
		// Set all eight signed 8-bit integers.
		inline void setSB( Cmp__int8 x0, Cmp__int8 x1, Cmp__int8 x2, Cmp__int8 x3, Cmp__int8 x4, Cmp__int8 x5, Cmp__int8 x6, Cmp__int8 x7) __QCMP_THROW
		{
			sb[0] = x0; sb[1] = x1; sb[2] = x2; sb[3] = x3; sb[4] = x4; sb[5] = x5; sb[6] = x6; sb[7] = x7;
		}

		//------------------------------------------------------------------------------
		// Set all eight unsigned 8-bit integers.
		inline void setUB( Cmp_unsigned__int8 x0, Cmp_unsigned__int8 x1, Cmp_unsigned__int8 x2, Cmp_unsigned__int8 x3, Cmp_unsigned__int8 x4, Cmp_unsigned__int8 x5, Cmp_unsigned__int8 x6, Cmp_unsigned__int8 x7) __QCMP_THROW
		{
			ub[0] = x0; ub[1] = x1; ub[2] = x2; ub[3] = x3; ub[4] = x4; ub[5] = x5; ub[6] = x6; ub[7] = x7;
		}

		//------------------------------------------------------------------------------
		// Set all four signed 16-bit integers.
		inline void setSW( Cmp__int16 x0, Cmp__int16 x1, Cmp__int16 x2, Cmp__int16 x3) __QCMP_THROW
		{
			sw[0] = x0; sw[1] = x1; sw[2] = x2; sw[3] = x3;
		}

		//------------------------------------------------------------------------------
		// Set all four unsigned 16-bit integers.
		inline void setUW( Cmp_unsigned__int16 x0, Cmp_unsigned__int16 x1, Cmp_unsigned__int16 x2, Cmp_unsigned__int16 x3) __QCMP_THROW
		{
			uw[0] = x0; uw[1] = x1; uw[2] = x2; uw[3] = x3;
		}

		//------------------------------------------------------------------------------
		// Set all two signed 32-bit integers.
		inline void setSD( Cmp__int32 x0, Cmp__int32 x1) __QCMP_THROW
		{
			sd[0] = x0; sd[1] = x1;
		}

		//------------------------------------------------------------------------------
		// Set all two unsigned 32-bit integers.
		inline void setUD( Cmp_unsigned__int32 x0, Cmp_unsigned__int32 x1) __QCMP_THROW
		{
			ud[0] = x0; ud[1] = x1;
		}

		//------------------------------------------------------------------------------
		// Set signed 64-bit integer.
		inline void setSQ( Cmp__int64 x0 ) __QCMP_THROW
		{
			sq[0] = x0;
		}

		//------------------------------------------------------------------------------
		// Set unsigned 64-bit integer.
		inline void setUQ( Cmp_unsigned__int64 x0 ) __QCMP_THROW
		{
			uq[0] = x0;
		}

		//------------------------------------------------------------------------------
		// Set all two SP-FP values.
		inline void setSF( float x0, float x1 ) __QCMP_THROW
		{
			sf[0] = x0; sf[1] = x1;
		}

		//Unioned data members

		Cmp__int8 sb[ 8 ];				// Array of eight signed 8-bit integers.
		Cmp_unsigned__int8 ub[ 8 ];		// Array of eight unsigned 8-bit integers.
		Cmp__int16 sw[ 4 ];				// Array of four signed 16-bit integers.
		Cmp_unsigned__int16 uw[ 4 ];	// Array of four unsigned 16-bit integers.
		Cmp__int32 sd[ 2 ];				// Array of two signed 32-bit integers.
		Cmp_unsigned__int32 ud[ 2 ];	// Array of two unsigned 32-bit integers.
		Cmp__int64 sq[ 1 ];				// Array of one signed 64-bit integer.
		Cmp_unsigned__int64 uq[ 1 ];	// Array of one unsigned 64-bit integer.
		float sf[ 2 ];					// Array of two SP-FP values.
	};

}//nsx86
}//nsArch

#endif//ARCH_X86PC_ASSEMBLERMMREG_H_2