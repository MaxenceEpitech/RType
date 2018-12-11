#include "UDPServer.hpp"

UDPServer::UDPServer(unsigned short port, boost::asio::io_service &io_service)
        : socket_(io_service, boost::asio::ip::udp::endpoint(
        boost::asio::ip::udp::v4(), port)) {
    socket_.async_receive_from(
            boost::asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::HandleReceiveFrom, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void UDPServer::Connect(sf::Packet &received) {
    try {
        auto lobby = GetLobby(received);
        if (!HasPlayerDatum(lobby, sender_endpoint_)) {
            /// It's a new client
            ConnectNewClient(lobby);
        }
    } catch (...) {
        /// Get Lobby failed (the packet is corrupt)
        RejectClient();
    }
}

void UDPServer::ConnectNewClient(std::shared_ptr<UDPServer::lobby_t> lobby) {
    auto &playerData = lobby->playerData;
    /// if there is there is not enough clients in the lobby,
    /// add it to the list of clients in the lobby
    if (playerData.size() < MAX_CLIENTS) {
        RType::player_datum_t playerDatum = {};
        playerDatum.endpoint = sender_endpoint_;
        playerDatum.playerEntityId = -1;

        playerData.push_back(playerDatum);
        /// buffer of size 1
        char buffer[1];
        auto playerId = playerData.size();
        *buffer = playerId;
        socket_.send_to(boost::asio::buffer(buffer, 1), sender_endpoint_);
        std::cerr << "Connected a new client: " << sender_endpoint_ << " at index "
                  << playerId << std::endl;

        std::cerr << "PlayerEntityId: " << playerDatum.playerEntityId << std::endl;

        lobby->world->update();

        /// Set Receive for the client
        socket_.async_receive_from(
                boost::asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
                boost::bind(&UDPServer::HandleReceiveFrom, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
        /// If the lobby is full, send an error and terminate coms
    } else {
        RejectClient();
    }
}

void UDPServer::RejectClient() {
    socket_.send_to(boost::asio::buffer("\0", 1), sender_endpoint_);
    /// sets handler for the next receive
    socket_.async_receive_from(
            boost::asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::HandleReceiveFrom, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    std::cerr << "Rejected a new client: " << sender_endpoint_ << std::endl;
}

void UDPServer::ListLobbies() {
    std::cerr << "ListLobbies client size: " << clients.size() << std::endl;
    Packet::Lobbies lobbies;
    for (auto lobby : clients) {
        auto &playerData = lobby->playerData;
        lobbies.push_back(playerData.size());
        std::cerr << "ListLobbies pushing " << playerData.size() << std::endl;
    }
    sf::Packet packet = Packet::Creator::MakeLobbies(lobbies);
    Send(packet);
    std::cerr << "Sent Lobbies" << std::endl;
}

std::shared_ptr<UDPServer::lobby_t> UDPServer::GetLobby(sf::Uint32 lobbyIndex) {
    if (lobbyIndex >= clients.size()) {
        throw std::runtime_error("Lobby does not exist, packet is corrupt");
    }
    return clients[lobbyIndex];
}

std::shared_ptr<UDPServer::lobby_t> UDPServer::GetLobby(sf::Packet packet) {
    auto lobbyIndex = Packet::Unpacker::UnpackConnect(packet);
    return GetLobby(lobbyIndex);
}

std::shared_ptr<UDPServer::lobby_t>
UDPServer::GetLobby(const boost::asio::ip::udp::endpoint &endpoint) {
    for (auto &lobby : clients) {
        for (auto &playerDatum : lobby->playerData) {
            if (endpoint == playerDatum.endpoint) {
                return lobby;
            }
        }
    }
    throw std::runtime_error(
            "Lobby not found for endpoint, a client tried to bypass connection");
}

bool UDPServer::HasPlayerDatum(
        std::shared_ptr<UDPServer::lobby_t> lobby,
        const boost::asio::ip::udp::endpoint &endpoint) const {
    for (auto &playerDatum : lobby->playerData) {
        if (endpoint == playerDatum.endpoint) {
            return true;
        }
    }
    return false;
}

RType::player_datum_t &UDPServer::GetPlayerDatum(
        std::shared_ptr<UDPServer::lobby_t> lobby,
        const boost::asio::ip::udp::endpoint &endpoint) const {
    for (auto &playerDatum : lobby->playerData) {
        if (endpoint == playerDatum.endpoint) {
            return playerDatum;
        }
    }
    throw std::runtime_error("PlayerDatum not found for endpoint, a client tried "
                             "to bypass connection");
}

void UDPServer::CreateLobby() {
    UDPServer::lobby_t tmp = {};
    std::shared_ptr<UDPServer::lobby_t> lobby =
            std::make_shared<UDPServer::lobby_t>(tmp);

    std::cerr << "Lobby playerdata size: " << std::endl;
    std::cerr << "size: \t\t" << lobby->playerData.size() << std::endl;
    lobby->world = std::make_shared<RType::World>(
            std::make_shared<NetworkHandler>(NetworkHandler(socket_, lobby->playerData)));
    ConnectNewClient(lobby);
    clients.push_back(lobby);
}

void UDPServer::CleanupEmptyLobbies() {
for (auto it = clients.begin(); it != clients.end();) {
    auto &lobby = *it;
    if (lobby->playerData.size() == 0) {
        std::cout << "Removing an empty lobby at iterator: " << it - clients.begin() << std::endl;
        it = clients.erase(it);
    } else {
        ++it;
    }
}
}

void UDPServer::Disconnect(
        std::shared_ptr<UDPServer::lobby_t> lobby,
        const boost::asio::ip::udp::endpoint &endpoint) {
    for (auto it = lobby->playerData.begin(); it != lobby->playerData.end();) {
        auto &playerDatum = *it;
        if (endpoint == playerDatum.endpoint) {
            std::cerr << "Erasing endpoint: " << endpoint << std::endl;
            it = lobby->playerData.erase(it);
            std::cerr << "Erased endpoint" << std::endl;
            CleanupEmptyLobbies();
            return;
        } else {
            ++it;
        }
    }
    throw std::runtime_error("PlayerDatum not found for endpoint, a client tried "
                             "to disconnect without connecting");
}


void UDPServer::HandleReceiveFrom(const boost::system::error_code &error,
                                  size_t bytesReceived) {
    /// If i received something
    if (!error && bytesReceived > 0) {
        sf::Packet received;
        received.append(data_, bytesReceived);
        //Packet::PrintPacket(received);

        Packet::TYPE type = Packet::GetEnum(received);

        /// Testing for unconnected packets
        if (type == Packet::LIST_LOBBIES) {
            ListLobbies();
        } else if (type == Packet::CONNECT) {
            Connect(received);
        } else if (type == Packet::CREATE) {
            CreateLobby();
            std::cout << "\t\t\t\t\t\tLobby Created" << std::endl;
        } else if (type == Packet::DISCONNECT) {
            try {
                std::shared_ptr<UDPServer::lobby_t> lobby = GetLobby(sender_endpoint_);
                std::cout << "Disconnecting " << sender_endpoint_ << std::endl;
                Disconnect(lobby, sender_endpoint_);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        } else {
            /// Client should be connected
            try {
                std::shared_ptr<UDPServer::lobby_t> lobby = GetLobby(sender_endpoint_);
                auto &playerDatum = GetPlayerDatum(lobby, sender_endpoint_);
                if (Packet::GetEnum(received) != Packet::REFRESH)
                    playerDatum.packet = received;
                lobby->world->update();

            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    SetReceive();
}

void UDPServer::HandleSendTo(
        [[maybe_unused]] const boost::system::error_code &error,
        [[maybe_unused]] size_t bytesSent) {
    /// Set the next receive
    socket_.async_receive_from(
            boost::asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::HandleReceiveFrom, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void UDPServer::Send(sf::Packet &packet) {
    socket_.async_send_to(
            boost::asio::buffer(packet.getData(), packet.getDataSize()),
            sender_endpoint_,
            boost::bind(&UDPServer::HandleSendTo, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void UDPServer::SetReceive() {
    socket_.async_receive_from(
            boost::asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::HandleReceiveFrom, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}
