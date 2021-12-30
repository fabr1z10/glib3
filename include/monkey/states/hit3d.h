#pragma once

#include <monkey/states/base3d.h>

class Hit3D : public Base3D {
public:
    explicit Hit3D(const ITab &);

    void Run(double) override;

    void Init(const ITab &) override;

    void End() override;
private:
    std::string m_hitAnim;
    std::string m_nextState;
    float m_dir;
    float m_timer;
    float m_timeOut;
};
