#include <monkey/components/ianimator.h>

void IAnimator::resetAnimation() {
    if (m_animation.empty()) {
        return;
    }
    std::string anim = m_animation;
    m_animation.clear();
    SetAnimation(anim);


}