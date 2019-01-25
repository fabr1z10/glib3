#pragma once

#include <gfx/scenefactory.h>
#include <gfx/entities/listview.h>
#include <gfx/entities/treeview.h>

class Entity;
class IMesh;
class TextMesh;

class Item {
public:
    Item (const std::string& s) : m_text(s) {}
    std::string GetText() const {
        return m_text;
    }
    bool operator<(const Item& other) const {
        return m_text < other.m_text;
    }
private:
    std::string m_text;
};

struct Item2 {
    int key;
    int parentKey;
    std::string text;
    std::string GetText() const {
        return text;
    }
    static int rootKey;

};


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
    TreeView<Item2>* m_animList;
    ListView<Item>* m_modelList;
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