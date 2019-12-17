#include <platformer/states/platformerstate.h>

class Controller2D;

// I think this walk class can be reused for other characters too!
class Jump : public State {
public:
    Jump();
    Jump (const Jump& orig);
    std::shared_ptr<State> clone() const override;

    void Init () override;
    void Run(double) override;
    void End () override;

private:
    Entity* m_entity;
};


