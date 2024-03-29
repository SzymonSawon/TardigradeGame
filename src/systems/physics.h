#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <raylib.h>

#include "../utils/ida.h"

typedef enum {
    PSCF_DEFAULT = 0,
    PSCF_NOGRAVITY = 1 << 0,
    PSCF_NOSOLID = 1 << 1,
    PSCF_STATIC = 1 << 2,
} PhysicsSystem_ColliderFlags;

typedef struct {
    size_t uuid;
    size_t flags;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 size;
} PhysicsSystem_Collider;

typedef struct {
    ida_list(PhysicsSystem_Collider);
} PhysicsSystem_Colliders;

typedef struct {
    Rectangle bounding_rect;
    Vector2 gravity;
    PhysicsSystem_Colliders colliders;
} PhysicsSystem;

void physics_system_update(PhysicsSystem* sys);

#endif
