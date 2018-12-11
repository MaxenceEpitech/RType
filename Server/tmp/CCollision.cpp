#include "../Include/CCollision.hpp"

namespace RType {
    CCollision::CCollision(int x, int y) {
        _size.x = x;
        _size.y = y;
    }

    CCollision::CCollision(SVector2d size) {
        _size.x = size.x;
        _size.y = size.y;
    }

    SVector2d CCollision::getSize() {
        return _size;
    }
} // RType
