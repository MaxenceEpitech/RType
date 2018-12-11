//
// Created by max on 27/11/18.
//

#include "SDeath.hpp"
#include "CHealth.hpp"
#include "EntityManager.hpp"

#include <iostream>

namespace RType {
SDeath::SDeath(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager)
    : ASystem(componentManager, entityManager) {
}

void SDeath::update(std::shared_ptr<RType::AComponent> component) {
    if (auto health = std::dynamic_pointer_cast<CHealth>(component)) {
        if (health->getHealth() <= 0) {
            _entityManager->removeComponent(EComponent::health, health->getParentId());
            _entityManager->removeComponent(EComponent::position, health->getParentId());
            _entityManager->removeComponent(EComponent::sprite, health->getParentId());
            _entityManager->removeComponent(EComponent::speed, health->getParentId());
            _entityManager->removeComponent(EComponent::team, health->getParentId());
        }
    }
}

} // RType