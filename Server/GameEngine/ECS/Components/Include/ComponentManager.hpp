#ifndef COMPONENTMANAGER_HPP
# define COMPONENTMANAGER_HPP

#include "AEntity.hpp"

#include <list>
#include <memory>

namespace RType {
    class EntityManager;

    class ComponentManager {
        public:
            virtual ~ComponentManager() = default;
            ComponentManager();
            void setEntityManager(std::shared_ptr<EntityManager> entityManager);

            Id createUniqueId();

            void createComponent(EComponent component, Id parentId);
            void removeComponent(Id id);
            void removeOnlyComponent(Id id);
            std::list<std::shared_ptr<AComponent>> &getComponents();

            void print();

        private:
            std::list<std::shared_ptr<AComponent>> _components;
            std::shared_ptr<EntityManager> _entityManager;
    };
} // RType

#endif  /* !COMPONENTMANAGER_HPP  */