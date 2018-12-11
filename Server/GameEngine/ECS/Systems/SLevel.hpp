//
// Created by max on 27/11/18.
//

#ifndef SERVER_SLEVEL_HPP
#define SERVER_SLEVEL_HPP

#include "ASystem.hpp"

#include <chrono>

#include "Vector.hpp"

namespace RType {

    static const int border = 1280 + 50;

    class SLevel : public ASystem {
    public:
        SLevel(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);

        void update(std::shared_ptr<AComponent> component);
        void createBasic(int lvl);
        void createBoss(int lvl);
        int genActualizeTime(int lvl);

    private:
        int _actualize;
        int _enemyLeft;
        std::chrono::high_resolution_clock::time_point _lastSpawn;
    };
} // RType


#endif //SERVER_SLEVEL_HPP
