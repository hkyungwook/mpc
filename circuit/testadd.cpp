// testadd.cpp
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
#include "testadd.h"
#include <cassert>
using namespace std;

BOOL CTestAddCircuit::Create(int nParties, const vector<int>& vParams)
{
	m_nNumParties = nParties;

	// parse params
	// params: width, depth, rep
	if( vParams.size() < (unsigned) 3 )
	{
		cout << "Error! This circuit needs " << 3  
			 << "parameters: width depth rep"
			 << endl;
		return FALSE;
	}

	m_nWidth = vParams[0];
	m_nDepth = vParams[1];
	m_nRep = vParams[2];
	m_vNumVBits.resize(m_nNumParties, m_nRep);
	
	// gates for inputs: only the first party will have one input
	m_vInputStart.resize(nParties);
	m_vInputEnd.resize(nParties);
		
	m_nFrontier = 2;
	m_vInputStart[0] = m_nFrontier;
	m_nFrontier += m_nRep;
	m_vInputEnd[0] =  m_nFrontier - 1;

	for(int i=1; i<nParties; i++)
	{
		m_vInputStart[i] = 1;
		m_vInputEnd[i] = 0;
	}

	//===========================================================================
	// computes roughly the number of gates beforehand --- need this for allocating space
	// gates for each equality gate:
	// bitwise xor, bitwise negation, AND of each bitwise outputs
	int gates_add = 6*m_nRep; 
	int gates_noninput = m_nDepth * m_nWidth * gates_add + m_nWidth*m_nRep;
	 	
	m_othStartGate = m_nFrontier;
	m_nNumGates = m_nFrontier + gates_noninput;
	m_pGates = new GATE[m_nNumGates];
	m_nNumXORs = 0;

	GATE* gate;

	for(int i=0; i<m_othStartGate; i++)
	{
		gate = m_pGates + i;
		gate->p_ids = 0;
		gate->p_num = 0;
		gate->left = -1;
		gate->right = -1;
		gate->type = 0;
	}

	// Prepare 0-th input layer: 
	// all of them are the first party's input
	m_vLayerInputs.resize(m_nWidth);
	m_vLayerOutputs.resize(m_nWidth,2);
	for(int i=0; i<m_nDepth; i++)
	{
		m_vLayerInputs = m_vLayerOutputs;
		PutAdditionLayer();
	}

	PutOutputLayer();
	PatchParentFields();
	return TRUE;
};

void CTestAddCircuit::PutAdditionLayer()
{
	int size = m_vLayerInputs.size(); 
	for(int i=0; i<size; i++)
	{
		int j = (i+1) % size;
		m_vLayerOutputs[i] = PutAddGate(m_vLayerInputs[i], m_vLayerInputs[j], m_nRep);
	}
}
 
void CTestAddCircuit::PutOutputLayer()
{
	int o_start = m_nFrontier;
	for(int i=0; i<1; i++)
	{
		for(int j=0; j<m_nRep; j++)
		{
			PutXORGate(m_vLayerOutputs[i] + j, 0);
		}
	}
	int o_end = m_nFrontier -1;

	m_vOutputStart.resize(m_nNumParties, o_start);
	m_vOutputEnd.resize(m_nNumParties, o_end);
	m_nNumGates = m_nFrontier;
}

 