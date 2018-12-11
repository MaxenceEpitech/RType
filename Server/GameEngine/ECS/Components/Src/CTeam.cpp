//
// Created by max on 27/11/18.
//

#include "CTeam.hpp"

namespace RType {
    CTeam::CTeam(Id id, Id parentId)
            : AComponent(id, parentId, EComponent::team),
                _team(ETeam::ally) {
    }

    ETeam CTeam::getTeam() const {
        return _team;
    }

    void CTeam::setTeam(ETeam team) {
        _team = team;
    }

} // RType
