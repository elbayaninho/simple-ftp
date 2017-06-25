/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/19
* File: server.h
* Comment: Client for myftp a file transfert protocol
*
* Copyright (C) 2017 BAIMI BADJOUA - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the MIT license, which unfortunately won't be
* written for another century.
*
* You should have received a copy of the MIT license with
* this file. If not, please write to: , or visit : 
* https://opensource.org/licenses/MIT
* Author email : <elbayaninho@outlook.fr>
*/

#ifndef SERVER_H
#define SERVER_H

#if defined (WIN32) /* For windows users */
	#include <winsock2.h>
    typedef int socklen_t; /* typedef, will help us */
#elif defined (linux) /* For Linux users */
	#include "../common/common.h"
	#include <unistd.h>
	#include <sys/wait.h>
#endif // End of os header description
#endif