#include "../Include/CPosition.hpp"
#include "CComponent.hpp"

namespace RType {
    CPosition::CPosition()
        : _movable(CComponent::_defaultMovable), _speed(CComponent::_defaultSpeed) {
    }

    CPosition::CPosition(bool moveable, float speed) 
        : _movable(moveable), _speed(speed) {
    }

    bool CPosition::isMovable() {
        return _movable;
    }

    float CPosition::getSpeed() {
        return _speed;
    }

    void CPosition::faster(float speed) {
        if (speed > 0) {
            _speed += speed;
            if (_speed > CComponent::_maximumSpeed) {
                _speed = CComponent::_maximumSpeed;
            }
        }
    }

    void CPosition::slower(float speed) {
        if (speed < 0) {
            _speed += speed;
            if (_speed < CComponent::_minimumSpeed) {
                _speed = CComponent::_minimumSpeed;
            }
        }
    }

} // RType