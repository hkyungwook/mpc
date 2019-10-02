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
#ifndef __P2P_CIRCUIT_H__BY_SGCHOI_
#define __P2P_CIRCUIT_H__BY_SGCHOI_

#include "circuit.h"

class CP2PCircuit : public CCircuit
{

public:
	CP2PCircuit(){}
	~CP2PCircuit(){}

// public interface
public:
	BOOL Create(int nParties, const vector<int>& vParams); // for multi-party computation
 	
private:
	void PutOutputLayer();
	void PutLayerI();
	void SetupIndices();
	void PutLayerB();
	int  PutELMGate(int r);
	int	 PutIdxGate(int r);
	void SetupInputGates();

private:
	int		m_nItems;
	int		m_nTotItems;
	int		m_nRep;
	int		m_nIdxRep;

	vector<int>	m_vELMs;
	vector<int>	m_vIdxs;
};

#endif // __P2P_CIRCUIT_H__BY_SGCHOI_

