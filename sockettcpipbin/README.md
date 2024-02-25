# TCPIP socket communication (binary data) sample App (C++)

## build
```bash
mkdir build
cd build
cmake ../
make
```

## Demo
Before Demo, the server and client must be placed within the same network.
**Server**  
```bash
#./main -s <SERVER_PORT>
./main -s 8888

> 
```
**Client**  
```bash
#./main -c <SERVER_PORT> <SERVER_IPADDR>
./main -c 8888 192.168.0.2

> Connection to Server Established :
> => ServerPort 8888, ServerIPaddr 192.168.0.1 
> => myPort 54090, myPaddr 192.168.0.2
> send 1024 bytes!
> AEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAE...
```
**Server**  
```bash
> Accept Client connection :
> => ClientPort 54090, ClientIPaddr 192.168.0.2
> => myPort 8888, myPaddr 192.168.0.1 
> bytes_read=1024
AEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAEAE...
```

Here, if you omit the arguments, application interpret them as Default parameters.  
 (Show bellow example;)

**Server**  
```bash
./main -s
#./main -s 8080
```
**Client** 
```bash
./main -c
#./main -c 8080 127.0.0.1
```


## Binary data
If you send & recv **binary data(not string)**, attention to **Terminal** !
**Binary data doesn't have delimiter** `\0`.  
**DONOT use** `strlen()`.  

```c
//========================================
//=== send()
//========================================
/* string */
char snd_buf[1024] = "Hello, TCPIP!";
send(sd_server, snd_buf, strlen(snd_buf), 0);

/* binary */
unsigned char snd_buf[1024];
send(sd_server, snd_buf, sizeof(snd_buf), 0);

//========================================
//=== recv()
//========================================
/* string */
char rcv_buf[1024] = {0};
recv(sd_client, rcv_buf, strlen(rcv_buf), 0);

/* binary */
unsigned  char rcv_buf[1024] = {0};
recv(sd_client, rcv_buf, sizeof(rcv_buf), 0); 
```