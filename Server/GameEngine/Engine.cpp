#include "CHealth.hpp"

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "World.hpp"

#include <iostream>

int main() {
	RType::CHealth health(100, 100);

	// Initialization
	RType::World world;

	world.createEntity(RType::EEntity::player);
    world.createEntity(RType::EEntity::player);
    world.createEntity(RType::EEntity::player);

	world.print();

	return (0);
}
