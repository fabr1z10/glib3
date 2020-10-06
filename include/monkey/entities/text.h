#pragma once

#include <monkey/entity.h>
#include <monkey/py.h>

// a sprite is just an entity with a sprite renderer and an animator
// it takes a MODEL parameter
class Text : public Entity {
public:
    Text (const ITable&);
};