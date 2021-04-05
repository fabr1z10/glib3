#pragma once

#include <monkey/activities/targetactivity.h>
#include <string>

class Turn : public TargetActivity {
public:
    Turn (char dir) : TargetActivity(), m_dir(dir) {}
    Turn (const ITab&);
    ~Turn() override {}
    Turn (int id, char dir) : Turn(dir) {
        SetId(id);
    }
    Turn (const std::string& tag, char dir) : Turn(dir) {
        SetTag(tag);
    }

    void Start() override;
    void Run(float) override {}
private:
    char m_dir;
};
