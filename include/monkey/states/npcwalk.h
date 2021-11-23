#include <monkey/components/statemachine.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/animrenderer.h>

class NPCWalk : public State {
public:
    NPCWalk(const ITab& t);
    void Init(const ITab& d) override;
    void Run(double) override;
    void End() override;
    void AttachStateMachine(StateMachine*) override;

private:
    Controller2D * m_controller;
    Dynamics * m_dynamics;
    Entity * m_entity;
    float m_gravity;
    float m_maxSpeed;
    float m_jumpSpeed;
    AnimationRenderer* m_renderer;
    std::string m_idleAnim;
    std::string m_walkAnim;
    std::string m_jUpAnim;
    std::string m_jDownAnim;
    int m_direction; // -1 = going left, 1 = going right
    bool m_fliph;
    bool m_flipIfPlatformEnds;

};