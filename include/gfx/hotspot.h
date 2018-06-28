#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/camera.h>
#include <graph/shape.h>
#include <vector>
#include <unordered_set>

// hotspot is a component I can attach to
class HotSpot : public Component {
public:
    HotSpot (int priority) : Component(), m_shape{nullptr}, m_focus{false}, m_priority{false} {}
    HotSpot (std::shared_ptr<Shape> shape, int priority) : Component(),
    m_shape{shape}, m_focus{false}, m_priority{priority} {}
    virtual ~HotSpot();
    virtual bool isMouseInside(glm::vec2);
    void SetFocus (bool);

    void Start() override;
    Shape* GetShape();
    void SetShape (std::shared_ptr<Shape> shape);
    void Update(double) override {}
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual void onClick(glm::vec2) = 0;
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


//class HotSpotGroup : public Ref {
//public:
//    HotSpotGroup() : Ref(), m_enabled{true} {}
//    HotSpotGroup(const std::string& camId) : Ref(), m_enabled{true}, m_camId(camId), m_currentlyActiveHotSpot{nullptr} {}
//    void Insert(HotSpot* hs) {
//        m_hotspots.insert(hs);
//    }
//    void Erase(HotSpot* hs) {
//        m_hotspots.erase(hs);
//        if (m_currentlyActiveHotSpot == hs) {
//            m_currentlyActiveHotSpot = nullptr;
//        }
//    }
//    void InitCamera();
//    void CheckCameraMove();
//    void Run(double x, double y);
//    void Click(double mouse_x, double mouse_y);
//    void CameraMove() ;
//    void SetEnabled(bool value) ;
//private:
//    bool m_enabled;
//    bool m_active;
//    std::unordered_set<HotSpot*> m_hotspots;
//    HotSpot* m_currentlyActiveHotSpot;
//    OrthographicCamera* m_cam;
//    std::string m_camId;
//};
//
//inline void HotSpotGroup::SetEnabled(bool value) {
//    m_enabled = value;
//    m_currentlyActiveHotSpot = nullptr;
//
//}

// I have one only mouse listener
// so when mouse moves, I just need to call one function and not one func for every hotspot.
// Each hotspoot registers to the hotspot handler at startup and it has a group id. For each group,
// only one hotspot can be active at any given time.
class HotSpotManager : public Component, public MouseListener {
public:
    HotSpotManager() : Component(), MouseListener(), m_active{true}, m_currentlyActiveHotSpot{nullptr} {}
    void Start() override ;
    void Update (double dt) override ;
    void CursorPosCallback(GLFWwindow*, double, double) override;
    void ScrollCallback(GLFWwindow*, double, double) override {}
    void MouseButtonCallback(GLFWwindow*, int, int, int) override;
    void Register (HotSpot*);
    void Unregister (HotSpot*);
    void AddGroup (int, const std::string& camId);
    using ParentClass = HotSpotManager;
    bool IsInViewport(float xScreen, float yScreen, glm::vec4 activeViewport);
    //void EnableGroup(int);
    //void DisableGroup(int);
protected:
    glm::vec2 m_worldCoordinates;
    HotSpot* m_currentlyActiveHotSpot;
    bool m_active;
    float m_pixelRatio;
    //std::unordered_map<int, std::unique_ptr<HotSpotGroup> > m_groups;
};
