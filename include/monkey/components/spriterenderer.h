#pragma once

#include <monkey/components/animrenderer.h>
#include <monkey/model/spritemodel.h>

class SpriteRenderer : public AnimationRenderer {
public:
    SpriteRenderer(std::shared_ptr<Model>);
    void Update(double) override;
    void Draw(Shader*) override;
    void setAnimation(const std::string&) override;
    int getFrame() const;
    std::type_index GetType() override;

private:
    int m_frame;
    SpriteModel* m_spriteModel;
    AnimationInfo* m_currentAnimInfo;
    int m_frameCount;
    double m_time;
};

inline int SpriteRenderer::getFrame() const {
    return m_frame;
}