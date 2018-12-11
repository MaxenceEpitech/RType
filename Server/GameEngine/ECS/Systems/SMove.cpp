//
// Created by max on 27/11/18.
//

#include "SMove.hpp"

#include "EntityManager.hpp"
#include "CPosition.hpp"
#include "CDirection.hpp"
#include "CSpeed.hpp"

#include <cmath>

namespace RType {
    SMove::SMove(std::shared_ptr<RType::ComponentManager> componentManager,
                 std::shared_ptr<RType::EntityManager> entityManager)
            : ASystem(componentManager, entityManager) {
    }

    void SMove::update(std::shared_ptr<AComponent> component) {
        auto dir = std::dynamic_pointer_cast<CDirection>(component);
        if (dir != nullptr) {
            auto compPos = _entityManager->getComponentFromEntity(EComponent::position, dir->getParentId());
            auto compSpeed = _entityManager->getComponentFromEntity(EComponent::speed, dir->getParentId());
            if (compPos != nullptr && compSpeed != nullptr) {
                auto pos = std::dynamic_pointer_cast<CPosition>(compPos);
                auto speed = std::dynamic_pointer_cast<CSpeed>(compSpeed);
                if (pos != nullptr && speed != nullptr) {
                    SVector2d currentPos = pos->getPosition();
                    pos->setPosition(SVector2d{currentPos.x + ((double) speed->getSpeed() *
                                                               cos((((double) dir->getDirection() * M_PI) / 180))),
                                               currentPos.y + ((double) speed->getSpeed() *
                                                               sin((((double) dir->getDirection() * M_PI) / 180)))});
                }
            }
        }
    }

} // RType
