#pragma once

// auto remove entity when goes out of scope
#include <monkey/component.h>
#include <monkey/camera.h>

class GarbageCollect : public Component {
public:
    //GarbageCollect(const std::string& target, float deltaXMax, float deltaYMax);
    GarbageCollect(const ITable&);
    GarbageCollect(const GarbageCollect&);
    void Start() override ;
    void Update(double) override;
    std::shared_ptr<Component> clone() const override;
private:
    std::string m_tag;
    Camera* m_target;
    float m_Dxmax;
    float m_Dymax;
    float m_timeout;
    float m_t;
};
