#pragma once

#include <monkey/activity.h>
#include <monkey/entity.h>

class NoOp : public Activity {
public:
    NoOp() : Activity() {}
    NoOp (const ITab&) {}
    void Start() {
        SetComplete();
    }
    void Run (float dt) {}
};