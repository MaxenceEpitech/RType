//
// Created by max on 27/11/18.
//

#include <CPosition.hpp>

#include "CPosition.hpp"

namespace RType {
    CPosition::CPosition(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::position) {
        _pos.x = 0;
        _pos.y = 0;
    }

    SVector2d CPosition::getPosition() const {
        return _pos;
    }

    void CPosition::setPosition(const SVector2d pos) {
        _pos.x = pos.x;
        _pos.y = pos.y;
    }

    void CPosition::moveUp(const int speed) {
        _pos.y -= speed;
    }

    void CPosition::moveDown(const int speed) {
        _pos.y += speed;
    }

    void CPosition::moveLeft(const int speed) {
        _pos.x -= speed;
    }

    void CPosition::moveRight(const int speed) {
        _pos.x += speed;
    }

} // RType