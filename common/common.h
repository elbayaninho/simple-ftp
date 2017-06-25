/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/21
* File: common.h
* Comment: Common header between client and server
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#define closesocket(s) close(s) /* For click men. :-) */
#define SERVER_PORT	7000
#define SERVER_IP	"127.0.0.1"
#define BUFFER_SIZE	1024