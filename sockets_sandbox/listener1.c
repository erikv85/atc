/**
 * Adapted from Donahoo, Calvert, "TCP/IP Sockets in C", 1st edition
 */

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXRECVSTRING 255  /* Longest string to receive */

int main(int argc, char *argv[])
{
    unsigned short broadcastPort = 1337;

    /* Create a best-effort datagram socket using UDP */
    int sock;                         /* Socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        printf("socket() failed");

    /* Construct bind structure */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
    broadcastAddr.sin_port = htons(broadcastPort);      /* Broadcast port */

    /* Bind to the broadcast port */
    printf("listener1 trying to connect/bind...\n");
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
        printf("bind() failed");

    /* Receive a single datagram from the server */
    int recvStringLen;                /* Length of received string */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
        printf("recvfrom() failed");

    recvString[recvStringLen] = '\0';
    printf("listener1 Received: %s\n", recvString);    /* Print the received string */

    close(sock);
    printf("listener1 infinite loop, bye\n");
    while (1) {}
    exit(0);
}
