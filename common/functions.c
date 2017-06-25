/**
* Author: BAIMI BADJOUA & BIO NIKKI BRUNO
* From: IFRI-UAC (Master I)
* Date: 2017/06/19
* File: functions.c
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

#include "functions.h"


/**
* To die errors
*/
void die(char *msg){
	perror(msg);
	exit(0);
}


/**
* Clean
* From OpencClassrooms
* Pour supprimer tous les retours a la ligne inutiles
*/
void clean(char* chaine)
{
	char *p = strchr(chaine, '\n');

	if(p)
	{
		*p = 0;
	}
}


/**
* doServerProcessing
*/
void doServerProcessing(int socket_client)
{
	int n;
	char buffer[256], command[5], filename[20];
	struct stat obj;
	int size, len, c;
	int filehandle, receive;
	int i = 1;
	bzero(buffer, 256);
	bzero(command, 5);
	bzero(filename, 20);


	n = recv(socket_client, buffer, 255, 0);

	if (n < 0) {
		die("\tERROR: reading from socket\n");
	}

	sscanf(buffer, "%s", command);
	if(!strcmp(command, "ls"))
	{
		system("ls > ../common/temps.txt");
		i = 0;
		stat("../common/temps.txt", &obj);
		size = obj.st_size;
		send(socket_client, &size, sizeof(int),0);
		filehandle = open("../common/temps.txt", O_RDONLY);
		sendfile(socket_client, filehandle, NULL, size);
	}
	else if(!strcmp(command,"get"))
	{
		sscanf(buffer, "%s%s", filename, filename);
		stat(filename, &obj);
		filehandle = open(filename, O_RDONLY);
		size = obj.st_size;
		if(filehandle == -1){
			size = 0;
		}
		send(socket_client, &size, sizeof(int), 0);
		if(size){
			sendfile(socket_client, filehandle, NULL, size);
		}
	}
	else if(!strcmp(command, "put"))
	{
		int c = 0, len;
		char *f;
		sscanf(buffer + strlen(command), "%s", filename);
		recv(socket_client, &size, sizeof(int), 0);
		i = 1;
		while(1)
		{
			filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
			if(filehandle == -1)
			{
				sprintf(filename + strlen(filename), "%d", i);
			}else{
				break;
			}
		}
		f = malloc(size);
		recv(socket_client, f, size, 0);
		c = write(filehandle, f, size);
		close(filehandle);
		send(socket_client, &c, sizeof(int), 0);
	}
	else if(!strcmp(command, "pwd"))
	{
		system("pwd > ../common/temp.txt");
		i = 0;
		FILE*f = fopen("../common/temp.txt","r");
		while(!feof(f))
		{
			buffer[i++] = fgetc(f);
		}
		buffer[i-1] = '\0';
		fclose(f);
		send(socket_client, buffer, strlen(buffer) + 1, 0);
	}
	else if(!strcmp(command, "cd"))
	{
		if(chdir(buffer + 3) == 0)
		{
			c = 1;
		}else{
			c = 0;
		}
		send(socket_client, &c, sizeof(int), 0);
	}
	else if(!strcmp(command, "bye") || !strcmp(command, "quit"))
	{
		printf("\tOne client is quitting...\n");
		i = 1;
		send(socket_client, &i, sizeof(int), 0);
		shutdown(socket_client, 2); // Disable send and receive on socket server
		closesocket(socket_client); // Close the client socket
		// exit(0);  Kill the child
	}
}

