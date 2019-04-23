//#include <gfx/compositemodel.h>
//#include <gfx/error.h>
//#include <gfx/entity.h>
//
//
//void CompositeModelStatus::Init(Entity* entity) {
//    m_entity = entity;
//    DepthFirstIterator<Entity> iterator(entity);
//    for (; !iterator.end();  ++iterator) {
//        auto it = m_componentStates.find(iterator->GetName());
//        if (it != m_componentStates.end()) {
//            it->second->Init(&(*iterator));
//        }
//    }
//    SetAnimation(m_model->GetDefaultAnimation(), true);
//
//}
//const std::vector<AnimationDefinition>& CompositeModel::GetAnimationDefinition(const std::string& name) const {
//    auto it = m_animInfo.find(name);
//    if (it == m_animInfo.end())
//        GLIB_FAIL("Unkwnon animation " << name);
//    return it->second;
//}
//
//std::unique_ptr<IModelStatus> CompositeModel::GetModelStatus() {
//    auto p = std::unique_ptr<CompositeModelStatus>(new CompositeModelStatus(this));
//    for (auto& component : m_components) {
//        std::unique_ptr<IModelStatus> sms = component.second.model->GetModelStatus();
//        SimpleModelStatus status(*(component.second.model->GetMesh().get()));
//        p->AddComponent(component.first, std::move(sms));
//
//    }
//    return p;
//}
//
//// the composite status update just updates all components
//void CompositeModelStatus::Update(double dt) {
//
//    for (auto& c : m_componentStates) {
//        c.second->Update(dt);
//    }
//}
//
//void CompositeModelStatus::AdvanceFrame(int inc) {
//    for (auto& c : m_componentStates) {
//        c.second->AdvanceFrame(inc);
//    }
//}
//
//void CompositeModelStatus::SetAnimation(const std::string &anim, bool fwd) {
//    auto animDef = m_model->GetAnimationDefinition(anim);
//    for (auto& a : animDef) {
//        auto sm = m_componentStates.at(a.node).get();
//        sm->SetAnimation(a.anim, fwd);
//        sm->GetEntity()->SetPosition(a.pos);
//    }
//}
//
//bool CompositeModelStatus::IsAnimComplete() const {
//    for (auto& a : m_componentStates) {
//        if (!a.second->IsAnimComplete())
//            return false;
//    }
//    return true;
//}
//
//std::vector<std::string> CompositeModel::GetAnimations() {
//    std::vector<std::string> animations;
//    for (auto& a : m_animInfo) {
//        animations.push_back(a.first);
//    }
//    return animations;
//}
