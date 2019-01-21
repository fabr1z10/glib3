#pragma once

#include <gfx/scenefactory.h>

class Entity;


class SpriteViewFactory : public SceneFactory {
public:
    SpriteViewFactory();
    std::shared_ptr<Entity> Create() override;
    void PostInit() override {}
    void LoadModel (const std::string& model);
private:
    Entity* m_mainNode;
    std::shared_ptr<Entity> GenerateGrid(int xFrom, int xTo, int yFrom, int yTo);
};