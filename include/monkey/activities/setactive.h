#pragma once

#include <string>
#include <monkey/activity.h>

class SetActive : public Activity {
public:
    SetActive(const std::string& tag, bool active);
    SetActive(const LuaTable&);
    void Start() override;
    void Run (float) override {}
private:
    std::string m_tag;
    bool m_active;


};
