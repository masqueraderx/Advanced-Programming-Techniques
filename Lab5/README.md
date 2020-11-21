# Lab5 Sockets

We have to build a socket to realize the communication between different applications.

To build the file on linux system, compile it with **g++ main.cpp ECE_UDPSocket.cpp -pthread -o client.out** and 
on **g++ main.cpp ECE_UDPSocket.cpp -pthread -o server.out** command window.

Then run it on two different command window. Run the server side with **./server.out 61717** and client side with
**./client.out localhost 61717**.

How to type in specfic command in server and client sides is listed in Lab5.pdf.
