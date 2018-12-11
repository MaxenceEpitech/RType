//
// Created by max on 27/11/18.
//

#ifndef SERVER_CSHOOT_HPP
#define SERVER_CSHOOT_HPP

#include "AComponent.hpp"

#include <list>

namespace RType {
    class CShoot : public AComponent {
    public:
        CShoot(Id id, Id parentId);

        std::list<int> getShootDir() const;
        void addShootDir(int dir);

    private:
        std::list<int> _shootDir;
    };
} // RType

#endif //SERVER_CSHOOT_HPP
