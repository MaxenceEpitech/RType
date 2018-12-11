//
// Created by max on 27/11/18.
//

#include <CSpeed.hpp>

#include "CSpeed.hpp"

namespace RType {

    CSpeed::CSpeed(Id id, Id parentId)
        : AComponent(id, parentId, EComponent::speed), _speed(1.0f) {

    }

    float CSpeed::getSpeed() const {
        return _speed;
    }

    void CSpeed::setSpeed(float speed) {
        _speed = speed;
    }

} // RType