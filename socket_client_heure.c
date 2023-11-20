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



    /* repete dans le socket tout ce qu'il entend */
    /*
    while (c!=EOF) {
        c = getchar();
        write(sockfd, &c, 1);
    }
     */
    char buffer[4];
    ssize_t bytesreceived = read(sockfd, buffer, 4);

    if(bytesreceived == -1){
        perror("Read failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    else if ( bytesreceived == 0 ){
        printf("Connection closed by the server");
    }

    unsigned long time_long = (unsigned long) ntohl(*((uint32_t *)buffer));

    time_t time = (time_t) (time_long - 2208988800UL);

    printf("NIST time received %s", ctime(&time));

    close(sockfd);

    /*  attention il s'agit d'une boucle infinie
     *  le socket n'est jamais ferme !
     */

    return 1;

}
