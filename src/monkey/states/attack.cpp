#include <monkey/states/attack.h>
#include <monkey/entity.h>
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;

AttackState::AttackState(const ITab& t) : State(t){
	m_anims = t.get<std::vector<std::string>>("anims");
	auto nextState = t.get<std::string>("next_state");
	m_currentAnim = 0;
	m_lastHit = 0;
}


void AttackState::onCollide() {
	m_lastHit = duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	m_currentAnim++;
	if (m_currentAnim >= m_anims.size()) {
		m_currentAnim = 0;
	}
}

void AttackState::Init(const ITab &d) {
	auto delta = duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - m_lastHit;
	if (delta > 500) {
		// reset
		m_currentAnim = 0;
	}
	m_renderer->setAnimation(m_anims[m_currentAnim]);
}

void AttackState::Run(double) {
	if (m_changeStateAfterAnim &&m_renderer->isComplete()) {
		m_sm->SetState(m_nextState);

	}


}

void AttackState::End() {}

void AttackState::AttachStateMachine(StateMachine * sm) {

	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();

	m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
}