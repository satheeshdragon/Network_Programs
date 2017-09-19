#include <stdio.h>
  #include <stdio_ext.h>
  #include <string.h>
  #include <sys/time.h>
  #include <netdb.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <stdlib.h>
  #include  <string.h>

  #define SERVER_UDP_PORT   5003  /* UDP port*/
  #define MAXLEN       64      /* maximum data length */

 int main(int argc, char **argv)
 {

	struct  hostent     *hp;
	struct  sockaddr_in      server, client;

	int     data_size = MAXLEN, port = SERVER_UDP_PORT;
   	int     sd, server_len;
	char    *pname, *host, rbuf[MAXLEN], sbuf[MAXLEN];

	int i;
	int opt =1;
      float n1,n2;
	char op;

    	pname = argv[0];
argc--;
argv++;
    	if (argc > 0)
{
		host = *argv;
        	if (--argc > 0)
			port = atoi(*++argv);                   // port number
	}

    	else
	{
//  must specify server address

fprintf(stderr,"Usage: %s [-s data_size] host [port]\n", pname);
            exit(1);
    	}

    	/* Create a datagram socket */
if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		fprintf(stderr, "Can't create a socket\n");
        	exit(1);
	}

     	/* Store server's information */
     	bzero((char *)&server, sizeof(server));
     	server.sin_family = AF_INET;
     	server.sin_port = htons(port);

if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr,"Can't get server's IP address\n");
        exit(1);
   	}

	bcopy(hp->h_addr, (char *)&server.sin_addr,hp->h_length);

     /* Bind local address to the socket */
   	bzero((char *)&client, sizeof(client));  // initalise client address
client.sin_family = AF_INET;    // asign address family
client.sin_port = htons(0);	// assign port
client.sin_addr.s_addr = htonl(INADDR_ANY); // assign any port

if (bind(sd, (struct sockaddr *)&client,sizeof(client)) == -1)
	{
       	fprintf(stderr, "Can't bind name to socket\n");
		close(sd);
       	exit(1);
    	}
printf(" \n Connected to the server : ");

server_len = sizeof(server);

while(opt == 1)
	{
		printf("\n Enter operator(+,-,/,*):");
		scanf("%c",&op);
		printf("\n Enter first number:");
		scanf("%f", &n1);
  		printf("\n Enter second number:");
		scanf("%f", &n2);
		sprintf (sbuf, "%f%c%f", n1,op, n2);

		/* send the parameters */
if (sendto(sd, sbuf, data_size, 0, (struct sockaddr *)&server, server_len) == -1)
		{
        	fprintf(stderr, "\n sendto error\n");
			close(sd);
         	exit(1);
		}

	     /* receive the result */
     	if (recvfrom(sd, rbuf, MAXLEN, 0, (struct sockaddr *) &server, &server_len) < 0)
		{
        	fprintf(stderr, "\n recvfrom error\n");
			close(sd);
	        exit(1);
     		}

		printf("\n Result : %s", rbuf);
     		printf("\n Want to continue ? (0/1) :");
		scanf("%d",&opt);

		setbuf(stdin,NULL);   	// clear  input streams
	}

    close(sd);
    return(0);
 }
