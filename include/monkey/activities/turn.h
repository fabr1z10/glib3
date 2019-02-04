#pragma once

#include <gfx/activity.h>
#include <string>

class Turn : public Activity {
public:
    Turn (const std::string& actor, char dir) :
            Activity(), m_actorId(actor), m_dir(dir) {}
    void Start() override;
    void Run(float) override {}

private:
    std::string m_actorId;
    char m_dir;
};
