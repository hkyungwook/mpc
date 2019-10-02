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
#ifndef __TYPEDEFS_H__BY_SGCHOI
#define __TYPEDEFS_H__BY_SGCHOI

#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>

typedef unsigned short	USHORT;
typedef int socklen_t;
#pragma comment(lib, "wsock32.lib")

#define SleepMiliSec(x)			Sleep(x)

#else //WIN32

typedef int				BOOL;
typedef unsigned long	DWORD;
typedef unsigned int	UINT;
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned short	USHORT;
typedef unsigned char	BYTE;

#define FALSE			0
#define TRUE			1
 
#include <sys/types.h>       
#include <sys/socket.h>      
#include <netdb.h>           
#include <arpa/inet.h>       
#include <unistd.h>          
#include <netinet/in.h>   
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
typedef int SOCKET;
#define INVALID_SOCKET -1
 
#define SleepMiliSec(x)			usleep((x)<<10)
#endif// WIN32

#include <cstring>
#include <string>  
#include <vector> 
#include <iostream>
using namespace std;




#endif //__TYPEDEFS_H__BY_SGCHOI


