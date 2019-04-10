#include <gfx/activities/treemove.h>
#include <gfx/engine.h>

TreeMove::TreeMove(const std::string& newParent) : TargetActivity(), m_newParent(newParent) {
}

//Animate(Entity* entity, const std::string& animId, bool forward, int flip = 0);
//@}
void TreeMove::Start() {
    TargetActivity::Start();

    //auto newParent = Engine::get().GetRef<Entity>(m_newParent);

    //newParent->AddChild()



}