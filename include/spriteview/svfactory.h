#pragma once

#include <gfx/scenefactory.h>
#include <gfx/entities/listview.h>
#include <gfx/entities/treeview.h>
#include <gfx/components/animator.h>
class Entity;
class IMesh;
class TextMesh;

class Item {
public:
    Item () {}
    Item (const std::string& s, const std::string& type) : m_text(s), m_type(type) {}
    std::string GetText() const {
        return m_text;
    }
    std::string GetType() const {
        return m_type;
    }

    bool operator<(const Item& other) const {
        return m_text < other.m_text;
    }
private:
    std::string m_text;
    std::string m_type;
};

struct Item2 {
    std::string key;
    std::string parentKey;
    std::string text;
    std::string GetText() const {
        return text;
    }
    static std::string rootKey;

};


class SpriteViewFactory : public SceneFactory {
public:
    SpriteViewFactory();
    std::shared_ptr<Entity> Create() override;
    void PostInit() override {}
    void CleanUp () override {}

    void LoadModel (const Item& model, const std::string& anim = "");
    void ChangeAnim (const std::string& anim);
    void Reload();
    void LoadAssets();
private:
    void printStatus();
    Entity* m_mainNode;
    TreeView<Item2>* m_animList;
    ListView<Item>* m_modelList;
    std::shared_ptr<IMesh> m_currentMesh;
    Renderer* m_renderer;
    std::shared_ptr<Entity> GenerateGrid(int xFrom, int xTo, int yFrom, int yTo);
    std::shared_ptr<Entity> GenerateAxis(float xFrom, float xTo, float yFrom, float yTo);
    std::shared_ptr<Entity> GenerateText(float x, float y, const std::string&, float, TextAlignment);

    // tells whether the tools is animating the model
    bool m_animate;
    TextMesh* m_labelModelName;
    TextMesh* m_labelAnimName;
    TextMesh* m_labelCurrentFrame;
    Animator* m_modelNode;
    Item m_currentItem;
    std::unordered_map<std::string, std::pair<std::string, int>> m_status;
    int m_currentFrame;
};