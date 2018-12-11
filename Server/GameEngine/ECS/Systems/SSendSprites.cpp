#include "SSendSprites.hpp"
#include "EntityManager.hpp"

namespace RType {
    void SSendSprites::update(std::shared_ptr <AComponent> component) {
        if (auto cSprite = std::dynamic_pointer_cast<CSprite>(component)) {
            // The component is a Sprite, now we get the Position to forge the
            // graphic packet

            Packet::Graphic graphic = {};
            graphic.index = cSprite->getIdTexture();

            ///Finding the CPosition
            std::shared_ptr <AComponent> comp = _entityManager->getComponentFromEntity(
                    EComponent::position, component->getParentId());
            if (!comp) {
                std::cerr << "CSprite doesn't have a CPosition" << std::endl;
                return;
            }
            std::shared_ptr <CPosition> cPosition =
                    std::dynamic_pointer_cast<CPosition>(comp);
            if (!cPosition) {
                std::cerr << "CPosition casting failed" << std::endl;
                return;
            }
            auto position = cPosition->getPosition();
            // found CPosition
            graphic.position = sf::Vector2f(position.x, position.y);
            sf::Packet graphicPacket = Packet::Creator::MakeGraphics(graphic);
            _networkHandler->SendToAll(graphicPacket);
        }
    }
}