#pragma once

#include <monkey/hotspot.h>
#include <monkey/funcs.h>
#include <graph/geom.h>

struct BlockedLine {
    LineSegment seg;
    bool active;
};

class WalkArea : public HotSpot {
public:
    WalkArea (std::shared_ptr<Shape> shape, int priority, int group, const std::string& playerId) : HotSpot(shape, priority, group), m_playerId{playerId},
    m_depthFunc{nullptr}, m_scaleFunc{nullptr} {}
    virtual bool isMouseInside(glm::vec2) {
        return true;
    }
    float GetDepth (float x, float y);
    float GetScale (float x, float y);
    void Start() override;
    void onEnter() override {}
    void onLeave() override {}
    void onClick(glm::vec2);
    void SetDepthFunction (std::unique_ptr<Function2D> func);
    void SetScalingFunction (std::unique_ptr<Function2D> func);
    using ParentClass = HotSpot;
    void AddBlockedLine(glm::vec2 A, glm::vec2 B, bool active);
    void EnableBlockedLine(int, bool);
    std::vector<LineSegment> GetActiveWalls() const;
private:

    std::vector<BlockedLine> m_walls;
    std::string m_playerId;
    std::unique_ptr<Function2D> m_depthFunc;
    std::unique_ptr<Function2D> m_scaleFunc;

};


inline void WalkArea::SetDepthFunction (std::unique_ptr<Function2D> func) {
    m_depthFunc = std::move(func);
}
inline void WalkArea::SetScalingFunction (std::unique_ptr<Function2D> func) {
    m_scaleFunc = std::move(func);
}
