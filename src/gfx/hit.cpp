//#include <gfx/hit.h>
//#include <gfx/entity.h>
//#include <gfx/engine.h>
//#include <gfx/components/renderer.h>
//#include <iostream>
//#include <glm/gtx/transform.hpp>
//#include <gfx/entitywrapper.h>
//
//Hit::Hit () : StateBehaviour()
//{}
//
//HitCollision::HitCollision (int frame, std::shared_ptr<Shape> collisionShape, glm::vec2 offset, int mask, luabridge::LuaRef callback) :
//Hit(), m_shape(collisionShape), m_hitDone{false}, m_callback(callback)
//{}
//
//void Hit::Init(Entity* e) {
//    StateBehaviour::Init(e);
//    m_renderer = e->GetComponent<Renderer>();
//}
//
//bool Hit::Run(double) {
//
////    if (m_renderer->GetLoopCount() > 0) {
////        m_nextState = "walk";
////        return true;
////    }
//    return false;
//}
//
//
//void HitCollision::Init(Entity* e) {
//    Hit::Init(e);
//    m_engine = Engine::get().GetRunner<CollisionEngine>();
//    m_entity = e;
//}
//
//
//
//void HitCollision::ResetState() {
//    m_hitDone = false;
//}
//
//
//
//bool HitCollision::Run(double dt) {
//    return false;
////    if (Hit::Run(dt))
////        return true;
////
////    if (!m_hitDone) {
////       //  int f = m_renderer->GetFrame();
////        if (f == m_frame) {
////            glm::vec3 pos = m_entity->GetPosition();
////            //std::cout <<" **** hit ****\n";
////            //std::cout << "character at position = " << pos.x << ", " << pos.y << "\n";
////            bool flip = m_entity->GetFlipX();
////            pos.x += flip ? -m_offset.x - m_shape->getBounds().GetSize().x : m_offset.x;
////            pos.y += m_offset.y;
////            //std::cout << "collider at position = " << pos.x << ", " << pos.y << "\n";
////            auto t = glm::translate(pos);
////
////            Entity *e = m_engine->ShapeCast(m_shape, t, m_mask);
////            // avoid collision with oneself
////            if (e != nullptr && e->GetParent() != m_entity) {
////                // I hit something, passing the collision box and the entity hitting
////                m_callback(EntityWrapper(e), EntityWrapper(m_entity));
////            }
////            m_hitDone = true;
////        }
////    }
////    return false;
//}
