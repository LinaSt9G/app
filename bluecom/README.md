# Bluetooth communication sample App (C++)

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
> Sent: Hello, Bluetooth!
```
```bash
# server
> accepted connection from E4:5F:01:70:A8:1E
> Received: Hello, Bluetooth!
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

