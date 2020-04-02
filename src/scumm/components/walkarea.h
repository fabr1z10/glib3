#pragma once

#include <monkey/components/hotspot.h>
#include <monkey/math/funcs.h>
#include <monkey/math/geom.h>
#include <monkey/lua/luafunc.h>
#include <monkey/components/scripthotspot.h>

class Scheduler;

struct BlockedLine {
    LineSegment seg;
    bool active;
};

class WalkArea : public ScriptHotSpot {
public:
    WalkArea (std::shared_ptr<Shape> shape, int priority);
    WalkArea (const LuaTable&);
    WalkArea (const ITable&);
    WalkArea (const WalkArea&);
    std::shared_ptr<Component> clone() const override;
    void assignDepth (Entity*);
    void assignScaleAndDepth (Entity*);
    void onAdd(Entity*);
    void Start() override;
//    void onEnter() override {}
//    void onLeave() override {}
//    void onClick(glm::vec2, int button, int action, int mods) override;
    //void onMove(glm::vec2) override {}
    void SetDepthFunction (std::shared_ptr<Function2D> func);
    void SetScalingFunction (std::shared_ptr<Function2D> func);
    void SetHandler (std::shared_ptr<LuaFunction> func);

    void AddBlockedLine(glm::vec2 A, glm::vec2 B, bool active);
    void EnableBlockedLine(int, bool);
    std::vector<LineSegment> GetActiveWalls() const;
    using ParentClass = HotSpot;
    std::type_index GetType() override;
private:
    std::shared_ptr<Entity> getDebugMesh() override ;

    std::vector<BlockedLine> m_walls;
    std::shared_ptr<Function2D> m_depthFunc;
    std::shared_ptr<Function2D> m_scaleFunc;
};



inline void WalkArea::SetDepthFunction (std::shared_ptr<Function2D> func) {
    m_depthFunc = func;
}

inline void WalkArea::SetScalingFunction (std::shared_ptr<Function2D> func) {
    m_scaleFunc = func;
}


inline std::type_index WalkArea::GetType() {
    return std::type_index(typeid(HotSpot));
}
