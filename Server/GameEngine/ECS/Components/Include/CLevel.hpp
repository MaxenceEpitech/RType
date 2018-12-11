//
// Created by max on 27/11/18.
//

#ifndef SERVER_CLEVEL_HPP
#define SERVER_CLEVEL_HPP

#include "AComponent.hpp"

namespace RType {
    class CLevel : public AComponent {
    public:
        CLevel(Id id, Id parentId);

        int getLevel() const;
        void setLevel(int level);
        void nextLevel();

    private:
        int _level;
    };
} // RType

#endif //SERVER_CLEVEL_HPP
