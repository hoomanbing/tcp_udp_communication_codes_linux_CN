#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
    char buffer[MAXLINE], response[MAXLINE];
    int sockfd, len, portno, n, num_msg;
    struct sockaddr_in serv_addr, cli_addr;

    printf("\nEnter number of messages: ");
    scanf("%d", &num_msg);
    printf("\nServer requires the following to operate");
    printf("\nPlease provide server port num: ");
    scanf("%d", &portno);
    getchar();

    // Open socket from server end
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Fill server address struct
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(portno);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Receive and send messages
    for (int i = 0; i < num_msg; ++i)
    {
        // Receive message from client
        len = sizeof(cli_addr);
        n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cli_addr, &len);
        if (n < 0)
            error("ERROR in receiving");
        printf("Message from client: %s\n", buffer);
    }

    // Prompt for response
    printf("Enter message to send to client: ");
    fgets(response, MAXLINE, stdin);

    for (int i = 0; i < num_msg; ++i)
    {
        // Sending response to client
        n = sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cli_addr, len);
        if (n < 0)
            error("ERROR in sending");
    }

    // Close the socket
    close(sockfd);

    return 0;
}
