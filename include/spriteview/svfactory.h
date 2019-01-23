#pragma once

#include <gfx/scenefactory.h>

class Entity;
class ListView;
class IMesh;
class TextMesh;

class SpriteViewFactory : public SceneFactory {
public:
    SpriteViewFactory();
    std::shared_ptr<Entity> Create() override;
    void PostInit() override {}
    void CleanUp () override {}

    void LoadModel (const std::string& model, const std::string& anim = "");
    void ChangeAnim (const std::string& anim);
    void Reload();
    void LoadAssets();
private:
    Entity* m_mainNode;
    ListView* m_animList;
    ListView* m_modelList;
    std::shared_ptr<IMesh> m_currentMesh;
    Renderer* m_renderer;
    std::shared_ptr<Entity> GenerateGrid(int xFrom, int xTo, int yFrom, int yTo);
    std::shared_ptr<Entity> GenerateAxis(int xFrom, int xTo, int yFrom, int yTo);
    std::shared_ptr<Entity> GenerateText(float x, float y, const std::string&, float, TextAlignment);

    // tells whether the tools is animating the model
    bool m_animate;
    TextMesh* m_labelModelName;
    TextMesh* m_labelAnimName;
    TextMesh* m_labelCurrentFrame;
    std::string m_currentMeshName;
    std::string m_currentAnimation;
    int m_currentFrame;
};