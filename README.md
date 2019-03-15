# Chrome Extension Native Messaging Example
Communicate between a C++ native app and a chrome extension with Native Messaging.

## Description
The example sends a text which a user entered through the extension popup view to a C++ native app. The native app will then write down the received data into log.txt. Later, it will send back the data to the chrome extension. The chrome extension will then display the received data in the popup view.

## Installation
1. Add the extension to chrome
```
Go to chrome://extensions/
Click Load unpacked
Choose the extension folder
```
2. Update the "allowed_origins" field with the extension id received from step 1 in "native-app/com.hashpire.pingpong.json"
3. Run install_host.sh (Make sure you have the required permission)
```
cd native-app
sudo sh ./install_host.sh
```

