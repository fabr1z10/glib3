#include "gfx/keyinput.h"
#include <GLFW/glfw3.h>
#include "gfx/renderer.h"
#include "gfx/entity.h"

void KeyInput::Start() {
    m_mesh = dynamic_cast<TextMesh*>(m_entity->GetComponent<Renderer>()->GetMesh());
}




void KeyInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //-std::cout << key << "\n";
    if (action == GLFW_PRESS)
    {
        std::string t = m_mesh->GetText();
        if (key == 259) {
            if (!t.empty()){
                t.pop_back();
            }
        } else {
            t.push_back(key);
        }
        m_mesh->UpdateText(t);
    }
}