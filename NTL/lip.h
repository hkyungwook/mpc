/**
 * Copyright (C) 2011, http://www.cs.umd.edu, http://www.cs.columbia.edu
 *
 * This file is part of "GMW".
 *
 * "GMW" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Seung Geol Choi (sgchoi@cs.umd.edu)
 * @date 8. 1. 2011
 *
 */
#ifndef NTL_g_lip__H
#define NTL_g_lip__H

#define __MULTI_THREADED

#ifdef __MULTI_THREADED
#define _STATIC_ST	
#define _CLEAR_Z(x)	_ntl_zfree(&x)
#else
#define _STATIC_ST	static
#define _CLEAR_Z(x)	
#endif


#include <NTL/config.h>
#include <NTL/mach_desc.h>

#ifdef NTL_GMP_LIP

#include <NTL/gmp_aux.h>

#include <NTL/g_lip.h>

#else

#include <NTL/c_lip.h>

#endif

#endif
