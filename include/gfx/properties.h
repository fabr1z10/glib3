#pragma once

#include <gfx/component.h>
#include <gfx/lua/luawrapper.h>
#include <memory>
#include <unordered_map>

class IAccessor {
public:
    virtual luabridge::LuaRef get() = 0;
    virtual void set(luabridge::LuaRef) = 0;
    virtual bool isReadOnly() const = 0;
};

template <typename T>
class Accessor : public IAccessor {
public:
    Accessor(T* ref, bool readonly) : m_ref(ref), m_readOnly(readonly) {}
    luabridge::LuaRef get() override {
        luabridge::LuaRef v(LuaWrapper::L, *m_ref);
        return v;
    }
    void set(luabridge::LuaRef value) override {
        m_ref = value;
    }
    bool isReadOnly() const override {
        return m_readOnly;
    }
private:
    T* m_ref;
    bool m_readOnly;
};


// a properties component is a holder for any additional stuff you want to add to an entity
// It allows you to get/set stuff in LUA and also to add any additional items u want.
class Properties : public Component {
public:
    Properties() : Component(), m_additionalProperties(nullptr) {}
    Properties(const Properties&);
    std::shared_ptr<Component> clone() const override;
    virtual ~Properties() = default;
    luabridge::LuaRef get(const std::string&);
    void set(const std::string& key, luabridge::LuaRef value);
    void addAdditionalProps(luabridge::LuaRef ref);
    void Start() override {}
    void Update(double) override  {}
protected:
    std::shared_ptr<luabridge::LuaRef> m_additionalProperties;
    std::unordered_map<std::string, std::unique_ptr<IAccessor>> m_getters;
};