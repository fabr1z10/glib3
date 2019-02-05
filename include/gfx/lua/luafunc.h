#pragma once

#include <gfx/lua/luawrapper.h>
#include <gfx/error.h>
#include <memory>

class LuaFunction {
public:
    LuaFunction(luabridge::LuaRef ref) : m_ref(ref) {}
    void execute() {
        try {
            m_ref();
        } catch (luabridge::LuaException const& e) {
            GLIB_FAIL(e.what());
        }
    }

private:
    luabridge::LuaRef m_ref;
};

