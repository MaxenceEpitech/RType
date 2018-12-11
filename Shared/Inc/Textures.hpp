#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace RType {

class Textures {

public:
    enum ID {
        NOTEXTURE,
        BACKGROUND,
        PLANET,
        PLAY,
        CREATE,
        EXIT,
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4,
        WALL,
        MONSTER,
        BOSS,
        GAMEOVER,
        ALLY_MISSILE,
        ENNEMY_MISSILE,
        BUTTON,
        BUTTON_ONPRESSED
    };
    Textures();
    ~Textures() = default;
    void loadTexture(ID, const std::string&, sf::IntRect);
    void loadSprite(ID, sf::Vector2f);
    sf::Texture& get(ID);
    const sf::Texture& get(ID) const;
    sf::Sprite& getSprite(ID);
    sf::Sprite& getGameSprite(ID);
    const sf::Sprite& getSprite(ID) const;
    sf::Sprite& loadAndGetSprite(ID, const std::string&, sf::IntRect,
        sf::Vector2f);
    sf::Vector2f getPosition(ID);
    sf::FloatRect getLocalBounds(ID);
    void addToGame(ID, const std::string&, sf::IntRect, sf::Vector2f);
    void setSpritePos(ID, sf::Vector2f);
    void setSpriteScale(ID, sf::Vector2f);
    sf::Vector2f getSpritePos(ID);
    //void setSpritePosition(ID);

private:
    std::map<ID, std::unique_ptr<sf::Texture>> _TextureMap;
    std::map<ID, std::unique_ptr<sf::Sprite>> _SpriteMap;
    std::unordered_map<ID, std::unique_ptr<sf::Texture>> _TextGame;
    std::unordered_map<ID, std::unique_ptr<sf::Sprite>> _SpriteGame;
};

} // namespace RType
