//
// Created by max on 27/11/18.
//

#include <CTimer.hpp>
#include "CTimer.hpp"

namespace RType {

    CTimer::CTimer(Id id, Id parentId)
        : AComponent(id, parentId, EComponent::timer), _timer(1) {
    }

    void CTimer::setTimer(int second) {
        _timer = second;
    }

    bool RType::CTimer::elapsed() {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        auto time_span = std::chrono::duration_cast < std::chrono::duration < double >> (now - _action);
        if (time_span.count() > _timer) {
            _action = std::chrono::high_resolution_clock::now();
            return true;
        }
        return false;
    }
} // RType
