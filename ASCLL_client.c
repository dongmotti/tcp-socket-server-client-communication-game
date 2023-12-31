#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int guess, result;
	int str_len, recv_len, recv_cnt;	

	struct sockaddr_in serv_adr;
	
	if(argc!=3){
		printf("Usage : %s <IP>\n",argv[0]);
		exit(1);
	}

	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock==-1)
		error_handling("socket() error");

	memset(&serv_adr, 0,sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));
	
	if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error");

	else
		puts("Connected...........");

	read(sock, message,sizeof(message)-1);
	
	//printf("ASCLL from server : %s \n", message); 
	result = *message;
	//printf("Result : %d \n " ,result);

	while(1)
	{	
		fputs("Guess 0~127 number: ",stdout);
		scanf("%d",&guess);
	
		if (guess < result){
           		 printf("Too low, try again\n");
		}
       		if (guess > result){
            		printf("Too high, try again\n");
		}
		if (guess == result)
        	{
                	printf("That's right!'\nCongratulaion!!!\n");
                	break;
            	}
	}

	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
