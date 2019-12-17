#include <platformer/states/platformerstate.h>

class Controller2D;

class ZenChanState : public PlatformerState {
public:
    ZenChanState(bool left, float speedx, float speedy);
    ZenChanState (const ZenChanState& orig);
    std::shared_ptr<State> clone() const override;

    void Init () override;
    void Run(double) override;
    void End () override;

    void ResetAnimation() override;
    void ModifyAnimation() override;
private:
    bool m_left;
    float m_speedx;
    float m_speedy;
    Controller2D* m_controller2D;

};


