#ifndef DIRECTION_HPP
# define DIRECTION_HPP

namespace RType {
    struct SDirection {
        int up = 0;
        int right = 90;
        int down = 180;
        int left = 270;
    };

    enum EDirection {
        up,
        right,
        down,
        left
    };
} // RType

#endif  /* !DIRECTION_HPP  */