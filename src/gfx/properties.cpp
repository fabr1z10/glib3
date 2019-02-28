#include <gfx/properties.h>
#include <gfx/error.h>

Properties::Properties(const Properties & orig) : Component(orig) {
    m_additionalProperties = orig.m_additionalProperties;
}

std::shared_ptr<Component> Properties::clone() const {
    return std::make_shared<Properties>(*this);

}

void Properties::addAdditionalProps(luabridge::LuaRef ref) {
    m_additionalProperties = std::make_shared<luabridge::LuaRef>(ref);
}


luabridge::LuaRef Properties::get(const std::string & key) {
    auto it = m_getters.find(key);
    if (it == m_getters.end()) {
        if (m_additionalProperties == nullptr) {
            GLIB_FAIL("Don't know property: " << key);
        }
        luabridge::LuaRef value = (*m_additionalProperties.get())[key.c_str()];
        if (value.isNil()) {
            GLIB_FAIL("Don't know property: " << key);
        }
        return value;
    }
    return it->second->get();
}

void Properties::set(const std::string &key, luabridge::LuaRef value) {
    auto it = m_getters.find(key);
    if (it == m_getters.end()) {

    }
    if (it->second->isReadOnly()) {
        GLIB_FAIL("Attempting to write a read-only property: " << key);
    }
    it->second->set(value);
}