#include <monkey/activities/treemove.h>
#include <monkey/engine.h>

TreeMove::TreeMove(const std::string& newParent) : TargetActivity(), m_newParent(newParent) {
}

//Animate(Entity* entity, const std::string& animId, bool forward, int flip = 0);
//@}
void TreeMove::Start() {
    TargetActivity::Start();

    auto newParent = Ref::Get<Entity>(m_newParent);
    //m_entity->GetParent()->Remove(m_entity->GetId());
    Engine::get().Move(m_entity, newParent);

    SetComplete();


}