/**
* doClientProcessing
*/
void doClientProcessing(int socket_client, char* prog, char* host)
{
   	char buffer[256], command[5], filename[20], *f, *local_file, save[20], task[20], choice[20];
   	struct stat obj;
	int size, status, filehandle, n;
	char * command_;
	int i = 1;

		printf("%s@%s>>> ", host, prog);
		bzero(buffer, 256);
		fgets(choice, 20, stdin);
		clean(choice); // remove '\n';
		command_ = strtok(choice, " ");
		// 1- pwd
		if(!strcmp(command_, "pwd"))
		{
			bzero(buffer, 256);
			strcpy(buffer, "pwd");
			send(socket_client, buffer, 100, 0);
			bzero(buffer, 256);
			recv(socket_client, buffer, 100, 0);
			printf("\tThe path of server directory is: \n%s\n", buffer);
		}
		// 2- lpwd
		else if(!strcmp(command_, "lpwd"))
		{
			printf("\tThe path of your directory is: \n");
			system("pwd");
		}
		// 3- cd repertoire
		else if(!strcmp(command_, "cd"))
		{
			bzero(buffer, 256);
			strcpy(buffer, "cd ");
			command_ = strtok(NULL, "\n"); // Moving to next
			strcat(buffer, command_);
			send(socket_client, buffer, 100, 0);
			recv(socket_client, &status, sizeof(int), 0);
			if(status)
			{
				printf("\tRemote directory successfully changed\n");
				system("ls");
			}else{
				printf("\tRemote directory failed to change\n");
			}
		}
		// 4- lcd repertoire
		else if(!strcmp(command_, "lcd"))
		{
			command_ = strtok(NULL, "\n"); // Moving to next
			bzero(buffer, 256);
			strcpy(buffer, "cd ");
			strcat(buffer, command_);
			if(chdir(buffer + 3) == 0)
			{
				printf("\tRemote directory successfully changed\n");
				system("ls");
			}else{
				printf("\tRemote directory failed to change\n");
			}
		}
		// 5- ls
		else if(!strcmp(command_, "ls"))
		{
			bzero(buffer, 256);
			strcpy(buffer, "ls");
			send(socket_client, buffer, 100, 0);
			recv(socket_client, &size, sizeof(int), 0);
			f = malloc(size);
			recv(socket_client, f, size, 0);
			filehandle = creat("../common/client-temp.txt", O_WRONLY);
			write(filehandle, f, size, 0);
			close(filehandle);
			printf("\tThe server directory listing is as follows:\n");
			system("cat ../common/client-temp.txt");
		}
		// 6- lls
		else if(!strcmp(command_, "lls"))
		{
			printf("\tYour directory listing is as follows:\n");
			system("ls");
		}		
		// 7- get ficher
		else if(!strcmp(command_, "get"))
		{
			command_ = strtok(NULL, "\n");
			bzero(buffer, 256);
			strcpy(buffer, "get ");
			strcpy(filename, command_);
			strcat(buffer, filename); // filename = commands
			send(socket_client, buffer, 100, 0);
			recv(socket_client, &size, sizeof(int), 0);
			if(!size)
			{
				printf("\tNo such file on the remote directory\n\n");
			}
			f = malloc(size);
			recv(socket_client, f, size, 0);
			while(1){
				filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
				if(filehandle == -1)
				{
					sprintf(filename + strlen(filename), "%d", i); // needed only if same directory is used for both server and client
				}
				else{
					break;
				} 
		        	/*------------------------------------------------------------------*/			
			}
			write(filehandle, f, size, 0);
			close(filehandle);
			printf("\tFile '%s' downloaded successfully, size = %dK\n", filename, size);
			strcpy(save, "ls ");
			strcat(save, filename);
			system(save); // Display file
		}		
		// 8- put ficher
		else if(!strcmp(command_, "put"))
		{
			command_ = strtok(NULL, "\n"); // command == filename
			strcpy(filename, command_);
			filehandle = open(filename, O_RDONLY);
			if(filehandle == -1)
			{
				printf("\tNo such file on the local directory\n\n");
			}
			bzero(buffer, 256);
			strcpy(buffer, "put ");
			strcat(buffer, filename);
			send(socket_client, buffer, 100, 0);
			stat(filename, &obj);
			size = obj.st_size;
			send(socket_client, &size, sizeof(int), 0);
			sendfile(socket_client, filehandle, NULL, size);
			recv(socket_client, &status, sizeof(int), 0);
			if(status)
			{
				printf("\tFile stored successfully\n");
			}else{
				printf("\tFile failed to be stored to remote machine\n");
			}
		}	
		// 9- lls
		else if(!strcmp(command_, "bye"))
		{
			bzero(buffer, 256);
			strcpy(buffer, "quit");
			send(socket_client, buffer, 100, 0);
			recv(socket_client, &status, 100, 0);
			if(status)
			{
				printf("\tmyftpd connexion closed\n\tQuitting...\n");
				shutdown(socket_client, 2); 
				closesocket(socket_client);
				exit(0);
			}
			printf("\tServer failed to close connection\n");
		}
		else{
			printf("\tCommands '%s' not found\n", choice);
			printf("\tAvailable commands are below:\n");
			system("cat ../common/commands.txt");
		}
}