#include <monkey/components/statemachine.h>
#include <monkey/components/animrenderer.h>
#include <chrono>

// attack double dragon/ final fight style
// basically we have a sequence of animations. If we hit
// a target we go to next animation.
class AttackState : public State {
public:
	AttackState(const ITab& t);
	void Init(const ITab& d) override;
	void Run(double) override;
	void End() override;
	void AttachStateMachine(StateMachine*) override;
	void onCollide() override;

private:
	Entity * m_entity;

	AnimationRenderer* m_renderer;

	// the animation to play
	std::vector<std::string> m_anims;

	// if true, move to nextState after anim is complete. Default value is false
	bool m_changeStateAfterAnim;
	long m_lastHit;
	// the state to go after animation is done
	std::string m_nextState;
	int m_currentAnim;

};