#include <monkey/monkey.h>
#include <monkey/activities/treemove.h>
#include <monkey/engine.h>

TreeMove::TreeMove(const std::string& newParent) : TargetActivity(), m_newParent(newParent) {
}

//Animate(Entity* entity, const std::string& animId, bool forward, int flip = 0);
//@}
void TreeMove::Start() {
    TargetActivity::Start();

    auto newParent = Monkey::get().Get<Entity>(m_newParent);
    //m_entity->GetParent()->Remove(m_entity->GetId());
    Engine::get().Move(m_entity.get(), newParent);

    SetComplete();


}