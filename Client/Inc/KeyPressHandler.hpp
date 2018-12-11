#ifndef KEY_PRESS_HANDLER_HPP
#define KEY_PRESS_HANDLER_HPP

#include "Packet.hpp"
#include "UDPClient.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>

class KeyPressHandler {
public:
    KeyPressHandler(UDPClient &udpClient)
            : udpClient(udpClient), _shooting(false) {}

    void HandleKeyPress() {
        Packet::Actions actions;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            actions.push_back(Packet::Action::UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            actions.push_back(Packet::Action::RIGHT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            actions.push_back(Packet::Action::DOWN);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            actions.push_back(Packet::Action::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _shooting = true;
            std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(now - _shoot);
            if (time_span.count() > 1) {
                actions.push_back(Packet::Action::SHOOT);
                _shoot = std::chrono::high_resolution_clock::now();
            }
        }
        // If there was at least one key pressed
        if (actions.size() != 0) {
            // Send the actions
            std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - _shoot);
            if (milliseconds.count() < 30 && actions.back() != Packet::Action::SHOOT) {
                actions.push_back(Packet::Action::SHOOT);
            }
            auto packet = Packet::Creator::MakeActions(actions);
            udpClient.Send(packet);
        } else {
            // Send a refresh
            auto packet = Packet::Creator::MakeRefresh();
            udpClient.Send(packet);
        }
    }

private:
    UDPClient &udpClient;
    std::chrono::high_resolution_clock::time_point _shoot;
    bool _shooting;
};

#endif /* !KEY_PRESS_HANDLER_HPP */
