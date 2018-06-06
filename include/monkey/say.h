#pragma once

#include <gfx/sequence.h>
#include <glm/glm.hpp>
#include <graph/shape.h>
#include <string>

class Say : public Sequence {
public:
    Say (int id, const std::string& actor, std::vector<std::string>& lines, glm::vec4 color) : Sequence(id), m_actorId{actor}, m_lines{lines}, m_color{color} {}
    void Start() override;
private:
    glm::vec4 m_color;
    std::string m_actorId;
    std::vector<std::string> m_lines;
};
