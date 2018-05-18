#pragma once

#include <gfx/engine.h>

class MonkeyFactory : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
};