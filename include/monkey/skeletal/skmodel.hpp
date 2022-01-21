#pragma once


#include <monkey/assets/model.h>
#include <monkey/texturedmesh.h>
#include <monkey/vertices.h>
#include <monkey/skeletal/skeletalanimation.hpp>
#include <monkey/skeletalmesh.h>


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

struct PointLocator {
    std::string jointId;
    std::string pointId;
};

struct AttackBox {
	float t0;
	float t1;
	size_t bone;
	std::string boneId;
	//std::vector<PointLocator> pts; // points contained within the attack box
	std::shared_ptr<IShape> shape;
	std::shared_ptr<IShape> shapeTransformed;
};

struct CollisionBox {
    std::vector<PointLocator> pts; // points contained within the attack box
};


struct DrawingBit {
	DrawingBit() : mesh(nullptr), bb(GL_LESS) {}
	std::shared_ptr<IMesh> mesh;
	GLenum bb;

};


struct JointInfo {
    JointInfo(int id, int parent, const std::string& name, glm::ivec3 weightIndex) : id(id),
        parent(parent), name(name), mesh(nullptr), weightIndex(weightIndex), scale(1.0f), z(0.0f) {}
    int id;
    int parent;
    float scale;
    float z;
    std::vector<int> children;
    std::string name;
    JointTransform restTransform;
    SkeletalMesh * mesh;
    glm::ivec3 weightIndex;
};

class SkModel : public Model {
public:
    SkModel (const ITab&);
    std::vector<glm::mat4> calculateCurrentPose(std::unordered_map<int, JointTransform>& pose);
	std::shared_ptr<Renderer> makeRenderer(std::shared_ptr<Model>) override;

	//Bounds getBounds() const ;
    const std::unordered_map<std::string, std::shared_ptr<SkAnimation>>& getAnimations() const ;
    std::string getDefaultAnimation() const;
    ShaderType GetShaderType() const;
    SkAnimation* getAnimation(const std::string&);
    JointInfo* getJoint(int);
    int getJointId(const std::string&);
    void setMesh (int id, const std::string& meshId, glm::vec2 attachPoint, float z, float scale);
    void setAnimation (const std::string& animId, const std::string& anim);
    void prova();
    /**
     *
     * Gets an array of the all important model-space transforms of all the
     * joints (with the current animation pose applied) in the entity. The
     * joints are ordered in the array based on their joint index. The position
     * of each joint's transform in the array is equal to the joint's index.
     *
     * @return The array of model-space transforms of the joints in the current
     *         animation pose.
     */
    JointTransform getRestTransform(const std::string& id) const;
    const glm::mat4& getRestTransform(int id) const {
        return m_restTransforms2[id];
    }
    glm::ivec3 getWeightIndex(int id)const {
        return m_jointInfos[id].weightIndex;
    }

    const std::vector<std::pair<int, glm::vec3>>& getOffsetPoints() const;
    const std::vector<std::shared_ptr<IShape>>& getShapes();
    int getShapeId (const std::string& animId);

    IShape* getShape (const std::string& animId);
    IShape* getShape (int shapeId);
    const AttackBox* getShapeCastId (const std::string& animId, float t);
    std::vector<std::shared_ptr<IShape>> getAttackShapes() const ;
    void computeOffset();
    const std::unordered_map<std::string, std::shared_ptr<AttackBox>>& getAttackInfo() const;
    const std::unordered_map<std::string, CollisionBox>& getBoxInfo() const;
    void addShape(const std::string& animId, std::shared_ptr<IShape> shape);

    glm::vec2 getKeyPoint(const std::string& joint, const std::string& pointId) const;
    float getAttackDistance() const;
    glm::vec4 getBoundingBox() const;
private:
    std::vector<glm::mat4> m_restTransforms2;
    std::vector<glm::mat4> m_invRestTransforms2;

    std::vector<JointInfo> m_jointInfos;
    std::unordered_map<std::string, int> m_jointNameToId;
	int m_root;
	std::unordered_map<std::string, std::vector<std::string>> m_jointChildren;
	std::unordered_map<std::string, SkeletalMesh*> m_skeletalMeshes;

    std::vector<std::shared_ptr<IShape>> m_shapes;
    std::unordered_map<std::string, int> m_animToShape;
    std::unordered_map<std::string, std::shared_ptr<AttackBox> > m_attackTimes;
    std::unordered_map<std::string, CollisionBox> m_boxInfo;

    int m_jointCount;
    float m_attackDistance;

    std::unordered_map<std::string, std::shared_ptr<SkAnimation>> m_animations;
    std::string m_defaultAnimation;
    std::unordered_map<std::string, JointTransform> m_restTransforms;
    std::vector<std::pair<int, glm::vec3>> m_offsetPoints;
    glm::vec4 m_meshBounds;
    Bounds m_maxBounds;
    std::vector<SkBoxInfo> m_skeletalBoxes;
    std::vector<std::pair<std::string, std::string>> m_offsetPointIds;
};

inline JointTransform SkModel::getRestTransform(const std::string& id) const {
    return m_restTransforms.at(id);
}

inline const std::vector<std::pair<int, glm::vec3>>& SkModel::getOffsetPoints() const {
    return m_offsetPoints;
}

inline IShape* SkModel::getShape(int shapeId) {
    return m_shapes[shapeId].get();
}

inline const std::unordered_map<std::string, CollisionBox> & SkModel::getBoxInfo() const {
    return m_boxInfo;
}

inline float SkModel::getAttackDistance() const {
    return m_attackDistance;
}