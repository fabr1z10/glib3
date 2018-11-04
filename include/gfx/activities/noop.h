#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class NoOp : public Activity {
public:
    NoOp() : Activity() {}
    void Start() {
        SetComplete();
    }
    void Run (float dt) {}
};