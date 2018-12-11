#ifndef PACKET_CREATOR_HPP
#define PACKET_CREATOR_HPP

#include "Textures.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <exception>
#include <iostream>
#include <string>
#include "Packet.hpp"

namespace Packet {
    namespace Creator {
        /// Graphic packet is ENUM + Packet::Graphic
        /// Throws if the packet is too big
        static sf::Packet MakeGraphics(Packet::Graphic &graphic) {
            sf::Packet packet;
            packet << Packet::TYPE::GRAPHIC << graphic;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Graphic Packet too big");
            }
            return packet;
        }

        /// Graphic packet is ENUM + Packet::Actions
        /// Throws if the packet is too big
        static sf::Packet MakeActions(Packet::Actions actions) {
            sf::Packet packet;
            packet << Packet::TYPE::ACTIONS << actions;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Actions Packet too big");
            }
            return packet;
        }

        /// Packet sent from the client to the server to ask for the list of lobbies
        /// Packet is just ENUM
        /// Shouldn't ever throw
        static sf::Packet MakeListLobbies() {
            sf::Packet packet;
            packet << Packet::TYPE::LIST_LOBBIES;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("List Lobby too big");
            }
            return packet;
        }

        /// Packet that is sent to the server to try to connect to a lobby at index
        /// Packet is ENUM + index
        /// Shouldn't ever throw
        static sf::Packet MakeConnect(sf::Uint32 lobbyIndex) {
            sf::Packet packet;
            packet << Packet::TYPE::CONNECT << lobbyIndex;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Connect packet too big");
            }
            return packet;
        }

        /// Packet sent from the client to the server to ask for a new lobby
        /// Packet is just ENUM
        /// Shouldn't ever throw
        static sf::Packet MakeCreate() {
            sf::Packet packet;
            packet << Packet::TYPE::CREATE;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Create too big");
            }
            return packet;
        }

        /// Makes the list of lobbies
        /// Packet is ENUM + Packet::Lobbies
        static sf::Packet MakeLobbies(Packet::Lobbies &lobbies) {
            sf::Packet packet;
            packet << Packet::TYPE::LOBBIES << lobbies;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Lobbies packet too big");
            }
            return packet;
        }
        /// Makes packet to request an Update
        /// Packet is ENUM
        /// Shouldn't ever throw
        static sf::Packet MakeRefresh() {
            sf::Packet packet;
            packet << Packet::TYPE::REFRESH;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Refresh packet too big");
            }
            return packet;
        }
        /// Makes packet to disconnect properly
        /// Packet is ENUM
        /// Shouldn't ever throw
        static sf::Packet MakeDisconnect() {
            sf::Packet packet;
            packet << Packet::TYPE::DISCONNECT;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Disconnect packet too big");
            }
            return packet;
        }
        /// Makes packet to notify the client of his death
        /// Packet is ENUM
        /// Shouldn't ever throw
        static sf::Packet MakeGameOver() {
            sf::Packet packet;
            packet << Packet::TYPE::GAME_OVER;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("game over packet too big");
            }
            return packet;
        }
        /// Makes packet to with the player health
        /// Packet is ENUM + Health struct
        /// Shouldn't ever throw
        static sf::Packet MakeHealth(const Packet::Health &health) {
            sf::Packet packet;
            packet << Packet::TYPE::HEALTH << health;
            if (packet.getDataSize() > Packet::MAX_SIZE) {
                throw std::runtime_error("Health packet too big");
            }
            return packet;
        }
    };
} // namespace Packet

#endif /* !PACKET_CREATOR_HPP */
