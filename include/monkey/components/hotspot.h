#pragma once

#include <monkey/listener.h>
#include <monkey/component.h>
#include <monkey/camera.h>
#include <monkey/math/shape.h>
#include <vector>
#include <unordered_set>
#include <monkey/event.h>
#include <monkey/runner.h>
#include <stack>

// hotspot is a component I can attach to
class HotSpot : public Component {
public:
    HotSpot (int priority) : Component(), m_shape{nullptr}, m_focus{false}, m_priority{priority} {}
    //HotSpot (const LuaTable&);
    HotSpot (const ITab&);
    HotSpot (const HotSpot&);
    HotSpot (std::shared_ptr<IShape> shape, int priority) : Component(),
    m_shape{shape}, m_focus{false}, m_priority{priority} {}
    virtual ~HotSpot();
    virtual bool isMouseInside(glm::vec2);
    void SetFocus (bool);
    Event<HotSpot*> onDestroy;
    void Start() override;
    IShape* GetShape();
    void SetShape (std::shared_ptr<IShape> shape);
    void Update(double) override {}
    void SetParent(Entity*) override;
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual void onClick(glm::vec2, int button, int action, int mods) = 0;
    virtual void onMove(glm::vec2) = 0;
    virtual void onScroll(float, float) {}
    virtual bool onKeyEvent (const KeyEvent&) {
        return false;
    }
    int GetGroup() const;
    int GetPriority() const;
    using ParentClass = HotSpot;

protected:
    virtual std::shared_ptr<Entity> getDebugMesh();
    int m_priority;
    std::shared_ptr<IShape> m_shape;
    bool m_focus;
};

inline IShape* HotSpot::GetShape()
{
    return m_shape.get();
}

inline void HotSpot::SetShape (std::shared_ptr<IShape> shape) {
    m_shape =shape;
}

inline int HotSpot::GetPriority() const {
    return m_priority;
}

// I have one only mouse listener
// so when mouse moves, I just need to call one function and not one func for every hotspot.
// Each hotspoot registers to the hotspot handler at startup and it has a group id. For each group,
// only one hotspot can be active at any given time.
class HotSpotManager : public Component, public MouseListener, public KeyboardListener {
public:
    HotSpotManager();
    HotSpotManager(const ITab&);


    ~HotSpotManager() override;

    void Start() override;
    void Update(double) override {}

    void CursorPosCallback(GLFWwindow*, double, double) override;
    void ScrollCallback(GLFWwindow*, double, double) override;
    void MouseButtonCallback(GLFWwindow*, int, int, int) override;

    void setRmbClickCallback(std::function<void(float, float)> f);
    void setLmbClickCallback(std::function<void(float, float)> f);

    void NotifyHotSpotDestructor(HotSpot*);
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    void setActive(bool) override;

    using ParentClass = HotSpotManager;
    //std::string toString() override;
protected:
    Camera* m_defaultCamera;
    glm::vec2 m_worldCoordinates;
    HotSpot* m_currentlyActiveHotSpot;
    float m_pixelRatio;
    std::function<void(float, float)> m_rmbClick;
    std::function<void(float, float)> m_lmbClick;
    //std::unordered_map<int, std::unique_ptr<HotSpotGroup> > m_groups;
};

inline void HotSpotManager::setActive(bool value) {
    Ref::setActive(value);
    MouseListener::Enable(value);
    if (value == false)
        m_currentlyActiveHotSpot= nullptr;
}

inline void HotSpotManager::setLmbClickCallback(std::function<void(float, float)> f) {
    m_lmbClick = f;
}

inline void HotSpotManager::setRmbClickCallback(std::function<void(float, float)> f) {
    m_rmbClick = f;
}