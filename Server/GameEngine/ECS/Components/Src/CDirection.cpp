//
// Created by max on 27/11/18.
//

#include <CDirection.hpp>

#include "CDirection.hpp"

namespace RType {
    CDirection::CDirection(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::direction) {
    }

    int RType::CDirection::getDirection() const {
        return _dir;
    }

    void CDirection::setDirection(int dir) {
        _dir = dir;
    }

} // RType
