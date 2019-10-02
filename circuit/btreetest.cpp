// btreetest.cpp
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
#include "btreetest.h"
#include <cassert>
#include <cmath>


///=================================================================================
// creates a full binary tree of AND gates
// input: number of depth  
// output: top node
BOOL CBTreeTest::Create(int nParties, const vector<int>& vParams)
{
	if( vParams.size() < 1 )
	{
		cout << "Error! This circuit needs two parameters: #depth." << endl;
		return FALSE;
	}
	
	m_nNumParties = nParties;
	m_nDepth = vParams[0];
	m_nTotItems = pow(double(2), double(m_nDepth-1));  
	m_vNumVBits.resize(m_nNumParties, 1);

 	// gates for inputs:  each party has one bit input
	m_vInputStart.resize(nParties);
	m_vInputEnd.resize(nParties);

	m_nFrontier = 2;
	for(int i=0; i<nParties; i++)
	{
		m_vInputStart[i] = m_vInputEnd[i] = m_nFrontier;
		m_nFrontier++;
	}
	     
	//===========================================================================
	// computes roughly the number of gates beforehand --- need this for allocating space
	m_othStartGate = m_nFrontier;
	m_nNumGates = m_nFrontier + m_nTotItems*2; 
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

void CBTreeTest::SetupInputGates()
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


void CBTreeTest::PutLayerI()
{
	m_vELMs.resize(m_nTotItems);
	for(int i=0; i<m_nTotItems; i++)
	{
		m_vELMs[i] = PutANDGate( m_vInputStart[i%m_nNumParties], m_vInputStart[(i+1)%m_nNumParties]); 
	}
}

    
void CBTreeTest::PutLayerB()
{
	// build a balanced binary tree
	while( m_vELMs.size() > 1 )
	{
		unsigned j=0;
		for(unsigned i=0; i<m_vELMs.size(); )
		{
			if( i+1 >=  m_vELMs.size() )
			{
				m_vELMs[j] = m_vELMs[i];
				i++;
				j++;
			}
			else
			{
				m_vELMs[j] = PutANDGate( m_vELMs[i], m_vELMs[i+1] );
				i+=2;
				j++;
			} 	 
		}
		m_vELMs.resize(j);
	}
}
 
 
void CBTreeTest::PutOutputLayer()
{
	m_vOutputStart.resize(m_nNumParties, m_vELMs[0]);
	m_vOutputEnd.resize(m_nNumParties, m_vELMs[0]);
	m_nNumGates = m_nFrontier;
}

