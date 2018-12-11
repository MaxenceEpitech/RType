#ifndef SEND_SPRITES_SYSTEM_HPP
#define SEND_SPRITES_SYSTEM_HPP

#include "ASystem.hpp"
#include "CPosition.hpp"
#include "CSprite.hpp"
#include "NetworkHandler.hpp"
#include "PacketCreator.hpp"
#include "Packet.hpp"
#include <iostream>

namespace RType {
    class SSendSprites : public ASystem {
    public:
        SSendSprites(std::shared_ptr<ComponentManager> componentManager,
                     std::shared_ptr<EntityManager> entityManager,
                     std::shared_ptr<NetworkHandler> networkHandler)
                : ASystem(componentManager, entityManager) {
            _networkHandler = networkHandler;
        }

    void update(std::shared_ptr<AComponent> component);

    private:
        std::shared_ptr<NetworkHandler> _networkHandler;
    }; // namespace RType
} // namespace RType
#endif // !SEND_SPRITES_SYSTEM_HPP
