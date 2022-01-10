#pragma once

#include <monkey/states/base3d.h>

class Dead3D : public Base3D {
public:
    explicit Dead3D(const ITab &);

    void Run(double) override;

    void Init(const ITab &) override;

    void End() override;
private:
    float m_initialVelocity;
    std::string m_animStart;
    std::string m_animFall;
    std::string m_animLie;
    float m_dir;
    float m_timer;
    // disappear after timeout - if set
    float m_timeOut;
    float m_t1;
    int m_state;
    float m_startBlinkAfter;
    float m_removeAfter;

};
