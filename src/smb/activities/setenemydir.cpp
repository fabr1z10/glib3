#include <platformer/activities/setenemydir.h>
#include <platformer/input/enemyinput.h>

SetEnemyDirection::SetEnemyDirection(bool left) : TargetActivity(), m_left(left) {}

void SetEnemyDirection::Start() {
    TargetActivity::Start();

    auto input = dynamic_cast<EnemyInputMethod*>(m_entity->GetComponent<InputMethod>());
    input->setLeft(m_left);

    SetComplete();
}
