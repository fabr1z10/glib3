#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/camera.h>
#include <graph/shape.h>
#include <vector>
#include <unordered_set>
#include <gfx/event.h>

// hotspot is a component I can attach to
class HotSpot : public Component {
public:
    HotSpot (int priority) : Component(), m_shape{nullptr}, m_focus{false}, m_priority{false} {}
    HotSpot (std::shared_ptr<Shape> shape, int priority) : Component(),
    m_shape{shape}, m_focus{false}, m_priority{priority} {}
    virtual ~HotSpot();
    virtual bool isMouseInside(glm::vec2);
    void SetFocus (bool);
    Event<HotSpot*> onDestroy;
    void Start() override;
    Shape* GetShape();
    void SetShape (std::shared_ptr<Shape> shape);
    void Update(double) override {}
    void SetParent(Entity*) override;
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual void onClick(glm::vec2) = 0;
    virtual void onMove(glm::vec2) = 0;
    int GetGroup() const;
    int GetPriority() const;
    using ParentClass = HotSpot;
protected:
    int m_priority;
    std::shared_ptr<Shape> m_shape;
    bool m_focus;
};

inline Shape* HotSpot::GetShape()
{
    return m_shape.get();
}

inline void HotSpot::SetShape (std::shared_ptr<Shape> shape) {
    m_shape =shape;
}

inline int HotSpot::GetPriority() const {
    return m_priority;
}


// I have one only mouse listener
// so when mouse moves, I just need to call one function and not one func for every hotspot.
// Each hotspoot registers to the hotspot handler at startup and it has a group id. For each group,
// only one hotspot can be active at any given time.
class HotSpotManager : public Ref, public MouseListener {
public:
    HotSpotManager();
    //void Start() override ;
    //void Update (double dt) override ;
    void CursorPosCallback(GLFWwindow*, double, double) override;
    void ScrollCallback(GLFWwindow*, double, double) override {}
    void MouseButtonCallback(GLFWwindow*, int, int, int) override;
    void Enable(bool) override;
    //void Register (HotSpot*);
    //void Unregister (HotSpot*);
    //void AddGroup (int, const std::string& camId);
    //bool IsInViewport(float xScreen, float yScreen, glm::vec4 activeViewport);
    void NotifyHotSpotDestructor(HotSpot*);
    //void EnableGroup(int);
    //void DisableGroup(int);
protected:
    glm::vec2 m_worldCoordinates;
    HotSpot* m_currentlyActiveHotSpot;
    bool m_active;
    float m_pixelRatio;
    //std::unordered_map<int, std::unique_ptr<HotSpotGroup> > m_groups;
};

inline void HotSpotManager::Enable(bool value) {
    m_active = value;
    if (value == false)
        m_currentlyActiveHotSpot= nullptr;
}