#pragma once

#include <monkey/components/mover.h>

class EllipseMover : public Mover {
public:
    EllipseMover (float xrad, float yrad, float period, glm::vec2 origin);
    EllipseMover (const EllipseMover&);
    std::shared_ptr<Component> clone() const override;
    std::type_index GetType() override;
    void Start() override;
    void Update(double) override ;
private:
    glm::vec2 m_origin;
    float m_angularSpeed;
    float m_period;
    float m_xrad;
    float m_yrad;
    float m_timer;
    float m_ab;
};
