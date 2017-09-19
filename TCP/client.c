#include <stdio.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <stdlib.h>
#include<string.h>

#define BUF_SIZE 500
#define PORT 3500

int main(int argc,char **argv)
{
    int n,sd;
    struct hostent *hp;
    struct sockaddr_in server;
    char *host,rbuf[BUF_SIZE],sbuf[BUF_SIZE];
    if(argc==2)
        host=argv[1];
    else
    {
        fprintf(stderr,"Usage:client host\n");
        exit(1);
    }
    //translate host name into peer's ip address
    hp=gethostbyname(host);
    if(!hp)
    {
        fprintf(stderr,"Client:unknown host:%s\n",host);
        exit(1);
    }
    //build address ds
    bzero((char *)&server,sizeof(struct sockaddr_in));
    bcopy(hp->h_addr,(char *)&server.sin_addr,hp->h_length);

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);

    //create client socket
    if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("Client:socket error");
        exit(1);
    }
    if(connect(sd,(struct sockaddr *)&server,sizeof(server))<0)
    {
        perror("Client:connect error");
        close(sd);
        exit(1);
    }
    printf("Enter the file name(type stop to close SERVER):\n");
    scanf("%s",sbuf);
    write(sd,sbuf,BUF_SIZE);
    printf("Content of the file:\n");
    while(n=read(sd,rbuf,BUF_SIZE)>0)
        printf("%s",rbuf);
    close(sd);
    return 0;
}
