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
#ifndef __SI_CIRCUIT_H__BY_SGCHOI_
#define __SI_CIRCUIT_H__BY_SGCHOI_

#include "circuit.h"
#include <cassert>

class CSICircuit : public CCircuit
{
public:
	BOOL Create(int nParties, const vector<int>& vParams);


private:
	void AddEqualityBlock(int Pi, int Pj);
	void ConstructOutput(int i);

	int INDEX(int Pi, int Pj)
	{ 
		return Pi*m_nNumParties + Pj;
	}
	
	int ITEM(int Pi, int Pj, int i, int j)
	{ 
		return i*m_vSizes[Pj] + j; 
	}

private:
	int						m_nNumVBits;
	vector<int>				m_vSizes;
	vector<int>				m_vAggSizes;
	vector<BOOL>			m_vNeedOutput;
	vector<int>				m_vMatchIdxStart;
};

#endif //__SI_CIRCUIT_H__BY_SGCHOI_