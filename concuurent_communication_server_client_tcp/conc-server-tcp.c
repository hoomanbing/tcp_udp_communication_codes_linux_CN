#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h> // Include pthread library for multithreading

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void *communication(void *newsockfd_void)
{
    int newsockfd = *((int *)newsockfd_void);
    char buffer[256];

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

    close(newsockfd);
    pthread_exit(NULL);
}

int main()
{
    int sockfd, newsockfd, portno;
    char portnumber[10];
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
    printf("\nServer listening for client connection ...");
    printf("\n");
    listen(sockfd, 5);

    while (1)
    {
        /* Accept client connection on request */
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        pthread_t thread; // Declare thread variable

        // Create a new thread for communication
        if (pthread_create(&thread, NULL, communication, (void *)&newsockfd) != 0)
        {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }

        // Detach the thread to avoid memory leaks
        pthread_detach(thread);
    }

    close(sockfd);
    return 0;
}
