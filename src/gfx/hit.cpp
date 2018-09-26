#include <gfx/hit.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <monkey/entitywrapper.h>

Hit::Hit (const std::string& anim) :
        State(), m_anim(anim)
{}

HitCollision::HitCollision (const std::string& anim, int frame, std::shared_ptr<Shape> collisionShape, glm::vec2 offset, int mask, luabridge::LuaRef callback) :
Hit(anim), m_frame(frame), m_shape(collisionShape), m_mask(mask), m_offset(offset), m_hitDone{false}, m_callback(callback)
{}

void Hit::Init(Entity* e) {
    State::Init(e);
    m_renderer = m_entity->GetComponent<Renderer>();
}

void HitCollision::Init(Entity* e) {
    Hit::Init(e);
    m_engine = Engine::get().GetRunner<CollisionEngine>();
}


void Hit::Start() {
    m_renderer->SetAnimation(m_anim);
}

void HitCollision::Start() {
    Hit::Start();
    m_hitDone = false;
}


bool Hit::Run(double) {

    if (m_renderer->GetLoopCount() > 0) {
        m_nextState = "walk";
        return true;
    } else {

    }
    return false;
}

bool HitCollision::Run(double dt) {
    if (Hit::Run(dt))
        return true;

    if (!m_hitDone) {
        int f = m_renderer->GetFrame();
        if (f == m_frame) {
            glm::vec3 pos = m_entity->GetPosition();
            std::cout <<" **** hit ****\n";
            std::cout << "character at position = " << pos.x << ", " << pos.y << "\n";
            bool flip = m_renderer->GetFlipX();
            pos.x += flip ? -m_offset.x - m_shape->getBounds().GetSize().x : m_offset.x;
            pos.y += m_offset.y;
            std::cout << "collider at position = " << pos.x << ", " << pos.y << "\n";
            auto t = glm::translate(pos);

            Entity *e = m_engine->ShapeCast(m_shape, t, m_mask);
            if (e != nullptr) {
                m_callback(EntityWrapper(e));
            }
            m_hitDone = true;
        }
    }
    return false;
}