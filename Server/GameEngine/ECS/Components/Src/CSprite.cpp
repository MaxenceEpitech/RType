//
// Created by max on 27/11/18.
//

#include <CSprite.hpp>

#include "CSprite.hpp"

namespace RType {
    CSprite::CSprite(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::sprite),
            _size{50, 50} {
    }

    SVector2d CSprite::getSize() const {
        return _size;
    }

    void CSprite::setSize(const SVector2d &size) {
        _size = size;
    }

    RType::Textures::ID CSprite::getIdTexture() const {
        return _idTexture;
    }

    void CSprite::setId(const RType::Textures::ID &id) {
        _idTexture = id;
    }
} // namespace RType
