#include <gfx/model/skeletalmodel.h>
#include <stack>
#include <gfx/engine.h>
#include <glm/gtx/transform.hpp>
#include <gfx/math/geom.h>

Bone::Bone() {}



Bounds SkeletalModel::GetBounds() const {
    // TODO
    return Bounds(glm::vec3(-1000.0f), glm::vec3(1000.0f));
}

ShaderType SkeletalModel::GetShaderType() const {
    return TEXTURE_SHADER;
}

std::vector<std::string> SkeletalModel::GetAnimations() const {
    std::vector<std::string> anims;
    for (const auto& m : m_animations) anims.push_back(m.first);
    return anims;
}

std::string SkeletalModel::GetDefaultAnimation() const {
    return m_defaultAnimation;
}

Bounds SkeletalModel::getBoundingBox(const std::vector<float> &angles) {

}

void SkeletalModel::Draw(Shader* shader, const std::vector<float>& angles) {
    // do a depth-first scan of the sk starting from the root
    std::stack<Bone*> s;
    auto re = Engine::get().GetRenderingEngine();
    auto& worldTransform = re->getModelViewMatrix();
    std::stack<glm::mat4> tm;
    s.push(m_root);
    tm.push(glm::mat4(1.0f));
    glm::mat4 viewMatrix = re->getCurrentCamera()->m_viewMatrix;
    m_dynamicBounds = Bounds();

    // find node transforms
    std::vector<glm::mat4> a1;
    std::vector<Bone*> a2;
    while (!s.empty()) {
        // get the top
        auto& top = s.top();

        //glm::mat4 nt = top->transform;
        // apply the angle of this node
        float angle = angles[top->id];

        glm::mat4 m = glm::scale(glm::vec3(top->scale)) * glm::rotate(deg2rad * angle, glm::vec3(0,0,1));
        glm::mat4 lpos = glm::translate(glm::vec3(top->pos, 0.0f));
        glm::mat4 local = lpos*m*glm::translate(glm::vec3(-top->center, top->z));
//        nt[1][0] = m[1][0];
//        nt[1][1] = m[1][1];
//        nt[0][0] = m[0][0];
//        nt[0][1] = m[0][1];

        glm::mat4 nodeTransform = (tm.top() * local);
        Bounds boneBounds = top->mesh->GetBounds();
        boneBounds.Transform(nodeTransform);

        m_dynamicBounds.ExpandWith(boneBounds);

        a1.push_back(nodeTransform);
        a2.push_back(top);

//        glm::mat4 mvm = viewMatrix * nodeTransform;
//
//
//        // draw this node
//        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
//        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
//        top->mesh->Draw(shader, 0, 0);
        // pop ...
        s.pop();
        tm.pop();
        // ... and push the children

        for (const auto& child : top->children) {
            tm.push(nodeTransform);
            s.push(child);
        }
    }

    glm::mat4 shift = glm::translate(glm::vec3(0,-m_dynamicBounds.min.y,0));
    //std::cout << m_maxBounds.min.y << ", " << m_dynamicBounds.min.y << "\n";
    worldTransform *= shift;
    for (size_t i = 0; i< a1.size(); ++i) {
        glm::mat4 mvm = viewMatrix * worldTransform * a1[i];
        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
        a2[i]->mesh->Draw(shader, 0, 0);
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

void SkeletalModel::setDefaultBounds(float width, float height, glm::vec2 offset) {
    m_defaultBounds = std::make_shared<Rect>(width, height, glm::vec3(offset, 0.0f));
    m_maxBounds.ExpandWith(m_defaultBounds->getBounds());

}

Shape* SkeletalModel::getBounds(const std::string &anim) {
    return m_defaultBounds.get();
}
std::vector<Bounds> SkeletalModel::getAllBounds() const {
    std::vector<Bounds> bounds;
    bounds.push_back(m_defaultBounds->getBounds());
    for (const auto& a : m_animSpecificBounds) bounds.push_back(a.second->getBounds());
    for (const auto& b : m_attackInfo) {
        bounds.push_back(b.second.shape->getBounds());
    }
    return bounds;

}
void SkeletalModel::addAnimation(const std::string& name, std::shared_ptr<SkeletalAnimation> anim) {
    if (m_defaultAnimation.empty()) m_defaultAnimation = name;
    m_animations.insert(std::make_pair(name, anim));
    //auto shape = anim->getBounds();
//    if (shape != nullptr ) {
//        m_maxBounds.ExpandWith(shape->getBounds());
//    }
}

float SkeletalModel::addAttack(const std::string &anim, float t, glm::vec4 box) {
    m_attackInfo[anim] = SkeletalAttackInfo{t, std::make_shared<Rect>(box[2], box[3], glm::vec3(box[0], box[1], 0.0f))};
}

SkeletalAttackInfo* SkeletalModel::hasAttack(const std::string &anim, float t0, float t1) {
    auto it = m_attackInfo.find(anim);
    if (it == m_attackInfo.end()) return nullptr;
    if (it->second.t >= t0 && it->second.t <= t1)
        return &(it->second);
    return nullptr;
}

SkeletalAnimation* SkeletalModel::getAnimation(const std::string &id) {
    return m_animations.at(id).get();
}