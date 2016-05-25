//i387FPU.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
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

#ifndef ARCHQOR_X86PC_I387FPU_H_2
#define ARCHQOR_X86PC_I387FPU_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/Assembler/BatchCPU/FPUBase.h"
#include "ArchQOR/x86/Assembler/BatchCPU/x86CPUCore.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/MMReg.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/XMMReg.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/GPReg.h"
#include "ArchQOR/x86/Assembler/Operands/Mem.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/X87Reg.h"
#include "ArchQOR/x86/Assembler/Operands/Imm.h"
#include "ArchQOR/x86/Assembler/Operands/Label.h"
#include "ArchQOR/x86/Assembler/BatchCPU/x86ISetExtension.h"


//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) C387FPU : public Cx86ISetExtension, public nsArch::CFPUBase
	{
	public:

		typedef unsigned int fexcept_t;

		//--------------------------------------------------------------------------------
		typedef struct
		{
			fexcept_t __excepts;				
		} fenv_t;

		//--------------------------------------------------------------------------------
		C387FPU( Cx86CPUCore& refCPU ) : Cx86ISetExtension( refCPU )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~C387FPU()
		{
		}

		//------------------------------------------------------------------------------
		//Compute 2^x - 1 (FPU).
		inline void f2xm1()
		{
			m_PU._emitInstruction( INST_F2XM1 );
		}

		//------------------------------------------------------------------------------
		//Absolute Value of st(0) (FPU).
		inline void fabs()
		{
			m_PU._emitInstruction( INST_FABS );
		}

		//------------------------------------------------------------------------------
		//Add src to dst and store result in dst (FPU).
		// Note One of dst or src must be st( 0 ).
		inline void fadd( const CX87Reg& dst, const CX87Reg& src )
		{
			//assert(dst.getRegIndex() == 0 || src.getRegIndex() == 0);
			m_PU._emitInstruction( INST_FADD, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Add src to st( 0 ) and store result in st( 0 ) (FPU).
		// Note SP-FP or DP-FP determined by adr size.
		inline void fadd( const CMem& src )
		{
			m_PU._emitInstruction( INST_FADD, &src );
		}

		//------------------------------------------------------------------------------
		//Add st(0) to dst and POP register stack (FPU).
		inline void faddp( const CX87Reg& dst = nsArch::nsx86::st( 1 ) )
		{
			m_PU._emitInstruction( INST_FADDP, &dst );
		}

		//------------------------------------------------------------------------------
		//Load Binary Coded Decimal (FPU).
		inline void fbld( const CMem& src )
		{
			m_PU._emitInstruction( INST_FBLD, &src );
		}

		//------------------------------------------------------------------------------
		//Store BCD Integer and Pop (FPU).
		inline void fbstp( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FBSTP, &dst );
		}

		//------------------------------------------------------------------------------
		//Change st(0) Sign (FPU).
		inline void fchs()
		{
			m_PU._emitInstruction( INST_FCHS );
		}

		//------------------------------------------------------------------------------
		//Clear Exceptions (FPU).
		//
		// Clear floating-point exception flags after checking for pending unmasked
		// floating-point exceptions.
		// Clears the floating-point exception flags (PE, UE, OE, ZE, DE, and IE),
		// the exception summary status flag (ES), the stack fault flag (SF), and
		// the busy flag (B) in the FPU status word. The FCLEX instruction checks
		// for and handles any pending unmasked floating-point exceptions before
		// clearing the exception flags.
		inline void fclex()
		{
			m_PU._emitInstruction( INST_FCLEX );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovb( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVB, &src );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovbe( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVBE, &src );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmove( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVE, &src );
		}
	
		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovnb( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVNB, &src );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovnbe( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVNBE, &src );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovne( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVNE, &src );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovnu( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVNU, &src );
		}

		//------------------------------------------------------------------------------
		//FP Conditional Move (FPU).
		inline void fcmovu( const CX87Reg& src )
		{
			m_PU._emitInstruction( INST_FCMOVU, &src );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with reg (FPU).
		inline void fcom( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FCOM, &reg );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with 4-byte or 8-byte FP at src (FPU).
		inline void fcom( const CMem& src )
		{
			m_PU._emitInstruction( INST_FCOM, &src );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with reg and pop the stack (FPU).
		inline void fcomp( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FCOMP, &reg );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with 4-byte or 8-byte FP at adr and pop the
		// stack (FPU).
		inline void fcomp( const CMem& mem )
		{
			m_PU._emitInstruction( INST_FCOMP, &mem );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with st(1) and pop register stack twice (FPU).
		inline void fcompp()
		{
			m_PU._emitInstruction( INST_FCOMPP );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) and reg and Set EFLAGS (FPU).
		inline void fcomi( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FCOMI, &reg );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) and reg and Set EFLAGS and pop the stack (FPU).
		inline void fcomip( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FCOMIP, &reg );
		}

		//------------------------------------------------------------------------------
		//Cosine (FPU).
		// This instruction calculates the cosine of the source operand in
		// register st(0) and stores the result in st(0).
		inline void fcos()
		{
			m_PU._emitInstruction( INST_FCOS );
		}

		//------------------------------------------------------------------------------
		//Decrement Stack-Top Pointer (FPU).
		//
		// Subtracts one from the TOP field of the FPU status word (decrements
		// the top-ofstack pointer). If the TOP field contains a 0, it is set
		// to 7. The effect of this instruction is to rotate the stack by one
		// position. The contents of the FPU data registers and tag register
		// are not affected.
		inline void fdecstp()
		{
			m_PU._emitInstruction( INST_FDECSTP );
		}

		//------------------------------------------------------------------------------
		//Divide dst by src (FPU).
		// Note One of dst or src register must be st(0).
		inline void fdiv( const CX87Reg& dst, const CX87Reg& src )
		{
			//assert(dst.getRegIndex() == 0 || src.getRegIndex() == 0);
			m_PU._emitInstruction( INST_FDIV, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Divide st(0) by 32-bit or 64-bit FP value (FPU).
		inline void fdiv( const CMem& src )
		{
			m_PU._emitInstruction( INST_FDIV, &src );
		}

		//------------------------------------------------------------------------------
		//Divide reg by st(0) (FPU).
		inline void fdivp( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FDIVP, &reg );
		}

		//------------------------------------------------------------------------------
		//Reverse Divide dst by src (FPU).
		// Note One of dst or src register must be st( 0 ).
		inline void fdivr( const CX87Reg& dst, const CX87Reg& src )
		{
			//assert(dst.getRegIndex() == 0 || src.getRegIndex() == 0);
			m_PU._emitInstruction( INST_FDIVR, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Reverse Divide st(0) by 32-bit or 64-bit FP value (FPU).
		inline void fdivr( const CMem& src )
		{
			m_PU._emitInstruction( INST_FDIVR, &src );
		}

		//------------------------------------------------------------------------------
		//Reverse Divide reg by st(0) (FPU).
		inline void fdivrp( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FDIVRP, &reg );
		}

		//------------------------------------------------------------------------------
		//Free Floating-Point Register (FPU).
		// Sets the tag in the FPU tag register associated with register reg
		// to empty (11B). The contents of reg and the FPU stack-top pointer
		// (TOP) are not affected.
		inline void ffree( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FFREE, &reg );
		}

		//------------------------------------------------------------------------------
		//Add 16-bit or 32-bit integer to st(0) (FPU).
		inline void fiadd( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FIADD, &src );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with 16-bit or 32-bit Integer (FPU).
		inline void ficom( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FICOM, &src );
		}

		//------------------------------------------------------------------------------
		//Compare st(0) with 16-bit or 32-bit Integer and pop the stack (FPU).
		inline void ficomp( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FICOMP, &src );
		}

		//------------------------------------------------------------------------------
		//Divide st(0) by 32-bit or 16-bit integer (FPU).
		inline void fidiv( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FIDIV, &src );
		}

		//------------------------------------------------------------------------------
		//Reverse Divide st(0) by 32-bit or 16-bit integer (FPU).
		inline void fidivr( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FIDIVR, &src );
		}

		//------------------------------------------------------------------------------
		//Load 16-bit, 32-bit or 64-bit Integer and push it to the stack (FPU).
		//
		// Converts the signed-integer source operand into double extended-precision
		// floating point format and pushes the value onto the FPU register stack.
		// The source operand can be a word, doubleword, or quadword integer. It is
		// loaded without rounding errors. The sign of the source operand is
		// preserved.
		inline void fild( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4 || src.getSize() == 8);
			m_PU._emitInstruction( INST_FILD, &src );
		}

		//------------------------------------------------------------------------------
		//Multiply st(0) by 16-bit or 32-bit integer and store it to st(0) (FPU).
		inline void fimul( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FIMUL, &src );
		}

		//------------------------------------------------------------------------------
		//Increment Stack-Top Pointer (FPU).
		// Adds one to the TOP field of the FPU status word (increments the
		// top-of-stack pointer). If the TOP field contains a 7, it is set to 0.
		// The effect of this instruction is to rotate the stack by one position.
		// The contents of the FPU data registers and tag register are not affected.
		// This operation is not equivalent to popping the stack, because the tag
		// for the previous top-of-stack register is not marked empty.
		inline void fincstp()
		{
			m_PU._emitInstruction( INST_FINCSTP );
		}

		//------------------------------------------------------------------------------
		//Initialize Floating-Point Unit (FPU).
		//
		// Initialize FPU after checking for pending unmasked floating-point exceptions.
		inline void finit()
		{
			m_PU._emitInstruction( INST_FINIT );
		}

		//------------------------------------------------------------------------------
		//Subtract 16-bit or 32-bit integer from st(0) and store result to st(0) (FPU).
		inline void fisub( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FISUB, &src );
		}

		//------------------------------------------------------------------------------
		//Reverse Subtract 16-bit or 32-bit integer from st(0) and
		// store result to  st(0) (FPU).
		inline void fisubr( const CMem& src )
		{
			//assert(src.getSize() == 2 || src.getSize() == 4);
			m_PU._emitInstruction( INST_FISUBR, &src );
		}

		//------------------------------------------------------------------------------
		//Initialize Floating-Point Unit (FPU).
		// Initialize FPU without checking for pending unmasked floating-point
		// exceptions.
		inline void fninit()
		{
			m_PU._emitInstruction( INST_FNINIT );
		}

		//------------------------------------------------------------------------------
		//Store st(0) as 16-bit or 32-bit Integer to dst (FPU).
		inline void fist( const CMem& dst )
		{
			//assert(dst.getSize() == 2 || dst.getSize() == 4);
			m_PU._emitInstruction( INST_FIST, &dst );
		}

		//------------------------------------------------------------------------------
		//Store st(0) as 16-bit, 32-bit or 64-bit Integer to dst and pop
		// stack (FPU).
		inline void fistp( const CMem& dst )
		{
			//assert(dst.getSize() == 2 || dst.getSize() == 4 || dst.getSize() == 8);
			m_PU._emitInstruction( INST_FISTP, &dst );
		}

		//------------------------------------------------------------------------------
		//Push 32-bit, 64-bit or 80-bit Floating Point Value onto the FPU
		// register stack (FPU).
		inline void fld( const CMem& src )
		{
			//assert(src.getSize() == 4 || src.getSize() == 8 || src.getSize() == 10);
			m_PU._emitInstruction( INST_FLD, &src );
		}

		//------------------------------------------------------------------------------
		//Push reg onto the FPU register stack (FPU).
		inline void fld( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FLD, &reg );
		}

		//------------------------------------------------------------------------------
		//Push +1.0 onto the FPU register stack (FPU).
		inline void fld1()
		{
			m_PU._emitInstruction( INST_FLD1 );
		}

		//------------------------------------------------------------------------------
		//Push log2(10) onto the FPU register stack (FPU).
		inline void fldl2t()
		{
			m_PU._emitInstruction( INST_FLDL2T );
		}

		//------------------------------------------------------------------------------
		//Push log2(e) onto the FPU register stack (FPU).
		inline void fldl2e()
		{
			m_PU._emitInstruction( INST_FLDL2E );
		}

		//------------------------------------------------------------------------------
		//Push pi onto the FPU register stack (FPU).
		inline void fldpi()
		{
			m_PU._emitInstruction( INST_FLDPI );
		}

		//------------------------------------------------------------------------------
		//Push log10(2) onto the FPU register stack (FPU).
		inline void fldlg2()
		{
			m_PU._emitInstruction( INST_FLDLG2 );
		}

		//------------------------------------------------------------------------------
		//Push ln(2) onto the FPU register stack (FPU).
		inline void fldln2()
		{
			m_PU._emitInstruction( INST_FLDLN2 );
		}

		//------------------------------------------------------------------------------
		//Push +0.0 onto the FPU register stack (FPU).
		inline void fldz()
		{
			m_PU._emitInstruction( INST_FLDZ );
		}

		//------------------------------------------------------------------------------
		//Load x87 FPU Control Word (2 bytes) (FPU).
		inline void fldcw( const CMem& src )
		{
			m_PU._emitInstruction( INST_FLDCW, &src );
		}

		//------------------------------------------------------------------------------
		//Load x87 FPU Environment (14 or 28 bytes) (FPU).
		inline void fldenv( const CMem& src )
		{
			m_PU._emitInstruction( INST_FLDENV, &src );
		}

		//------------------------------------------------------------------------------
		//Multiply dst by src and store result in dst (FPU).
		//
		// Note One of dst or src must be st(0).
		inline void fmul( const CX87Reg& dst, const CX87Reg& src )
		{
			//assert(dst.getRegIndex() == 0 || src.getRegIndex() == 0);
			m_PU._emitInstruction( INST_FMUL, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Multiply st(0) by src and store result in st(0) (FPU).
		//
		// Note SP-FP or DP-FP determined by adr size.
		inline void fmul( const CMem& src )
		{
			m_PU._emitInstruction( INST_FMUL, &src );
		}

		//------------------------------------------------------------------------------
		//Multiply st(0) by dst and POP register stack (FPU).
		inline void fmulp( const CX87Reg& dst = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FMULP, &dst );
		}

		//------------------------------------------------------------------------------
		//Clear Exceptions (FPU).
		//
		// Clear floating-point exception flags without checking for pending
		// unmasked floating-point exceptions.
		//
		// Clears the floating-point exception flags (PE, UE, OE, ZE, DE, and IE),
		// the exception summary status flag (ES), the stack fault flag (SF), and
		// the busy flag (B) in the FPU status word. The FCLEX instruction does
		// not checks for and handles any pending unmasked floating-point exceptions
		// before clearing the exception flags.
		inline void fnclex()
		{
			m_PU._emitInstruction( INST_FNCLEX );
		}

		//------------------------------------------------------------------------------
		//No Operation (FPU).
		inline void fnop()
		{
			m_PU._emitInstruction( INST_FNOP );
		}

		//------------------------------------------------------------------------------
		//Save FPU State (FPU).
		//
		// Store FPU environment to m94byte or m108byte without
		// checking for pending unmasked FP exceptions.
		// Then re-initialize the FPU.
		inline void fnsave( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FNSAVE, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Environment (FPU).
		//
		// Store FPU environment to dst (14 or 28 Bytes) without checking for
		// pending unmasked floating-point exceptions. Then mask all floating
		// point exceptions.
		inline void fnstenv( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FNSTENV, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Control Word (FPU).
		//
		// Store FPU control word to dst (2 Bytes) without checking for pending
		// unmasked floating-point exceptions.
		inline void fnstcw( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FNSTCW, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Status Word (2 Bytes) (FPU).
		inline void fnstsw( const CGPReg& dst )
		{
			//assert(dst.isRegCode(REG_AX));
			m_PU._emitInstruction( INST_FNSTSW, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Status Word (2 Bytes) (FPU).
		inline void fnstsw( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FNSTSW, &dst );
		}

		//------------------------------------------------------------------------------
		//Partial Arctangent (FPU).
		//
		// Replace st(1) with arctan(st(1)/st(0)) and pop the register stack.
		inline void fpatan()
		{
			m_PU._emitInstruction( INST_FPATAN );
		}

		//------------------------------------------------------------------------------
		//Partial Remainder (FPU).
		// Replace st(0) with the remainder obtained from dividing st(0) by st(1).
		inline void fprem()
		{
			m_PU._emitInstruction( INST_FPREM );
		}

		//------------------------------------------------------------------------------
		//Partial Remainder (FPU).
		// Replace st(0) with the IEEE remainder obtained from dividing st(0) by
		// st(1).
		inline void fprem1()
		{
			m_PU._emitInstruction( INST_FPREM1 );
		}

		//------------------------------------------------------------------------------
		//Partial Tangent (FPU).
		// Replace st(0) with its tangent and push 1 onto the FPU stack.
		inline void fptan()
		{
			m_PU._emitInstruction( INST_FPTAN );
		}

		//------------------------------------------------------------------------------
		//Round to Integer (FPU).
		//
		// Rount st(0) to an Integer.
		inline void frndint()
		{
			m_PU._emitInstruction( INST_FRNDINT );
		}

		//------------------------------------------------------------------------------
		//Restore FPU State (FPU).
		//
		// Load FPU state from src (94 or 108 bytes).
		inline void frstor( const CMem& src )
		{
			m_PU._emitInstruction( INST_FRSTOR, &src );
		}

		//------------------------------------------------------------------------------
		//Save FPU State (FPU).
		// Store FPU state to 94 or 108-bytes after checking for
		// pending unmasked FP exceptions. Then reinitialize
		// the FPU.
		inline void fsave( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FSAVE, &dst );
		}

		//------------------------------------------------------------------------------
		//Scale (FPU).
		// Scale st(0) by st(1).
		inline void fscale()
		{
			m_PU._emitInstruction( INST_FSCALE );
		}

		//------------------------------------------------------------------------------
		//Sine (FPU).
		// This instruction calculates the sine of the source operand in
		// register st(0) and stores the result in st(0).
		inline void fsin()
		{
			m_PU._emitInstruction( INST_FSIN );
		}

		//------------------------------------------------------------------------------
		//Sine and Cosine (FPU).
		// Compute the sine and cosine of st(0); replace st(0) with
		// the sine, and push the cosine onto the register stack.
		inline void fsincos()
		{
			m_PU._emitInstruction( INST_FSINCOS );
		}

		//------------------------------------------------------------------------------
		//Square Root (FPU).
		// Calculates square root of st(0) and stores the result in st(0).
		inline void fsqrt()
		{
			m_PU._emitInstruction( INST_FSQRT );
		}

		//------------------------------------------------------------------------------
		//Store Floating Point Value (FPU).
		//
		// Store st(0) as 32-bit or 64-bit floating point value to dst.
		inline void fst( const CMem& dst )
		{
			//assert(dst.getSize() == 4 || dst.getSize() == 8);
			m_PU._emitInstruction( INST_FST, &dst );
		}

		//------------------------------------------------------------------------------
		//Store Floating Point Value (FPU).
		//
		// Store st(0) to reg.
		inline void fst( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FST, &reg );
		}

		//------------------------------------------------------------------------------
		//Store Floating Point Value and Pop Register Stack (FPU).
		//
		// Store st(0) as 32-bit or 64-bit floating point value to dst
		// and pop register stack.
		inline void fstp( const CMem& dst )
		{
			//assert(dst.getSize() == 4 || dst.getSize() == 8 || dst.getSize() == 10);
			m_PU._emitInstruction( INST_FSTP, &dst );
		}

		//------------------------------------------------------------------------------
		//Store Floating Point Value and Pop Register Stack (FPU).
		//
		// Store st(0) to reg and pop register stack.
		inline void fstp( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FSTP, &reg );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Control Word (FPU).
		//
		// Store FPU control word to dst (2 Bytes) after checking for pending
		// unmasked floating-point exceptions.
		inline void fstcw( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FSTCW, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Environment (FPU).
		//
		// Store FPU environment to dst (14 or 28 Bytes) after checking for
		// pending unmasked floating-point exceptions. Then mask all floating
		// point exceptions.
		inline void fstenv( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FSTENV, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Status Word (2 Bytes) (FPU).
		inline void fstsw( const CGPReg& dst )
		{
			//assert(dst.isRegCode(REG_AX));
			m_PU._emitInstruction( INST_FSTSW, &dst );
		}

		//------------------------------------------------------------------------------
		//Store x87 FPU Status Word (2 Bytes) (FPU).
		inline void fstsw( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FSTSW, &dst );
		}

		//------------------------------------------------------------------------------
		//Subtract src from dst and store result in dst (FPU).
		//
		// Note One of dst or src must be st(0).
		inline void fsub( const CX87Reg& dst, const CX87Reg& src )
		{
			//assert(dst.getRegIndex() == 0 || src.getRegIndex() == 0);
			m_PU._emitInstruction( INST_FSUB, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Subtract src from st(0) and store result in st(0) (FPU).
		//
		// Note SP-FP or DP-FP determined by adr size.
		inline void fsub( const CMem& src )
		{
			//assert(src.getSize() == 4 || src.getSize() == 8);
			m_PU._emitInstruction( INST_FSUB, &src );
		}

		//------------------------------------------------------------------------------
		//Subtract st(0) from dst and POP register stack (FPU).
		inline void fsubp( const CX87Reg& dst = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FSUBP, &dst );
		}

		//------------------------------------------------------------------------------
		//Reverse Subtract src from dst and store result in dst (FPU).
		//
		// Note One of dst or src must be st(0).
		inline void fsubr( const CX87Reg& dst, const CX87Reg& src )
		{
			//assert(dst.getRegIndex() == 0 || src.getRegIndex() == 0);
			m_PU._emitInstruction( INST_FSUBR, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Reverse Subtract src from st( 0 ) and store result in st( 0 ) (FPU).
		//
		// Note SP-FP or DP-FP determined by adr size.
		inline void fsubr( const CMem& src )
		{
			//assert(src.getSize() == 4 || src.getSize() == 8);
			m_PU._emitInstruction( INST_FSUBR, &src );
		}

		//------------------------------------------------------------------------------
		//Reverse Subtract st(0) from dst and POP register stack (FPU).
		inline void fsubrp( const CX87Reg& dst = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FSUBRP, &dst );
		}

		//------------------------------------------------------------------------------
		//Floating point test - Compare st(0) with 0.0. (FPU).
		inline void ftst()
		{
			m_PU._emitInstruction( INST_FTST );
		}

		//------------------------------------------------------------------------------
		//Unordered Compare st(0) with reg (FPU).
		inline void fucom( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FUCOM, &reg );
		}

		//------------------------------------------------------------------------------
		//Unordered Compare st(0) and reg, check for ordered values and Set EFLAGS (FPU).
		inline void fucomi( const CX87Reg& reg )
		{
			m_PU._emitInstruction( INST_FUCOMI, &reg );
		}

		//------------------------------------------------------------------------------
		//UnorderedCompare st(0) and reg, Check for ordered values and Set EFLAGS and pop the stack (FPU).
		inline void fucomip( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FUCOMIP, &reg );
		}

		//------------------------------------------------------------------------------
		//Unordered Compare st(0) with reg and pop register stack (FPU).
		inline void fucomp( const CX87Reg& reg = st( 1 ) )
		{
			m_PU._emitInstruction( INST_FUCOMP, &reg );
		}

		//------------------------------------------------------------------------------
		//Unordered compare st(0) with st(1) and pop register stack twice
		// (FPU).
		inline void fucompp()
		{
			m_PU._emitInstruction( INST_FUCOMPP );
		}

		//------------------------------------------------------------------------------
		inline void fwait()
		{
			m_PU._emitInstruction( INST_FWAIT );
		}

		//------------------------------------------------------------------------------
		//Examine st(0) (FPU).
		//
		// Examines the contents of the ST(0) register and sets the condition code
		// flags C0, C2, and C3 in the FPU status word to indicate the class of
		// value or number in the register.
		inline void fxam()
		{
			m_PU._emitInstruction( INST_FXAM );
		}

		//------------------------------------------------------------------------------
		//Exchange Register Contents (FPU).
		//
		// Exchange content of st(0) with reg.
		inline void fxch( const CX87Reg& reg = st( 1 ) ) 
		{
			m_PU._emitInstruction( INST_FXCH, &reg );
		}

		//------------------------------------------------------------------------------
		//Restore FP And MMX(tm) State And Streaming SIMD Extension State
		// (FPU, MMX, SSE).
		//
		// Load FP and MMX(tm) technology and Streaming SIMD Extension state from src (512 bytes).
		inline void fxrstor( const CMem& src )
		{
			m_PU._emitInstruction( INST_FXRSTOR, &src );
		}

		//------------------------------------------------------------------------------
		//Store FP and MMX(tm) State and Streaming SIMD Extension State (FPU, MMX, SSE).
		// Store FP and MMX(tm) technology state and Streaming SIMD Extension state to dst (512 bytes).
		inline void fxsave( const CMem& dst )
		{
			m_PU._emitInstruction( INST_FXSAVE, &dst );
		}

		//------------------------------------------------------------------------------
		//Extract Exponent and Significand (FPU).
		//
		// Separate value in st(0) into exponent and significand, store exponent
		// in st(0), and push the significand onto the register stack.
		inline void fxtract()
		{
			m_PU._emitInstruction( INST_FXTRACT );
		}

		//------------------------------------------------------------------------------
		//Compute y * log2(x).
		// Replace st(1) with (st(1) * log2st(0)) and pop the register stack.
		inline void fyl2x()
		{
			m_PU._emitInstruction( INST_FYL2X );
		}

		//------------------------------------------------------------------------------
		//Compute y * log_2(x+1).
		// Replace st(1) with (st(1) * (log2st(0) + 1.0)) and pop the register stack.
		inline void fyl2xp1()
		{
			m_PU._emitInstruction( INST_FYL2XP1 );
		}

		
		//--------------------------------------------------------------------------------
		virtual int feclearexcept( int /*excepts*/ )
		{
			/*
			fenv_t _env;
			excepts &= FE_ALL_EXCEPT;
			__asm__ volatile ("fnstenv %0;" : "=m" (_env)); // get the env
			_env.__status_word &= ~excepts; // clear the except
			__asm__ volatile ("fldenv %0;" :: "m" (_env)); //set the env
			*/

            /*
			__asm
			{
				sub	esp, 0x2c
				mov eax, dword ptr [esp + 48]
				fnstenv	 dword ptr [esp]
				mov edx, dword ptr [esp+4]
				and eax, 0x3f
				not eax
				and eax, edx
				mov dword ptr [esp+4], eax
				fldenv dword ptr [esp]
				xor eax, eax
				add esp, 0x2c
				ret
			}
			*/

			/*
			if (__HAS_SSE)
			{
				unsigned _csr;
				__asm__ volatile("stmxcsr %0" : "=m" (_csr)); // get the register
				_csr &= ~excepts; // clear the except
				__asm__ volatile("ldmxcsr %0" : : "m" (_csr)); // set the register
			}
			*/
			return 0;
		}

		virtual int fegetexceptflag( fexcept_t* /*flagp*/, int /*excepts*/ )
		{
			///TODO:
			/*
			unsigned short _sw;
			__asm__ ("fnstsw %%ax;": "=a" (_sw));
			*flagp = _sw  & excepts & FE_ALL_EXCEPT;
			*/
			return 0;
		}

		virtual int feraiseexcept( int /*excepts*/ )
		{
			///TODO:
			/*
			fenv_t _env;
			__asm__ volatile ("fnstenv %0;" : "=m" (_env));
			_env.__status_word |= excepts & FE_ALL_EXCEPT;
			__asm__ volatile ("fldenv %0;"
			"fwait;" : : "m" (_env));
			*/
			return 0;		
		}

		virtual int fesetexceptflag( const fexcept_t* /*flagp*/, int /*excepts*/ )
		{
			///TODO:
			/*
			fenv_t _env;

			excepts &= FE_ALL_EXCEPT;
			__asm__ volatile ("fnstenv %0;" : "=m" (_env));
			_env.__status_word &= ~excepts;
			_env.__status_word |= (*flagp & excepts);
			__asm__ volatile ("fldenv %0;" : : "m" (_env));

			if (__HAS_SSE)
			{
			unsigned int _csr;
			__asm__ __volatile__("stmxcsr %0" : "=m" (_csr));
			_csr &= ~excepts;
			_csr |= *flagp & excepts;
			__asm__ volatile ("ldmxcsr %0" : : "m" (_csr));
			}
			*/
			return 0;
		}

		virtual int fetestexcept( int /*excepts*/ )
		{
			///TODO:
			//unsigned int _res;
			/*
			__asm__ ("fnstsw %%ax" : "=a" (_res));


			// If SSE supported, return the union of the FPU and SSE flags.
			if (__HAS_SSE)
			{     
			unsigned int _csr; 	
			__asm__ volatile("stmxcsr %0" : "=m" (_csr));
			_res |= _csr;    
			}

			return (_res & excepts & FE_ALL_EXCEPT);
			*/
			return 0;
		}

		virtual int fegetround( void )
		{
			///TODO:
			/*
			unsigned short _cw;
			__asm__ ("fnstcw %0;"	: "=m" (_cw));

			// If the MXCSR flag is different, there is no way to indicate, so just report the FPU flag.
			return _cw & ( FE_TONEAREST | FE_DOWNWARD | FE_UPWARD | FE_TOWARDZERO );
			*/
			return 0;
		}

		virtual int fesetround( int /*round*/ )
		{
			///TODO:
			/*
			unsigned short _cw;
			if ((mode & ~(FE_TONEAREST | FE_DOWNWARD | FE_UPWARD | FE_TOWARDZERO))
			!= 0)
			return -1;
			__asm__ volatile ("fnstcw %0;": "=m" (_cw));
			_cw &= ~(FE_TONEAREST | FE_DOWNWARD | FE_UPWARD | FE_TOWARDZERO);
			_cw |= mode;
			__asm__ volatile ("fldcw %0;" : : "m" (_cw));

			if (__HAS_SSE)
			{
			unsigned int _mxcsr;
			__asm__ volatile ("stmxcsr %0" : "=m" (_mxcsr));
			_mxcsr &= ~ 0x6000;
			_mxcsr |= (mode <<  __MXCSR_ROUND_FLAG_SHIFT);
			__asm__ volatile ("ldmxcsr %0" : : "m" (_mxcsr));
			}
			*/
			return 0;
		}

		virtual int fegetenv( fenv_t* /*envp*/ )
		{
			///TODO:
			/*
			__asm__ ("fnstenv %0;": "=m" (*envp));
			// fnstenv sets control word to non-stop for all exceptions, so we need to reload our env to restore the original mask.
			__asm__ ("fldenv %0" : : "m" (*envp));
			// And the SSE environment.
			if (__HAS_SSE)
			{
				__asm__ ("stmxcsr %0" : "=m" (envp->__mxcsr));
			}
			*/
			return 0;
		}

		virtual int feholdexcept( fenv_t* /*envp*/ )
		{
			///TODO:
			/*
			__asm__ ("fnstenv %0;" : "=m" (* envp)); // save current into envp
			// fnstenv sets control word to non-stop for all exceptions, so all we need to do is clear the exception flags.
			__asm__ ("fnclex");

			if (__HAS_SSE)
			{
				unsigned int _csr;
				// Save the SSE MXCSR register. 
				__asm__ ("stmxcsr %0" :  "=m" (envp->__mxcsr));  
				// Clear the exception flags.
				_csr = envp->__mxcsr & ~FE_ALL_EXCEPT;
				// Set exception mask to non-stop 
				_csr |= (FE_ALL_EXCEPT << __MXCSR_EXCEPT_MASK_SHIFT); //= 0x1f80
				__asm__ volatile ("ldmxcsr %0" : : "m" (_csr));
			} 
			*/
			return 0;
		}

		virtual int fesetenv( const fenv_t* /*envp*/ )
		{
			///TODO
			/*
			// Default mxcsr status is to mask all exceptions.  All other bits are zero.
			unsigned int _csr = FE_ALL_EXCEPT << __MXCSR_EXCEPT_MASK_SHIFT; //= 0x1f80

			if( envp == FE_PC64_ENV )
			{
				//fninit initializes the control register to 0x37f,
				// the status register to zero and the tag word to 0FFFFh.
				// The other registers are unaffected.
				__asm__ ("fninit");
			}
			else if( envp == FE_PC53_ENV )
			{
				//MS _fpreset() does same *except* it sets control word
				// to 0x27f (53-bit precison).
				// We force calling _fpreset in msvcrt.dll

				(*_imp___fpreset)();
			}
			else if( envp == FE_DFL_ENV )
			{
				// Use the choice made at app startup
				_fpreset();
			}
			else
			{
				__asm__ ("fldenv %0;" : : "m" (*envp));
				// Setting the reserved high order bits of MXCSR causes a segfault
				_csr = envp ->__mxcsr & 0xffff;
			}

			// Set MXCSR
			if( __HAS_SSE )
			{
				__asm__ volatile ("ldmxcsr %0" : : "m" (_csr));
			}
			*/
			return 0;
		}

		virtual int feupdateenv( const fenv_t* /*envp*/ )
		{
			///TODO:
			/*
			unsigned int _fexcept;
			__asm__ ("fnstsw %%ax" : "=a" (_fexcept)); //save excepts
			if (__HAS_SSE)
			{
				unsigned int  _csr;
				__asm__ ("stmxcsr %0" : "=m" (_csr));
				_fexcept |= _csr;
			}
			fesetenv( envp ); // install the env
			feraiseexcept( _fexcept & FE_ALL_EXCEPT ); // raise the execeptions
			*/
			return 0;
		}

		__QCS_DECLARE_NONCOPYABLE( C387FPU );

	};

}//nsx86
}//nsArch

#endif//ARCHQOR_X86PC_I387FPU_H_2