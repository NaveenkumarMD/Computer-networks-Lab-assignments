#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAX 10000

int main(){
	int sockfd;
	struct sockaddr_in servaddr;

	int n;
	char msg[MAX];
	char msg1[MAX];

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(SERVER_IP);
    servaddr.sin_port=htons(PORT);

    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<1){
       printf("Connection failed....\n");
      
    }
    printf("Connected successfully...\n");
    FILE *fp;
    while(1){
    	printf("Enter the mesage:");
    	bzero(msg,sizeof(msg));

    	fp=fopen("test.txt","r");
    	char buffer[MAX];
    	bzero(buffer,sizeof(buffer));
    	while(fgets(buffer,MAX,fp))
    		strcat(msg,buffer);


    	send(sockfd,msg,sizeof(msg),0);
    	bzero(msg,sizeof(msg));

    	printf("Message sent....\n");
    	recv(sockfd,msg,MAX,0);
    	int i=0;
    	printf("An count is %d\n",msg[i++]);
    	printf("A count is %d\n",msg[i++]);
    	printf("The count is %d\n",msg[i++]);
    	printf("Word count is %d\n",msg[i++]);
    	printf("Character count is %d\n",msg[i++]);
    	break;

    }
    close(sockfd);
}