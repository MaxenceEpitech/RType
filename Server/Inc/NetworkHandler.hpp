#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include "PlayerDatum.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>

class NetworkHandler {
public:
  /// Creates the netowrkHandler that goes into the World, with all the
  /// necessary data
  NetworkHandler(boost::asio::ip::udp::socket &socket,
                 std::vector<RType::player_datum_t> &playerData)
      : socket_(socket), playerData(playerData) {
    std::cout << "\t\t\t\t\t\tNetworkHandler Has been created" << std::endl;
  }

  ~NetworkHandler() {
    std::cout << "NetworkHandler Has been destroyed" << std::endl;
  }

  /// Sends the packet to 1 player
  void Send(RType::player_datum_t &playerDatum, sf::Packet &packet) {
    socket_.send_to(boost::asio::buffer(packet.getData(), packet.getDataSize()),
                    playerDatum.endpoint);
  }

  /// Sends the packet to All the players currently in the lobby
  void SendToAll(sf::Packet &packet) {
    for (auto &datum : playerData) {
      Send(datum, packet);
    }
  }

  std::vector<RType::player_datum_t> &getPlayerData() { return playerData; }

private:
  boost::asio::ip::udp::socket &socket_;
  std::vector<RType::player_datum_t> &playerData;
};

#endif // !NETWORK_HANDLER_HPP
