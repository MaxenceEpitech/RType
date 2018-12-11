//
// Created by max on 27/11/18.
//

#ifndef SERVER_CTIMER_HPP
#define SERVER_CTIMER_HPP

#include "AComponent.hpp"

#include <chrono>

namespace RType {

    class CTimer : public AComponent {
    public:
        CTimer(Id id, Id parentId);

        void setTimer(int second);
        bool elapsed();

    private:
        int _timer;
        std::chrono::high_resolution_clock::time_point _action;
    };
} // RType

#endif //SERVER_CTIMER_HPP
