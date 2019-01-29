//#include <gfx/components/spriteanimator.h>
//#include <gfx/components/renderer.h>
//#include <gfx/error.h>
//
//SpriteAnimator::SpriteAnimator(std::shared_ptr<Model> model) : m_model(model) {
//
//}
//
//void SpriteAnimator::Start() {
//    for (auto& s : m_status) {
//        s.second.SetAnimation(s.second.m_mesh->GetDefaultAnimation());
//    }
//}
//
//void SpriteAnimator::Update(double dt) {
//    for (auto& node : m_status) {
//        Status& status = node.second;
//        status.Update(dt, m_increment);
//    }
//}
//
//void SpriteAnimator::addRenderer(const std::string &name, Renderer * r) {
//    Status status;
//    status.renderer = r;
//    status.frame = 0;
//    status.time = 0;
//    status.loopEnd = false;
//    status.m_mesh = m_model->GetSpriteMesh(name);
//    status.animation = status.m_mesh->GetDefaultAnimation();
//    m_status[name] = status;
//}
//
//
//void SpriteAnimator::SetAnimation (const std::string& anim) {
//    auto& animDetails = m_model->GetAnimDetails(anim);
//    for (auto& a : animDetails) {
//        Status& status = m_status.at(a.first);
//        status.SetAnimation(a.second);
//    }
//
//}
//void SpriteAnimator::SetAnimation (const std::string& node, const std::string& animation) {
//    m_status.at(node).SetAnimation(animation);
//}
//
//std::shared_ptr<AnimatorState> SpriteAnimator::SaveState() {
//    auto ptr = std::make_shared<SpriteAnimatorState>();
//    for (auto& s : m_status) {
//        SimpleAnimatorState state;
//        state.animation = s.second.animation;
//        state.frame = s.second.frame;
//        state.time = s.second.time;
//        state.loopEnd = s.second.loopEnd;
//        ptr->m_states[s.first] = state;
//    }
//    return ptr;
//}
//
//
//void SpriteAnimator::LoadState(std::shared_ptr<AnimatorState> s) {
//    auto& state = *dynamic_cast<SpriteAnimatorState*>(s.get());
//
//    for (auto& st : state.m_states) {
//        auto it = m_status.find(st.first);
//        if (it != m_status.end()) {
//            it->second.SetAnimation(st.second.animation, st.second.frame);
//            it->second.time = st.second.time;
//            it->second.loopEnd = st.second.loopEnd;
//        }
//
//    }
//}
//
//
//bool SpriteAnimator::HasAnimation(const std::string & name) {
//    m_model->HasAnimation(name);
//}
//
//bool SpriteAnimator::HasAnimation(const std::string & node, const std::string& name) {
//    auto it = m_status.find(node);
//    if (it == m_status.end())
//        GLIB_FAIL("Animator doesn't have node " << node);
//    return (it->second.m_mesh->GetAnimInfo(name) != nullptr);
//}
//
