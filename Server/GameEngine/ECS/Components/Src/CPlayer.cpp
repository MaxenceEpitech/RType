//
// Created by max on 27/11/18.
//

#include <CPlayer.hpp>
#include <AComponent.hpp>

#include "CPlayer.hpp"

namespace RType {

    RType::CPlayer::CPlayer(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::player) {
    }

    int RType::CPlayer::getTextureId() const {
        return _textureId;
    }

    void RType::CPlayer::setTextureId(int id) {
        _textureId = id;
    }

} // RType
