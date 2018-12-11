#include "EntityManager.hpp"

#include <iostream>

namespace RType {
    EntityManager::EntityManager() {
    }

    void EntityManager::setComponentManager(std::shared_ptr<ComponentManager> componentManager) {
        _componentManager = componentManager;
    }

    void EntityManager::CreateEntity(EEntity entity) {
        std::cout << "EntityManager Creating Entity : ";
        int entityId = getUniqueId();

        switch (entity) {
            case (EEntity::player):
                std::cout << "Player " << entityId << std::endl;
                _entities.push_back(AEntity(entityId));
                _componentManager->createComponent(EComponent::health, entityId);
                _componentManager->createComponent(EComponent::position, entityId);
                _componentManager->createComponent(EComponent::sprite, entityId);
                _componentManager->createComponent(EComponent::player, entityId);
                _componentManager->createComponent(EComponent::speed, entityId);
                _componentManager->createComponent(EComponent::team, entityId);
                break;
            case (EEntity::missile):
                std::cout << "Missile "  << entityId << std::endl;
                _entities.push_back(AEntity(entityId));
                _componentManager->createComponent(EComponent::position, entityId);
                _componentManager->createComponent(EComponent::sprite, entityId);
                _componentManager->createComponent(EComponent::speed, entityId);
                _componentManager->createComponent(EComponent::direction, entityId);
                _componentManager->createComponent(EComponent::team, entityId);
                _componentManager->createComponent(EComponent::damage, entityId);
                break;
            case (EEntity::basicMonster):
                std::cout << "Basic Monster : " << entityId << std::endl;
                _entities.push_back(AEntity(entityId));
                _componentManager->createComponent(EComponent::health, entityId);
                _componentManager->createComponent(EComponent::position, entityId);
                _componentManager->createComponent(EComponent::sprite, entityId);
                _componentManager->createComponent(EComponent::speed, entityId);
                _componentManager->createComponent(EComponent::direction, entityId);
                _componentManager->createComponent(EComponent::timer, entityId);
                _componentManager->createComponent(EComponent::shoot, entityId);
                _componentManager->createComponent(EComponent::team, entityId);
                break;
            default:
                std::cout << "None" << std::endl;
                break;
        }
    }

    Id EntityManager::getUniqueId() {
        bool keepSearching = true;
        Id uniqueId = 1;
        while (keepSearching) {
            uniqueId += 1;
            keepSearching = false;
            for (std::list<AEntity>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
                if ((*it).getId() == uniqueId)
                    keepSearching = true;
            }
        }
        return uniqueId;
    }

    void EntityManager::removeEntity(Id id) {
        for (std::list<AEntity>::iterator it = _entities.begin(); it != _entities.end();) {
            if ((*it).getId() == id) {
                for (std::list<Id>::iterator itIds = (*it).getComponents().begin();
                     itIds != (*it).getComponents().end(); itIds++) {
                    std::cout << "cc " << (*itIds);
                    _componentManager->removeOnlyComponent((*itIds));
                }
                it = _entities.erase(it);
                return;
            } else {
                it++;
            }
        }
    }

    void EntityManager::addComponent(Id entityId, Id id) {
        for (std::list<AEntity>::iterator it = _entities.begin(); it != _entities.end();) {
            if ((*it).getId() == entityId) {
                (*it).addComponent(id);
                break;
            } else {
                it++;
            }
        }
    }

    void EntityManager::removeComponent(Id id) {
        for (std::list<AEntity>::iterator it = _entities.begin(); it != _entities.end(); it++) {
            if ((*it).removeComponent(id))
                break;
        }
    }

    void EntityManager::print() {
        std::cout << "EntityManager print" << std::endl;
        for (std::list<AEntity>::iterator it = _entities.begin();
             it != _entities.end(); it++) {
            std::cout << "Id : " << (*it).getId() << "Component amount " << (*it).getComponents().size() << std::endl
                      << std::endl;
        }
    }

    Id EntityManager::getLastEntityId() {
        return _entities.back().getId();
    }

    std::shared_ptr<AComponent> EntityManager::getComponentFromEntity(EComponent component, Id entityId) {
        for (std::list<std::shared_ptr<AComponent>>::iterator it = _componentManager->getComponents().begin();
             it != _componentManager->getComponents().end(); it++) {
            if ((*it)->getParentId() == entityId && (*it)->getType() == component) { // ici
                return (*it);
            }
        }
        return nullptr;
    }

    void EntityManager::removeComponent(EComponent component, Id parentId) {
        if (auto cmp = getComponentFromEntity(component, parentId)) {
            _componentManager->removeComponent(cmp->getId());
        }
    }

} // RType