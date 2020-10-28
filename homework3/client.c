#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define BUFF_SIZE 1024

int menu(void);

int main (int argc, char const *argv[])
{
	int client_sock;
	char buff[BUFF_SIZE];
	char buff2[BUFF_SIZE];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received;
	socklen_t sin_size;
	int select;
	
	// valid number of argument
	if (argc != 3)
	{
		printf("Usage: ./client IPAddress PortNumber\n\n");
		return 0;
	}

	// Construct a UDP socket
	if ((client_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("\nError: ");
		exit(0);
	}

	// Define the address of the server
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	while (1)
	{
		select = menu();
		switch (select)
		{
		case 1:
			getchar();
			// Communicate with server
			printf("\nInsert string to send (ENTER to quit): ");
			fgets(buff, BUFF_SIZE, stdin);
			// for(int i = 0; i < strlen(buff); i++){
			// 	buff[i+1] = buff[i];
			// }
			// buff[0] = '1';

			// exit if user only input ENTER
			if (buff[0] == '\n') break;

			// replace \n with \0
			buff[strcspn(buff, "\n")] = '\0';
			puts(buff);
			// send to server
			sin_size = sizeof(struct sockaddr);
			bytes_sent = sendto(client_sock, buff, strlen(buff), 0, (struct sockaddr *) &server_addr, sin_size);
			if(bytes_sent < 0)
			{
				perror("Error: ");
				close(client_sock);
				return 0;
			}

			// send reply
			bytes_received = recvfrom(client_sock, buff, BUFF_SIZE - 1, 0, (struct sockaddr *) &server_addr, &sin_size);
			if(bytes_received < 0)
			{
				perror("Error: ");
				close(client_sock);
				return 0;
			}
			
			// print out reply
			buff[bytes_received] = '\0';
			printf("Reply from server:\n");
			puts(buff);
			break;
		case 2:
			getchar();
			// Communicate with server
			printf("\nEnter ip or domain name:  ");
			fgets(buff2, BUFF_SIZE, stdin);

			// exit if user only input ENTER
			if (buff2[0] == '\n') break;

			// replace \n with \0
			buff2[strcspn(buff2, "\n")] = '\0';

			// send to server
			sin_size = sizeof(struct sockaddr);
			bytes_sent = sendto(client_sock, buff2, strlen(buff2), 0, (struct sockaddr *) &server_addr, sin_size);
			if(bytes_sent < 0)
			{
				perror("Error: ");
				close(client_sock);
				return 0;
			}

			// send reply
			bytes_received = recvfrom(client_sock, buff2, BUFF_SIZE - 1, 0, (struct sockaddr *) &server_addr, &sin_size);
			if(bytes_received < 0)
			{
				perror("Error: ");
				close(client_sock);
				return 0;
			}
			
			// print out reply
			buff2[bytes_received] = '\0';
			printf("Reply from server:\n");
			puts(buff2);
			break;
		case 0:
			puts("Out!");
			return 0;
		default:
			break;
		}
	}

	close(client_sock);
	return 0;
}

int menu(void){
	int select;
	puts("1. Split string");
	puts("2. Convert ip or domain name");
	puts("0. Cancel");
	printf("Select option: ");
	scanf("%d", &select);
	return select;
}