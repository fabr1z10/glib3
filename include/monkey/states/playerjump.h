#include <monkey/components/statemachine.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/icontroller.h>
#include <monkey/components/animrenderer.h>

class PlayerJump : public State {
public:
    PlayerJump(const ITab& t);
    void Init(const ITab& d) override;
    void Run(double) override;
    void End() override;
    void AttachStateMachine(StateMachine*) override;

private:
    InputMethod * m_input;
    IController * m_controller;
    Dynamics * m_dynamics;
    Entity * m_entity;
    float m_gravity;
    float m_acceleration;
    float m_maxSpeed;
    std::string m_walkState;
    AnimationRenderer* m_renderer;
    std::string m_jumpUpAnim;
    std::string m_jumpDownAnim;

};