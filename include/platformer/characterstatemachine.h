#include <gfx/components/statemachine2.h>
#include <glm/glm.hpp>

class CharacterStateMachine : public StateMachine2 {
    
public:
    glm::vec2 m_velocity;
    float m_gravity;
    float m_accTimeGnd;
};




