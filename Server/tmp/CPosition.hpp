#ifndef CPOSITION_HPP
# define CPOSITION_HPP

#include "../../Interface/IComponent.hpp"
#include "../../Utils/Vector.hpp"
#include "../../Utils/Direction.hpp"

namespace RType {
    class CPosition : public IComponent {
        private:
            SVector2d _pos;

        public:
            ~CPosition() = default;
            CPosition(int x, int y);
            CPosition(SVector2d pos);

            SVector2d getPosition();
            void setPosition(int x, int y);
            void setPosition(SVector2d pos);

            void move(EDirection dir, int value);
    };
} // RType

#endif  /* !CPOSITION_HPP  */