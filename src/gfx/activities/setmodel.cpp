#include "gfx/activities/setmodel.h"
#include "gfx/engine.h"
#include "gfx/components/renderer.h"

SetModel::SetModel(const std::string &actorId, const std::string &model, const std::string &animId, int flip) :
        Activity(), m_actorId(actorId), m_model(model), m_animId(animId), m_flipX(flip) {}

void SetModel::Start() {
    auto entity = Engine::get().GetRef<Entity>(m_actorId);
    m_renderer = entity->GetComponent<Renderer>();

    if (m_renderer == nullptr)
        GLIB_FAIL("Error! No renderer found for " << m_actorId << " when trying to animate " << m_animId);
    if (m_flipX != 0) {
        //m_entity->Set
        m_entity->SetFlipX(m_flipX == 2);
    }
    //auto model = Engine::get().GetAssetManager().GetModel(m_model);
    //m_renderer->SetMesh(model);
    //m_renderer->SetAnimation(m_animId);
    SetComplete();

}