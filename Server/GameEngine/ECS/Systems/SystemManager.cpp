//
// Created by max on 27/11/18.
//

#include "SystemManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"

#include "SDeath.hpp"
#include "SSendSprites.hpp"
#include "SPlayerConnection.hpp"
#include "SMapBorder.hpp"
#include "SMove.hpp"
#include "SShot.hpp"
#include "SLevel.hpp"
#include "SCollision.hpp"

#include <time.h>
#include <stdlib.h>

namespace RType {
    SystemManager::SystemManager(std::shared_ptr<ComponentManager> componentManager,
                                 std::shared_ptr<EntityManager> entityManager,
                                 std::shared_ptr<NetworkHandler> networkHandler) {
        _networkHandler = networkHandler;
        _componentManager = componentManager;
        _entityManager = entityManager;

        _systems.push_back(std::make_shared<SDeath>(componentManager, entityManager));
        _systems.push_back(std::make_shared<SPlayerConnection>(componentManager, entityManager, networkHandler));
        _systems.push_back(std::make_shared<SMapBorder>(componentManager, entityManager));
        _systems.push_back(std::make_shared<SMove>(componentManager, entityManager));
        _systems.push_back(std::make_shared<SLevel>(componentManager, entityManager));
        _systems.push_back(std::make_shared<SShot>(componentManager, entityManager));
        _systems.push_back(std::make_shared<SCollision>(componentManager, entityManager));
        _systems.push_back(std::make_shared<SSendSprites>(componentManager, entityManager, networkHandler));

        _timer = std::chrono::high_resolution_clock::now();
        srand(time(NULL));
    }

    void SystemManager::updateSystem() {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - _timer);
        if (milliseconds.count() > 30) {
            _timer = std::chrono::high_resolution_clock::now();
            for (auto itS : _systems) {
                int beforeUpdateSize, afterUpdateSize;
                do {
                    for (auto itC : _componentManager->getComponents()) {
                        beforeUpdateSize = _componentManager->getComponents().size();
                        (*itS).update(itC);
                        if ((afterUpdateSize = _componentManager->getComponents().size()) < beforeUpdateSize) {
                            break;
                        }
                    }
                } while (beforeUpdateSize < afterUpdateSize);
            }
        }
    }

} // namespace RType
