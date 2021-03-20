#pragma once

#include <monkey/texturedmesh.h>

struct SkeletalJoint {
    int id;
    int parent;
    glm::vec2 pos;
};

class SkeletalMesh : public TexturedMesh<VertexSkeletal> {
public:
    explicit SkeletalMesh(const std::string& filename) : TexturedMesh<VertexSkeletal>(SKELETAL_SHADER, GL_TRIANGLES, filename) {}
    void addJoint (int id, int parent, glm::vec2 pos);
private:
    std::unordered_map<int, SkeletalJoint> m_joints;
};