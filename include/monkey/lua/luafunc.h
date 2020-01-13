#pragma once

#include <monkey/lua/luawrapper.h>
#include <monkey/error.h>
#include <memory>

class LuaFunction {
public:
    LuaFunction(luabridge::LuaRef ref) : m_ref(ref) {}
    template<typename... Args>
    void execute(Args... args) const {
        try {
            m_ref(args...);
        } catch (luabridge::LuaException const& e) {
            GLIB_FAIL(e.what());
        }
    }

private:
    luabridge::LuaRef m_ref;
};

