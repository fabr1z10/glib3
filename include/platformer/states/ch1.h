//#pragma once
//
//#include <platformer/states/platformerstate.h>
//
//class CustomHit1 : public PlatformerState {
//public:
//    CustomHit1(const std::string& target, float speedUp, float speedDown, const std::string& animUp, const std::string& animDown);
//    CustomHit1 (const CustomHit1& orig);
//    std::shared_ptr<State> clone() const override;
//    //void Start() override;
//    void Run (double) override;
//    void Init () override ;
//    void End () override {}
//    void AttachStateMachine(StateMachine*) override;
//
//private:
//    std::string m_target;
//    float m_speedUp;
//    float m_speedDown;
//    std::string m_jumpAnimUp;
//    std::string m_jumpAnimDown;
//    float m_vx;
//    Entity* m_targetEntity;
//    bool m_done;
//    double m_timer;
//};
