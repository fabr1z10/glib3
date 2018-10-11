#include <gfx/state.h>
#include <vector>
#include <gfx/lua/luawrapper.h>
#include <gfx/components/info.h>

class Entity;
class Renderer;

// super basic initializer, just set an animation
class AnimInitializer : public StateInitializer {
public:
    AnimInitializer (const std::string& anim);
    void Init(Entity* e) override;
    void Start () override;
protected:
    Renderer* m_renderer;
    std::string m_anim;
};


class AnimColliderInitializer : public AnimInitializer {
public:
    AnimColliderInitializer (const std::string& anim, const std::vector<std::string>&);
    void Init(Entity* e) override;
    void Start () override;
private:
    Entity* m_entity;
    std::vector<Entity*> m_colliders;
    std::vector<std::string> m_activeColliders;
};

class LuaAnimColliderInitializer : public StateInitializer {
public:
    LuaAnimColliderInitializer (luabridge::LuaRef func);
    void Init(Entity* e) override;
    void Start () override;
private:
    Renderer* m_renderer;
    LuaInfo * m_info;
    Entity* m_entity;
    luabridge::LuaRef m_ref;
};