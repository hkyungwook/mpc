// p2pcircuit.cpp
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
#include "p2pcircuit.h"
#include <cassert>
#include <cmath>


///=================================================================================
// creates the binary circuit that consits of only gate infomation
// input: the number of items of each server,	
//        range for each item "value"  
// output: void
BOOL CP2PCircuit::Create(int nParties, const vector<int>& vParams)
{
	if( vParams.size() < 2 )
	{
		cout << "Error! This circuit needs two parameters: #items and input_range." << endl;
		return FALSE;
	}
	

	m_nNumParties = nParties;
	int num_servers = nParties - 1;
	m_nItems  = vParams[0];
	int input_range = vParams[1];
		
	m_nTotItems = m_nItems * num_servers;
	m_nIdxRep = (int) ceil(log((double)m_nTotItems+1)/log(2.0)); 
	m_nRep = (int) ceil(log((double)input_range+1)/log(2.0));

	/*
	cout << "m_nIdxrep=" << m_nIdxRep << endl;
	cout << "m_nRep=" << m_nRep << endl;
	cout << "m_nItems=" << m_nItems << endl;
	*/

	m_vNumVBits.resize(m_nNumParties, m_nRep);
	m_vNumVBits[m_nNumParties-1] = 1;

 	// gates for inputs:  
	m_vInputStart.resize(nParties);
	m_vInputEnd.resize(nParties);

	m_nFrontier = 2;
	for(int i=0; i<nParties-1; i++)
	{
		m_vInputStart[i] = m_nFrontier;
		m_nFrontier += m_nRep*m_nItems;
		m_vInputEnd[i] =  m_nFrontier - 1;
	}

	m_vInputStart[nParties-1] = m_nFrontier;
	m_nFrontier += m_nTotItems;
	m_vInputEnd[nParties-1] = m_nFrontier-1;
	    
	//===========================================================================
	// computes roughly the number of gates beforehand --- need this for allocating space
 	int gates_ge =  4*m_nRep+1;
	int gates_mux = 3*m_nRep;
	int gates_idx_mux = 3*m_nIdxRep;
	int gates_elm = gates_mux + 2*gates_ge + 1;
	int gates_tournament =  gates_ge + gates_mux + gates_idx_mux;
	int gates_noninput = m_nTotItems*( m_nIdxRep + gates_elm + gates_tournament );
	 	
	m_othStartGate = m_nFrontier;
	m_nNumGates = m_nFrontier + gates_noninput;
	m_pGates = new GATE[m_nNumGates];
	m_nNumXORs = 0;

	//============================================================================
	// Now construct the circuit 
	SetupInputGates();
	PutLayerI();
	PutLayerB();
	PutOutputLayer();
	PatchParentFields();

	return TRUE;

}

void CP2PCircuit::SetupInputGates()
{
 
	GATE* gate;
 	 
	for(int i=0; i<m_othStartGate; i++)
	{
		gate = m_pGates + i;
		gate->p_ids = 0;
		gate->p_num = 0;
		gate->left = -1;
		gate->right = -1;
		gate->type = 0;
		gate->val = 0;
	}

	// constant 1
	m_pGates[1].val = 1;
}	 



void CP2PCircuit::PutLayerI()
{
	m_vIdxs.resize(m_nTotItems);
	for(int i=0; i<m_nTotItems; i++)
	{
		m_vIdxs[i] = PutIdxGate(i+1);
	}

	m_vELMs.resize(m_nTotItems);
	for(int i=0; i<m_nTotItems; i++)
	{
		m_vELMs[i] = PutELMGate(i);
	}
}


int CP2PCircuit::PutIdxGate(int r)
{
	int start = m_nFrontier;
	int digit;
  	for(int j=0; j<m_nIdxRep; j++)
	{
		digit = (r >> j) & 1;
		PutXORGate(digit,0);
	}

	//cout << "PutIdxGate(" << r <<")=" << start << endl;
	return start;
}


int CP2PCircuit::PutELMGate(int r)
{
	int vr = 2+m_nRep*r;
	int br = m_vInputStart[m_nNumParties-1] + r;
	int out = PutELM0Gate(vr, br, m_nRep); 
	
	//cout << "PutELMGate(" << r << ")=" << out << endl;

	return out;
}
   
void CP2PCircuit::PutLayerB()
{
	// build a balanced binary tree
	int cmp;
	while( m_vELMs.size() > 1 )
	{
		unsigned j=0;
		for(unsigned i=0; i<m_vELMs.size(); )
		{
			if( i+1 >=  m_vELMs.size() )
			{
				m_vELMs[j] = m_vELMs[i];
				m_vIdxs[j] = m_vIdxs[i];
				i++;
				j++;
			}
			else
			{
				cmp = PutGEGate(m_vELMs[i], m_vELMs[i+1], m_nRep);	// elm[i] >= elm[i+1] ?
				m_vELMs[j] = PutMUXGate(m_vELMs[i], m_vELMs[i+1], cmp, m_nRep);
				m_vIdxs[j] = PutMUXGate(m_vIdxs[i], m_vIdxs[i+1], cmp, m_nIdxRep);
				 
				i+=2;
				j++;
			} 	 
		}
		m_vELMs.resize(j);
		m_vIdxs.resize(j);
	}
}
 
 
void CP2PCircuit::PutOutputLayer()
{
	m_vOutputStart.resize(m_nNumParties, 1);
	m_vOutputEnd.resize(m_nNumParties, 0);
	 
	m_vOutputStart[m_nNumParties-1] = m_vIdxs[0];
	m_vOutputEnd[m_nNumParties-1] = m_vIdxs[0]+m_nIdxRep-1;

	m_nNumGates = m_nFrontier;
}

