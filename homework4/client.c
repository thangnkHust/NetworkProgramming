#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024

int menu(void);

int main (int argc, char const *argv[])
{
	// valid number of argument
	if (argc != 3)
	{
		printf("Usage: ./client IPAddress PortNumber\n\n");
		return 0;
	}

	int client_sockfd;
	int recvBytes, sendBytes;

	struct sockaddr_in serv_addr;
	
	char buff[BUFF_SIZE];

  int select;
  int sock = 0;

  char buffer[100];
  int count;
  char message[100];
  int g=0, ch=0;

	// Construct socket
	client_sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	// Specify server address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	// Request to connect server
	if(connect(client_sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) < 0){
		printf("\nError!Can not connect to sever! Client exit imediately! ");
		return 0;
	}
		
	// Communicate with server			
	while(1){
    select = menu();
    printf("%d\n", select);
    switch(select){
      case 1:
        getchar();
        //send message
        printf("\nInsert string to send (ENTER to quit): ");
        fgets(buff, BUFF_SIZE, stdin);

        // exit if user only input ENTER
        if (buff[0] == '\n') break;

        // replace \n with \0
        buff[strcspn(buff, "\n")] = '\0';

        sendBytes = send(client_sockfd, buff, strlen(buff), 0);
        if(sendBytes <= 0){
          printf("\nConnection closed!\n");
          break;
        }
        
        // receive echo reply
        recvBytes = recv(client_sockfd, buff, BUFF_SIZE-1, 0);
        if(recvBytes <= 0){
          printf("\nError!Cannot receive data from sever!\n");
          break;
        }
        
        // print reply
        buff[recvBytes] = '\0';
        puts("Reply from server:");
        puts(buff);
        break;
      case 2:
        getchar();
				// input file name
				printf("INPUT: "); 
				g = scanf("%[^\n]", message);
				if (g == 0) break;
				// change file name to txt type
				strcat(message, ".txt");
				// send file name to server
				send(client_sockfd , message , strlen(message) , 0 );	
				// get number line in that file			
				read(client_sockfd, &count, sizeof(int));
				// get contain of that file
				while(ch < count + 1){
					read(client_sockfd, buffer,100);
					ch++;
					printf("%s\n",buffer);		
				}
				printf("\n");
        break;
      default:
        // Close socket
        close(client_sockfd);
        return 0;
    }
	}
	return 0;
}

int menu(void){
  int select;
  puts("MENU");
  puts("-------------------------");
  puts("1. Split string");
  puts("2. Transfer file");
  puts("Other. out");
  printf("Enter selection: ");
  scanf("%d", &select);
  return select;
}