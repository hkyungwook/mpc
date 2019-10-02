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
#include "config.h"
#include <fstream>
#include <sstream>
  

BOOL CConfig::Load(const char* filename)
{
 	ifstream fs(filename);
	if(!fs.is_open()) return FALSE;

	string sLine;
	for( int nLineNum = 1; fs.good(); nLineNum++ )
	{ 	
		getline(fs, sLine);
		if( sLine.empty() ) continue;

		istringstream is(sLine);

		string sParam;
		is >> sParam;
		if( is.bad() )
		{
			cout  << nLineNum << ": " << sLine << endl;
			cout << " error in parsing the parameter" << endl;
			return FALSE;
		}

		if( sParam == "" || sParam[0] == TOKEN_COMMENT ) continue;
		 
		if( sParam == TOKEN_PID)
		{
			is >> m_nPID; 
		}
		else if ( sParam == TOKEN_NUMINPUT )
		{	
			is >> m_nNumInputs;
			m_vInputs.reserve(m_nNumInputs);
		}
		else if ( sParam == TOKEN_INPUT )
		{
			string fname;
			is >> fname;
			ifstream fs(fname.c_str());
			int in;
			if( fs.is_open() )
			{
				for( fs >> in; fs.good(); fs >> in )
					m_vInputs.push_back(in); 
			}
			fs.close();
		}
		else if ( sParam == TOKEN_ADDRS )
		{
			string fname;
			is >> fname;
			LoadAddressBook(fname.c_str());
		}
		else if ( sParam == TOKEN_P	)
		{
			is >> m_P;
		}
		else if ( sParam == TOKEN_Q	)
		{
			is >> m_Q;
		}
		else if ( sParam == TOKEN_G )
		{
			is >> m_G;
		}
		else if ( sParam == TOKEN_SEED )
		{
			is >> m_strSeed;
		}
		else if ( sParam == TOKEN_NUMPARTIES )
		{
			is >> m_nNumParties;
		}
		else if ( sParam == TOKEN_LOAD_CIRC )
		{
			is >> m_strCircFileName;
		}
		else if ( sParam == TOKEN_CREATE_CIRC )
		{
			is >> m_strCircCreateName;
			int v;
			while( is.good() )
			{
				is >> v;
				m_vCircCreateParam.push_back(v);
			}
		}
		else 
		{
			cout << "unrecognized command in line (skip)" << nLineNum << ": " << sLine << endl;
		}
	
 		if( is.bad())
		{
			cout << "error in line " << nLineNum << ": " << sLine << endl;
			return FALSE;
		} 
	}
	return true;
}

BOOL CConfig::LoadAddressBook(const char* filename)
{
 	ifstream fs(filename);
	if(!fs.is_open()) return FALSE;

	m_vAddrs.resize(m_nNumParties);
	m_vPorts.resize(m_nNumParties);

	string sLine;
	for( int nLineNum = 1; fs.good(); nLineNum++ )
	{ 	
		getline(fs, sLine);
		if( sLine.empty() || sLine[0] == TOKEN_COMMENT ) continue;

		istringstream is(sLine);
		
		int    nPID;  
		string sAddr;
		USHORT nPort;

		is >> nPID >> sAddr >> nPort; 
		if( is.bad() )
		{
			cout  << nLineNum << ": " << sLine << endl;
			cout << " error in parsing the address book" << endl;
			return FALSE;
		}

		if( nPID < m_nNumParties )
		{
			m_vAddrs[nPID] = sAddr;
			m_vPorts[nPID] = nPort;
		}
	}

	return TRUE;
}
		
