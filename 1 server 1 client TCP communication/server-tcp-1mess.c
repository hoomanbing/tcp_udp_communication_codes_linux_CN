#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, newsockfd, portno;
    char buffer[256], portnumber[10];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    /* Ask user to provide a port number */
    printf("\nServer requires a port number to operate.");
    printf("\nPlease provide a port number: ");
    scanf("%s", portnumber);

    /* Open socket from server end */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(portnumber);

    /* Bind socket to the server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    /* Listen to the socket for client connection */
    printf("\nServer created\thostname : 'localhost'\n\t\tport num : '%s'", portnumber);
    printf("\nCreate a client and send connection request");
    printf("\nServer listening for client connection ...");
    printf("\n");
    listen(sockfd, 5);

    /* Accept client connection on request */
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer, sizeof(buffer));

    /* Listen to the socket for client message */
    printf("\nClient connected");
    printf("\nServer listening for client message ...");
    printf("\n");

    /* Read client message from socket */
    if (read(newsockfd, buffer, sizeof(buffer)) < 0)
        error("ERROR reading from socket");
    printf("\nRead successful for client message");
    printf("\nClient sent this message : %s", buffer);

    /* Send ACK for client message */
    char ack[] = "Thanks, I got your message";
    if (write(newsockfd, ack, strlen(ack)) < 0)
        error("ERROR writing to socket");
    printf("\nACK sent in response to client message");

    /* Close the socket and end communication */
    printf("\nClosing the socket ...\n\n");
    close(newsockfd);
    close(sockfd);
    return 0;
}