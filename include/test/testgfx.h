#include <gfx/engine.h>

class Factory1 : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
};

class Factory2 : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
};