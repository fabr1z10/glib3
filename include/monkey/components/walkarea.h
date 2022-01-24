#pragma once

#include <monkey/components/hotspot.h>
#include <monkey/math/funcs.h>
#include <monkey/math/geom.h>
#include <monkey/components/scripthotspot.h>
#include <monkey/math/algo/shortestpath.h>

class Scheduler;

//struct BlockedLine {
//    LineSegment seg;
//    bool active;
//};

class WalkArea : public Component {
public:
    //WalkArea (std::shared_ptr<IShape> shape, int priority);
    WalkArea (const ITab&);
    void Update(double) override {}
    const IShape* getShape() const;
    void assignDepth (Entity*);
    void assignScaleAndDepth (Entity*);
    void onAdd(Entity*);
    void Start() override;
    void recalc();
//    void onEnter() override {}
//    void onLeave() override {}
//    void onClick(glm::vec2, int button, int action, int mods) override;
    //void onMove(glm::vec2) override {}
    void SetDepthFunction (std::shared_ptr<Function2D> func);
    void SetScalingFunction (std::shared_ptr<Function2D> func);
    //void SetHandler (std::shared_ptr<LuaFunction> func);
    std::vector<glm::vec2> findPath(glm::vec2 A, glm::vec2 B, int&);
    float checkMove (glm::vec2 A, glm::vec2 dir, float);
    void AddBlockedLine(glm::vec2 A, glm::vec2 B, bool active);
    void EnableBlockedLine(int, bool);
    std::vector<LineSegment> GetActiveWalls() const;
    using ParentClass = WalkArea;
    std::type_index GetType() override;
private:
    //std::shared_ptr<Entity> getDebugMesh() override ;
    std::shared_ptr<IShape> m_shape;

    //std::vector<BlockedLine> m_walls;
    std::shared_ptr<Function2D> m_depthFunc;
    std::shared_ptr<Function2D> m_scaleFunc;
    std::shared_ptr<IShortestPath> m_shortestPath;

    std::set<Entity*> m_scaleDepthExclude;
};

inline const IShape * WalkArea::getShape() const {
    return m_shape.get();
}


inline void WalkArea::SetDepthFunction (std::shared_ptr<Function2D> func) {
    m_depthFunc = func;
}

inline void WalkArea::SetScalingFunction (std::shared_ptr<Function2D> func) {
    m_scaleFunc = func;
}


inline std::type_index WalkArea::GetType() {
    return std::type_index(typeid(WalkArea));
}


