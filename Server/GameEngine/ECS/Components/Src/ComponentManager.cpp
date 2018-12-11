#include "ComponentManager.hpp"
#include "EntityManager.hpp"

#include "CLevel.hpp"

#include "CHealth.hpp"
#include "CPosition.hpp"
#include "CSprite.hpp"
#include "CPlayer.hpp"
#include "CDirection.hpp"
#include "CSpeed.hpp"
#include "CTeam.hpp"
#include "CTimer.hpp"
#include "CShoot.hpp"
#include "CDamage.hpp"

#include <iostream>
#include <CPlayer.hpp>

namespace RType {
    ComponentManager::ComponentManager() {
        _components.push_back(std::make_shared<CLevel>(0, 0));
    }

    void ComponentManager::setEntityManager(std::shared_ptr<EntityManager> entityManager) {
        _entityManager = entityManager;
    }

    void ComponentManager::createComponent(RType::EComponent component, Id parentId) {
        int newComponentId = createUniqueId();
        switch (component) {
            case (EComponent::sprite):
                _components.push_back(std::make_shared<CSprite>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::player):
                _components.push_back(std::make_shared<CPlayer>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::position):
                _components.push_back(std::make_shared<CPosition>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::health):
                _components.push_back(std::make_shared<CHealth>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::direction):
                _components.push_back(std::make_shared<CDirection>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::speed):
                _components.push_back(std::make_shared<CSpeed>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::team):
                _components.push_back(std::make_shared<CTeam>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::timer):
                _components.push_back(std::make_shared<CTimer>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::shoot):
                _components.push_back(std::make_shared<CShoot>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            case (EComponent::damage):
                _components.push_back(std::make_shared<CDamage>(newComponentId, parentId));
                _entityManager->addComponent(parentId, newComponentId);
                break;
            default:
                break;
        }
    }

    void ComponentManager::removeOnlyComponent(Id id) {
        for (std::list<std::shared_ptr<AComponent>>::iterator it = _components.begin(); it != _components.end(); it++) {
            if ((*it)->getId() == id) {
                it = _components.erase(it);
                return;
            }
        }
    }

    void ComponentManager::removeComponent(Id id) {
        _entityManager->removeComponent(id);
        removeOnlyComponent(id);
    }

    Id ComponentManager::createUniqueId() {
        bool keepSearching = true;
        Id uniqueId = 1;
        while (keepSearching) {
            uniqueId += 1;
            keepSearching = false;
            for (std::list<std::shared_ptr<AComponent>>::iterator it = _components.begin();
                 it != _components.end(); ++it) {
                if ((*it)->getId() == uniqueId)
                    keepSearching = true;
            }
        }
        return uniqueId;
    }

    void ComponentManager::print() {
        std::cout << "ComponentManager print" << std::endl;
        if (!_components.empty()) {

            for (std::list<std::shared_ptr<AComponent>>::iterator it = _components.begin();
                 it != _components.end(); it++) {

                //
                //  try convert Acomponent to Cheath
                //
                auto tmp = std::dynamic_pointer_cast<CHealth>((*it));
                if (tmp != nullptr)
                    std::cout << "This component is a health component hp : " << tmp->getHealth() << " Parent Id " << tmp->getParentId() << std::endl;
                //
                //
                //

                auto tmp1 = std::dynamic_pointer_cast<CPosition>((*it));
                if (tmp1 != nullptr)
                    std::cout << "This component is a POS component pos : " << tmp1->getPosition().x << " " << tmp1->getPosition().y << " Parent Id " << tmp1->getParentId() <<  std::endl;
                //
                //
                //

                auto tmp2 = std::dynamic_pointer_cast<CSprite>((*it));
                if (tmp2 != nullptr)
                    std::cout << "This component is a SPRITE component ID : " << tmp2->getIdTexture() << " Parent Id " << tmp2->getParentId() << std::endl;
                //
                //
                //

                std::cout << "id : " << (*it)->getId() << " / Parent Id : " << (*it)->getParentId() << std::endl
                          << std::endl;
            }
        } else {
            std::cout << "  List is emplty" << std::endl;
        }
    }

    std::list<std::shared_ptr<AComponent>> &ComponentManager::getComponents() {
        return _components;
    }

} // RType
