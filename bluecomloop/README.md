# Bluetooth communication loop App (C++)

## depencencies
```bash
sudo apt-get -y install bluetooth
sudo apt-get -y install bluez
sudo apt-get -y install libbluetooth-dev
```

## build
```bash
mkdir build
cd build
cmake ../
make
```

## Demo
Before Demo, you should establish bluetooth connection between two devices. See [./BluetoothConnectGuide.md](./BluetoothConnectGuide.md).
```bash
./main s # server
```
```bash
./main c # client

> send !
> AEAEAEAEAEAEAEAEAE...  # binary data '0xAE' 1024 byte
> send !
> AEAEAEAEAEAEAEAEAE...  # binary data '0xAE' 1024 byte
> ...
```
```bash
# server
> accepted connection from E4:5F:01:70:A8:1E
> bytes_read=1016
> AEAEAEAEAEAEAEAEAEAE...
> bytes_read=8
> AEAEAEAEAEAEAEAE
> bytes_read=1024
> AEAEAEAEAEAEAEAEAEAE...
```





## bluetooth command / libraries
```bash
hciconfig
bluetoothctl
bluez  # sudo apt -y install bluetooth bluez
```
```c
#include <bluetooth/rfcomm.h>  // bluez
#include <bluetooth/bluetooth.h>   // sudo apt-get install libbluetooth-dev
```

