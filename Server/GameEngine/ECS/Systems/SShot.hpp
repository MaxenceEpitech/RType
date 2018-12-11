//
// Created by max on 27/11/18.
//

#ifndef SERVER_SSHOT_HPP
#define SERVER_SSHOT_HPP

#include "ASystem.hpp"
#include "Vector.hpp"
#include "CTeam.hpp"

namespace RType {
    class SShot : public ASystem {
    public:
        SShot(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);

        void update(std::shared_ptr<AComponent> component);
        void createMissile(int dir, SVector2d pos, ETeam team, int spriteY_2);
    };
} // RType

#endif //SERVER_SSHOT_HPP
