#pragma once

#include <gfx/mesh.h>
#include <memory>

class MeshFactory {
public:
    static std::shared_ptr<IMesh> CreateLineMesh (glm::vec2 A, glm::vec2 B, glm::vec4 color, float z= 0.0f);
    static std::shared_ptr<IMesh> CreateLineMesh (glm::vec2 A, glm::vec2 B);
    static std::shared_ptr<IMesh> CreateBoxMesh (float width, float height, glm::vec4 color);




};