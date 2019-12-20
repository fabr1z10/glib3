#include <gfx/components/luahook.h>
#include <iostream>

LuaHook::LuaHook() : Component() {
}

LuaHook::LuaHook(const LuaHook & orig) : Component(orig) {

}

std::shared_ptr<Component> LuaHook::clone() const {
    return std::make_shared<LuaHook>(*this);
}

void LuaHook::addHook (const std::string& id, std::function<void(luabridge::LuaRef)> f) {
    m_callbacks[id] = f;

}

void LuaHook::call(const std::string& id , luabridge::LuaRef args) {
    auto it = m_callbacks.find(id);
    if (it == m_callbacks.end()) {
        std::cerr << "WARNING! callback " << id << " not found.\n";
        return;
    }
    it->second(args);

}