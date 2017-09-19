#include <stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <stdlib.h>
#include<string.h>
#include<fcntl.h>

#define BUF_SIZE 500
#define PORT 3500

int main()
{
    int fd;
    int sd,new_sd;
    int client_len;
    struct sockaddr_in server,client;
    char n,rbuf[BUF_SIZE],buf[BUF_SIZE];

    //build address ds
    bzero((char *)&server,sizeof(struct sockaddr_in));

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);

    //create socket server
    if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("server:socket error");
        exit(1);
    }
    if(bind(sd,(struct sockaddr *)&server,sizeof(server))<0)
    {
        perror("server:bind error");
        exit(1);
    }

    //Listen to the incoming connections
    listen(sd,5);
    while(1)
    {
        client_len=sizeof(client);
        printf("waiting for connection...\n");
        if((new_sd=accept(sd,(struct sockaddr *)&client,&client_len))<0)
        {
            perror("Server:accept error");
            exit(1);
        }
        printf("Connected...\n");
        n=read(new_sd,buf,BUF_SIZE);
        if(strcmp(buf,"stop")==0)
        {
            printf("Server is closed");
            break;
        }
        fd=open(buf,O_RDONLY);
        if(fd==-1)
            printf("File %s does not exists\n",buf);
        else
        {
            while(n=read(fd,rbuf,BUF_SIZE)>0)
            {
                write(new_sd,rbuf,BUF_SIZE);
            }
            printf("File %s content sent...\n",buf);
        }
        close(new_sd);
        close(fd);
    }
    close(sd);
    return 0;
}
