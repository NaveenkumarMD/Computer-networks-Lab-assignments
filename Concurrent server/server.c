#include "stdio.h"
#include "sys/types.h"
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PORT 8000
#define MAX 100

int main(){
	int sockfd;
	int newsockfd;

	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;

	int n;
	char msg[MAX];
	int clientAddresslength;

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);

	if (bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
	{
		printf("Socket bind failed..\n");
		exit(0);
	}
	printf("Socket binded successfully...\n");
    
    listen(sockfd,5);
    printf("Listening......\n");

    

    while(1){
    	printf(".........Server waiting..........\n");
    	clientAddresslength=sizeof(cliaddr);
    	newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clientAddresslength);
    	printf("Accepted..\n");

    	bzero(msg,sizeof(msg));
    	recv(newsockfd,msg,MAX,0);
    	printf("%s",msg);
    	

    	int charactercount=0;
    	int wordcount=0;
    	int an=0;
    	int the=0;
    	int a=0;
    	for (int i=0;i<strlen(msg);i++){
    		charactercount++;
    		if(msg[i]==' ')
    			wordcount++;
    		if (msg[i]=='a' && msg[i+1]=='n'){
            	if(msg[i-1]==' ' || msg[i+2]==' '){
    				an++;
    				continue;
    			}
            }
    		if (msg[i]=='a'){
    			if(msg[i-1]==' ' || msg[i+1]==' '){
    				a++;
    			}
    		}


    		if (msg[i]=='t' && msg[i+1]=='h' && msg[i+2]=='e'){
                if(msg[i-1]==' ' || msg[i+3]==' '){
    				the++;
    			}
    		}
    	}
    	
    	charactercount-=wordcount;
    	wordcount++;
    	bzero(msg,sizeof(msg));
    	printf("%d\n",an);
    	printf("%d\n",a);
    	printf("%d\n",the);
    	printf("%d\n",wordcount);
    	printf("%d\n",charactercount);

        int x=0;
        msg[x++]=an;
        msg[x++]=a;
        msg[x++]=the;
        msg[x++]=wordcount;
        msg[x++]=charactercount;
    	send(newsockfd,msg,x,0);
    	bzero(msg,sizeof(msg));
    	close(newsockfd);
    }



	return 0;
}