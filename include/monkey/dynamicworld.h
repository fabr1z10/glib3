#pragma once

#include <monkey/runner.h>
#include <monkey/script.h>
#include <unordered_map>
#include <monkey/camera.h>
#include <monkey/bounds.h>
#include <monkey/entity.h>

struct DynamicWorldItem {
    DynamicWorldItem() : id(-1),
                         ref(nullptr),
                         removedByDynamicWorld(false),
                         active(false) {}
    std::shared_ptr<Entity> m_blueprint;
    //Bounds m_bounds;
    Bounds m_localBounds;
    glm::vec3 m_initPos;
    int id;
    bool createOnce;
    bool removedByDynamicWorld;
    bool active;
    Entity* ref;
    //std::shared_ptr<Entity> m_object;
    //std::shared_ptr<Entity> ref;
    std::shared_ptr<Entity> m_parent;
};

// The world is divided into rectangular blocks of specified width and height
// When the player is at (0, 0) only the block (0, 0) is created
// When the player moves to (x, y)

class DynamicWorldBuilder : public Runner {
public:
    DynamicWorldBuilder(float cellWidth, float cellHeight, const std::string& camName) : Runner(),
        m_width(cellWidth), m_height(cellHeight), m_x(-1), m_y(-1), m_camName(camName), m_halfWidth(cellWidth*0.5f), m_halfHeight(cellHeight*0.5f) {}
    void Init() override;
    //void SetCamera(Camera*);
    void OnCameraMove(Camera*);
    void UpdateWorld(glm::vec3);
    void Update(double) override {}
    //void AddItem(std::shared_ptr<Entity>, std::shared_ptr<Entity>);
    void AddItem (std::shared_ptr<Entity>);
private:
    std::vector<DynamicWorldItem> m_items;
    // keep track of items removed externally
    std::unordered_set<int> m_removedItems;
    std::unordered_set<int> m_outBounds;
    // cam position center in grid coordinates
    // when cam is in (x, y) we need to build the world in the 16 cells
    float m_width, m_height;
    float m_halfWidth, m_halfHeight;
    int m_x, m_y;
    //float m_x0, m_y0;
    float m_xc, m_yc;
    float m_xc0, m_yc0;
    float m_xmin, m_xmax;
    float m_ymin, m_ymax;
    Bounds m_activeBounds;
    std::string m_camName;
    Entity* m_parentEntity;
};
