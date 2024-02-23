#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <pthread.h>

#define CHANNEL 1 // channel No

/*****************************
   For Thread 
*****************************/
struct arg_st_sock_info{
    int sock_fd;
};

pthread_mutex_t g_mutex;  // for rvc thread & send thread

void *ThreadSend(void * arg_sock_info  /* struct arg_st_sock_sndrcv */){
    struct arg_st_sock_info *sock_info = (struct arg_st_sock_info *)arg_sock_info;
    int sd_client = sock_info->sock_fd;
    char snd_buf[1024] = "Hello, Bluetooth!";
    int ret;

    while(1){
        // Send
        if(fgets(snd_buf, sizeof(snd_buf), stdin) !=NULL){
            snd_buf[  strcspn(snd_buf, "\n")  ] = '\0'; // '\n --> \0'
        }
        ret = write(sd_client, snd_buf, strlen(snd_buf));  // send string by terminal '\0'

        /****************************************/
        pthread_mutex_lock(&g_mutex);
        // start

        printf("Sent: %s\n", snd_buf);
  
        // end
        pthread_mutex_unlock(&g_mutex);
        /****************************************/
    }
}

void *ThreadRecv(void * arg_sock_info  /* struct arg_st_sock_sndrcv */){
    struct arg_st_sock_info *sock_info = (struct arg_st_sock_info *)arg_sock_info;
    int sd_client = sock_info->sock_fd;
    char rcv_buf[1024] = {0};
    ssize_t bytes_read;

    while(1){
        // Recv
        bytes_read = read(sd_client, rcv_buf, sizeof(rcv_buf));
        if( bytes_read > 0 ) {

            /****************************************/
            pthread_mutex_lock(&g_mutex);
            // start

            printf("Received: %s\n", rcv_buf);

            // end
            pthread_mutex_unlock(&g_mutex);
            /****************************************/

        }
    }
}

void server() {

    /***** local Variables *******/
    // For  socket
    struct sockaddr_rc server_addr = {0};  // Bluetooth MAC Address and other meta info
    struct sockaddr_rc client_addr = {0};  // Bluetooth MAC Address and other meta info
    char mac_addr_str_buf[255] = {0};
    int sd_listen, sd_client;
    socklen_t opt = sizeof(client_addr);

    // For  thread
    pthread_t thread_recv;
    pthread_t thread_send;
    struct arg_st_sock_info sock_info;

    /***** Function Process  *******/

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

    // Thread args preparation
    sock_info.sock_fd = sd_client;

    // recv() thread
    if(pthread_create(&thread_recv, NULL, ThreadRecv, (void *)&sock_info)) {
        fprintf(stderr, "Error creating thread\n");
    }

    // recv() thread
    if(pthread_create(&thread_send, NULL, ThreadSend, (void *)&sock_info)) {
        fprintf(stderr, "Error creating thread\n");
    }

    // thread terminate process
    pthread_join(thread_recv, NULL);
    pthread_join(thread_send, NULL);
    pthread_exit(NULL);

    // close
    close(sd_client);
    close(sd_listen);
}

void client() {
    /***** local Variables *******/
    // For socket
    struct sockaddr_rc addr = {0};
    int sd_server;
    int ret;
    char server_mac_addr_str[18] = "A0:C5:89:7D:C9:94"; 

    // For  thread
    pthread_t thread_recv;
    pthread_t thread_send;
    struct arg_st_sock_info sock_info;

    /***** Function Process  *******/

    // Socket Create
    sd_server = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set server MAC addr
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) CHANNEL;
    str2ba(server_mac_addr_str, &addr.rc_bdaddr);

    // connect
    ret = connect(sd_server, (struct sockaddr *)&addr, sizeof(addr));

    if(ret == 0) {

        // Thread args preparation
        sock_info.sock_fd = sd_server;

        // recv() thread
        if(pthread_create(&thread_recv, NULL, ThreadRecv, (void *)&sock_info)) {
            fprintf(stderr, "Error creating thread\n");
        }

        // recv() thread
        if(pthread_create(&thread_send, NULL, ThreadSend, (void *)&sock_info)) {
            fprintf(stderr, "Error creating thread\n");
        }

        // thread terminate process
        pthread_join(thread_recv, NULL);
        pthread_join(thread_send, NULL);
        pthread_exit(NULL);

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
