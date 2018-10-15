#include <gfx/states/animinitializer.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>
#include <gfx/components/multicollider.h>
#include <gfx/entitywrapper.h>

AnimInitializer::AnimInitializer(const std::string &anim) : StateInitializer(), m_anim(anim) {}

void AnimInitializer::Init(Entity* e) {
    m_renderer = e->GetComponent<Renderer>();
}

void AnimInitializer::Start () {
    m_renderer->SetAnimation(m_anim);
}

AnimColliderInitializer::AnimColliderInitializer(const std::string &anim, const std::string& activeCollider) : AnimInitializer(anim), m_activeCollider(activeCollider) {
}

void AnimColliderInitializer::Init(Entity* e) {
    AnimInitializer::Init(e);
    m_entity = e;
    m_collider = dynamic_cast<MultiCollider*>(e->GetComponent<Collider>());
    //for (auto& s : m_activeColliders)
    //    m_colliders.push_back(e->GetNamedChild(s));
}

void AnimColliderInitializer::Start () {

    AnimInitializer::Start();
    m_collider->SwitchTo(m_activeCollider);
}

LuaAnimColliderInitializer::LuaAnimColliderInitializer (luabridge::LuaRef func) : m_ref(func) {

}

void LuaAnimColliderInitializer::Init(Entity* e) {
    m_entity = e;
    m_renderer = e->GetComponent<Renderer>();
    m_collider = dynamic_cast<MultiCollider*>(e->GetComponent<Collider>());
    if (m_collider == nullptr) {
        GLIB_FAIL("Missing comp multicollider");
    }
    m_info = e->GetComponent<LuaInfo>();
}


void LuaAnimColliderInitializer::Start () {
    //std::cout << "Calling ...\n";
    luabridge::LuaRef f = m_ref(m_info->get());
    
    std::string anim=  f["anim"].cast<std::string>();
    std::string collider = f["collider"].cast<std::string>();
    //for (auto& c : m_entity->GetChildren()) {
    //    c->SetActive(false);
    //}


    m_renderer->SetAnimation(anim);
    m_collider->SwitchTo(collider);
    //for (auto& c : m_entity->GetChildren()) {
    //    c->SetActive(false);
    //}
    //luabridge::LuaRef colliders = f["colliders"];
    //for (int i = 0; i < colliders.length(); ++i) {
    //    std::string n = colliders[i+1].cast<std::string>();
    //    m_entity->GetNamedChild(n)->SetActive(true);
    //}

}

