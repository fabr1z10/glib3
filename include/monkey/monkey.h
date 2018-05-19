#pragma once

#include <monkey/luatable.h>
#include <gfx/singleton.h>
#include <unordered_map>

class Monkey : public Singleton<Monkey> {
public:
    LuaTable& operator[] (const std::string& key);
    void AddTable (const std::string& name);
    Monkey();
    void Start();
    
private:
    std::unordered_map<std::string, LuaTable> m_tables;
};
