#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_PORT_SERVER 8080
#define DEFAULT_IPADDR_CLIENT "127.0.0.1"

void server(const int port_server) {
    struct sockaddr_in address_server;
    struct sockaddr_in address_client;
    int addrlen_client = sizeof(address_client);
    char rcv_buf[1024] = {0};
    int sd_listen, sd_client;
    ssize_t bytes_read;

    // Socket Create
    if ((sd_listen = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting Server Address
    address_server.sin_family = AF_INET;
    address_server.sin_addr.s_addr = INADDR_ANY;
    address_server.sin_port = htons(port_server);

    // Bind
    bind(sd_listen, (struct sockaddr *)&address_server, sizeof(address_server));

    // Listen
    if (listen(sd_listen, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept (Waiting for connection from client)
    if ((sd_client = accept(sd_listen, (struct sockaddr *)&address_client, (socklen_t*)&addrlen_client))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Accept Client connection :\n");

    // print established client port & addr
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address_client.sin_addr, clientIP, sizeof(clientIP));
    printf("=> ClientPort %d, ClientIPaddr %s  \n", ntohs(address_client.sin_port), clientIP);

    // check established server port & addr
    struct sockaddr_in myaddr;
    socklen_t len = sizeof(myaddr);
    if (getsockname(sd_client, (struct sockaddr *)&myaddr, &len) == -1) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }

    // print established server port & addr
    char serverIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &myaddr.sin_addr, serverIP, sizeof(serverIP));
    printf("=> myPort %d, myPaddr %s  \n", ntohs(myaddr.sin_port), serverIP);

    // Recv
    bytes_read = read(sd_client, rcv_buf, sizeof(rcv_buf));
    if( bytes_read > 0 ) {
        printf("Received: %s\n", rcv_buf);
    }

    // close
    close(sd_client);
    close(sd_listen);
}


void client(const int port_server, const char *ipaddr_server) {
    struct sockaddr_in addr_server;
    int sd_server;
    int ret;
    char snd_buf[1024] = "Hello, TCPIP!";

    // Socket Create
    if ((sd_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    // set server addr
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port_server);
    if(inet_pton(AF_INET, ipaddr_server, &addr_server.sin_addr)<=0) {
        printf("Invalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    // connect
    if (connect(sd_server, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0) {
        printf("Connection Failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Connection to Server Established :\n");
    printf("=> ServerPort %d, ServerIPaddr %s \n", port_server, ipaddr_server);

    // check established client port & addr
    struct sockaddr_in myaddr;
    socklen_t len = sizeof(myaddr);
    if (getsockname(sd_server, (struct sockaddr *)&myaddr, &len) == -1) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }

    // print established client port & addr
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &myaddr.sin_addr, clientIP, sizeof(clientIP));
    printf("=> myPort %d, myPaddr %s  \n", ntohs(myaddr.sin_port), clientIP);


    // send
    send(sd_server, snd_buf, strlen(snd_buf), 0);
    printf("sent : %s\n",snd_buf);

    // Close
    close(sd_server);
}


int main(int argc, char **argv) {
    // ===== server launch
    if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        server(DEFAULT_PORT_SERVER); // default port
    } else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        int port = atoi(argv[2]);
        if (port > 0) {  // check if port number is valid
            server(port); // designated port
        } else {
            fprintf(stderr, "Error: Invalid port number\n");
            return 1;
        }

    // ===== client launch
    } else if (argc == 2 && strcmp(argv[1], "-c") == 0) {
        client(DEFAULT_PORT_SERVER, DEFAULT_IPADDR_CLIENT); // default port & ipaddr
    } else if (argc == 4 && strcmp(argv[1], "-c") == 0) {
        int port = atoi(argv[2]);
        struct sockaddr_in sa;
        if (port > 0 && inet_pton(AF_INET, argv[3], &(sa.sin_addr)) == 1) {   // check if port number & ipaddr is valid
            client(port, argv[3]); // designated port & ipaddr
        } else {
            fprintf(stderr, "Error: Invalid port number or IP address\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: \n");
        fprintf(stderr, "  Server: %s -s [port]\n", argv[0]);
        fprintf(stderr, "  Client: %s -c <port> <ip_address>\n", argv[0]);
        return 1;
    }

    return 0;
}
