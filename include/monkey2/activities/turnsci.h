#pragma once

#include <gfx/activities/targetactivity.h>
#include <string>

class TurnSci : public TargetActivity {
public:
    TurnSci (char dir) : TargetActivity(), m_dir(dir) {}
    ~TurnSci() override { std::cerr << "clearing turn\n"; }
    TurnSci (int id, char dir) : TurnSci(dir) {
        SetId(id);
    }
    TurnSci (const std::string& tag, char dir) : TurnSci(dir) {
        SetTag(tag);
    }

    void Start() override;
    void Run(float) override {}
private:
    char m_dir;
};
