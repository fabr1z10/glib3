#pragma once

#include <monkey/activities/sequence.h>
#include <glm/glm.hpp>
#include <monkey/math/shape.h>
#include <string>

class Say : public Sequence {
public:
    Say (const LuaTable&);
    Say (const ITable&);
    Say (int actor, std::vector<std::string>& lines, glm::vec4 color, glm::vec2 offset) :
            Sequence(), m_actorId{actor}, m_lines{lines}, m_color{color}, m_offset{offset}, m_noAnim{false} {}
    Say (const std::string& tag, std::vector<std::string>& lines, glm::vec4 color, glm::vec2 offset) :
            Sequence(), m_tag {tag}, m_lines{lines}, m_color{color}, m_offset{offset}, m_noAnim{false} {}
    void Start() override;
    // say should also be able to handle override on anim start and anim end
    void SetAnimationStart(const std::string&);
    void SetAnimationEnd(const std::string&);
    void SetNoAnim(bool);
private:
    glm::vec2 m_offset;
    std::string m_animStart;
    std::string m_animEnd;
    std::string m_fontId;
    glm::vec4 m_color;
    int m_actorId;
    std::string m_tag;
    std::vector<std::string> m_lines;
    bool m_noAnim;
};

inline void Say::SetAnimationEnd(const std::string & animEnd) {
    m_animEnd = animEnd;


}


inline void Say::SetAnimationStart(const std::string & animStart) {
    m_animStart  = animStart;

}

inline void Say::SetNoAnim(bool value) {
    m_noAnim = value;
}
