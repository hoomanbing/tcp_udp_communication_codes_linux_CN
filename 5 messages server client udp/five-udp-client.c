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
    int sockfd, len, portno, n, num_msg;
    struct sockaddr_in serv_addr;

    char hostname[MAXLINE];

    printf("\nEnter number of messages: ");
    scanf("%d", &num_msg);
    printf("\nClient requires the following to operate");
    printf("\nPlease provide server hostname: ");
    scanf("%s", hostname);
    printf("\nPlease provide server port num: ");
    scanf("%d", &portno);
    getchar(); // Consume the newline character left in the input buffer

    // Open socket from client end
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Get server details
    struct hostent *server = gethostbyname(hostname);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR: No such host\n");
        exit(EXIT_FAILURE);
    }

    // Fill server address struct
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Send and receive messages
    for (int i = 0; i < num_msg; ++i)
    {
        // Sending message to server
        printf("Enter message to send to server: ");
        fgets(buffer, MAXLINE, stdin);
        n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (n < 0)
            error("ERROR sending to socket");

        // Receive response from server
        len = sizeof(serv_addr);
        n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&serv_addr, &len);
        if (n < 0)
            error("ERROR receiving from socket");
        buffer[n] = '\0';
        printf("Message from server: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
