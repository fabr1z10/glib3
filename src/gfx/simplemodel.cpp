#include <gfx/simplemodel.h>
#include <gfx/entity.h>
#include <iostream>
#include <gfx/error.h>

std::vector<std::string> SimpleModel::GetAnimations() {
    const auto& m = m_mesh->GetAnimInfo();
    std::vector<std::string> animations;
    for (auto& a : m) {
        animations.push_back(a.first);
    }
    return animations;
}
