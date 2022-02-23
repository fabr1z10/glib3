#pragma once

#include <monkey/states/base3d.h>
#include <monkey/components/icollider.h>
#include <monkey/entity.h>

class JumpAttack : public Base3D {
public:
    JumpAttack(const ITab&);
    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init(const ITab &) override;
    void End() override;
private:
    Entity* m_target;
    float m_peakHeight;
    float m_downSpeed;
    ICollisionEngine* m_engine;
    int m_castMask;
    int m_castTag;
    bool m_hit;
};