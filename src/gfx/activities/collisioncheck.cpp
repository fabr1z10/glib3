#include <gfx/activities/collisioncheck.h>
#include <gfx/engine.h>
#include <glm/gtx/transform.hpp>
#include <gfx/entitywrapper.h>
#include <gfx/components/renderer.h>
#include <gfx/collisionengine.h>

CollisionCheck::CollisionCheck(std::shared_ptr<Shape> shape, const std::string& actorId, glm::vec2 offset, int mask, luabridge::LuaRef callback)
        : Activity(), m_shape(shape), m_actorId(actorId), m_offset(offset), m_mask(mask), m_callback(callback)
{
    m_engine = Engine::get().GetRunner<CollisionEngine>();
    m_actor = Engine::get().GetRef<Entity>(m_actorId);
    //m_renderer = m_actor->GetComponent<Renderer>();

}

void CollisionCheck::Start() {
    glm::mat4 p = m_actor->GetWorldTransform();
    glm::vec2 offset (p * glm::vec4(m_offset, 0.0f, 0.0f));
    //glm::vec2 offset = m_offset;
    //if (m_renderer->GetFlipX())
    p[3][0] += offset.x;
    p[3][1] += offset.y;
    //glm::mat4 t = glm::translate(pos);


    auto result = m_engine->ShapeCast(m_shape, p, m_mask);
    if (result != nullptr) {
        m_callback(EntityWrapper(result));
    }
    SetComplete();
}

