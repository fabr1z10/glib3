#pragma once

#include <monkey/states/platformerstate.h>

class Controller2D;

// this is the walk state used in platformers like SuperMario
class Bounce : public PlatformerState {
public:
    Bounce (const ITable&);

    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init (pybind11::dict&) override;
    //void Init (luabridge::LuaRef) override;
    void End () override;
    void ResetAnimation() override {}
    void ModifyAnimation() override {}
private:
    void setDirection(int);
    Controller2D* m_c;
    std::string m_anim;
    float m_speed;
    bool m_fliph;
    float m_a;
    float m_b;
};