//
// Created by max on 27/11/18.
//

#include <CDamage.hpp>
#include <AComponent.hpp>

#include "CDamage.hpp"

namespace RType {

    RType::CDamage::CDamage(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::damage), _damage(10) {
    }

    float CDamage::getDamage() const {
        return _damage;
    }

    void CDamage::setDamage(float damage) {
        _damage = damage;
    }

} // RTYpe