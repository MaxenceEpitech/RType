#ifndef ENTITYMANAGER_HPP
# define ENTITYMANAGER_HPP

#include <list>
#include <memory>

#include "ComponentManager.hpp"
#include "AEntity.hpp"

namespace RType {
    enum EEntity {
        player,
        missile,
        basicMonster
    };

    class EntityManager {
    public:
        virtual ~EntityManager() = default;
        void setComponentManager(std::shared_ptr<ComponentManager> componentManager);
        EntityManager();

        void CreateEntity(EEntity entity);
        Id getLastEntityId();
        std::shared_ptr<AComponent> getComponentFromEntity(EComponent component, Id entityId);
        void removeComponent(EComponent component, Id parentId);
        Id getUniqueId();

        void addComponent(Id EntityId, Id id);
        void removeComponent(Id id);
        void removeEntity(Id id);

        void print();

    private:
        std::list<AEntity> _entities;
        std::shared_ptr<ComponentManager> _componentManager;
    };
} // RType

#endif  /* !ENTITYMANAGER_HPP  */