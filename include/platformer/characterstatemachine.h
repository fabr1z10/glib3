#include <gfx/components/statemachine2.h>
#include <glm/glm.hpp>

class Ciao : public StateMachine2 {
    
public:
    glm::vec2 m_velocity;
    float m_gravity;
};

class Controller2D;

class Idle : public State2 {
public:
    // when the state changes to idle,
    // we need to update the animation and the
    // collider shape. These might depend also on other
    // factors (for instance, is supermario? can fire?)
    void Init () override;
    void Run (double) override;
    virtual void End () = 0;
private:
    Ciao* m_stateMachine;
    Controller2D* m_controller;
};
