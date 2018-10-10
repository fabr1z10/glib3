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

AnimColliderInitializer::AnimColliderInitializer(const std::string &anim, const std::vector<std::string> &) : AnimInitializer(anim) {

}

void AnimColliderInitializer::Init(Entity* e) {
    AnimInitializer::Init(e);
    m_colliderContainer = e->GetNamedChild("colliders");
    for (auto& s : m_activeColliders)
        m_colliders.push_back(m_colliderContainer->GetNamedChild(s));
}

void AnimColliderInitializer::Start () {
    AnimInitializer::Start();
    if (m_colliderContainer != nullptr) {
        auto &v = m_colliderContainer->GetChildren();
        for (auto &c : v)
            c->SetActive(false);
        for (auto &c : m_colliders)
            c->SetActive(true);
    }
}




