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


void scanPort(char* host, int port);

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("usage : socket_client <hostname>\n");
        exit(0);
    }

    char* hostname = argv[1];


    /*
     *  partie client
     */
    printf("client starting\n");

        printf("Scanning port : %d\r\n", 80);
        scanPort(hostname, 80);
        sleep(5);


    /*  attention il s'agit d'une boucle infinie
     *  le socket n'est jamais ferme !
     */

    return 1;

}

void scanPort(char* host, int port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Socket creation failed... désolé");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        perror("Invalid address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }


    printf("Port %d is open\r\n", port);


    close(sockfd);
}
