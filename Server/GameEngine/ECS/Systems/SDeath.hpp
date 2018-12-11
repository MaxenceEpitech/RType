//
// Created by max on 27/11/18.
//

#ifndef SERVER_DEATH_HPP
#define SERVER_DEATH_HPP

#include "ASystem.hpp"

namespace RType {
    class SDeath : public ASystem {
    public:
        SDeath(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);

        void update(std::shared_ptr<AComponent> component);
    };
}

#endif //SERVER_DEATH_HPP
