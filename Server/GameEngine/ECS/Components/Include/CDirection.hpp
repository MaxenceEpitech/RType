//
// Created by max on 27/11/18.
//

#ifndef SERVER_CDIRECTION_HPP
#define SERVER_CDIRECTION_HPP

#include "AComponent.hpp"

namespace RType {
    class CDirection : public AComponent {
    public:
        CDirection(Id id, Id parentId);

        int getDirection() const;
        void setDirection(int dir);

    private:
        int _dir;
    };
} // RType

#endif //SERVER_CDIRECTION_HPP
