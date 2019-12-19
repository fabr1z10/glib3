#include <platformer/states/platformerstate.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>
#include <functional>

class Controller2D;

struct BubbleMove {
    glm::vec2 toPoint;
    bool immediate;
};

struct TimedEvent {
    int t;
    std::function<void()> func;

};


// I think this walk class can be reused for other characters too!
class Bubble : public State {
public:
    Bubble (bool left, float speed, float speedUp);
    Bubble (const Bubble& orig);
    std::shared_ptr<State> clone() const override;
    void AttachStateMachine(StateMachine*) override;
    void Init () override;
    void Run(double) override;
    void End () override {}

private:
    void initMove(int);
    void c1();
    float m_speed;
    float m_speedUp;
    bool m_left;
    bool m_shooting;
    Controller2D* m_controller2D;
    IAnimator* m_animator;

    Entity* m_entity;
    float m_x0;
    std::vector<BubbleMove> m_moves;
    std::vector<int> m_next;
    int m_currentMove;
    float m_lengthTraversed;
    float m_lengthToCover;
    glm::vec2 m_direction;
    glm::vec2 m_goal;
    float m_timer;
    float m_t1;
    float m_t2;
    std::list<TimedEvent> m_timedEvents;
};


