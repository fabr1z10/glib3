#pragma once

#include <monkey/runner.h>
#include <monkey/script.h>
#include <unordered_map>
#include <monkey/camera.h>
#include <monkey/bounds.h>
#include <monkey/entity.h>

class DynamicWorldItem : public Ref {
public:
    DynamicWorldItem(std::shared_ptr<Entity> entity,/*const PyTable& table*/ const Bounds& localBounds, const glm::vec3& initPos);
    std::shared_ptr<Entity> create ();
    void destroy ();
    void onRemove();
    glm::vec3 getPosition() const;
    Bounds getInitBounds() const;
    Bounds getCurrentBounds() const;
    bool candidateForCreation() const;
    bool candidateForDestruct() const;
private:
    //std::shared_ptr<Entity> m_blueprint;
	std::shared_ptr<Entity> m_entity;
    //PyTable m_template;
    // when player active bounds intersect the item bounds,
    // item is created (if not created already). When player leaves the area
    // item is removed.
    Bounds m_localBounds;
    Bounds m_initBounds;
    glm::vec3 m_initPos;
    bool m_alive;
    bool m_active;
    bool m_removedByDynamicWorld;
    int m_id;

};

inline bool DynamicWorldItem::candidateForCreation() const {
    return !m_alive && m_active;
}
inline bool DynamicWorldItem::candidateForDestruct() const {
    return m_alive;
}

inline Bounds DynamicWorldItem::getInitBounds() const {
    return m_initBounds;
}

class DynamicWorldBuilder : public Runner {
public:
    DynamicWorldBuilder(float cellWidth, float cellHeight, const std::string& camName) : Runner(),
        m_width(cellWidth), m_height(cellHeight), m_x(-1), m_y(-1), m_camName(camName), m_halfWidth(cellWidth*0.5f), m_halfHeight(cellHeight*0.5f), m_itemCount(0) {}
    DynamicWorldBuilder(const ITable& t);
    ~DynamicWorldBuilder() override;
    //void Init() override;
	void Begin() override;
    //void SetCamera(Camera*);
    void OnCameraMove(Camera*);
    void UpdateWorld(glm::vec3);
    void Update(double) override {}
    //void AddItem(std::shared_ptr<Entity>, std::shared_ptr<Entity>);
    //void AddItem (std::shared_ptr<Entity>);
private:
    std::unordered_map<int, std::shared_ptr<DynamicWorldItem> > m_items;
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
    size_t m_itemCount;
};
