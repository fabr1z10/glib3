#include <gfx/model/skeletalmodel.h>
#include <stack>
#include <gfx/engine.h>
#include <glm/gtx/transform.hpp>
#include <gfx/math/geom.h>

Bone::Bone() : transform(glm::mat4(1.0f)) {}


void Bone::setAngle(float angle) {
    glm::mat4 m = glm::rotate(deg2rad * angle, glm::vec3(0,0,1));
    transform[1][0] = m[1][0];
    transform[1][1] = m[1][1];
}

Bounds SkeletalModel::GetBounds() const {
    // TODO
    return Bounds(glm::vec3(-1000.0f), glm::vec3(1000.0f));
}

ShaderType SkeletalModel::GetShaderType() const {
    return TEXTURE_SHADER;
}

std::vector<std::string> SkeletalModel::GetAnimations() const {
    return std::vector<std::string>();
}

std::string SkeletalModel::GetDefaultAnimation() const {
    return m_defaultAnimation;
}

void SkeletalModel::Draw(Shader* shader, const std::vector<float>& angles) {
    // do a depth-first scan of the sk starting from the root
    std::stack<Bone*> s;
    auto re = Engine::get().GetRenderingEngine();
    auto& worldTransform = re->getModelViewMatrix();
    std::stack<glm::mat4> tm;
    s.push(m_root);
    tm.push(worldTransform);
    glm::mat4 viewMatrix = re->getCurrentCamera()->m_viewMatrix;

    while (!s.empty()) {
        // get the top
        auto& top = s.top();
        glm::mat4 nt = top->transform;
        // apply the angle of this node
        float angle = angles[top->id];

        glm::mat4 m = glm::rotate(deg2rad * angle, glm::vec3(0,0,1));
        glm::mat4 lpos = glm::translate(glm::vec3(top->pos, 0.0f));
        glm::mat4 local = lpos*m*glm::translate(glm::vec3(-top->center, top->z));
//        nt[1][0] = m[1][0];
//        nt[1][1] = m[1][1];
//        nt[0][0] = m[0][0];
//        nt[0][1] = m[0][1];

        glm::mat4 nodeTransform = (tm.top() * local);
        glm::mat4 mvm = viewMatrix * nodeTransform;


        // draw this node
        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
        top->mesh->Draw(shader, 0, 0);
        // pop ...
        s.pop();
        tm.pop();
        // ... and push the children

        for (const auto& child : top->children) {
            tm.push(nodeTransform);
            s.push(child);
        }
    }

}

Bone& SkeletalModel::getBone (const std::string& id) {
    return *(m_boneMap.at(id));
}

void SkeletalModel::addBone(const std::string& id, std::unique_ptr<Bone> bone, const std::string& parent) {

    m_bones.push_back(std::move(bone));
    m_boneMap.insert(std::make_pair(id, m_bones.back().get()));
    if (parent.empty()) {
        m_root = m_bones.back().get();
    } else {
        getBone(parent).children.push_back(m_bones.back().get());
    }
}

void SkeletalModel::addAnimation(const std::string& name, std::shared_ptr<SkeletalAnimation> anim) {
    if (m_defaultAnimation.empty()) m_defaultAnimation = name;
    m_animations.insert(std::make_pair(name, anim));
}

SkeletalAnimation* SkeletalModel::getAnimation(const std::string &id) {
    return m_animations.at(id).get();
}