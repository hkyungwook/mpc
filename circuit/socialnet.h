// socialnet.h
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
#ifndef __SOCIAL_NET__H__BY_SGCHOI_
#define __SOCIAL_NET__H__BY_SGCHOI_
 
#include "circuit.h"
#include <cassert>

class CSNetCircuit : public CCircuit
{
public:
	BOOL Create(int nParties, const vector<int>& vParams);
 
public:
	void CreateFindAllCloseMatches();
	void PutOutputLayer();
	void PutLayerI();
	void SetupIndices();
	void PutLayerB();
	int  PutELMGate(int r);
	int	 PutIdxGate(int r);
	int	 PutDSTGate(int r);
	int	 PutCAPGate(int r);
	int	 PutCNTGate(int r);
	int	 PutINGate(int r);
	int	 PutCNTGate(const vector<int>&, int rep);
	void SetupInputGates();

private:
	enum ProtType
	{
		e_AllCloseMatches = 0,
		e_ClosetMatch = 1,
		e_BestResource = 2,
	}; 

	int		m_nType;
	int		m_nTotItems;
	int		m_nRep;
	int		m_nIdxRep;
	int		m_nIdxStart;
	int		m_nCntRep;
	int		m_nCntRange;


	vector<int>	m_vELMs;
	vector<int>	m_vIdxs;
};

#endif //__SOCIAL_NET__H__BY_SGCHOI_
