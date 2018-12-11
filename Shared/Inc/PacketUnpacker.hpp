//
// Created by segfault on 27/11/18.
//

#ifndef PACKETUNPACKER_HPP
#define PACKETUNPACKER_HPP


#include "Textures.hpp"
#include "Packet.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <exception>
#include <iostream>
#include <string>

namespace Packet {
    /// Creates a new component from a network Packet,
    /// please use a switch case with Packet::GetEnum
    /// first to determine what datum to get
    namespace Unpacker {
        static Packet::Actions UnpackActions(sf::Packet packet) {
            Packet::TYPE type;
            if (!(packet >> type) || type != Packet::TYPE::ACTIONS) {
                throw std::runtime_error(
                        "Packet isn't a Actions Packet, packet enum is: " +
                        std::to_string(static_cast<int>(type)));
            }
            Actions actions;
            if (!(packet >> actions)) {
		throw std::runtime_error("Actions Packet doesn't contain Actions data");
            }
            // Extraction successful
            return actions;
        }

        static Packet::Graphic UnpackGraphics(sf::Packet packet) {
            Packet::TYPE type;
            if (!(packet >> type) || type != Packet::TYPE::GRAPHIC) {
                throw std::runtime_error(
                        "Packet isn't a Graphic Packet, packet enum is: " +
                        std::to_string(static_cast<int>(type)));
            }
            Graphic graphic;
            if (!(packet >> graphic)) {
                throw std::runtime_error("Graphic Packet doesn't contain Graphic data");
            }
            // Extraction successful
            return graphic;
        }

        static Packet::Lobbies UnpackLobbies(sf::Packet packet) {
            Packet::TYPE type;
            if (!(packet >> type) || type != Packet::TYPE::LOBBIES) {
                throw std::runtime_error(
                        "Packet isn't a Lobbies Packet, packet enum is: " +
                        std::to_string(static_cast<int>(type)));
            }
            Lobbies lobbies;
            if (!(packet >> lobbies)) {
                throw std::runtime_error("Lobbies Packet doesn't contain Lobbies data");
            }
            // Extraction successful
            return lobbies;
        }

        /// Returns the index of the lobby to connect to
        static sf::Uint32 UnpackConnect(sf::Packet packet) {
            Packet::TYPE type;
            if (!(packet >> type) || type != Packet::TYPE::CONNECT) {
                throw std::runtime_error(
                        "Packet isn't a Connect Packet, packet enum is: " +
                        std::to_string(static_cast<int>(type)));
            }
            sf::Uint32 index;
            if (!(packet >> index)) {
                throw std::runtime_error(
                        "Connect Packet doesn't contain the lobby index");
            }
            // Extraction successful
            return index;
        }

        /// Returns the player health from the packet
        static Packet::Health UnpackHealth(sf::Packet packet) {
            Packet::TYPE type;
            if (!(packet >> type) || type != Packet::TYPE::HEALTH) {
                throw std::runtime_error(
                        "Packet isn't a Health Packet, packet enum is: " +
                        std::to_string(static_cast<int>(type)));
            }
            Packet::Health health;
            if (!(packet >> health)) {
                throw std::runtime_error(
                        "Health Packet doesn't contain the health");
            }
            // Extraction successful
            return health;
        }
    };
} // namespace Packet

#endif // !PACKETUNPACKER_HPP
