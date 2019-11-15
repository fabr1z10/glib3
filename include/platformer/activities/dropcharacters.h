#pragma once

#include <gfx/activities/targetactivity.h>


class DropCharacters : public TargetActivity {
public:
    DropCharacters();
    void Start() override;
    void Run (float dt) override {}
};
