//error.h

# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */

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

#ifndef QOR_PREPROCESSOR_DEBUG_ERROR_H_1
#define QOR_PREPROCESSOR_DEBUG_ERROR_H_1

#include "../cat.h"
#include "../config/config.h"

//QOR_PP_ERROR

#if QOR_PP_CONFIG_ERRORS
#	define QOR_PP_ERROR( code )		QOR_PP_CAT( QOR_PP_ERROR_, code )
#endif

#define QOR_PP_ERROR_0x0000			QOR_PP_ERROR( 0x0000, QOR_PP_INDEX_OUT_OF_BOUNDS )
#define QOR_PP_ERROR_0x0001			QOR_PP_ERROR( 0x0001, QOR_PP_WHILE_OVERFLOW )
#define QOR_PP_ERROR_0x0002			QOR_PP_ERROR( 0x0002, QOR_PP_FOR_OVERFLOW )
#define QOR_PP_ERROR_0x0003			QOR_PP_ERROR( 0x0003, QOR_PP_REPEAT_OVERFLOW )
#define QOR_PP_ERROR_0x0004			QOR_PP_ERROR( 0x0004, QOR_PP_LIST_FOLD_OVERFLOW )
#define QOR_PP_ERROR_0x0005			QOR_PP_ERROR( 0x0005, QOR_PP_SEQ_FOLD_OVERFLOW )
#define QOR_PP_ERROR_0x0006			QOR_PP_ERROR( 0x0006, QOR_PP_ARITHMETIC_OVERFLOW )
#define QOR_PP_ERROR_0x0007			QOR_PP_ERROR( 0x0007, QOR_PP_DIVISION_BY_ZERO )

#endif//QOR_PREPROCESSOR_DEBUG_ERROR_H_1