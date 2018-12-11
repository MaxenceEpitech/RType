#include "Textures.hpp"

namespace RType {
Textures::Textures() {}

sf::Texture& Textures::get(Textures::ID id)
{
    auto& texture = _TextureMap.at(id);
    return *texture;
}

const sf::Texture& Textures::get(Textures::ID id) const
{
    auto& texture = _TextureMap.at(id);
    return *texture;
}

sf::Sprite& Textures::getSprite(Textures::ID id)
{
    auto& sprite = _SpriteMap.at(id);
    return *sprite;
}

const sf::Sprite& Textures::getSprite(Textures::ID id) const
{
    auto& sprite = _SpriteMap.at(id);
    return *sprite;
}

void Textures::loadTexture(Textures::ID id, const std::string& filename,
    sf::IntRect scale)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());

    if (scale.height != -1)
        texture->loadFromFile(filename, scale);
    else
        texture->loadFromFile(filename);
    _TextureMap.insert(std::make_pair(id, std::move(texture)));
}

void Textures::loadSprite(Textures::ID id, sf::Vector2f pos)
{
    std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());

    sprite->setTexture(get(id));
    sprite->setPosition(pos);
    _SpriteMap.insert(std::make_pair(id, std::move(sprite)));
}

sf::Sprite& Textures::loadAndGetSprite(Textures::ID id, const std::string& path,
    sf::IntRect scale, sf::Vector2f pos)
{
    loadTexture(id, path, scale);
    loadSprite(id, pos);
    if (id == Textures::ID::PLANET) {
        sf::Sprite& sprite = getSprite(id);
        sprite.setPosition(pos);
        sprite.setScale(sf::Vector2f(0.6, 0.6));
    }
    return getSprite(id);
}

sf::FloatRect Textures::getLocalBounds(Textures::ID id)
{
    try {
        auto& sprite = _SpriteMap.at(id);
        return sprite->getLocalBounds();
    } catch (std::out_of_range& e) {
        return sf::FloatRect(-1, -1, -1, -1);
    }
}

sf::Vector2f Textures::getPosition(Textures::ID id)
{
    auto& sprite = _SpriteMap.at(id);
    return sprite->getPosition();
}

void Textures::setSpritePos(Textures::ID id, sf::Vector2f pos)
{
    auto& found = _SpriteGame.at(id);
    found->setPosition(pos);
}

void Textures::setSpriteScale(Textures::ID id, sf::Vector2f scale)
{
    auto& found = _SpriteGame.at(id);
    found->setScale(scale);
}

sf::Vector2f Textures::getSpritePos(Textures::ID id)
{
    try {
        auto& found = _SpriteGame.at(id);
        return found->getPosition();
    } catch (std::out_of_range& e) {
        return sf::Vector2f(0, 0);
    }
}

void Textures::addToGame(Textures::ID id, const std::string& path,
    sf::IntRect rect, sf::Vector2f pos)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());

    if (rect.height != -1)
        texture->loadFromFile(path, rect);
    else
        texture->loadFromFile(path);
    _TextGame.insert(std::make_pair(id, std::move(texture)));
    auto& found = _TextGame.at(id);
    sprite->setTexture(*found);
    sprite->setPosition(pos);
    _SpriteGame.insert(std::make_pair(id, std::move(sprite)));
}

sf::Sprite& Textures::getGameSprite(Textures::ID id)
{
    auto& sprite = _SpriteGame.at(id);
    return *sprite;
}
} // namespace RType
