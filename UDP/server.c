#include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <string.h>
 #include <stdlib.h>
 #include <math.h>

 #define SERVER_UDP_PORT   5003           /* Server port */
 #define MAXLEN    64                  /* maximum data length */

 int main(int argc, char **argv)
 {
 	int      sd, client_len, port, n;
   	char     buf[MAXLEN];                 /* buffer for storing  messages */
   	struct   sockaddr_in server, client;
   	int  dv_flg=0;                        /* to check for division error */
   	float n1,n2,res;
 	char op;

  	switch(argc)
	{
	case 1:
		port = SERVER_UDP_PORT;
		break;
     case 2:
         port = atoi(argv[1]);
         break;
     default:
         fprintf(stderr, "Usage: %s [port]\n", argv[0]);
         exit(1);
     }

     	/* Create a datagram socket */
	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		fprintf(stderr, "Can't create a socket\n");
        exit(1);
	}

	/* Bind an address to the socket */
	bzero((char *)&server, sizeof(server));/* fill the structure with zeros*/
	server.sin_family = AF_INET;             /* assign address family */
	server.sin_port = htons(port);           /* assign port */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* any IP address */

    if (bind(sd, (struct sockaddr *)&server,sizeof(server)) == -1)
	{
		fprintf(stderr, "Can't bind name to socket\n");
		close(sd);
	    exit(1);
	}

	printf("waiting .. .");
	client_len = sizeof(client);
	while (1)
	{
		dv_flg=0;

		/* Recieve first number */
if ((n = recvfrom(sd, buf, MAXLEN, 0,(struct sockaddr *)&client, &client_len)) < 0)
	 	{
			fprintf(stderr, "Can't receive datagram\n");
			close(sd);
			exit(1);
		}

		/* Extract the parameters */
		sscanf (buf,"%f%c%f",&n1,&op,&n2);
		if(op == '+')
			res = n1 + n2;
		if(op == '-')
			res = n1 - n2;
		if(op == '*')
			res = n1 * n2;
		if(op == '/')
		{
			if (n2==0)
				dv_flg =1;
			else
				res = n1 / n2;
		}
		if(dv_flg == 1)    /* division error */
			strcpy(buf,"Divison error");
		else
			sprintf (buf, "%f", res);


if (sendto(sd, buf, n, 0,(struct sockaddr *)&client, client_len) < 0 )  /* send datagram */
		{
			fprintf(stderr, "Can't send datagram\n");
			close(sd);
             exit(1);
		}
	}
	close(sd);
    return(0);
 }
