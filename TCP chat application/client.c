#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define SA struct sockaddr
#define MAX 80

void func(int sockfd){
	char buff[MAX];
	for(;;){
		int i=0;
		bzero(buff,sizeof(buff));
		while((buff[i++]=getchar())!='\n')
			;
		printf("Entered string is %s",buff);
		write(sockfd,buff,sizeof(buff));
		bzero(buff,sizeof(buff));
		read(sockfd,buff,MAX);
		printf("From server is %s",buff);
	}
}
int main(){
	int sockfd,confd,len;
	struct sockaddr_in servaddr,cli;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("Socket creation failed\n");
		exit(0);
	}
	printf("Socket creation successfull\n");

	//Assigning port
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);

	//connection
	if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0){
		printf("connection failed\n");
		exit(0);
	}
	printf("connection success\n");
	func(sockfd);
	close(sockfd);

}