#ifndef WORLD_HPP
#define WORLD_HPP

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "NetworkHandler.hpp"
#include "SystemManager.hpp"

#include <memory>
#include <string>

namespace RType {
class World {
public:
  World(std::shared_ptr<NetworkHandler> networkHandler);
  ~World();
  void createEntity(EEntity entity);
  void update();
  void print();

private:
  std::shared_ptr<ComponentManager> _componentManager;
  std::shared_ptr<EntityManager> _entityManager;
  std::shared_ptr<SystemManager> _systemManager;
  std::shared_ptr<NetworkHandler> _networkHandler;
};
} // namespace RType

#endif /* !WORLD_HPP  */
