#include "TeglaServer/NetworkServer.h"

#include "MessageIdentifiers.h"

#include <iostream>

NetworkServer::NetworkServer(unsigned short port_) : port(port_) {
    peer = RakNet::RakPeerInterface::GetInstance();
}

NetworkServer::~NetworkServer() {
    RakNet::RakPeerInterface::DestroyInstance(peer);
}

void NetworkServer::Start() {
    RakNet::SocketDescriptor sd(port, 0);

    peer->Startup(32, &sd, 1);
    peer->SetMaximumIncomingConnections(32);

    std::cout << "NetworkServer started on port " << port << std::endl;
}

void NetworkServer::Stop() {
    peer->Shutdown(300);
}

void NetworkServer::Poll() {
    for (RakNet::Packet* packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
        switch (packet->data[0]) {
            case ID_NEW_INCOMING_CONNECTION:
                std::cout << "new connection: " << packet->systemAddress.ToString() << std::endl;
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                std::cout << "disconnected: " << packet->systemAddress.ToString() << std::endl;
                break;
            case ID_CONNECTION_LOST:
                std::cout << "connection lost: " << packet->systemAddress.ToString() << std::endl;
                break;
            default:
                std::cout << "received packet with ID " << (int)packet->data[0] << std::endl;
                break;
        }
    }
}

unsigned int NetworkServer::NumberOfConnections() {
    return peer->NumberOfConnections();
}
