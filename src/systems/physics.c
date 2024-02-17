#include "physics.h"

#include <raymath.h>

static Rectangle rect(PhysicsSystem_Collider* c) {
    return (Rectangle){
        .x = c->position.x,
        .y = c->position.y,
        .width = c->size.x,
        .height = c->size.y,
    };
}

static float* comp(Vector2* v, int c) { return &((float*)v)[c]; }

void physics_system_update(PhysicsSystem* sys) {
    float dt = GetFrameTime();

    // apply gravity
    for (size_t i = 0; i < sys->colliders.count; i++) {
        sys->colliders.items[i].acceleration =
            Vector2Add(sys->colliders.items[i].acceleration, sys->gravity);
    }

    // apply separate axis computation
    for (int c = 0; c < 2; c++) {
        for (size_t i = 0; i < sys->colliders.count; i++) {
            // calculate new postion
            *comp(&sys->colliders.items[i].position, c) +=
                *comp(&sys->colliders.items[i].velocity, c) * dt +
                *comp(&sys->colliders.items[i].acceleration, c) * dt * dt * 0.5;
            // update velocity
            *comp(&sys->colliders.items[i].velocity, c) +=
                *comp(&sys->colliders.items[i].acceleration, c) * dt;
            // update acceleration
            *comp(&sys->colliders.items[i].acceleration, c) = 0;

            // clamp position to physics bounding rect
            float* p = comp(&sys->colliders.items[i].position, c);
            float* s = comp(&sys->colliders.items[i].size, c);
            if (*p < *comp((Vector2*)&sys->bounding_rect, c) ||
                *p + *s > *comp((Vector2*)&sys->bounding_rect, c) +
                              *comp((Vector2*)&sys->bounding_rect.width, c)) {
                *comp(&sys->colliders.items[i].velocity, c) = 0;
                *p = Clamp(*p, *comp((Vector2*)&sys->bounding_rect, c),
                           *comp((Vector2*)&sys->bounding_rect, c) +
                               *comp((Vector2*)&sys->bounding_rect.width, c) -
                               *s);
            }

            // resolve collisions based on velocity direction
            for (size_t j = 0; j < sys->colliders.count; j++) {
                if (j == i) continue;
                if (CheckCollisionRecs(rect(&sys->colliders.items[i]),
                                       rect(&sys->colliders.items[j]))) {
                    if (*comp(&sys->colliders.items[i].velocity, c) > 0) {
                        *comp(&sys->colliders.items[i].position, c) =
                            *comp(&sys->colliders.items[j].position, c) -
                            *comp(&sys->colliders.items[i].size, c);
                    } else {
                        *comp(&sys->colliders.items[i].position, c) =
                            *comp(&sys->colliders.items[j].position, c) +
                            *comp(&sys->colliders.items[j].size, c);
                    }
                    *comp(&sys->colliders.items[i].velocity, c) = 0;
                }
            }
        }
    }
}
