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
#ifndef NTL_vec_ZZ__H
#define NTL_vec_ZZ__H

#include <NTL/ZZ.h>
#include <NTL/vector.h>

NTL_OPEN_NNS

NTL_vector_decl(ZZ,vec_ZZ)

NTL_eq_vector_decl(ZZ,vec_ZZ)

NTL_io_vector_decl(ZZ,vec_ZZ)

void mul(vec_ZZ& x, const vec_ZZ& a, const ZZ& b);
inline void mul(vec_ZZ& x, const ZZ& a, const vec_ZZ& b)
   { mul(x, b, a); }

void mul(vec_ZZ& x, const vec_ZZ& a, long b);
inline void mul(vec_ZZ& x, long a, const vec_ZZ& b)
   { mul(x, b, a); }

void add(vec_ZZ& x, const vec_ZZ& a, const vec_ZZ& b);

void sub(vec_ZZ& x, const vec_ZZ& a, const vec_ZZ& b);
void clear(vec_ZZ& x);
void negate(vec_ZZ& x, const vec_ZZ& a);




void InnerProduct(ZZ& x, const vec_ZZ& a, const vec_ZZ& b);

long IsZero(const vec_ZZ& a);

vec_ZZ operator+(const vec_ZZ& a, const vec_ZZ& b);
vec_ZZ operator-(const vec_ZZ& a, const vec_ZZ& b);
vec_ZZ operator-(const vec_ZZ& a);

inline vec_ZZ operator*(const vec_ZZ& a, const ZZ& b)
   { vec_ZZ x; mul(x, a, b); NTL_OPT_RETURN(vec_ZZ, x); }

inline vec_ZZ operator*(const vec_ZZ& a, long b)
   { vec_ZZ x; mul(x, a, b); NTL_OPT_RETURN(vec_ZZ, x); }

inline vec_ZZ operator*(const ZZ& a, const vec_ZZ& b)
   { vec_ZZ x; mul(x, a, b); NTL_OPT_RETURN(vec_ZZ, x); }

inline vec_ZZ operator*(long a, const vec_ZZ& b)
   { vec_ZZ x; mul(x, a, b); NTL_OPT_RETURN(vec_ZZ, x); }


ZZ operator*(const vec_ZZ& a, const vec_ZZ& b);





// assignment operator notation:

inline vec_ZZ& operator+=(vec_ZZ& x, const vec_ZZ& a)
{ 
   add(x, x, a);
   return x;
}

inline vec_ZZ& operator-=(vec_ZZ& x, const vec_ZZ& a)
{ 
   sub(x, x, a);
   return x;
}

inline vec_ZZ& operator*=(vec_ZZ& x, const ZZ& a)
{ 
   mul(x, x, a);
   return x;
}

inline vec_ZZ& operator*=(vec_ZZ& x, long a)
{ 
   mul(x, x, a);
   return x;
}

void VectorCopy(vec_ZZ& x, const vec_ZZ& a, long n);
inline vec_ZZ VectorCopy(const vec_ZZ& a, long n)
   { vec_ZZ x; VectorCopy(x, a, n); NTL_OPT_RETURN(vec_ZZ, x); }


NTL_CLOSE_NNS


#endif
