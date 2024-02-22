#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define CHANNEL 1 // channel No

void server() { // rem_addr -> client_addr
    struct sockaddr_rc server_addr = {0};  // Bluetooth MAC Address and other meta info
    struct sockaddr_rc client_addr = {0};  // Bluetooth MAC Address and other meta info
    char mac_addr_str_buf[255] = {0};
    char rcv_buf[1024] = {0};
    int sd_listen, sd_client;
    ssize_t bytes_read;
    socklen_t opt = sizeof(client_addr);

    // Socket Create
    sd_listen = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Setting Local Address
    server_addr.rc_family = AF_BLUETOOTH;
    memset(&server_addr.rc_bdaddr, 0, sizeof(server_addr.rc_bdaddr)); // Zero clear Bluetooth MAC Addr
    server_addr.rc_channel = (uint8_t) CHANNEL;

    // Bind
    bind(sd_listen, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Listen
    listen(sd_listen, 1);

    // Accept (Waiting for connection from client)
    sd_client = accept(sd_listen, (struct sockaddr *)&client_addr, &opt);

    // Get client address 
    ba2str(&client_addr.rc_bdaddr, mac_addr_str_buf);  // bluetooth address(binary) to bluetooth address(string)
    fprintf(stderr, "accepted connection from %s\n", mac_addr_str_buf);
    memset(mac_addr_str_buf, 0, sizeof(mac_addr_str_buf));

    // Recv
    bytes_read = read(sd_client, rcv_buf, sizeof(rcv_buf));
    if( bytes_read > 0 ) {
        printf("Received: %s\n", rcv_buf);
    }

    // close
    close(sd_client);
    close(sd_listen);
}


void client() {
    struct sockaddr_rc addr = {0};
    int sd_server;
    int ret;
    char server_mac_addr_str[18] = "A0:C5:89:7D:C9:94"; 
    char snd_buf[1024] = "Hello, Bluetooth!";

    // Socket Create
    sd_server = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set server MAC addr
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) CHANNEL;
    str2ba(server_mac_addr_str, &addr.rc_bdaddr);

    // connect
    ret = connect(sd_server, (struct sockaddr *)&addr, sizeof(addr));

    if(ret == 0) {
        // Send
        ret = write(sd_server, snd_buf, strlen(snd_buf));
        printf("Sent: %s\n", snd_buf);
    }

    // Close
    close(sd_server);
}


int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: %s s for server, c for client\n", argv[0]);
        exit(0);
    }

    if(argv[1][0] == 's') {
        server();
    } else if(argv[1][0] == 'c') {
        client();
    } else {
        printf("Invalid option. Use 's' for server or 'c' for client.\n");
        exit(0);
    }

    return 0;
}
