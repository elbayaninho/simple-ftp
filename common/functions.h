/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/21
* File: die.c
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

#include "common.h"
void die(char*);
void clean(char*);
void doServerProcessing (int);
void doClientProcessing(int, char*, char*);