#pragma once

#include <monkey/activity.h>
#include <monkey/listener.h>


class WaitForKey : public Activity, public KeyboardListener {
public:
    WaitForKey(const ITab&);
    void Start() override;
    void Run (float dt) override;
    void KeyCallback(GLFWwindow*, int key, int scancode, int action, int mods) override;

private:
    int m_key;
};
