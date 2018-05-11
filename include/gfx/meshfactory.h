#pragma once

#include <gfx/mesh.h>
#include <memory>

class MeshFactory {
public:
    static std::shared_ptr<IMesh> CreateLineMesh (glm::vec2 A, glm::vec2 B, glm::vec4 color);
    static std::shared_ptr<IMesh> CreateBoxMesh (float width, float height, glm::vec4 color);




};