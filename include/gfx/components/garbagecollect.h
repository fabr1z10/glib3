#pragma once

// auto remove entity when goes out of scope
#include <gfx/component.h>
#include <gfx/camera.h>

class GarbageCollect : public Component {
public:
    GarbageCollect(const std::string& target, float deltaXMax, float deltaYMax);
    GarbageCollect(const GarbageCollect&);
    void Start() override ;
    void Update(double) override;
    std::shared_ptr<Component> clone() const override;
private:
    std::string m_tag;
    Camera* m_target;
    float m_Dxmax;
    float m_Dymax;
};
