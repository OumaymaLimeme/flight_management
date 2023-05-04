# flight_management

1 .TCP Server-Client implementation in C

TCP Server-Client implementation refers to the process of creating two programs, one acting as a server and the other acting as a client, that communicate with each other over a network using the TCP (Transmission Control Protocol) protocol.
In this process, the server program creates a socket and listens for incoming connection requests from clients. When a client requests a connection, the server accepts the connection and creates a new socket to communicate with the client. The server can then send and receive data to/from the client through this socket.
On the other hand, the client program connects to the server using the server's IP address and port number. Once the connection is established, the client can send and receive data to/from the server through the socket.
Overall, TCP Server-Client implementation is a common way to create networked applications that allow computers to communicate with each other over a network.

2 .MultiThreading with Socket Programming by using TCP/IP in C.

What is MultiThreading?
Multithreading is the ability of a program to manage its use by more than one user at 
a time and to even manage multiple requests by the same user without having to 
have multiple copies of the programming running in the computer.
In the designed protocol there is :
1. Implemented a multithreaded file Server and its using Tcp sockets.
2. Server can establish the connection with the clients in the project i did with 
three clients.
3. Clients can upload and download any type of file.I tried with jpeg, png, iso, 
video file.
4. The file size will be divided in the chunks and chunks size would be 1KB and 
will transfer in chunks, can increase the speed but in the program took 1024 
bytes.
5. Any type of file can be uploaded and also can be downloaded from the server.
