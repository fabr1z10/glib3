#pragma once

#include <string>
#include <gfx/activity.h>

class SetActive : public Activity {
public:
    SetActive(const std::string& tag, bool active);
    void Start() override;
    void Run (float) override {}
private:
    std::string m_tag;
    bool m_active;


};
