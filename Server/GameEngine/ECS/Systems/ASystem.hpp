//
// Created by max on 27/11/18.
//

#ifndef GAMEENGINE_ASYSTEM_HPP
#define GAMEENGINE_ASYSTEM_HPP

#include "ISystem.hpp"

namespace RType {
class ASystem {
public:
    ASystem(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);
    virtual void update(std::shared_ptr<AComponent> component);

protected:
    std::shared_ptr<ComponentManager> _componentManager;
    std::shared_ptr<EntityManager> _entityManager;
};
} // RType

#endif //GAMEENGINE_ASYSTEM_HPP
