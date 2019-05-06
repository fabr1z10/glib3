#pragma once

#include <gfx/scenefactory.h>

class PlatformerFactory : public SceneFactory {
public:
    PlatformerFactory();
    void extendLua() override;
    //std::shared_ptr<Entity> Create() override;

};