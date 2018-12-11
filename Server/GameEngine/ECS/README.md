# RType

## List of components and systems for each entity:
### Player:
- Components:

    Health,
    Speed,
    Position,
    Joystick,
    Sprite,
    Collide -> -5hp

- Systems:

    onDamageTaken,
    onCollision,

    isCollided(component1) {
        forEach(component2)
            if collide()
                - onCollide(component1.getComponentByComponent(id, type), component2.getEntity())
    }

    onCollide(Health, entity2) {
        entity1->Health -= entity1->collide;
    }

