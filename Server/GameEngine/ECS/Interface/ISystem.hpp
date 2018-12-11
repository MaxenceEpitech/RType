#ifndef ISYSTEM_HPP
# define ISYSTEM_HPP

#include <memory>

#include "AComponent.hpp"

namespace RType {
    class ComponentManager;
    class EntityManager;

    class ISystem {
        public:
            virtual ~ISystem() = default;

            void update(std::shared_ptr<AComponent> component);
    };
} // RType

#endif  /* !ISYSTEM_HPP */
