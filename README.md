# network-communication-example
This is a project for establishing a TCP connection between server and client and subsequent continuous communication between the two systems/ devices that are on the same LAN (Local Area Network).

This is exclusively for Mac-OS. (External software that supports linux commands can be used on Windows).
Steps:
1) Open Terminal on both systems and navigate to the directory where the respective files are present using "cd" command.
2) Edit the ip-address in BOTH the files to the ip-address of the server machine. Presently, a placeholder ip-address "192.168.1.1" is used, and if executed without using the appropriate server ip-address, the project will result in an error.
3) Compile each file in their respective devices using the command: "gcc filename.c -o somefile"
4) Then, execute both the compiled files using "./somefile" in their respective machines.
5) Finally, communicate away........
6) To end the connection/process in any of the systems: press ctrl + z
