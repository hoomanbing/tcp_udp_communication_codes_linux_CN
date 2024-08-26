#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXLINE 100

// Function to handle errors
void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Driver code
int main()
{
    char buffer[MAXLINE];
    int sockfd, n, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char hostname[MAXLINE], portnumber[MAXLINE];

    printf("\nClient requires the following to operate");
    printf("\nPlease provide server hostname: ");
    scanf("%s", hostname);
    printf("\nPlease provide server port num: ");
    scanf("%s", portnumber);
    getchar(); // Consume the newline character left in the input buffer

    /* Open socket from client end */
    portno = atoi(portnumber);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /* Get server details */
    server = gethostbyname(hostname);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR: No such host\n");
        exit(EXIT_FAILURE);
    }

    /* Fill server address struct */
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Sending message to server
    printf("Enter message to send to server: ");
    fgets(buffer, MAXLINE, stdin);
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0)
        error("ERROR sending to socket");

    printf("\nWaiting for message from server\n");

    // Waiting for response from server
    bzero(buffer, MAXLINE);
    socklen_t serv_len = sizeof(serv_addr);
    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&serv_addr, &serv_len);
    if (n < 0)
        error("ERROR receiving from socket");
    printf("Message from server: %s\n", buffer);

    // Close the socket
    close(sockfd);

    return 0;
}
