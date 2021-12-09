#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd){
    char buff[MAX];
    int i;
    for(;;){
    	bzero(buff,MAX);
    	read(sockfd,buff,sizeof(buff));
    	printf("From client %s",buff);
    	bzero(buff,sizeof(buff));
    	i=0;
    	while ((buff[i++]=getchar())!='\n')
    		;
    	printf("Entered string is %s",buff);
    	write(sockfd,buff,sizeof(buff));
    }
}

int main(){
	int sockfd,confd,len;
	struct sockaddr_in servaddr,cli;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd==-1){
		printf("Socket creation failed\n");
		exit(0);
	}
	printf("Socket created successfully\n");
		bzero(&servaddr,sizeof(servaddr));

	//Assigning port and family
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	//bind
	if(bind(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0){
		printf("Socket bind failed\n");
		exit(0);
	}
	printf("Socket binded to PORT \n");
	len=sizeof(cli);

	//listen

	if(listen(sockfd,5)!=0){
		printf("Listen failed\n");
		exit(0);
	}
	printf("Socket listening.........\n");
	
	//accept
	confd=accept(sockfd,(SA*)&cli,&len);
	if(confd<0){
		printf("Accept failed\n");
		exit(0);
	}
	printf("successfully connected...\n");

    func(confd);
	return 0;
	return 0;
}