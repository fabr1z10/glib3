#include <monkey/components/statemachine.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/icontroller.h>

class PlayerWalk : public State {
public:
    PlayerWalk(const ITab& t);
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
    float m_jumpSpeed;
    std::string m_jumpState;
};