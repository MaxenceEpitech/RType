#ifndef SYSTEM_DEATH_HPP
#define SYSTEM_DEATH_HPP

#include "ASystem.hpp"
#include "CPosition.hpp"

namespace RType {
    class SCollision : public ASystem {
    public:
        SCollision(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);

        void update(std::shared_ptr<AComponent> component);

        bool hasCollide(std::shared_ptr<CPosition> current, std::shared_ptr<CPosition> other);
        void handleCollide(std::shared_ptr<CPosition> current, std::shared_ptr<CPosition> other);
    };
}

#endif //SYSTEM_DEATH_HPP
