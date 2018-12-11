#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

#include <SFML/Network.hpp>
#include "PacketCreator.hpp"
#include "PacketUnpacker.hpp"

class UDPClient {
public:
    /// Creates a client with every info it needs to send and receive data
    UDPClient(const unsigned short destPort,
              const sf::IpAddress &destAddress = sf::IpAddress::Any)
            : destPort(destPort), destAddress(destAddress) {
    }

    Packet::Lobbies getLobbies() {
        auto toSend = Packet::Creator::MakeListLobbies();
        Send(toSend);
        sf::Packet packet;
        Packet::Lobbies lobbies;
        if (Receive(packet, 0)) {
            lobbies = Packet::Unpacker::UnpackLobbies(packet);
        }
        return lobbies;
    }

    void Disconnect() {
        auto disconnectPacket = Packet::Creator::MakeDisconnect();
        Send(disconnectPacket);
    }

    void Send(sf::Packet &packet) {
        //Packet::PrintPacket(packet);
        [[maybe_unused]] auto res = udpSocket.send(packet, destAddress, destPort);
//        std::cerr << "Send result: " << res << std::endl;
    }

    /// Pseudo non blocking receive
    /// False if it received nothing
    /// True if it received something
    /// This takes a minimum of 1 microsecond to execute due to polling
    bool Receive(sf::Packet &packet, int timeOut = 1) {
        sf::SocketSelector selector;
        /// Smallest possible timeout
        sf::Time time = sf::microseconds(timeOut);

        selector.add(udpSocket);
        /// This is badly explained in the documentation,
        /// but to check if the socket is ready, you HAVE to wait
        if (selector.wait(time)) {
            if (selector.isReady(udpSocket)) {
                udpSocket.receive(packet, destAddress, destPort);
                //Packet::PrintPacket(packet);
                return true;
            }
        }
        return false;
    }

    /// Gets the client number assigned by the server,
    /// if this returns 0 the party is full
    int Connect(int channel) {
        sf::Packet connectPacket = Packet::Creator::MakeConnect(channel);
        udpSocket.send(connectPacket, destAddress, destPort);

        char buff[1];
        std::size_t bytesReceived;
        udpSocket.receive((void *) buff, 1, bytesReceived, destAddress, destPort);
        if (bytesReceived < 1) {
            clientNumber = 0;
        }
        clientNumber = *buff;
        return clientNumber;
    }

    /// Gets the client number assigned by the server,
    /// if this returns 0, please retry
    int Create() {
        sf::Packet createPacket = Packet::Creator::MakeCreate();
        udpSocket.send(createPacket, destAddress, destPort);

        char buff[1];
        std::size_t bytesReceived;
        udpSocket.receive((void *) buff, 1, bytesReceived, destAddress, destPort);
        if (bytesReceived < 1) {
            clientNumber = 0;
        }
        clientNumber = *buff;
        return clientNumber;
    }

    int getClientNumber() { return clientNumber; }

private:
    int clientNumber = 0;

    unsigned short destPort;
    sf::IpAddress destAddress;
    sf::UdpSocket udpSocket;
};

#endif /* !UDP_CLIENT_HPP */
