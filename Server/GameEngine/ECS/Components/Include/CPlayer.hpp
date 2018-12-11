//
// Created by max on 27/11/18.
//

#ifndef SERVER_CPLAYER_HPP
#define SERVER_CPLAYER_HPP

#include "AComponent.hpp"

namespace RType {
    class CPlayer : public AComponent {
    public:
        CPlayer(Id id, Id parentId);

        int getTextureId() const;
        void setTextureId(int id);

    private:
        int _textureId;
    };
} // RType


#endif //SERVER_CPLAYER_HPP
