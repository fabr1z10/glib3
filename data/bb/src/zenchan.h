#include <platformer/states/platformerstate.h>
#include <glm/glm.hpp>


class Controller2D;

enum class WalkType {
    GROUNDED, JUMPUP, JUMPDOWN
};

// I think this walk class can be reused for other characters too!
class ZenChanWalk : public State {
public:
    ZenChanWalk(bool left, float speedx, float speedy);
    ZenChanWalk (const ZenChanWalk& orig);
    std::shared_ptr<State> clone() const override;
    void AttachStateMachine(StateMachine*) override;
    void Init () override;
    void Run(double) override;
    void End () override;

private:
    void flip();
    bool m_left;
    WalkType m_type;
    float m_speedx;
    float m_speedy;
    float m_jumpHeight;
    float m_jumpLevel;
    Controller2D* m_controller2D;
    Entity* m_player;
    Entity* m_entity;
    glm::vec3 m_delta;
};


