#include <gfx/collisioncheck.h>
#include <gfx/engine.h>
#include <glm/gtx/transform.hpp>
#include <monkey/entitywrapper.h>
#include <gfx/collisionengine.h>

CollisionCheck::CollisionCheck(std::shared_ptr<Shape> shape, const std::string& actorId, glm::vec2 offset, int mask, luabridge::LuaRef callback)
        : Activity(), m_shape(shape), m_actorId(actorId), m_offset(offset), m_mask(mask), m_callback(callback)
{
    m_engine = Engine::get().GetRunner<CollisionEngine>();
    m_actor = Engine::get().GetRef<Entity>(m_actorId);

}

void CollisionCheck::Start() {
    glm::vec3 pos = m_actor->GetPosition();
    pos += glm::vec3(m_offset, 0.0f);
    glm::mat4 t = glm::translate(pos);


    auto result = m_engine->ShapeCast(m_shape, t, m_mask);
    if (result != nullptr) {
        m_callback(EntityWrapper(result));
    }
    SetComplete();
}

