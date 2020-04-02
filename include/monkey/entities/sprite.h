#pragma once

#include <monkey/entity.h>

// a sprite is just an entity with a sprite renderer and an animator
// it takes a MODEL parameter
class Sprite : public Entity {
public:
    Sprite (const LuaTable&);
    Sprite (const ITable&);


};
