#include "SCollision.hpp"
#include "CSprite.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "CTeam.hpp"
#include "CDamage.hpp"
#include "CHealth.hpp"

namespace RType {
    SCollision::SCollision(std::shared_ptr<ComponentManager> componentManager,
                           std::shared_ptr<EntityManager> entityManager)
            : ASystem(componentManager, entityManager) {
    }

    void SCollision::update(std::shared_ptr<RType::AComponent> component) {
        if (auto curPos = std::dynamic_pointer_cast<CPosition>(component)) {
            for (auto &cNextPos : _componentManager->getComponents()) {
                if (cNextPos->getId() != curPos->getId()) // Check not same component
                    if (auto nextPos = std::dynamic_pointer_cast<CPosition>(cNextPos)) {
                        if (hasCollide(curPos, nextPos)) {
                            handleCollide(curPos, nextPos);
                            break;
                        }
                    }
            }
        }
    }

    void SCollision::handleCollide(std::shared_ptr<CPosition> current, std::shared_ptr<CPosition> other) {
        float cDamage = -1, oDamage = -1;

        auto compCurrentDamage = _entityManager->getComponentFromEntity(EComponent::damage, current->getParentId());
        auto compOtherDamage = _entityManager->getComponentFromEntity(EComponent::damage, other->getParentId());
        if (compCurrentDamage != nullptr) {
            auto currentDamage = std::dynamic_pointer_cast<CDamage>(compCurrentDamage);
            cDamage = currentDamage->getDamage();
        }
        if (compOtherDamage != nullptr) {
            auto otherDamage = std::dynamic_pointer_cast<CDamage>(compOtherDamage);
            oDamage = otherDamage->getDamage();
        }
        /*
         *      If collided Entity has Damage, take damage if has Health
         */
        if (cDamage != -1) {
            auto compOtherHealth = _entityManager->getComponentFromEntity(EComponent::health, other->getParentId());
            if (compOtherHealth != nullptr) {
                auto otherHealth = std::dynamic_pointer_cast<CHealth>(compOtherHealth);
                if (otherHealth != nullptr) {
                    otherHealth->takeDamage(cDamage);
                }
            }
        }
        if (oDamage != -1) {
            auto compCurrentHealth = _entityManager->getComponentFromEntity(EComponent::health, current->getParentId());
            if (compCurrentHealth != nullptr) {
                auto currentHealth = std::dynamic_pointer_cast<CHealth>(compCurrentHealth);
                if (currentHealth != nullptr) {
                    currentHealth->takeDamage(oDamage);
                }
            }
        }
        /*
         *      If Entity dont has Health Component remove it
         */
        if (_entityManager->getComponentFromEntity(EComponent::health, current->getParentId()) == nullptr) {
            _entityManager->removeEntity(current->getParentId());
        }
        if (_entityManager->getComponentFromEntity(EComponent::health, other->getParentId()) == nullptr) {
            _entityManager->removeEntity(other->getParentId());
        }
    }

    bool SCollision::hasCollide(std::shared_ptr<CPosition> current, std::shared_ptr<CPosition> other) {
        auto compCurrentTeam = _entityManager->getComponentFromEntity(EComponent::team, current->getParentId());
        auto compOtherTeam = _entityManager->getComponentFromEntity(EComponent::team, other->getParentId());
        if (compCurrentTeam != nullptr && compOtherTeam != nullptr) {
            auto currentTeam = std::dynamic_pointer_cast<CTeam>(compCurrentTeam);
            auto otherTeam = std::dynamic_pointer_cast<CTeam>(compOtherTeam);
            if (currentTeam != nullptr && otherTeam != nullptr) {
                if (currentTeam->getTeam() == otherTeam->getTeam()) {
                    return false;
                }
            }
        }
        auto compCurrentSprite = _entityManager->getComponentFromEntity(EComponent::sprite, current->getParentId());
        auto compOtherSprite = _entityManager->getComponentFromEntity(EComponent::sprite, other->getParentId());
        if (compCurrentSprite != nullptr && compOtherSprite != nullptr) {
            auto currentSprite = std::dynamic_pointer_cast<CSprite>(compCurrentSprite);
            auto otherSprite = std::dynamic_pointer_cast<CSprite>(compOtherSprite);
            if (currentSprite != nullptr && otherSprite != nullptr) {
                auto curSpX = currentSprite->getSize().x;
                auto curSpY = currentSprite->getSize().y;
                auto curX = current->getPosition().x;// + (curSpX / 2);
                auto curY = current->getPosition().y;// + (curSpY / 2);
                auto nextSpX = otherSprite->getSize().x;
                auto nextSpY = otherSprite->getSize().y;
                auto nextX = other->getPosition().x;// + (nextSpX / 2);
                auto nextY = other->getPosition().y;// + (nextSpX / 2);

                // Haut à gauche
                if ((curX > nextX && curX < (nextX + nextSpX)) && curY > nextY && curY < (nextY + nextSpY))
                    return true;
                    // Haut à droite
                else if ((curX + curSpX > nextX && curX + curSpX < (nextX + nextSpX)) && curY > nextY &&
                         curY < (nextY + nextSpY))
                    return true;
                    // Bas à gauche
                else if ((curX > nextX && curX < (nextX + nextSpX)) && curY + curSpY > nextY &&
                         curY + curSpY < (nextY + nextSpY))
                    return true;
                    // Bas à droite
                else if ((curX + curSpX > nextX && curX + curSpX < (nextX + nextSpX)) && curY + curSpY > nextY &&
                         curY + curSpY < (nextY + nextSpY))
                    return true;
            }
        }
        return false;
    }
}