#include <platformer/states/playanim.h>

PlayAnim::PlayAnim(PlatformerState* state, const std::string &anim) : StateAction(), m_anim(anim), m_state(state) {}

void PlayAnim::Run(StateMachine * sm) {
    m_state->SetOverrideAnimation(m_anim);
}