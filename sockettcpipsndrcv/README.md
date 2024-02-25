# TCPIP socket communication (send & recv) sample App (C++)

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
> 
```
**Server**  
```bash
> Accept Client connection :
> => ClientPort 54090, ClientIPaddr 192.168.0.2
> => myPort 8888, myPaddr 192.168.0.1 
> 
```
**Client**  
```bash
> hoge         # type
> Sent: hoge
```
**Server**  
```bash
> Received: hoge
```
**Server**  
```bash
> piyo         # type
> Sent: piyo
```
**Client**  
```bash
> Received: piyo
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