/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 17-Nov-2020
Description: This file defines class ECE_UDPSocket's
member functions and private variables.
*/
#pragma once

#include <thread>
#include <list>
#include <string>
#include <mutex>
#include <cstring>
#include <iostream>
#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>

    #pragma comment (lib, "Ws2_32.lib")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */

typedef int SOCKET;
#endif

// composite message
struct udpMessage
{
    unsigned short nVersion;
    unsigned short nType;
    unsigned short nMsgLen;
    unsigned long lSeqNum;
    char chMsg[1000] = {0};
};

class ECE_UDPSocket
{
public:
    // Destructor
    ECE_UDPSocket() = delete;
    ~ECE_UDPSocket();
    // Constructor
    ECE_UDPSocket(unsigned short usPort);
    // Server: get Next Message from Client
    bool getNextMessage(udpMessage& msg);
    // Client side: send Message
    void sendMessage(const std::string& strTo, unsigned short usPortNum, const udpMessage& msg);
    // Clear Composite Message
    void clearCompositeMsg();
    // Display Composite Message
    void displayCompositeMsg();
    // Other stuff
    // Send Composite Message
    void sendCompositeMsg();
    // Process the Message
    void processMessage(const udpMessage &inMsg); // Add msg to the list
    void addSource(const sockaddr_in &from); // Add source to the list
    // Sockets Basic Functions
    // Initiate
    int sockInit(void);
    // Quit
    int sockQuit(void);
    // Close
    int sockClose();
    // Error
    void error(const char* msg);

    int m_sockfd;
private:
    unsigned short m_usPort;
    std::thread m_recvThread;
    std::list<udpMessage> m_lstMsgs;
    std::list<udpMessage>::iterator m_it;
    std::list<sockaddr_in> m_lstSources;
    std::mutex m_mutex;

};

