#pragma once

#include <monkey/states/platformerstate.h>

// this is the walk state used in platformers like SuperMario
class KoopaShell : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    KoopaShell (float time, float timeWalk);
    KoopaShell (const ITab&);

    void Run(double) override;
    void Init (pybind11::dict&) override;
    void End () override;
    void ResetAnimation() override {}
    void ModifyAnimation() override {}
private:
    float m_time;
    float m_time_walk;
    float m_timer;
    int m_seq;
    int m_id;
};