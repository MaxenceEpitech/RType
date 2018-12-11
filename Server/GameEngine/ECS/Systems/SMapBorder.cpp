//
// Created by max on 27/11/18.
//

#include "SMapBorder.hpp"
#include "CPosition.hpp"
#include "CPlayer.hpp"
#include "EntityManager.hpp"

#include <iostream>

namespace RType {

    SMapBorder::SMapBorder(std::shared_ptr<ComponentManager> componentManager,
                           std::shared_ptr<EntityManager> entityManager)
                           : ASystem(componentManager, entityManager), _size{1280 + 60, 860 + 10} {
    }

    void SMapBorder::update(std::shared_ptr<AComponent> component) {
        if (auto cPosition = std::dynamic_pointer_cast<CPosition>(component)) {
            if (_entityManager->getComponentFromEntity(EComponent::player, component->getParentId()) == nullptr) {
                SVector2d pos = cPosition->getPosition();
                if (pos.x < -30 || pos.x > _size.x || pos.y < -30 || pos.y > _size.y) {
                    std::cout << "SBorder : Entity : " << cPosition->getId() << " has been remove." << std::endl;
                    _entityManager->removeEntity(cPosition->getParentId());
                    std::cout << "SUCCESS" << std::endl;
                }
            }
        }
    }

} // RType