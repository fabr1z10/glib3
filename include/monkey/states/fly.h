#include <monkey/components/statemachine.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/icontroller.h>
#include <monkey/components/animrenderer.h>

class Fly : public State {
public:
    Fly(float gravity, glm::vec2 initialVelocity, float angularSpeed = 0.0f);
    Fly(const ITab& t);
    void Init(const ITab& d) override;
    void Run(double) override;
    void End() override;
    void AttachStateMachine(StateMachine*) override;

private:
    IController * m_controller;
    Dynamics * m_dynamics;
    Entity * m_entity;
    float m_gravity;
    float m_acceleration;
    float m_maxSpeed;
    float m_jumpSpeed;
    std::string m_jumpState;
    AnimationRenderer* m_renderer;
    glm::vec2 m_initialVelocity;
    float m_angularSpeed;
};