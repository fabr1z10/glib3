#include <monkey/components/statemachine.h>
#include <monkey/components/animrenderer.h>

// do-nothing state
class AnimState : public State {
public:
    AnimState(const ITab& t);
    void Init(const ITab& d) override;
    void Run(double) override;
    void End() override;
    void AttachStateMachine(StateMachine*) override;

private:
    Entity * m_entity;

    AnimationRenderer* m_renderer;

    // the animation to play
    std::string m_anim;

    // if true, move to nextState after anim is complete. Default value is false
    bool m_changeStateAfterAnim;

    // the state to go after animation is done
    std::string m_nextState;

    //
};