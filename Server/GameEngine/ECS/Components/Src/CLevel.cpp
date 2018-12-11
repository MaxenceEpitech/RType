//
// Created by max on 27/11/18.
//

#include "CLevel.hpp"

namespace RType {

    CLevel::CLevel(Id id, Id parentId)
        : AComponent(id, parentId, EComponent::level), _level(1) {
    }

    int CLevel::getLevel() const {
        return _level;
    }

    void CLevel::setLevel(int level) {
        if (level < 0) {
            _level = 0;
        } else {
            _level = level;
        }
    }

    void CLevel::nextLevel() {
        _level += 1;
    }

} // RType