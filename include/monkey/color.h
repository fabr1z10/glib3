#pragma once

#include <glm/glm.hpp>



class Color {
public:
    Color (int r, int g, int b, int a = 255) : m_color(r/255.0f, g/255.0f, b/255.0f, a/255.0f) {}
    glm::vec4 Get() {
        return m_color;
    }
private:
    glm::vec4 m_color;
};

namespace color {
    static const Color WHITE = Color(255, 255, 255);
    static const Color BLACK = Color(0, 0, 0);

}