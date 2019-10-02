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
#ifndef NTL_new__H
#define NTL_new__H

#include <NTL/config.h>

#if (defined(NTL_STD_CXX) || defined(NTL_PSTD_NTN))

// We use <new> and std::nothrow, even if neither NTL_STD_CXX nor  
// NTL_PSTD_NHF are set.  This appears to be somewhat more compatible
// with current compilers.

#include <new>

#define NTL_NEW_OP new (std::nothrow)


#else

#define NTL_NEW_OP new

#endif

#endif
