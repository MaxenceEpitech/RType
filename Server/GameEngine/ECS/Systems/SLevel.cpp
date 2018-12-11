//
// Created by max on 27/11/18.
//

#include <EntityManager.hpp>
#include "RandomInt.hpp"
#include "SLevel.hpp"

#include "CLevel.hpp"
#include "CDirection.hpp"
#include "CPosition.hpp"
#include "CSprite.hpp"
#include "CSpeed.hpp"
#include "CHealth.hpp"
#include "CTimer.hpp"
#include "CShoot.hpp"
#include "CTeam.hpp"

namespace RType {

    SLevel::SLevel(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager)
            : ASystem(componentManager, entityManager), _enemyLeft(10) {
        _actualize = genActualizeTime(1);
    }

    int SLevel::genActualizeTime(int lvl) {
        return (2 + RType::randomInt(1, 5)) - lvl;
    }

    void SLevel::update(std::shared_ptr<AComponent> component) {
        auto cLevel = std::dynamic_pointer_cast<CLevel>(component);
        if (cLevel != nullptr) {
            auto lvl = cLevel->getLevel();
            if (_enemyLeft <= 0) {
                _enemyLeft = lvl * 10;
                cLevel->nextLevel();
            } else {
                std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
                auto time_span = std::chrono::duration_cast<std::chrono::duration<double >>(now - _lastSpawn);
                if (time_span.count() > _actualize) {
                    _actualize = genActualizeTime(lvl);
                    _lastSpawn = std::chrono::high_resolution_clock::now();
                    if (_enemyLeft > 1) {
                        createBasic(lvl);
                    } else {
                        createBoss(lvl);
                    }
                }

            }
        }
    }

    void SLevel::createBasic(int lvl) {
        _enemyLeft--;
        _entityManager->CreateEntity(EEntity::basicMonster);
        Id id = _entityManager->getLastEntityId();
        auto component = _entityManager->getComponentFromEntity(EComponent::direction, id);
        if (auto cDir = std::dynamic_pointer_cast<CDirection>(component)) {
            cDir->setDirection(180);
        }
        component = _entityManager->getComponentFromEntity(EComponent::position, id);
        if (auto cPos = std::dynamic_pointer_cast<CPosition>(component)) {
            cPos->setPosition(SVector2d{border, (double) RType::randomInt(50, 800)});
        }
        component = _entityManager->getComponentFromEntity(EComponent::speed, id);
        if (auto speed = std::dynamic_pointer_cast<CSpeed>(component)) {
            switch (+RType::randomInt(1, 3)) {
                case (1):
                    speed->setSpeed(4);
                    break;
                case (2):
                    speed->setSpeed(5);
                    break;
                case (3):
                    speed->setSpeed(3);
                    break;
                default:
                    speed->setSpeed(2);
                    break;
            }
        }
        component = _entityManager->getComponentFromEntity(EComponent::team, id);
        if (auto cTeam = std::dynamic_pointer_cast<CTeam>(component)) {
            cTeam->setTeam(ETeam::annemy);
        }
        component = _entityManager->getComponentFromEntity(EComponent::sprite, id);
        if (auto sprite = std::dynamic_pointer_cast<CSprite>(component)) {
            sprite->setId(Textures::ID::MONSTER); // set missile texture
            sprite->setSize(SVector2d{55, 55});
        }
        component = _entityManager->getComponentFromEntity(EComponent::health, id);
        if (auto health = std::dynamic_pointer_cast<CHealth>(component)) {
            health->setHealth(10);
        }
        component = _entityManager->getComponentFromEntity(EComponent::timer, id);
        if (auto timer = std::dynamic_pointer_cast<CTimer>(component)) {
            timer->setTimer(RType::randomInt(5, 7));
        }
        component = _entityManager->getComponentFromEntity(EComponent::shoot, id);
        if (auto shoot = std::dynamic_pointer_cast<CShoot>(component)) {
            shoot->addShootDir((int) EDirection::left);
            if (RType::randomInt(0, 1))
                shoot->addShootDir((int) EDirection::left + RType::randomInt(10, 30));
            if (RType::randomInt(0, 1))
                shoot->addShootDir((int) EDirection::left - RType::randomInt(10, 30));
        }
    }

    void SLevel::createBoss(int lvl) {
        _enemyLeft--;
        std::cout << "CREATING BOSS" << std::endl;
        _entityManager->CreateEntity(EEntity::basicMonster);
        Id id = _entityManager->getLastEntityId();
        auto component = _entityManager->getComponentFromEntity(EComponent::direction, id);
        if (auto cDir = std::dynamic_pointer_cast<CDirection>(component)) {
            cDir->setDirection(180);
        }
        component = _entityManager->getComponentFromEntity(EComponent::position, id);
        if (auto cPos = std::dynamic_pointer_cast<CPosition>(component)) {
            cPos->setPosition(SVector2d{border, (double) RType::randomInt(50, 800)});
        }
        component = _entityManager->getComponentFromEntity(EComponent::team, id);
        if (auto cTeam = std::dynamic_pointer_cast<CTeam>(component)) {
            cTeam->setTeam(ETeam::annemy);
        }
        component = _entityManager->getComponentFromEntity(EComponent::speed, id);
        if (auto speed = std::dynamic_pointer_cast<CSpeed>(component)) {
            switch (+RType::randomInt(1, 2)) {
                case (1):
                    speed->setSpeed(0.5);
                    break;
                case (2):
                    speed->setSpeed(0.7);
                    break;
                default:
                    speed->setSpeed(1);
                    break;
            }
        }
        component = _entityManager->getComponentFromEntity(EComponent::sprite, id);
        if (auto sprite = std::dynamic_pointer_cast<CSprite>(component)) {
            sprite->setId(Textures::ID::BOSS);
            sprite->setSize(SVector2d{270, 264});
        }
        component = _entityManager->getComponentFromEntity(EComponent::health, id);
        if (auto health = std::dynamic_pointer_cast<CHealth>(component)) {
            health->setHealth((lvl * 100));
        }
        component = _entityManager->getComponentFromEntity(EComponent::timer, id);
        if (auto timer = std::dynamic_pointer_cast<CTimer>(component)) {
            timer->setTimer(2);
        }
        component = _entityManager->getComponentFromEntity(EComponent::shoot, id);
        if (auto shoot = std::dynamic_pointer_cast<CShoot>(component)) {
            shoot->addShootDir((int) EDirection::left);
            shoot->addShootDir((int) EDirection::left + RType::randomInt(10, 30));
            shoot->addShootDir((int) EDirection::left - RType::randomInt(10, 30));
            shoot->addShootDir((int) EDirection::left + RType::randomInt(5, 15));
            shoot->addShootDir((int) EDirection::left - RType::randomInt(5, 15));
        }
    }


} // RType