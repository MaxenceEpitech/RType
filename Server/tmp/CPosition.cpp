#include "../Include/CPosition.hpp"

namespace RType {
    CPosition::CPosition(int x, int y) {
        _pos.x = x;
        _pos.y = y;
    }

    CPosition::CPosition(SVector2d pos) {
        _pos.x = pos.x;
        _pos.y = pos.y;
    }

    SVector2d CPosition::getPosition() {
        return _pos;
    }

    void CPosition::setPosition(SVector2d pos) {
        _pos.x = pos.x;
        _pos.y = pos.y;
    }

    void CPosition::setPosition(int x, int y) {
        _pos.x = x;
        _pos.y = y;
    }

    void CPosition::move(EDirection dir, int value) {
        switch (dir) {
            case EDirection::down:
                _pos.y += value;
                break;
            case EDirection::left:
                _pos.x -= value;
                break;
            case EDirection::right:
                _pos.x += value;
                break;
            case EDirection::up:
                _pos.y -= value;
                break;
        }
    }

} //RType
