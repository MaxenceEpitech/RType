#ifndef CCOLLISION_HPP
# define CCOLLISION_HPP

#include "../../Interface/IComponent.hpp"
#include "../../Utils/Vector.hpp"

namespace RType {
    class CCollision : public IComponent{
        private:
            SVector2d _size;

        public:
            ~CCollision() = default;
            CCollision(int x, int y);
            CCollision(SVector2d size);

            SVector2d getSize();
    };
} // RType

#endif  /* !CCOLLISION_HPP  */