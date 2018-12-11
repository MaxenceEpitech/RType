//
// Created by max on 27/11/18.
//

#ifndef GAMEENGINE_SYSTEMMANAGER_H
#define GAMEENGINE_SYSTEMMANAGER_H

#include <memory>
#include <list>
#include <chrono>

#include "ASystem.hpp"
#include "NetworkHandler.hpp"

namespace RType {
    class ComponentManager;
    class EntityManager;

    class SystemManager {
        public:
            SystemManager(std::shared_ptr<ComponentManager> componentManager,
                    std::shared_ptr<EntityManager> entityManager, std::shared_ptr<NetworkHandler> networkHandler);
            void updateSystem();

        private:
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<EntityManager> _entityManager;
            std::shared_ptr<NetworkHandler> _networkHandler;

            std::list<std::shared_ptr<ASystem>> _systems;
            std::chrono::high_resolution_clock::time_point _timer;
    };
}

#endif //GAMEENGINE_SYSTEMMANAGER_H
