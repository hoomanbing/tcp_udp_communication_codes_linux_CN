/*--------------------------*/
/* Code for a simple client */
/*--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256],hostname[20],portnumber[10];
     
    /* Ask user to provide hostname and port number */
    printf("\nClient requires the following to operate");
    printf("\nPlease provide server hostname: ");
    scanf("%s",hostname);
    printf("\nPlease provide server port num: ");
    scanf("%s",portnumber);
    getchar();

    /* Open socket from client end */                                                        
    portno = atoi(portnumber);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* Connect to server using hostname */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    /* Client connected -- Wait for user message */
    printf("\nConnected to server 'localhost' at port num '%s'",portnumber);
    printf("\nReady for communication ...");
    printf("\n");

    /* Take user input for message */
    printf("\nPlease enter the message: ");
    bzero(buffer,sizeof(buffer));
    fgets(buffer,sizeof(buffer),stdin);

    /* Write message to socket for communication */
    printf("\nWriting message to socket ...");
    if (write(sockfd,buffer,sizeof(buffer)) < 0) 
         error("ERROR writing to socket");
    printf("\nMessage sent/written to socket");

    /* Listen to the socket for client message */
    printf("\nClient listening for server ACK ...");
    printf("\n");

    /* Read ACK from server */
    bzero(buffer,256);
    if (read(sockfd,buffer,sizeof(buffer)) < 0) 
         error("ERROR reading from socket");
    printf("\nRead successful for server ACK");
    printf("\nServer sent this ACK : %s",buffer);

    /* Close the socket and end communication */
    printf("\nClosing the socket ...\n\n");
    close(sockfd);
    return 0;
}
