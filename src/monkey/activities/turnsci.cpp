#include <monkey/activities/turnsci.h>
#include <gfx/engine.h>
#include <gfx/states/walk25.h>
#include <gfx/components/ianimator.h>

void TurnSci::Start() {

    TargetActivity::Start();

    auto walkState = dynamic_cast<Walk25*>(m_entity->GetComponent<StateMachine>()->GetState("walk"));
    bool fourWay = walkState->isFourWay();
    std::stringstream anim;
    anim << "idle";
    if (fourWay) {
        char c = m_dir;
        if (c=='w') c='e';
        anim << "_" << c;
    }

    m_entity->SetFlipX(m_dir=='w');
    m_entity->GetComponent<IAnimator>()->SetAnimation(anim.str());
    SetComplete();
}
