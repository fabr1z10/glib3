#include <monkey/skeletal/skmesh.h>

void SkeletalMesh::addJoint(int id, int parent, glm::vec2 pos) {
    m_joints[id] = SkeletalJoint{id, parent, pos};
}