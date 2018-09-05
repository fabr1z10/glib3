#pragma once

#include "entity.h"

class Entity;

class CollisionResponse {
public:
    virtual void onStart (Entity*, Entity*, ) = 0;
    virtual void onEnd (Entity*, Entity*) = 0;
    virtual void onStay () = 0;
};