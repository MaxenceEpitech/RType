//
// Created by max on 27/11/18.
//

#ifndef SERVER_CTEAM_HPP
#define SERVER_CTEAM_HPP

#include "AComponent.hpp"

namespace RType {

    enum class ETeam {
        ally,
        annemy
    };

    class CTeam : public AComponent {
    public:
        CTeam(Id id, Id parentId);

        ETeam getTeam() const;
        void setTeam(ETeam team);

    private:
        ETeam _team;
    };
} // RType

#endif //SERVER_CTEAM_HPP
