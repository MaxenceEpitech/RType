#include "AEntity.hpp"

namespace RType {
    AEntity::AEntity(const Id id)
        : _id(id) {
    }

    Id AEntity::getId() const {
        return _id;
    }

    void AEntity::addComponent(Id id) {
        _componentsId.push_back(id);
    }

    bool AEntity::removeComponent(Id id) {
        for (std::list<Id>::iterator it = _componentsId.begin(); it != _componentsId.end(); it++) {
            if ((*it) == id) {
                it = _componentsId.erase(it);
                return true;
            }
        }
        return false;
    }

    std::list<Id> &AEntity::getComponents() {
        return _componentsId;
    }

} // RType
