//#include <monkey/components/scaling.h>
//#include <monkey/entity.h>
//#include <monkey/components/renderer.h>
//#include <monkey/engine.h>
//#include <monkey/components/walkarea.h>
//
//void ScalingDepthComponent::Start() {
//    m_renderer = m_entity->GetComponent<Renderer>();
//    // get the walkarea
//    m_walkArea = Engine::get().GetRef<WalkArea>("walkarea");
//}
//
//void ScalingDepthComponent::Update(double) {
//
//    glm::vec2 pos(m_entity->GetPosition());
//
//    if (m_prevPos != pos) {
//        float depth = m_walkArea->GetDepth (pos.x, pos.y);
//        float scale = m_walkArea->GetScale (pos.x, pos.y);
//        m_entity->SetPosition(glm::vec3(pos, depth));
//        m_renderer->SetScale(scale);
//        m_prevPos = pos;
//    }
//}