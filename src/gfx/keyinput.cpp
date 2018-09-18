#include "gfx/keyinput.h"
#include <GLFW/glfw3.h>
#include "gfx/renderer.h"
#include "gfx/entity.h"
#include <iostream>

void KeyInput::Start() {
    m_mesh = dynamic_cast<TextMesh*>(m_entity->GetComponent<Renderer>()->GetMesh());
}




void KeyInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << key << "\n";
    if (action == GLFW_PRESS)
    {
        std::string t = m_mesh->GetText();
        if (key == GLFW_KEY_BACKSPACE) {
            if (!t.empty()){
                t.pop_back();
            }
        } else {
            if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
                if (mods == GLFW_MOD_SHIFT) {
                    t.push_back(key);
                } else {
                    t.push_back(key+32);
                }
            } else {
                t.push_back(key);
            }

        }
        m_mesh->UpdateText(t);
    }
}