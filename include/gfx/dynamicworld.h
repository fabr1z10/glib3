#pragma once

#include <gfx/runner.h>
#include <gfx/script.h>
#include <unordered_map>
#include <gfx/camera.h>
#include <gfx/bounds.h>
#include <gfx/entity.h>

struct DynamicWorldItem {
    std::shared_ptr<Entity> m_blueprint;
    Bounds m_bounds;
    Bounds m_localBounds;
    std::shared_ptr<Entity> m_object;
    Entity* m_parent;
};

class DynamicWorldBuilder : public Runner {
public:
    DynamicWorldBuilder(float cellWidth, float cellHeight) : Runner(), m_width(cellWidth), m_height(cellHeight), m_x(-1), m_y(-1) {}
    void SetCamera(Camera*);
    void OnCameraMove(Camera*);
    void UpdateWorld(glm::vec3);
    void Update(double) {}
    void AddItem(Entity*, std::shared_ptr<Entity>);
private:
    std::vector<DynamicWorldItem> m_items;
    // cam position center in grid coordinates
    // when cam is in (x, y) we need to build the world in the 16 cells
    float m_width, m_height;
    int m_x, m_y;
    float m_x0, m_y0;
    Bounds m_activeBounds;
};
