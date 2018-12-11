//
// Created by max on 27/11/18.
//

#include "SShot.hpp"

#include "CTimer.hpp"
#include "CShoot.hpp"
#include "CDirection.hpp"
#include "CPosition.hpp"
#include "CSpeed.hpp"
#include "CSprite.hpp"

#include "RandomInt.hpp"
#include "EntityManager.hpp"

namespace RType {

    SShot::SShot(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager)
            : ASystem(componentManager, entityManager) {

    }

    void SShot::update(std::shared_ptr<AComponent> component) {
        auto cTimer = std::dynamic_pointer_cast<CTimer>(component);
        if (cTimer != nullptr && cTimer->elapsed()) {
            auto compShoot = _entityManager->getComponentFromEntity(EComponent::shoot, component->getParentId());
            auto compPos = _entityManager->getComponentFromEntity(EComponent::position, component->getParentId());
            auto compTeam = _entityManager->getComponentFromEntity(EComponent::team, component->getParentId());
            auto compSprite = _entityManager->getComponentFromEntity(EComponent::sprite, component->getParentId());
            if (compShoot != nullptr && compPos != nullptr && compTeam != nullptr && compSprite != nullptr) {
                auto cShoot = std::dynamic_pointer_cast<CShoot>(compShoot);
                auto cPos = std::dynamic_pointer_cast<CPosition>(compPos);
                auto cTeam = std::dynamic_pointer_cast<CTeam>(compTeam);
                auto cSprite = std::dynamic_pointer_cast<CSprite>(compSprite);
                if (cShoot != nullptr && cPos != nullptr && cTeam != nullptr && cSprite != nullptr) {
                    for (int direction : cShoot->getShootDir()) {
                        createMissile(direction, cPos->getPosition(), ETeam::annemy, cSprite->getSize().y / 2);
                    }
                }
            }
        }
    }

    void SShot::createMissile(int dir, SVector2d pos, ETeam team, int spriteY_2) {
        _entityManager->CreateEntity(EEntity::missile);
        Id id = _entityManager->getLastEntityId();
        auto component = _entityManager->getComponentFromEntity(EComponent::direction, id);
        if (auto cDir = std::dynamic_pointer_cast<CDirection>(component)) {
            cDir->setDirection(dir);
        }
        component = _entityManager->getComponentFromEntity(EComponent::team, id);
        if (auto cTeam = std::dynamic_pointer_cast<CTeam>(component)) {
            cTeam->setTeam(team);
        }
        component = _entityManager->getComponentFromEntity(EComponent::position, id);
        if (auto cPos = std::dynamic_pointer_cast<CPosition>(component)) {
            cPos->setPosition(SVector2d{pos.x, pos.y + spriteY_2});
        }
        component = _entityManager->getComponentFromEntity(EComponent::speed, id);
        if (auto speed = std::dynamic_pointer_cast<CSpeed>(component)) {
            speed->setSpeed(RType::randomInt(7, 9));
        }
        component = _entityManager->getComponentFromEntity(EComponent::sprite, id);
        if (auto sprite = std::dynamic_pointer_cast<CSprite>(component)) {
            sprite->setId(Textures::ID::ENNEMY_MISSILE);
            sprite->setSize(SVector2d{55, 15});
        }
    }

} // RType