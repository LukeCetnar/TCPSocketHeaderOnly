#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <string>

#pragma warning(disable : 4996)
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 69
#define IP_ADDR "127.0.0.1"


class NetworkHandler
{
public:
    NetworkHandler();
    ~NetworkHandler();

    
    int sendData(std::string data);

private:
    void closeConnection();
    int iResult;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;

};


NetworkHandler::NetworkHandler()
{


    int recvbuflen = DEFAULT_BUFLEN;
    //std::string test = "<event version=\"2.0\" uid=\"88772c0d-b218-469f-a995-37981b209928\" type=\"a-n-S\" time=\"2020-11-20T21:01:13.618516Z\" start=\"2020-11-20T21:01:13.618516Z\" stale=\"2020-11-20T21:03:13.618516Z\" how=\"h-g-i-g-o\"><point lat=\"28.171008728590223\" lon=\"-79.92\" hae=\"0\" ce=\"9999999\" le=\"9999999\" /><detail><contact callsign=\"USNS Mercy\" /></detail><remarks><remarks source=\"AIS\" /></remarks></event>";
    //const char* sendbuf = test.c_str();
    char recvbuf[DEFAULT_BUFLEN] = "";

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        closeConnection();
    }

    //----------------------
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        closeConnection();
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(IP_ADDR);
    clientService.sin_port = htons(8088);

    //----------------------
    // Connect to server.
    iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect failed with error: %d\n", WSAGetLastError());
        closeConnection();
    }
}


NetworkHandler::~NetworkHandler()
{
    closeConnection();
}

/**
 * \brief Closes Socket Connection and cleans up library.
 * 
 */
inline void NetworkHandler::closeConnection()
{
    closesocket(ConnectSocket);
    WSACleanup();

}



/**
 * \brief Sends String data Over TCP.
 * 
 * \param data String to be sent.
 * \return 1 - Successful 0 - Error
 */
inline int NetworkHandler::sendData(std::string data)
{
    char sendbuf[9999];
    strcpy(sendbuf, data.c_str());
    //----------------------
   // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) 
    {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closeConnection();
    }
    return 1;
}
