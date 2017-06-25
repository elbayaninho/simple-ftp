/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/19
* File: client.c
* Comment: Client for myftp a file transfert protocol
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

#include "client.h"
#include "../common/functions.h"

int main(int argc, char *argv[]) {
   int socket_client;
   struct sockaddr_in server_addr;
   struct hostent *server;
   char buffer[256], command[5], filename[20], *f, *local_file, save[20], task[20], choice[20];
   struct stat obj;
   int size, status, filehandle, n;
   char * command_;
   int i = 1;
   
   if (argc != 2) {
      fprintf(stderr,"\tUsage: %s hostname\n", argv[0]);
      exit(0);
   }
   
   /* Create a socket point */
   socket_client = socket(AF_INET, SOCK_STREAM, 0);
   
   if (socket_client < 0) {
      die("\tERROR: socket() failed\n");
   }
	
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"\tERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *)&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
   server_addr.sin_port = htons(SERVER_PORT);
   
   /* Now connect to the server */
   if (connect(socket_client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
      die("\tERROR: connect() failed\n");
   }

	while(1){
   		doClientProcessing(socket_client, argv[0], argv[1]);         
	}

   // Implementation ... OK
   return 0;
}