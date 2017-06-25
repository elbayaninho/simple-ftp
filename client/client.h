/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/19
* File: client.h
* Comment: Client header for myftp a file transfert protocol
*
* Copyright (C) 2017 BAIMI BADJOUA & BIO NIKKI BRUNO - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the MIT license, which unfortunately won't be
* written for another century.
*
* You should have received a copy of the MIT license with
* this file. If not, please write to: , or visit : 
* https://opensource.org/licenses/MIT
* Author email : <elbayaninho@outlook.fr>
*/

#ifndef CLIENT_H
#define CLIENT_H

#if defined (WIN32) /* For windows users */
	#include <winsock2.h>
    typedef int socklen_t; /* typedef, will help us */
#elif defined (linux) /* For Linux users */
	#include "../common/common.h"
	#define closesocket(s) close(s) /* For click men. :-) */
#endif // End of os header description
#endif