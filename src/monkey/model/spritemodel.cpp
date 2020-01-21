#include <monkey/model/spritemodel.h>
#include <monkey/entity.h>
#include <iostream>
#include <monkey/error.h>

std::vector<std::string> SpriteModel::GetAnimations() const {
    const auto& m = m_mesh->GetAnimInfo();
    std::vector<std::string> animations;
    for (auto& a : m) {
        animations.push_back(a.first);
    }
    return animations;
}

std::string SpriteModel::GetDefaultAnimation() const {
    return m_mesh->GetDefaultAnimation();
}


ShaderType SpriteModel::GetShaderType() const {
    return TEXTURE_SHADER;
}

const AnimInfo* SpriteModel::GetAnimInfo() const {
    return m_mesh->GetAnimInfo(m_mesh->GetDefaultAnimation());
}

const AnimInfo* SpriteModel::GetAnimInfo(const std::string& anim) const {
    return m_mesh->GetAnimInfo(anim);
}

void SpriteModel::Draw(Shader* shader, int offset, int count) {
    m_mesh->Draw(shader, offset, count);
}
