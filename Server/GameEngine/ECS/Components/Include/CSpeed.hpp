//
// Created by max on 27/11/18.
//

#ifndef SERVER_CSPEED_HPP
#define SERVER_CSPEED_HPP

#include "AComponent.hpp"

namespace RType {
    class CSpeed : public AComponent {
    public:
        CSpeed(Id id, Id parentId);

        float getSpeed() const;
        void setSpeed(float speed);

    private:
        float _speed;
    };
} // RType

#endif //SERVER_CSPEED_HPP
