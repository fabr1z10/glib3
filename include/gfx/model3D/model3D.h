#pragma once

#include <gfx/mesh.h>
#include <memory>

class Model3DFactory {
public:
    static std::shared_ptr<IMesh> CreatePlane (float width, float depth, glm::vec4);
    static std::shared_ptr<IMesh> CreateBox (float width, float depth, float height, glm::vec4);
};

