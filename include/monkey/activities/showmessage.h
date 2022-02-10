#pragma once

#include <monkey/activity.h>
#include <glm/glm.hpp>
#include <monkey/enums.h>
#include <string>
#include <monkey/camera.h>
#include <monkey/listener.h>

class Entity;

class __attribute__ ((visibility ("default"))) ShowMessage : public Activity {
public:
    ShowMessage(const ITab&);
    ShowMessage(
            const std::string& message,
            const std::string& font,
            int actor,
            float size,
            glm::vec4 color,
            glm::vec4 outlineColor,
            TextAlignment align,
            float time,
            glm::vec2 offset) : Activity(), m_generatedEntity{nullptr}, m_message{message}, m_time{time}, m_font{font}, m_actor{actor}, m_size{size},
                                m_align{align}, m_color{color}, m_outlineColor{outlineColor}, m_offset{offset}, m_maxWidth{1000.0f} {}
    ShowMessage(
            const std::string& message,
            const std::string& font,
            glm::vec3 pos,
            float size,
            glm::vec4 color,
            glm::vec4 outlineColor,
            TextAlignment align,
            float time,
            glm::vec2 offset) : Activity(), m_generatedEntity{nullptr}, m_message{message}, m_time{time}, m_font{font}, m_pos{pos}, m_size{size},
                                m_align{align}, m_color{color}, m_outlineColor{outlineColor}, m_offset{offset}, m_actor(-1), m_maxWidth{1000.0f} {}
    virtual ~ShowMessage();
    void Start() override;
    void Run (float dt) override;
    void NotifySuspend() override;
private:
	std::shared_ptr<Entity> makeBorder(float, float, float, float, float, float);
    TextAlignment m_align;
    float m_elapsedTime;
    float m_size;
    glm::vec2 m_offset;
    glm::vec3 m_pos;
    glm::vec4 m_color;
    glm::vec4 m_outlineColor;
    float m_time;
    int m_actor;
    std::string m_message;
    std::string m_font;
    std::shared_ptr<Entity> m_generatedEntity;
    OrthographicCamera* m_mainCam;
    bool m_endOnClick;
    std::shared_ptr<MouseListener> m_mouseListener;
    bool m_outline;
    // box stuff
    bool m_box;
    glm::vec2 m_padding;
    std::string m_innerTexture;
    std::string m_borderTexture;
    float m_maxWidth;
    float m_outlineThickness;
};
