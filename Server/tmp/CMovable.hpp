#ifndef CMOVABLE_HPP
# define CMOVABLE_HPP

#include "../../Interface/IComponent.hpp"

namespace RType {
    class CPosition : public IComponent {
        private:
            bool _movable;
            float _speed;

        public:
            ~CPosition() = default;
            CPosition();
            CPosition(bool movable, float speed);

            bool isMovable();
            float getSpeed();
            void faster(float speed);
            void slower(float speed);
    };
} // RType

#endif  /* !CMOVABLE_HPP  */