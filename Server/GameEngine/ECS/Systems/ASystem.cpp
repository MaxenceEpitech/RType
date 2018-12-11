//
// Created by max on 27/11/18.
//

#include "ASystem.hpp"
#include <iostream>

namespace RType {
    ASystem::ASystem(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager) {
        _componentManager = componentManager;
        _entityManager = entityManager;
    }

    void ASystem::update(std::shared_ptr<AComponent> component) {
        (void) component;
        std::cout << "This is an Asystem" << std::endl;
    }

} // RType