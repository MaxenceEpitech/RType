#include "Menu.hpp"
#include <cmath>

namespace RType {

int Menu::onClick()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(_Window);
    auto pos = _Text.getPosition(RType::Textures::EXIT);
    auto rect = _Text.getLocalBounds(RType::Textures::EXIT);
    if (mouse.x > pos.x && mouse.x < pos.x + rect.width && mouse.y > pos.y && mouse.y < pos.y + rect.height) {
        return -1;
    } else {
        auto pos = _Text.getPosition(RType::Textures::PLAY);
        auto rect = _Text.getLocalBounds(RType::Textures::PLAY);
        if (mouse.x > pos.x && mouse.x < pos.x + rect.width && mouse.y > pos.y && mouse.y < pos.y + rect.height) {
            return 1;
        } else {
            auto pos = _Text.getPosition(RType::Textures::CREATE);
            auto rect = _Text.getLocalBounds(RType::Textures::CREATE);
            if (mouse.x > pos.x && mouse.x < pos.x + rect.width && mouse.y > pos.y && mouse.y < pos.y + rect.height) {
                return 2;
            }
        }
        return 0;
    }
}

int Menu::handleEvents()
{
    switch (_Event.type) {
    case sf::Event::EventType::Closed:
        return -1;
    case sf::Event::EventType::MouseButtonPressed:
        if (_Event.mouseButton.button == sf::Mouse::Left)
            return onClick();
        return 0;
    default:
        return 0;
    }
    return 0;
}

double randomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

double square(int a)
{
    return pow(a, 2);
}

void Menu::movePlanet()
{
    double rad = 0;
    if ((_PlanetPosition.x < -50 || _PlanetPosition.x > _WindowX - 100) && _PlanetPosition.x < _WindowX) {
        rad = acos(_PlanetPosition.y / (sqrt(square(_PlanetPosition.x) + square(_PlanetPosition.y))));
        _Direction = abs(180 * (rad - (M_PI / 2)) / M_PI);
        _Clock.restart();
    } else if ((_PlanetPosition.y < -50 || _PlanetPosition.y > _WindowY - 200) && _PlanetPosition.x < _WindowX) {
        _Direction = -_Direction;
        _Clock.restart();
    } else if (_PlanetPosition.x > _WindowX && _Clock.getElapsedTime().asSeconds() > 5) {
        _PlanetPosition.x = -200;
        _PlanetPosition.y = 50;
        _Direction = randomInt(270, 360);
        _Clock.restart();
    }
    _PlanetPosition.x += (2 * cos(((_Direction * M_PI) / 180)));
    _PlanetPosition.y += (2 * sin(((_Direction * M_PI) / 180)));
}

void Menu::drawSprites()
{
    _Window.draw(_Text.loadAndGetSprite(
        RType::Textures::BACKGROUND, "./Assets/Sprites/Game/background.jpg",
        sf::IntRect(-1, -1, -1, -1), sf::Vector2f(0.f, 0.f)));
    _Window.draw(_Text.loadAndGetSprite(
        RType::Textures::PLANET, "./Assets/Sprites/Menu/Planet.png",
        sf::IntRect(-1, -1, -1, -1), _PlanetPosition));
    _Window.draw(_Text.loadAndGetSprite(
        RType::Textures::PLAY, "./Assets/Sprites/Menu/PlayButton.png",
        sf::IntRect(5, 5, 150, 75),
        sf::Vector2f(_WindowX / 2 - 80, _WindowY / 2 - 175)));
    _Window.draw(_Text.loadAndGetSprite(
        RType::Textures::CREATE, "./Assets/Sprites/Menu/CreateButton.png",
        sf::IntRect(5, 5, 150, 75),
        sf::Vector2f(_WindowX / 2 - 80, _WindowY / 2 - 50)));
    _Window.draw(_Text.loadAndGetSprite(
        RType::Textures::EXIT, "./Assets/Sprites/Menu/ExitButton.png",
        sf::IntRect(5, 5, 150, 75),
        sf::Vector2f(_WindowX / 2 - 75, _WindowY / 2 + 75)));
}

int Menu::menuLoop()
{
    int clicked = 0;
    while (_Window.isOpen()) {
        while (_Window.pollEvent(_Event))
            if ((clicked = handleEvents()) != 0)
                return clicked;
        _Window.clear();
        drawSprites();
        movePlanet();
        _Window.display();
    }
    return clicked;
}

Menu::Menu(sf::RenderWindow& window, const int winX, const int winY)
    : _Window(window)
    , _WindowX(winX)
    , _WindowY(winY)
    , _Clock()
    , _Direction(120)
    , _Frames(60)
{
}

} // namespace RType
