//
// Created by max on 27/11/18.
//

#include <CShoot.hpp>
#include <AComponent.hpp>

#include "CShoot.hpp"

namespace RType {

    CShoot::CShoot(Id id, Id parentId)
        : AComponent(id, parentId, EComponent::shoot) {
    }

    std::list<int> RType::CShoot::getShootDir() const {
        return _shootDir;
    }

    void RType::CShoot::addShootDir(int dir) {
        _shootDir.push_back(dir);
    }

} // RType