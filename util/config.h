// config.h
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
#ifndef __CONFIG_H__BY_SGCHOI
#define __CONFIG_H__BY_SGCHOI

#define NTL_NO_MIN_MAX
#include "../NTL/ZZ.h"
#include "../util/typedefs.h"
using namespace NTL;

#include <vector>

#define TOKEN_PID			"pid"					// player id 
#define TOKEN_NUMINPUT		"num_input"				// #items in server
#define TOKEN_INPUTRANGE	"input_range"			// the range of the input 
#define	TOKEN_INPUT			"input"					// actual input
#define TOKEN_ADDRS			"address-book"			// address book
#define TOKEN_P				"p"						// field
#define TOKEN_Q				"q"						// order
#define TOKEN_G				"g"						// generator
#define TOKEN_SEED			"seed"					// seed
#define TOKEN_NUMPARTIES	"num_parties"			// number of parties
#define TOKEN_LOAD_CIRC		"load-circuit"			// binary circuit file
#define TOKEN_CREATE_CIRC	"create-circuit"			// create a circuit 
#define TOKEN_COMMENT		'%'						// comment

class CConfig 
{
public:
	CConfig(){ GetInstance(this); }
	~CConfig(){}

public:
	static CConfig* GetInstance(CConfig* p = NULL){ static CConfig* sp; if(p) sp = p; return sp;}
	 
public:
	BOOL		Load(const char* filename);
	BOOL		LoadAddressBook(const char* filename);
	int			GetNumInputs(){ return m_nNumInputs; }
	int			GetNumParties(){ return m_nNumParties;}
	BOOL		IsServer(){ return m_nPID < m_nNumParties-1; }
	int			GetPID(){ return m_nPID; }
	void		GetInput(vector<int>& v){ v = m_vInputs;}	
	string		GetSeed(){ return m_strSeed;}
	USHORT		GetPortPID(int i){ return m_vPorts[i];}
	string		GetAddrPID(int i){ return m_vAddrs[i];}
	ZZ&			GetPrime(){ return m_P;}
	ZZ&			GetGenerator(){ return m_G;}
	ZZ&			GetOrder(){ return m_Q;}
	int			GetInputRange(){ return m_nInputRange;}
	string		GetCircFileName(){ return m_strCircFileName;}
	string		GetCircCreateName(){ return m_strCircCreateName; }
	vector<int>& GetCircCreateParams(){ return m_vCircCreateParam; }

private:
	vector<int>			m_vInputs;
	vector<USHORT>		m_vPorts;
	vector<string>		m_vAddrs;
	int					m_nPID;  
	ZZ					m_P;
	ZZ					m_Q;
	ZZ					m_G;
	string				m_strSeed;
	int					m_nNumParties;
	int					m_nInputRange;
	int					m_nNumInputs;
	string				m_strCircFileName;
	string				m_strCircCreateName;
	vector<int>			m_vCircCreateParam;
};

#endif //__CONFIG_H__BY_SGCHOI

