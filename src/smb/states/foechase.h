#pragma once

#include <monkey/states/platformerstate.h>

class Controller2D;

/**
 * This enemy follows the player and places himself at a distance where he's able to attack him
 * If player is at range, the enemy will attack with some probability
 * Also, you can provide several attack states
 */
class FoeChase : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    FoeChase (const std::string& walkAnim, const std::string& idleAnim,
              float speed, float acceleration, bool fliph, bool flipIfPlatformEnds, int left);
    FoeChase (const FoeChase& orig);
    FoeChase (const ITable&);
    std::shared_ptr<State> clone() const override;
    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init (pybind11::dict&) override;
    //void Init (luabridge::LuaRef) override;
    void End () override;
    void ResetAnimation() override {}
    void ModifyAnimation() override {}
private:
    void computeDirection();
    void setDirection(int);
    Controller2D* m_c;

    std::string m_walkAnim;
    std::string m_idleAnim;
    std::vector<std::string> m_attacks;
    float m_speed;
    float m_acceleration;
    float m_probAttack;
    // flip gfx horizontally when going left
    // bool m_fliph;
    //bool m_flipIfPlatformEnds;
    int m_left;
    float m_attackPos;
    float m_targetVelocityX;
    Entity* m_target;
    bool m_inRange;
    bool m_jumpAttack;
    bool m_jumping;
};