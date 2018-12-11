//
// Created by max on 27/11/18.
//

#ifndef GAMEENGINE_CSPRITE_HPP
#define GAMEENGINE_CSPRITE_HPP

#include <string>

#include "AComponent.hpp"
#include "Textures.hpp"
#include "Vector.hpp"

namespace RType {
    class CSprite : public AComponent {
    public:
        CSprite(Id id, Id parentId);

        SVector2d getSize() const;
        void setSize(const SVector2d &size);

        RType::Textures::ID getIdTexture() const;
        void setId(const RType::Textures::ID &id);

    private:
        SVector2d _size;
        RType::Textures::ID _idTexture = RType::Textures::ID::NOTEXTURE;
    };
} // namespace RType

#endif // GAMEENGINE_CSPRITE_HPP
