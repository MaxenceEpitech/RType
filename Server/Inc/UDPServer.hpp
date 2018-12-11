#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include "NetworkHandler.hpp"
#include "Packet.hpp"
#include "PacketCreator.hpp"
#include "PacketUnpacker.hpp"
#include "World.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <iostream>

class UDPServer {
public:
    class lobby_t {
    public:
        lobby_t() { std::cerr << "\t\t\tlobby created" << std::endl; };

        ~lobby_t() { std::cerr << "\t\t\tlobby destroyed" << std::endl; };

        std::vector<RType::player_datum_t> playerData;
        std::shared_ptr<RType::World> world;
    };

    /// Creates a UDP socket and runs it on the specified port
    /// port is in normal endianness (no ntohs)
    /// Uses an external io_service, to have multiple servers running at once
    /// Usefull if i need to run an UDPServer + a TCPServer
    UDPServer(unsigned short port, boost::asio::io_service &io_service);

private:
    void HandleReceiveFrom(const boost::system::error_code &error,
                           size_t bytesReceived);

    void HandleSendTo([[maybe_unused]] const boost::system::error_code &error,
                      [[maybe_unused]] size_t bytesSent);

    void SetReceive();

    /// Send to sender_endpoint_
    void Send(sf::Packet &packet);

    /// Helper function, returns the lobby at the index, throws if it doesn't
    /// exist
    std::shared_ptr<UDPServer::lobby_t> GetLobby(sf::Uint32 lobbyIndex);

    /// Helper function, returns the lobby at the index, throws if it doesn't
    /// exist
    std::shared_ptr<UDPServer::lobby_t> GetLobby(sf::Packet packet);

    /// Gets the lobby in clients which contains the endpoint,
    /// throws if there is no endpoint in client
    /// (it means the client isn't connected yet)
    std::shared_ptr<UDPServer::lobby_t> GetLobby(const boost::asio::ip::udp::endpoint &endpoint);

    bool HasPlayerDatum(std::shared_ptr<UDPServer::lobby_t> lobby,
                        const boost::asio::ip::udp::endpoint &endpoint) const;

    /// Get the player_datum_t struct from the lobby by comparing the
    /// sender_endpoint
    /// throws if there is no endpoint in lobby
    /// (it means the client isn't connected yet)
    RType::player_datum_t &
    GetPlayerDatum(std::shared_ptr<UDPServer::lobby_t> lobby,
                   const boost::asio::ip::udp::endpoint &endpoint) const;

    /// Sends te list of lobbies to the client
    void ListLobbies();

    /// On first connection, adds it to the list of clients
    void Connect(sf::Packet &received);

    void ConnectNewClient(std::shared_ptr<UDPServer::lobby_t> lobby);

    void RejectClient();

    /// Disconnects a client by removing it from the lobby
    /// and removing the lobby if empty
    void Disconnect(std::shared_ptr<UDPServer::lobby_t> lobby, const boost::asio::ip::udp::endpoint &endpoint);

    /// Removes empty lobbies
    void CleanupEmptyLobbies();

    /// Creates a new lobby for the client
    void CreateLobby();

    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    /// Max unfragmented size
    static constexpr int MAX_LENGTH = 508;
    /// Maximum clients per game
    static constexpr char MAX_CLIENTS = 4;
    char data_[MAX_LENGTH];
    /// This is the list of every clients that sent something
    /// to the server at one point in time (UDP has no handshake)
    std::vector<std::shared_ptr<lobby_t>> clients;
};

#endif /* !UDP_SERVER_HPP */
