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
    char buffer[MAXLINE];
    int sockfd, len, portno;
    struct sockaddr_in serv_addr, cli_addr;

    printf("\nServer requires the following to operate");
    printf("\nPlease provide server port num: ");
    scanf("%d", &portno);

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

    printf("\nWaiting for message from client...\n");

    // Receive message from client
    len = sizeof(cli_addr);
    int n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cli_addr, &len);
    if (n < 0)
        error("ERROR in receiving");
    buffer[n] = '\0';
    printf("Message from client: %s\n", buffer);

    // Sending response to client
    printf("Enter message to send to client: ");
    getchar(); // Consume the newline character left in the input buffer
    fgets(buffer, MAXLINE, stdin);
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cli_addr, len);
    if (n < 0)
        error("ERROR in sending");

    // Close the socket
    close(sockfd);

    return 0;
}
