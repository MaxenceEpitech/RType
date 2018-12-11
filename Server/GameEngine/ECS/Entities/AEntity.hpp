#ifndef AENTITY_HPP
# define AENTITY_HPP

#include "AComponent.hpp"

#include <memory>
#include <list>
#include <string>

namespace RType {

    class AEntity {
        public:
            AEntity(const Id Id);

            void addComponent(Id id);
            bool removeComponent(Id id);
            Id getId() const;
            std::list<Id> &getComponents();

        private:
            Id _id;
            std::list<Id> _componentsId;
    };
} // RType

#endif /* !AENTITY_HPP */