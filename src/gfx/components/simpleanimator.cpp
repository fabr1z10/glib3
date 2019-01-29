//#include <gfx/components/simpleanimator.h>
//#include <gfx/components/renderer.h>
//#include <gfx/error.h>
//#include <gfx/entity.h>
//
//SimpleAnimator::SimpleAnimator(std::shared_ptr<IMesh> mesh)  {
//    m_mesh = std::dynamic_pointer_cast<SpriteMesh>(mesh);
//    m_status.m_mesh = m_mesh.get();
//}
//
//void SimpleAnimator::Start() {
//    m_status.renderer = m_entity->GetComponent<Renderer>();
//    if (m_status.renderer == nullptr) {
//        GLIB_FAIL("SimpleAnimator requires a renderer component");
//    }
//    m_status.SetAnimation(m_mesh->GetDefaultAnimation());
//}
//
//void SimpleAnimator::Update(double dt) {
//    m_status.Update(dt, m_increment);
//}
//
//
//void SimpleAnimator::SetAnimation(const std::string &anim) {
//    m_status.SetAnimation(anim);
//}
//
//void SimpleAnimator::SetAnimation(const std::string&, const std::string& anim) {
//    SetAnimation(anim);
//
//}
//
//std::shared_ptr<AnimatorState> SimpleAnimator::SaveState() {
//    auto ptr = std::make_shared<SimpleAnimatorState>();
//    ptr->animation = m_status.animation;
//    ptr->frame = m_status.frame;
//    ptr->loopEnd = m_status.loopEnd;
//    ptr->time = m_status.time;
//    return ptr;
//}
//
//void SimpleAnimator::LoadState(std::shared_ptr<AnimatorState> s) {
//    auto state = dynamic_cast<SimpleAnimatorState*>(s.get());
//    m_status.SetAnimation(state->animation, m_status.frame);
//    m_status.time = state->time;
//    m_status.loopEnd = state->loopEnd;
//}