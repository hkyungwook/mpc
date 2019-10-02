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
#include <NTL/ctools.h>


#include <stdlib.h>
#include <math.h>

#if (defined(NTL_CXX_ONLY) && !defined(__cplusplus))
#error "CXX_ONLY flag set...must use C++ compiler"
#endif

/*
 * An IEEE double x is finite if and only if x - x == 0.
 * The function _ntl_IsFinite implements this logic;  however,
 * it does not completely trust that an optimizing compiler
 * really implements this correctly, and so it goes out of its way to
 * confuse the compiler.  For a good compiler that respects IEEE floating
 * point arithmetic, this is not be necessary, but it is better
 * to be a bit paranoid.
 *
 * Like the routine _ntl_ForceToMem below, this routine has the
 * side effect of forcing its argument into memory.
 */

double _ntl_IsFinite__local;
double *_ntl_IsFinite__ptr1 = &_ntl_IsFinite__local;
double *_ntl_IsFinite__ptr2 = &_ntl_IsFinite__local;
double *_ntl_IsFinite__ptr3 = &_ntl_IsFinite__local;
double *_ntl_IsFinite__ptr4 = &_ntl_IsFinite__local;

long _ntl_IsFinite(double *p)
{
   *_ntl_IsFinite__ptr1 = *p;
   *_ntl_IsFinite__ptr3 = (*_ntl_IsFinite__ptr2 - *p);
   if (*_ntl_IsFinite__ptr4 != 0.0) return 0;
   return 1;
}


/*
 * On machines with wide floating point registers, the routine _ntl_ForceToMem
 * is used to force a floating point double to a memory location.
 * This relies on "separate compilation" model, so that optimizing
 * compilers cannot "optimize away" the whole thing.
 */


void _ntl_ForceToMem(double *p)
{ }



/*
 * The routine _ntl_ldexp(x, e) is like the standard ldexp(x, e) routine,
 * except that it takes a long exponent e, rather than an int exponenet.
 * Some care is taken to ensure reasonable overflow/undeflow behavior.
 * If the value of e does not fit into an int, then the result
 * is x*infinity or x*0, as appropriate.
 * Of course, this can only happen on platforms where long is wider
 * than int (e.g., most 64-bit platforms).
 *
 * We go out of our way to hide the fact that we are multiplying/dividing
 * by zero, so as to avoid unnecessary warnings, and to prevent 
 * overly-agressive optimizing compilers from screwing things up.
 */

double _ntl_ldexp_zero = 0.0;

double _ntl_ldexp(double x, long e)
{
   if (e > NTL_MAX_INT)
      return x/_ntl_ldexp_zero;
   else if (e < NTL_MIN_INT)
      return x*_ntl_ldexp_zero;
   else
      return ldexp(x, ((int) e));
}


void _ntl_abort(void)
{
   _ntl_abort_cxx_callback();
   abort();
}



