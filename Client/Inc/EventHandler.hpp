#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "KeyPressHandler.hpp"
#include "UDPClient.hpp"
#include <SFML/Graphics.hpp>

class EventHandler {
public:
    EventHandler(UDPClient &udpClient) : keyPressHandler(udpClient) {}

    void HandleEvents(sf::RenderWindow &window) {
        keyPressHandler.HandleKeyPress();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                    // We don't process other types of events
                default:
                    break;
            }
        }
    }

private:
    KeyPressHandler keyPressHandler;
};

#endif // !EVENT_HANDLER_HPP
