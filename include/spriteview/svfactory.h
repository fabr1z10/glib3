#pragma once

#include <gfx/scenefactory.h>

class Entity;
class ListView;


class SpriteViewFactory : public SceneFactory {
public:
    SpriteViewFactory();
    std::shared_ptr<Entity> Create() override;
    void PostInit() override {}
    void CleanUp () override {}

    void LoadModel (const std::string& model);
private:
    Entity* m_mainNode;
    ListView* m_animList;
    std::shared_ptr<Entity> GenerateGrid(int xFrom, int xTo, int yFrom, int yTo);
};