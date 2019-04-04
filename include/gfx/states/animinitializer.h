//#include <gfx/state.h>
//#include <vector>
//#include <gfx/lua/luawrapper.h>
//#include <gfx/components/info.h>
//
//class Entity;
//class Animator;
//class MultiCollider;
//
//// super basic initializer, just set an animation
//class AnimInitializer : public StateInitializer {
//public:
//    AnimInitializer (const std::string& anim);
//    void Init(Entity* e) override;
//    void Start () override;
//protected:
//    Animator* m_animator;
//    std::string m_anim;
//};
//
//
//class AnimColliderInitializer : public AnimInitializer {
//public:
//    AnimColliderInitializer (const std::string& anim, const std::string& collider);
//    void Init(Entity* e) override;
//    void Start () override;
//private:
//    Entity* m_entity;
//    MultiCollider* m_collider;
//    std::string m_activeCollider;
//};
//
//class LuaAnimColliderInitializer : public StateInitializer {
//public:
//    LuaAnimColliderInitializer (luabridge::LuaRef func);
//    void Init(Entity* e) override;
//    void Start () override;
//private:
//    Animator* m_animator;
//    LuaInfo * m_info;
//    Entity* m_entity;
//    MultiCollider* m_collider;
//    luabridge::LuaRef m_ref;
//};
//
