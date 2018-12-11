//
// Created by segfault on 27/11/18.
//

#ifndef PACKET_HPP
#define PACKET_HPP


#include "Textures.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <exception>
#include <iostream>
#include <string>

namespace Packet {

    /// Max unfragmented size
    static constexpr size_t MAX_SIZE = 508;

    /// Maximum clients in a lobby
    static constexpr size_t MAX_CLIENT = 4;

    struct Graphic {
        RType::Textures::ID index;
        sf::Vector2f position;
    };

    inline sf::Packet &operator>>(sf::Packet &packet, RType::Textures::ID &i) {
        sf::Uint32 temp;
        packet >> temp;
        i = static_cast<RType::Textures::ID>(temp);
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const RType::Textures::ID &i) {
        sf::Uint32 temp = i;
        packet << temp;
        return packet;
    }

    inline sf::Packet &operator>>(sf::Packet &packet, sf::Vector2f &p) {
        packet >> p.x >> p.y;
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const sf::Vector2f &p) {
        packet << p.x << p.y;
        return packet;
    }

    inline sf::Packet &operator>>(sf::Packet &packet, ::Packet::Graphic &g) {
        packet >> g.index >> g.position;
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const ::Packet::Graphic &g) {
        packet << g.index << g.position;
        return packet;
    }

    struct Health {
        int currentHealth;
        int maxHealth;
	    int level;
    };

    inline sf::Packet &operator>>(sf::Packet &packet, ::Packet::Health &h) {
	    packet >> h.currentHealth >> h.maxHealth >> h.level;
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const ::Packet::Health &h) {
	    packet << h.currentHealth << h.maxHealth << h.level;
        return packet;
    }


    using Lobbies = std::vector<sf::Uint32>;

    inline sf::Packet &operator>>(sf::Packet &packet, ::Packet::Lobbies &l) {
        sf::Uint32 size;
        if (!(packet >> size))
            size = 0;
        l.reserve(size);
        for (sf::Uint32 i = 0; i < size; i++) {
            sf::Uint32 temp;
            packet >> temp;
            l.push_back(temp);
        }
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const ::Packet::Lobbies &l) {
        packet << static_cast<sf::Uint32>(l.size());
        for (sf::Uint32 i = 0; i < l.size(); i++) {
            packet << l[i];
        }
        return packet;
    }

    enum Action {
        NOACTION = '0', UP = 'U', RIGHT = 'R', DOWN = 'D', LEFT = 'L', SHOOT = 'S'
    };
    using Actions = std::vector<Action>;

    inline sf::Packet &operator>>(sf::Packet &packet, ::Packet::Action &a) {
        sf::Uint32 temp;
        packet >> temp;
        a = static_cast<Action>(temp);
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const ::Packet::Action &a) {
        sf::Uint32 temp = a;
        packet << temp;
        return packet;
    }

    inline sf::Packet &operator>>(sf::Packet &packet, ::Packet::Actions &a) {
        sf::Uint32 size;
        if (!(packet >> size))
            size = 0;
        a.reserve(size);
        for (sf::Uint32 i = 0; i < size; i++) {
            Packet::Action temp;
            packet >> temp;
            a.push_back(temp);
        }
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const ::Packet::Actions &a) {
        packet << static_cast<sf::Uint32>(a.size());
        for (sf::Uint32 i = 0; i < a.size(); i++) {
            packet << a[i];
        }
        return packet;
    }

    /// Packet Type
    enum TYPE {
        NOTYPE = '0',
        LIST_LOBBIES = 'L',
        LOBBIES = 'B',
        CONNECT = 'C',
        DISCONNECT = 'D',
        CREATE = 'R',
        GRAPHIC = 'G',
        ACTIONS = 'A',
        REFRESH = 'E',
        GAME_OVER = 'M',
        HEALTH = 'H'
    };

    inline sf::Packet &operator>>(sf::Packet &packet, ::Packet::TYPE &t) {
        sf::Uint32 temp;
        packet >> temp;
        t = static_cast<::Packet::TYPE>(temp);
        return packet;
    }

    inline sf::Packet &operator<<(sf::Packet &packet, const ::Packet::TYPE &t) {
        sf::Uint32 temp = t;
        packet << temp;
        return packet;
    }

    /// Returns Packet Type from a Packet
    /// It copies the packet
    /// to not mess with the position indicator of the stream
    /// (This was hard to debug)
    static Packet::TYPE GetEnum(sf::Packet packet) {
        sf::Int32 temp;

        if (packet >> temp) {
            Packet::TYPE type = static_cast<Packet::TYPE>(temp);
            return type;
        }
        return Packet::TYPE::NOTYPE;
    }

    /// Pretty prints the packet
    static void PrintPacket(sf::Packet &packet, FILE *fd = stderr) {
        fprintf(fd, "Packet Size: %lu\n", packet.getDataSize());
        fprintf(fd, "Packet Type: 0x%x\n", Packet::GetEnum(packet));
        fprintf(fd, "Packet Data:\n");
        for (size_t i = 0; i < packet.getDataSize(); i++) {
            char c = *((char *) packet.getData() + i);
            if (isprint(c)) {
                fprintf(fd, "%c ", c);
            } else {
                fprintf(fd, "0x%x ", c);
            }
        }
        fprintf(fd, "\n");
    }
} // namespace Packet

#endif //PACKET_HPP
