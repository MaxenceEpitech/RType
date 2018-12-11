//
// Created by max on 27/11/18.
//

#ifndef SERVER_SMOVE_HPP
#define SERVER_SMOVE_HPP

#include "ASystem.hpp"

namespace RType {
    class SMove : public ASystem {
    public:
        SMove(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);

        void update(std::shared_ptr<AComponent> component);
    };
} // RType

#endif //SERVER_SMOVE_HPP
