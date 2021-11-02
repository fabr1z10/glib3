#pragma once

#include <monkey/entity.h>
#include <monkey/model/spritemodel.h>

// a sprite is just an entity with a sprite renderer and an animator
// it takes a MODEL parameter
class Sprite : public Entity {
public:
    Sprite (const ITab&);
    ~Sprite() override = default;
private:
    std::shared_ptr<SpriteModel> m_model;
};
