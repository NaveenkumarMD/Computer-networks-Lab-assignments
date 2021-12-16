#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<time.h>
#define PORT 8080
#define MAXLINE 1024

int main() {
int sockfd;
char buffer[MAXLINE];
struct sockaddr_in servaddr, cliaddr;
// Creating socket file descriptor
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);

if ( bind(sockfd, (const struct sockaddr *)&servaddr,

sizeof(servaddr)) < 0 )

{
perror("bind failed");

exit(EXIT_FAILURE);
}
int len, n;
len = sizeof(cliaddr);
n = recvfrom(sockfd, buffer, MAXLINE,

MSG_WAITALL, ( struct sockaddr *) &cliaddr,
&len);
printf("Name is : %s\n", buffer);
char arr[11]={'1','2','3','4','5','6','7','8','9','0'};
srand(time(0));
char pan[11];
for (int i=0;i<3;i++){
pan[i]=rand()%26+'0'+17;
}
pan[3]='P';
char x;
for(int i=0;i<sizeof(buffer);i++){
if(buffer[i]==' '){
x=buffer[i+1];
break;
}
}
pan[4]=x;
for (int i=5;i<9;i++){
pan[i]=arr[rand()%10];
}
pan[9]=buffer[0];
pan[10]='\0';
printf("%s\n",pan);

sendto(sockfd, pan, strlen(pan),
MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
len);
printf("Message sent.\n");
bzero(pan,sizeof(pan));
return 0;
}