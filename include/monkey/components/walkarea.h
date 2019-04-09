#pragma once

#include <gfx/components/hotspot.h>
#include <gfx/math/funcs.h>
#include <gfx/math/geom.h>
#include <gfx/lua/luafunc.h>

class Scheduler;

struct BlockedLine {
    LineSegment seg;
    bool active;
};

class WalkArea : public HotSpot {
public:
    WalkArea (std::shared_ptr<Shape> shape, int priority, const std::string& playerId) : HotSpot(shape, priority), m_playerId{playerId} {}
    WalkArea (const WalkArea&);
    std::shared_ptr<Component> clone() const override;
    /* m_depthFunc{nullptr}, m_scaleFunc{nullptr}*/
//    bool isMouseInside(glm::vec2) override {
//        return true;
//    }
    //float GetDepth (float x, float y);
    //float GetScale (float x, float y);
    void Start() override;
    void onEnter() override {}
    void onLeave() override {}
    void onClick(glm::vec2, int button, int action, int mods) override;
    void onMove(glm::vec2) override {}
    //void SetDepthFunction (std::unique_ptr<Function2D> func);
    //void SetScalingFunction (std::unique_ptr<Function2D> func);

    void AddBlockedLine(glm::vec2 A, glm::vec2 B, bool active);
    void EnableBlockedLine(int, bool);
    std::vector<LineSegment> GetActiveWalls() const;
    using ParentClass = HotSpot;
    std::type_index GetType() override;
private:
    int m_id;
    Entity* m_player;
    std::vector<BlockedLine> m_walls;
    std::string m_playerId;
    //std::unique_ptr<Function2D> m_depthFunc;
    //std::unique_ptr<Function2D> m_scaleFunc;
    Scheduler* m_scheduler;

};



//inline void WalkArea::SetDepthFunction (std::unique_ptr<Function2D> func) {
//    m_depthFunc = std::move(func);
//}
//inline void WalkArea::SetScalingFunction (std::unique_ptr<Function2D> func) {
//    m_scaleFunc = std::move(func);
//}
inline std::type_index WalkArea::GetType() {
    return std::type_index(typeid(HotSpot));
}
