#pragma once

#include <string>
#include <monkey/activity.h>

class EnableBlock : public Activity {
public:
    EnableBlock(const std::string& id, int wall, bool active) : Activity(), m_id(id), m_wall{wall}, m_active{active} {}
    EnableBlock(const LuaTable&);
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_id;
    int m_wall;
    bool m_active;
};
