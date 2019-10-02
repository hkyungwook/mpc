// main.cpp
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
#include "../util/typedefs.h"
#include "../util/config.h"
#include "../circuit/circuit.h"

#include "party.h"
#include <ctime>
using namespace std;

void PrintOutput(const vector<int>& vOutput) 
{
	cout << "output:" << endl;
	cout << "(binary)";
	for( UINT i=0; i<vOutput.size(); i++ )
	{
		cout << " " << (int) vOutput[i];
	}
	cout << endl;

	ZZ out;
	out.SetSize(vOutput.size());
	
	cout << "(numeric:big-endian) ";

	int size = vOutput.size();
	for( int i=0; i<size; i++ )
	{
		if( bit(out,i) != vOutput[i] )
			SwitchBit(out,i);
	}
	cout << out << endl;


	cout << "(numeric:little-endian) ";

	for( int i=0; i<size; i++ )
	{
		if( bit(out,i) != vOutput[size-i-1] )
			SwitchBit(out,i);
	}
	cout << out << endl;
}


int main(int argc, char** argv)
{
	if( argc != 2 )
	{
		cout << "usage: mpc.exe config_file " << endl;
		return 0;
	}

	double tt = clock();

	CConfig* pConfig = new CConfig();
	if(!pConfig->Load(argv[1]))
	{
		cout << "failure in opening the config file: " << argv[1] << endl;
		return 0;
	}

	CParty* pParty = new CParty();
	pParty->Run();
	PrintOutput( pParty->GetOutput() );
	 
	delete pParty; 
 	 
	double tt1 = clock();
	cout << endl << "elapsed " <<  (tt1-tt)/CLOCKS_PER_SEC << " seconds." << endl;

	 
	return 0;
}

