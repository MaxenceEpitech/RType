#ifndef CHEALTH_HPP
#define CHEALTH_HPP

#include "AComponent.hpp"

namespace RType {
class CHealth : public AComponent {
public:
    CHealth(Id id, Id parentId);

    float getHealth() const;
    void setHealth(float health);
    void takeDamage(float health);

private:
    float _health;
};
} // RType

#endif /* !CHEALTH_HPP  */