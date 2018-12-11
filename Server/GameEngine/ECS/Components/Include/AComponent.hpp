//
// Created by max on 27/11/18.
//

#ifndef GAMEENGINE_ACOMPONENT_HPP
#define GAMEENGINE_ACOMPONENT_HPP


#include <stb.h>

namespace RType {
    enum class EComponent {
        health,
        position,
        sprite,
        player,
        direction,
        speed,
        timer,
        shoot,
        team,
        damage,
        level
    };

    enum class EDirection {
        up = 90,
        down = 270,
        left = 180,
        right = 0
    };

    using Id = std::size_t;

    class AComponent {
    public:
        explicit AComponent(Id id, Id parentId, EComponent type);
        virtual ~AComponent() = default;

        Id getParentId() const;
        Id getId() const;
        EComponent getType() const;

    private:
        Id _id;
        Id _parentId;
        EComponent _type;
    };
} // RType


#endif //GAMEENGINE_ACOMPONENT_HPP
