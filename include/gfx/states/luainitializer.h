#include <gfx/state.h>
#include <vector>
#include <gfx/lua/luawrapper.h>

class Entity;
class Renderer;

// will call a custom LUA function when state starts
class LuaInitializer : public StateInitializer {
public:
    LuaInitializer (luabridge::LuaRef ref);
    void Init(Entity* e) override;
    void Start () override;
protected:
    Entity* m_entity;
    luabridge::LuaRef m_ref;
};

