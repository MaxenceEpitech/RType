//
// Created by max on 27/11/18.
//

#ifndef SERVER_CONCOLLIDE_HPP
#define SERVER_CONCOLLIDE_HPP

#include "AComponent.hpp"

namespace RType {
    class CDamage : public AComponent {
    public:
        CDamage(Id id, Id parentId);

        float getDamage() const;
        void setDamage(float damage);

    private:
        float _damage;
    };
} // RType

#endif //SERVER_CONCOLLIDE_HPP
