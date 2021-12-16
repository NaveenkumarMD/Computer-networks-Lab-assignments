#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
// Driver code
int main() {
int sockfd;
char buffer[MAXLINE];
struct sockaddr_in servaddr;
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr = INADDR_ANY;
int n, len;
int y=0;
char name[MAXLINE];
bzero(name,sizeof(name));
printf("Enter your full name: ");
while((name[y++]=getchar())!='\n');
sendto(sockfd, name, strlen(name),
MSG_CONFIRM, (const struct sockaddr *) &servaddr,
sizeof(servaddr));
printf("Name sent.\n");
n = recvfrom(sockfd, buffer, MAXLINE,

MSG_WAITALL, (struct sockaddr *) &servaddr,
&len);

buffer[n] = '\0';

printf("Server : %s\n", buffer);
close(sockfd);
return 0;
}