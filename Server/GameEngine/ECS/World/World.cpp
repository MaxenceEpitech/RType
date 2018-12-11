#include "World.hpp"

#include <iostream>
#include <thread>

namespace RType {
    World::World(std::shared_ptr<NetworkHandler> networkHandler) {
        std::cerr << "\t\t\t\t\t\tWorld Has been Created" << std::endl;
        _networkHandler = networkHandler;
        _componentManager = std::make_shared<ComponentManager>();
        _entityManager = std::make_shared<EntityManager>();
        _componentManager->setEntityManager(_entityManager);
        _entityManager->setComponentManager(_componentManager);
        _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager, _networkHandler);
    }

    World::~World() {
        std::cerr << "\t\t\t\t\t\tWorld Has been destroyed" << std::endl;
    }

    void World::createEntity(EEntity entity) {
        _entityManager->CreateEntity(entity);
    }

void World::update() {
  //std::cout << "Update playerData size: \t\t\t"
  //          << _networkHandler->getPlayerData().size() << std::endl;
  //std::cout << "World Update" << std::endl;
  _systemManager->updateSystem();
  //std::cout << "Update End\n\n\n";
}

void World::print() {

  _componentManager->createComponent(EComponent::health, 0);
  _componentManager->createComponent(EComponent::health, 0);
  _componentManager->createComponent(EComponent::health, 0);

  _entityManager->removeEntity(0);

  _componentManager->print();
  _entityManager->print();
}

} // namespace RType
