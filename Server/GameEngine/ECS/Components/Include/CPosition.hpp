//
// Created by max on 27/11/18.
//

#ifndef GAMEENGINE_CMOVABLE_HPP
#define GAMEENGINE_CMOVABLE_HPP

#include "AComponent.hpp"
#include "Vector.hpp"

namespace RType {
    class CPosition : public AComponent {
    public:
        CPosition(Id id, Id parentId);

        SVector2d getPosition() const;
        void setPosition(const SVector2d pos);

        void moveUp(const int speed);
        void moveDown(const int speed);
        void moveLeft(const int speed);
        void moveRight(const int speed);

    private:
        SVector2d _pos;
    };
} // RType

#endif //GAMEENGINE_CMOVABLE_HPP
