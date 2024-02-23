# Bluetooth Connection Guide

## Prerequisite
- Bluetooth Connection between two Linux devices.
  eg) **Ubuntu PC** vs. **RaspberryPi**


## Example Senario
This paper explains how to establish bluetooth connection between two **Linux** devices, following bellow example description:
- Establish bluetooth connection **Ubuntu PC** vs. **RaspberryPi** .
- **RaspberryPi** request pairing, that is "***Initiator***", like **client**.
- **Ubuntu PC** accept pairing, that is "***Responder***", like **server**.

## Step1. Confirm Bluetooth device
```bash
hciconfig
```
```bash
## Ubuntu PC
hci0:   Type: Primary  Bus: USB
        BD Address: A0:C5:89:7D:C9:94  ACL MTU: 1021:4  SCO MTU: 96:6
        UP RUNNING 
        RX bytes:724014 acl:0 sco:0 events:22657 errors:0
        TX bytes:600137 acl:0 sco:0 commands:2439 errors:0
```

```bash
## RaspberryPi
hci0:   Type: Primary  Bus: UART
        BD Address: E4:5F:01:70:A8:1E  ACL MTU: 1021:8  SCO MTU: 64:1
        UP RUNNING 
        RX bytes:1196447 acl:0 sco:0 events:33364 errors:0
        TX bytes:3588 acl:0 sco:0 commands:105 errors:0
```


## Step2. Pairing and Remember Pairing list

**1. Responder (Ubuntu PC)  setup**
```bash
# Confirm my bluetooth devices.
echo -e "list" | bluetoothctl   

#=== Device Power ON
echo -e "power on" | bluetoothctl 
echo -e "show"     | bluetoothctl  | grep  "Powered" 

#=== Make discoverable from others
echo -e "discoverable on" | bluetoothctl  
echo -e "show"            | bluetoothctl  | grep  "Discoverable:" 

#=== discoverable timeout
echo -e "discoverable-timeout 3600" | bluetoothctl 
echo -e "show"            | bluetoothctl  | grep  "DiscoverableTimeout"

#== Check if Pairable
echo -e "show" | bluetoothctl  | grep  "Pairable" 
```

**2. Initiator (RaspberryPi)  setup**
```bash
# Confirm my bluetooth devices.
echo -e "list" | bluetoothctl   

#=== Device Power ON
echo -e "power on" | bluetoothctl 
echo -e "show"     | bluetoothctl  | grep  "Powered" 

#=== Make discoverable from others
echo -e "discoverable on" | bluetoothctl  
echo -e "show"            | bluetoothctl  | grep  "Discoverable:" 

#=== discoverable timeout
echo -e "discoverable-timeout 3600" | bluetoothctl 
echo -e "show"            | bluetoothctl  | grep  "DiscoverableTimeout"

#== Check if Pairable
echo -e "show" | bluetoothctl  | grep  "Pairable" 
```

**3. Start bluetoothctl talk on Responder (Ubuntu PC)**
```bash
bluetoothctl
```

**4. Start bluetoothctl talk on Initiator (RaspberryPi)**
```bash
bluetoothctl
```

**5. Initiator (RaspberryPi) searches Responder (Ubuntu PC)**
```bash
#== Search & Register surrounding bluetooth devices
scan on

#== Stop search if you find Responder (Ubuntu PC) MAC Address
scan off

#== Check if detected list contains  Responder (Ubuntu PC) MAC Address
devices
```
**6. Pair Initiator (RaspberryPi) and Responder (Ubuntu PC)**
```bash
#== Pairing request from Initiator (RaspberryPi) to Responder (Ubuntu PC)
#== !!! Immediately establish pairing ! Otherwise device list evapolates.
pair A0:C5:89:7D:C9:94  # <-- Responder (Ubuntu PC) MAC Address

#== Confirm Pairing list
paired-devices
```
**7. Initiator (RaspberryPi) establish Connection to Responder (Ubuntu PC)**
```bash
#== Establish Connection
connect A0:C5:89:7D:C9:94  # <-- Responder (Ubuntu PC) MAC Address
```

**8. Responder (Ubuntu PC) accepts connection request**
```bash
yes
yes
yes
```
**9. Responder (Ubuntu PC) trust and remember Initiator (RaspberryPi)**
```bash
trust E4:5F:01:70:A8:1E  # <-- Initiator (RaspberryPi) MAC Address
```
**10. Initiator (RaspberryPi) disconnect**
```bash
disconnect A0:C5:89:7D:C9:94  # <-- Responder (Ubuntu PC) MAC Address
```

## Step3. Connect & Disconnect
**1. Start bluetoothctl talk on Responder (Ubuntu PC)**
```bash
bluetoothctl
```

**2. Start bluetoothctl talk on Initiator (RaspberryPi)**
```bash
bluetoothctl
```

**3. Initiator (RaspberryPi) establish Connection to Responder (Ubuntu PC)**
```bash
#== Establish Connection
connect A0:C5:89:7D:C9:94  # <-- Responder (Ubuntu PC) MAC Address
```

**4. Responder (Ubuntu PC) accepts**
```bash
### Auto establishconnection because trusted
```

**5. Initiator (RaspberryPi) disconnect**
```bash
disconnect A0:C5:89:7D:C9:94
```


## 3. Remove device registoration

**1. Initiator (RaspberryPi) remove Responder (Ubuntu PC)**
```bash
remove A0:C5:89:7D:C9:94  # <-- Responder (Ubuntu PC) MAC Address
paired-devices
```

**2. Responder (Ubuntu PC) remove Initiator (RaspberryPi)**
```bash
remove E4:5F:01:70:A8:1E  # <-- Initiator (RaspberryPi) MAC Address
paired-devices
```


