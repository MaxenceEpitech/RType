//
// Created by max on 27/11/18.
//

#ifndef SERVER_SMAPBORDER_HPP
#define SERVER_SMAPBORDER_HPP

#include "ASystem.hpp"
#include "Vector.hpp"

namespace RType {
    class SMapBorder : public ASystem {
    public:
        SMapBorder(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);

        void update(std::shared_ptr<AComponent> component);

    private:
        SVector2d _size;
    };
}

#endif //SERVER_SMAPBORDER_HPP
