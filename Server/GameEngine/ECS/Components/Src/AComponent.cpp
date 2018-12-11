//
// Created by max on 27/11/18.
//

#include <AComponent.hpp>

#include "AComponent.hpp"

namespace RType {
    AComponent::AComponent(Id id, Id parentId, EComponent type)
        : _id(id), _parentId(parentId), _type(type) {
    }

    Id AComponent::getParentId() const {
        return _parentId;
    }

    Id AComponent::getId() const {
        return _id;
    }

    EComponent AComponent::getType() const {
        return _type;
    }


} // RType