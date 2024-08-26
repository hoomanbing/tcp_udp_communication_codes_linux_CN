#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h> // Include pthread library for multithreading

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void *communication(void *sockfd_void)
{
    int sockfd = *((int *)sockfd_void);
    char buffer[256];

    /* Client connected -- Wait for user message */
    printf("\nConnected to server 'localhost'");
    printf("\nReady for communication ...");
    printf("\n");

    /* Take user input for message */
    printf("\nPlease enter the message: ");
    bzero(buffer, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    /* Write message to socket for communication */
    printf("\nWriting message to socket ...");
    if (write(sockfd, buffer, sizeof(buffer)) < 0)
        error("ERROR writing to socket");
    printf("\nMessage sent/written to socket");

    /* Listen to the socket for server ACK */
    printf("\nClient listening for server ACK ...");
    printf("\n");

    /* Read ACK from server */
    bzero(buffer, 256);
    if (read(sockfd, buffer, sizeof(buffer)) < 0)
        error("ERROR reading from socket");
    printf("\nRead successful for server ACK");
    printf("\nServer sent this ACK : %s", buffer);

    close(sockfd);
    pthread_exit(NULL);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char hostname[20], portnumber[10];

    /* Ask user to provide hostname and port number */
    printf("\nClient requires the following to operate");
    printf("\nPlease provide server hostname: ");
    scanf("%s", hostname);
    printf("\nPlease provide server port num: ");
    scanf("%s", portnumber);
    getchar();

    /* Open socket from client end */
    portno = atoi(portnumber);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /* Connect to server using hostname */
    server = gethostbyname(hostname);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    pthread_t thread; // Declare thread variable

    // Create a new thread for communication
    if (pthread_create(&thread, NULL, communication, (void *)&sockfd) != 0)
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    return 0;
}
