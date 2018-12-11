#include "CHealth.hpp"

namespace RType {
    CHealth::CHealth(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::health), _health(50) {
    }

    float CHealth::getHealth() const {
        return _health;
    }

    void CHealth::setHealth(float health) {
        _health = health;
    }

    void CHealth::takeDamage(float health) {
        _health -= health;
    }

} // RType
