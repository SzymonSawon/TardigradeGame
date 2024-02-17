#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <raylib.h>

#include "../utils/da.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 size;
} PhysicsSystem_Collider;

typedef struct {
    da_list(PhysicsSystem_Collider);
} PhysicsSystem_Colliders;

typedef struct {
    Rectangle bounding_rect;
    Vector2 gravity;
    PhysicsSystem_Colliders colliders;
} PhysicsSystem;

void physics_system_update(PhysicsSystem* sys);

#endif
