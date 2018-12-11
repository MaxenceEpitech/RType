//
// Created by max on 27/11/18.
//

#ifndef SERVER_RANDOMINT_HPP
#define SERVER_RANDOMINT_HPP

#include <cstdlib>
#include <ctime>

namespace RType {
    static int randomInt(int min, int max) {
        return rand() % (max - min + 1) + min;
    }
} // RType

#endif //SERVER_RANDOMINT_HPP
