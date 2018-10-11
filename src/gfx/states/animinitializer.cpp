#include <gfx/states/animinitializer.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>


AnimInitializer::AnimInitializer(const std::string &anim) : StateInitializer(), m_anim(anim) {}

void AnimInitializer::Init(Entity* e) {
    m_renderer = e->GetComponent<Renderer>();
}

void AnimInitializer::Start () {
    m_renderer->SetAnimation(m_anim);
}

AnimColliderInitializer::AnimColliderInitializer(const std::string &anim, const std::vector<std::string> & colliders) : AnimInitializer(anim),
m_activeColliders(colliders) {

}

void AnimColliderInitializer::Init(Entity* e) {

    AnimInitializer::Init(e);
    m_entity = e;
    for (auto& s : m_activeColliders)
        m_colliders.push_back(e->GetNamedChild(s));
}

void AnimColliderInitializer::Start () {

    AnimInitializer::Start();
    for (auto& c : m_entity->GetChildren()) {
        c->SetActive(false);
    }
    for (auto& c : m_colliders) {
        c->SetActive(true);
    }

//    auto &v = m_entity->GetChildren();
//    for (auto &c : v)
//        c->SetActive(false);
//    for (auto &c : m_colliders)
//        c->SetActive(true);

}




