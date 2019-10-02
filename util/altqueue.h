// altqueue.h
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
#ifndef __ALT_QUEUE_H__BY_SGCHOI
#define __ALT_QUEUE_H__BY_SGCHOI

#include "typedefs.h"

// Queue with Alternate operation: alternate queue buffer reading/writing.
class CAltQueue
{
public:
	CAltQueue(){ m_pItems[0] = m_pItems[1] = NULL;}
	~CAltQueue(){ Cleanup();}

public:
	void Create(int max_size)
	{
		m_pItems[0] = new int[max_size];
		m_pItems[1] = new int[max_size];
		m_nHeads[0] = m_nHeads[1] = 0;
		m_nTails[0] = m_nTails[1] = 0;
		m_nWrite = 0;
	}
	
	void Cleanup()
	{
		if( m_pItems[0] ) delete [] m_pItems[0];
		if( m_pItems[1] ) delete [] m_pItems[1];
	}

	void AddCurr(int item)
	{
		*(m_pItems[m_nWrite] + m_nTails[m_nWrite]++) = item;
	}

	void AddAlt(int item)
	{
		*(m_pItems[m_nWrite^1] + m_nTails[m_nWrite^1]++) = item;
	}
	
	BOOL PopCurr(int& item)
	{		
		if(m_nHeads[m_nWrite] == m_nTails[m_nWrite])
			return FALSE; 
	
		item = *(m_pItems[m_nWrite] + m_nHeads[m_nWrite]++);
		
		if(m_nHeads[m_nWrite] == m_nTails[m_nWrite])
		{
			m_nHeads[m_nWrite] = m_nTails[m_nWrite] = 0;			
		}

		return TRUE;
 	}

	void Alternate()
	{		
		m_nWrite ^= 1;
	}
	
	void ClearCurr()
	{
		m_nHeads[m_nWrite] = m_nTails[m_nWrite] = 0;	
	}

	void ClearAlt()
	{
		m_nHeads[m_nWrite^1] = m_nTails[m_nWrite^1] = 0;
	}
	
	BOOL IsCurrEmpty()
	{
		return m_nHeads[m_nWrite] == m_nTails[m_nWrite];
	}

	int CurrSize()
	{
		return m_nTails[m_nWrite] - m_nHeads[m_nWrite];
	}

	BOOL Peek(int idx, int& item)
	{
		if( m_nHeads[m_nWrite] + idx >= m_nTails[m_nWrite] ) return FALSE;
		item = *(m_pItems[m_nWrite] + m_nHeads[m_nWrite] + idx);
		return TRUE;
	}


public:  
	int*	m_pItems[2];
	int		m_nHeads[2];
	int		m_nTails[2];
	int		m_nWrite;
};

#endif //__ALT_QUEUE_H__BY_SGCHOI
