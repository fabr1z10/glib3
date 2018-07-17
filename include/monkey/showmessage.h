#pragma once

#include <gfx/activity.h>
#include <glm/glm.hpp>
#include <gfx/enums.h>
#include <string>
#include <gfx/camera.h>

class Entity;

class ShowMessage : public Activity {
public:
    ShowMessage(
            int id,
            const std::string& message,
            const std::string& font,
            const std::string& actor,
            float size,
            glm::vec4 color,
            glm::vec4 outlineColor,
            TextAlignment align,
            float time,
            glm::vec2 offset) : Activity(id), m_generatedEntity{nullptr}, m_message{message}, m_time{time}, m_font{font}, m_actor{actor}, m_size{size},
                                m_align{align}, m_color{color}, m_outlineColor{outlineColor}, m_offset{offset} {}
    ShowMessage(
            int id,
            const std::string& message,
            const std::string& font,
            glm::vec3 pos,
            float size,
            glm::vec4 color,
            glm::vec4 outlineColor,
            TextAlignment align,
            float time,
            glm::vec2 offset) : Activity(id), m_generatedEntity{nullptr}, m_message{message}, m_time{time}, m_font{font}, m_pos{pos}, m_size{size},
                                m_align{align}, m_color{color}, m_outlineColor{outlineColor}, m_offset{offset} {}
    virtual ~ShowMessage();
    void Start() override;
    void Run (float dt) override;
private:
    TextAlignment m_align;
    float m_elapsedTime;
    float m_size;
    glm::vec2 m_offset;
    glm::vec3 m_pos;
    glm::vec4 m_color;
    glm::vec4 m_outlineColor;
    float m_time;
    std::string m_actor;
    std::string m_message;
    std::string m_font;
    Entity* m_generatedEntity;
    OrthographicCamera* m_mainCam;
};
