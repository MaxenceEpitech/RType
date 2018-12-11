#ifndef PLAYER_DATUM_HPP
#define PLAYER_DATUM_HPP

#include <SFML/Network.hpp>
#include <boost/asio.hpp>

namespace RType {
    struct player_datum_t {
        /// Information used for networking
        boost::asio::ip::udp::endpoint endpoint;
        /// Datum to parse inside the systems
        sf::Packet packet;
        /// Entity ID of the player
        int playerEntityId;
    };
} // namespace RType

#endif // !PLAYER_DATUM_HPP
