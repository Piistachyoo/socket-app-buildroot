# Socket App Buildroot
### 👋🏼 Hello everyone,  
I want to share with you my last assignment for "Linux System Programming and Introduction to Buildroot" course in the "Advanced Embedded Linux Development" Specialization  
  
### 🌟 I created a socket server that runs as a daemon 😈 on startup, using buildroot and linux system calls !  
[Socket app - Buildroot - YouTube](https://youtu.be/ppKGV3WJVFM)

### 🔴 First:  
- The app is written in C language  
- Supports running in normal mode, or in daemon mode using "-d" argument  
- Added signal handling for handling SIGTERM/SIGKILL/SIGINT signals to shutdown properly  
- Uses syslog to log connection status to logs  
- On startup, it truncates a temp file (/var/tmp/aesdsocket)  
- Upon receiving data, it appends incoming data into that temp file  
- Once it receives a new line "\n", it stops receiving and sends all the contents of the temp file back to the sender  
- Created a simple makefile to support cross-compile  
- Added valgrind support in makefile, and checked for any memory leaks -> result: no memory leaks  
  
### 🔴 Second:  
- Created a start-stop script which will start or stop my daemon on system startup/shutdown   
  
### 🔴 Third:  
- Added my package into buildroot's external package folder, configured my files into their destination (/usr/bin and /etc/init.d)   
  
### 🔴 Fourth:  
- Configured qemu's running script to forward port my host's 10022 port to 22 port for SSH, and 9000 port to 9000 port which my socket app uses  
  
### 🔴 Fifth:  
- Built my linux using buildroot (including my external package) and ran it to test my app  
  
### 🌟 What's in the video?  
  
- I'll start qemu in a terminal, which will show my app "aesdsocket" starting automatically as the last app in startup (because I named my file S99, which means my app will be run the last one)  
- I'll search the running processes to make sure my process is running in daemon mode  
- I'll open the file that my app uses to save any incoming data into (/var/log/messages)  
- I'll log in to my system remotely using SSH using port 10022 in another terminal, to track the system logs (/var/tmp/aesdsocketdata)  
- I'll run [sockettest.sh](http://sockettest.sh/) on my host, which sends data on port 9000, checks if it receives the same data on the same port, and returns success if so!


https://github.com/Piistachyoo/socket-app-buildroot/assets/50787380/165d5422-7460-4085-bbe2-9464fbdfe881



