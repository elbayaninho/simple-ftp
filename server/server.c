/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/19
* File: server_addr.c
* Comment: Server for myftp a file transfert protocol
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
#include "server.h"
#include "../common/functions.h"

int main( int argc, char *argv[] ) {
   int socket_server, socket_client;
   struct sockaddr_in server_addr, client_addr;
   int pid;
   int n;
   char buffer[256], command[5], filename[20];
   struct stat obj;
   int size, len, c;
   int filehandle, receive;
   int i = 1;
   bzero(buffer, 256);
   bzero(command, 5);
   bzero(filename, 20);

   if (argc != 2) {
      fprintf(stderr,"Usage: %s hostname\n", argv[0]);
      exit(0);
   }
   
   /* First call to socket() function */
   socket_server = socket(AF_INET, SOCK_STREAM, 0);
   
   if (socket_server < 0) {
      die("ERROR: socket() failed\n");
   }
   
   /* Initialize socket structure */
   bzero((char *) &server_addr, sizeof(server_addr));
   
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(SERVER_PORT);
   
   /* Now bind the host address using bind() call.*/
   if (bind(socket_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
      die("ERROR: bind() failed\n");
   }
   
   listen(socket_server, 5);
   socklen_t client_addr_len = sizeof(client_addr);
   printf("\tListening of port %d...\n", SERVER_PORT);

   signal(SIGCHLD, SIG_IGN); // For killing zombies process
   while (1) {
     
      socket_client = accept(socket_server, (struct sockaddr *) &client_addr, &client_addr_len);
      
      if (socket_client < 0) {
         die("ERROR: accept() failed\n");
      }

      printf("\tClient %s is connected on the port %d\n", inet_ntoa(client_addr.sin_addr), 
               htons(client_addr.sin_port));
      
      /* Create child process */
      pid = fork();
		
      if (pid < 0) {
         die("ERROR: fork() failed\n");
      }
      
      if (pid == 0) {
         closesocket(socket_server);
         doServerProcessing(socket_client);
      }
      else {
         closesocket(socket_client);
         continue;
      }
		
   } /* end of while */
      closesocket(socket_server);
}
