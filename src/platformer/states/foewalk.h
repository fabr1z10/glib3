#pragma once

#include <monkey/states/platformerstate.h>

class Controller2D;

// this is the walk state used in platformers like SuperMario
class FoeWalk : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    FoeWalk (const std::string& anim, float speed, float acceleration, bool fliph, bool flipIfPlatformEnds, int left);
    FoeWalk (const ITab&);
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
    float m_acceleration;
    // flip gfx horizontally when going left
    bool m_fliph;
    bool m_flipIfPlatformEnds;
    int m_left;
    float m_targetVelocityX;
};