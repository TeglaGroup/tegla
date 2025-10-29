#pragma once

#include <RakPeerInterface.h>

class NetworkServer {
public:
    NetworkServer(unsigned short port = 4000);
    ~NetworkServer();

    void Start();
    void Stop();
    void Poll();

    unsigned int NumberOfConnections();

private:
    RakNet::RakPeerInterface* peer;
    unsigned short port;
};