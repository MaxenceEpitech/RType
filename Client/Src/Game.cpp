#include "Game.hpp"

namespace RType {

    void Game::loadAllSprites() {
        _Text.addToGame(Textures::BACKGROUND, "./Assets/Sprites/Game/background.jpg",
                        sf::IntRect(-1, -1, -1, -1), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::PLAYER_1, "./Assets/Sprites/Game/spaceship.png",
                        sf::IntRect(70, 10, 300, 150), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::PLAYER_2, "./Assets/Sprites/Game/spaceship.png",
                        sf::IntRect(70, 10, 300, 150), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::PLAYER_3, "./Assets/Sprites/Game/spaceship.png",
                        sf::IntRect(70, 10, 300, 150), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::PLAYER_4, "./Assets/Sprites/Game/spaceship.png",
                        sf::IntRect(70, 10, 300, 150), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::BOSS, "./Assets/Sprites/Game/GameBoss.png",
                        sf::IntRect(-1, -1, -1, -1), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::MONSTER, "./Assets/Sprites/r-typesheet9.gif",
                        sf::IntRect(50, 0, 55, 55), sf::Vector2f(0.f, 0.f));
        _Text.addToGame(Textures::BUTTON, "./Assets/Sprites/Menu/LobbyButtonCopied.png",
                        sf::IntRect(5, 5, 275, 75), sf::Vector2f(_WindowX / 2 - 95, 40));
        _Text.addToGame(Textures::BUTTON_ONPRESSED, "./Assets/Sprites/Menu/OnPressedButton.png",
                        sf::IntRect(5, 5, 275, 75), sf::Vector2f(_WindowX / 2 - 95, 40));
        _Text.setSpriteScale(Textures::PLAYER_1, sf::Vector2f(0.5, 0.5));
        _Text.setSpriteScale(Textures::PLAYER_2, sf::Vector2f(0.5, 0.5));
        _Text.setSpriteScale(Textures::PLAYER_3, sf::Vector2f(0.5, 0.5));
        _Text.setSpriteScale(Textures::PLAYER_4, sf::Vector2f(0.5, 0.5));
        _Text.addToGame(Textures::ALLY_MISSILE, "./Assets/Sprites/r-typesheet1.gif",
                        sf::IntRect(135, 155, 65, 15), sf::Vector2f(0, 0));
        _Text.setSpriteScale(Textures::ALLY_MISSILE, sf::Vector2f(0.9, 0.9));
        _Text.addToGame(Textures::ENNEMY_MISSILE, "./Assets/Sprites/r-typesheet9.gif",
                        sf::IntRect(35, 60, 55, 15), sf::Vector2f(200, 200));
        _Text.addToGame(Textures::GAMEOVER, "./Assets/Sprites/Game/over.png",
                        sf::IntRect(-1, -1, -1, -1), sf::Vector2f(150.f, 0.f));
        _Text.setSpriteScale(Textures::GAMEOVER, sf::Vector2f(0.7, 0.7));
    }

    int Game::activateLobby(sf::Vector2f buttonVec) {
        sf::Vector2i mouse = sf::Mouse::getPosition(_Window);
        sf::FloatRect rect(5, 5, 275, 75);
        if (mouse.x > buttonVec.x && mouse.x < buttonVec.x + rect.width && mouse.y > buttonVec.y &&
            mouse.y < buttonVec.y + rect.height)
            return 1;
        return 0;
    }

    int Game::onClick(Packet::Lobbies &lobbies) {
        sf::Vector2f vec(_WindowX / 2 - 75, 50);
        for (size_t i = 0; i < lobbies.size(); i++) {
            if (activateLobby(vec) == 1)
                return i;
            vec.y += 100;
        }
        return -1;
    }

    int Game::handleEvents(Packet::Lobbies &lobbies, sf::Event event) {
        switch (event.type) {
            case sf::Event::EventType::Closed:
                _Window.close();
                exit(84);
            case sf::Event::EventType::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                    return onClick(lobbies);
                break;
            default:
                _Window.clear();
                _Window.draw(_Text.getGameSprite(Textures::BACKGROUND));
                displayLobbies(lobbies);
                _Window.display();
                break;
        }
        return -1;
    }

    int Game::joinLobby(Packet::Lobbies &lobbies) {
        sf::Event event;
        int toJoin = -1;
        _Window.display();
        while (_Window.isOpen()) {
            while (_Window.pollEvent(event)) {
                toJoin = handleEvents(lobbies, event);
                if (toJoin != -1)
                    return toJoin;
            }
        }
        // Je dois renvoyer quel lobby a été join
        return toJoin;
    }

    int Game::noLobbies() {
        std::cout << "No lobbies found, creating a new one now\n";
        return -1;
    }

    void Game::drawButton(sf::Vector2f buttonVec) {
        sf::Vector2i mouse = sf::Mouse::getPosition(_Window);
        sf::FloatRect rect(5, 5, 275, 75);
        if (mouse.x > buttonVec.x && mouse.x < buttonVec.x + rect.width && mouse.y > buttonVec.y &&
            mouse.y < buttonVec.y + rect.height) {
            _Text.setSpritePos(Textures::BUTTON_ONPRESSED, buttonVec);
            _Text.setSpriteScale(Textures::BUTTON_ONPRESSED, sf::Vector2f(1.1, 1));
            _Window.draw(_Text.getGameSprite(Textures::BUTTON_ONPRESSED));
        } else {
            _Text.setSpritePos(Textures::BUTTON, buttonVec);
            _Text.setSpriteScale(Textures::BUTTON, sf::Vector2f(1.07, 1));
            _Window.draw(_Text.getGameSprite(Textures::BUTTON));
        }
    }

    void Game::drawText(sf::Font font, std::string s, sf::Vector2f vec) {
        sf::Text text;
        text.setFont(font);
        for (auto &x : s)
            x = toupper(x);
        text.setString(s);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(vec);
        _Window.draw(text);
    }

    int Game::displayLobbies(Packet::Lobbies &lobbies) {
        sf::Vector2f vec(_WindowX / 2 - 75, 50);
        sf::Vector2f buttonVec(vec.x - 20, vec.y - 10);
        sf::Font font;

        if (!font.loadFromFile("Assets/Fonts/elixia.ttf"))
            std::cerr << "Font not found" << std::endl;
        else {
            for (size_t i = 0; i < lobbies.size(); i++) {
                drawButton(buttonVec);
                drawText(font, "Lobby number " + std::to_string(i + 1) + "\t\t" + std::to_string(lobbies[i]) + "/" +
                               std::to_string(Packet::MAX_CLIENT), vec);
                vec.y += 100;
                buttonVec.y += 100;
            }
        }
        return 0;
    }

    int Game::handleLobbies(Packet::Lobbies &lobbies) {
        if (lobbies.size() == 0)
            return noLobbies();
        return displayLobbies(lobbies);
    }

    Textures &Game::getText() {
        return _Text;
    }

    Game::Game(sf::RenderWindow &win, const int winX, const int winY)
            : _Window(win), _WindowX(winX), _WindowY(winY) {
        std::cout << "Starting the game now\n";
        loadAllSprites();
    }
}