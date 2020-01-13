//#include <monkey/aiwalk.h>
//#include <monkey/engine.h>
//#include <monkey/components/animator.h>
//#include <monkey/random.h>
//
//void AIWalk::Init(Entity* e) {
//    m_entity = e;
//    m_target = Engine::get().GetRef<Entity>(m_targetId);
//    m_animator = e->GetComponent<Animator>();
//    m_eps = 0.1;
//    m_offset = glm::vec2(40, 0);
//}
//
//
//bool AIWalk::Run(double dt) {
//    glm::vec3 targetPos = m_target->GetPosition();
//    glm::vec3 enemyPos = m_entity->GetPosition();
//    float targetX = targetPos.x;
//    float enemyX = m_entity->GetPosition().x;
//    m_entity->SetFlipX(enemyX > targetX);
//    glm::vec2 pos (targetPos.x + m_offset.x, targetPos.y + m_offset.y);
//    glm::vec2 dist = pos - glm::vec2(enemyPos);
//    if (dist.x*dist.x + dist.y*dist.y > m_eps) {
//        dist = glm::normalize(dist);
//        enemyPos += (m_speed * static_cast<float>(dt)) * glm::vec3(dist, 0.0f);
//        m_entity->SetPosition(enemyPos);
//        m_animator->SetAnimation("walk");
//    } else {
//        m_animator->SetAnimation("idle");
//        m_nextState = "idle";
//        return true;
//
//    }
//    return false;
//}
