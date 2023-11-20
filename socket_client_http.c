/* Client pour les sockets
 *    socket_client ip_server port
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#define MAX_BUFFER_SIZE 4096


int main(int argc, char **argv) {
    int sockfd, newsockfd, clilen, chilpid, ok, nleft, nbwriten;
    char c;
    struct sockaddr_in cli_addr, serv_addr;

    if (argc != 3) {
        printf("usage  socket_client server port\n");
        exit(0);
    }


    /*
     *  partie client
     */
    printf("client starting\n");

    /* initialise la structure de donnee */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    /* ouvre le socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n");
        exit(0);
    }

    /* effectue la connection */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("socket error\n");
        exit(0);
    }


    // Send HTTP GET request
    const char *request = "GET / HTTP/1.1\r\nHost: perdu.com\r\nConnection: close\r\n\r\n";
    if (send(sockfd, request, strlen(request), 0) == -1) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }

    // Receive and print HTTP response
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    if (bytes_received == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }


    close(sockfd);

    /*  attention il s'agit d'une boucle infinie
     *  le socket n'est jamais ferme !
     */

    return 1;

}

