#pragma once


#include <monkey/assets/imodel.h>
#include <monkey/texturedmesh.h>
#include <monkey/vertices.h>
#include <monkey/skeletal/joint.hpp>

struct SkPointInfo {
	glm::vec2 point;
	glm::ivec3 joints;
	glm::vec3 weights;
};

struct SkBoxInfo {
	SkPointInfo A;
	SkPointInfo B;
	float width;
};

class SkModel : public IModel {
public:
    SkModel (const ITable&);

    Bounds GetBounds() const override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override;
    ShaderType GetShaderType() const override;
    SkAnimation* getAnimation(const std::string&);
    std::shared_ptr<Joint> getRootJoint();
    Joint* getJoint (const std::string&);
    void Draw (Shader*);
    /**
     * Gets an array of the all important model-space transforms of all the
     * joints (with the current animation pose applied) in the entity. The
     * joints are ordered in the array based on their joint index. The position
     * of each joint's transform in the array is equal to the joint's index.
     *
     * @return The array of model-space transforms of the joints in the current
     *         animation pose.
     */
    std::vector<glm::mat4> getJointTransforms();
    JointTransform getRestTransform(const std::string& id) const;
    const std::vector<std::pair<std::string, glm::vec3>>& getOffsetPoints() const;
    const std::vector<std::shared_ptr<Shape>>& getShapes();
    int getShapeId (const std::string& animId);

    Shape* getShape (const std::string& animId);
    Shape* getShape (int shapeId);
    int getShapeCastId (const std::string& animId, float t0, float t1);
    std::vector<std::shared_ptr<Shape>> getAttackShapes() const override;

private:
    //std::shared_ptr<Shape> m_defaultShape;
    std::vector<std::shared_ptr<Shape>> m_shapes;
    std::unordered_map<std::string, int> m_animToShape;
    std::unordered_map<std::string, std::unordered_map<float, int>> m_attackTimes;

    std::shared_ptr<Joint> m_rootJoint;
    int m_jointCount;

    // create one mesh per texture!

    std::vector<std::shared_ptr<TexturedMesh<VertexSkeletal> > > m_meshes;
    std::unordered_map<std::string, std::shared_ptr<SkAnimation>> m_animations;
    std::string m_defaultAnimation;
    void addJointsToArray(Joint*, std::vector<glm::mat4>&);
    std::unordered_map<std::string, JointTransform> m_restTransforms;
    std::vector<std::pair<std::string, glm::vec3>> m_offsetPoints;
    std::unordered_map<std::string, Joint*> m_allJoints;
    Bounds m_maxBounds;
    std::vector<SkBoxInfo> m_skeletalBoxes;
};

inline std::shared_ptr<Joint> SkModel::getRootJoint() {
    return m_rootJoint;
}

inline JointTransform SkModel::getRestTransform(const std::string& id) const {
    return m_restTransforms.at(id);

}

inline const std::vector<std::pair<std::string, glm::vec3>>& SkModel::getOffsetPoints() const {
    return m_offsetPoints;

}

inline Joint* SkModel::getJoint(const std::string & id) {
    return m_allJoints.at(id);
}

inline Shape* SkModel::getShape(int shapeId) {
    return m_shapes[shapeId].get();

}