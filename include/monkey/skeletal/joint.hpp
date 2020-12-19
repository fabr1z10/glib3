#pragma once


#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <monkey/skeletal/jointtransform.hpp>

/**
 *
 * Represents a joint in a "skeleton". It contains the index of the joint which
 * determines where in the vertex shader uniform array the joint matrix for this
 * joint is loaded up to. It also contains the name of the bone, and a list of
 * all the child joints.
 *
 * The "animatedTransform" matrix is the joint transform that I keep referring
 * to in the tutorial. This is the transform that gets loaded up to the vertex
 * shader and is used to transform vertices. It is a model-space transform that
 * transforms the joint from it's bind (original position, no animation applied)
 * position to it's current position in the current pose. Changing this
 * transform changes the position/rotation of the joint in the animated entity.
 *
 * The two other matrices are transforms that are required to calculate the
 * "animatedTransform" in the {@link Animator} class. It also has the local bind
 * transform which is the original (no pose/animation applied) transform of the
 * joint relative to the parent joint (in bone-space).
 *
 * The "localBindTransform" is the original (bind) transform of the joint
 * relative to its parent (in bone-space). The inverseBindTransform is that bind
 * transform in model-space, but inversed.
 *
 * @author Karl
 *
 */
class Joint {
public:
    Joint (int index, const std::string& name, float z);

    void addChild (std::shared_ptr<Joint>);

    void setLocalToParentTransform(const JointTransform& t, const glm::mat4& parentBindTransform);
    void setParent (const std::string& parent, const std::string& attachPoint);
    /// the animated transform that gets loaded up to the shader
    glm::mat4 getAnimatedTransform();
    float getZ() const;
    glm::mat4 getInverseBindTransform() const;
    glm::mat4 getBindTransform() const;
    glm::mat4 getLocalBindTransform() const;

    void setAnimationTransform(glm::mat4 animationTransform);

    /**
     * This is called during set-up, after the joints hierarchy has been
     * created. This calculates the model-space bind transform of this joint
     * like so: </br>
     * </br>
     * {@code bindTransform = parentBindTransform * localBindTransform}</br>
     * </br>
     * where "bindTransform" is the model-space bind transform of this joint,
     * "parentBindTransform" is the model-space bind transform of the parent
     * joint, and "localBindTransform" is the bone-space bind transform of this
     * joint. It then calculates and stores the inverse of this model-space bind
     * transform, for use when calculating the final animation transform each
     * frame. It then recursively calls the method for all of the children
     * joints, so that they too calculate and store their inverse bind-pose
     * transform.
     *
     * @param parentBindTransform
     *            - the model-space bind transform of the parent joint.
     */
    void calcInverseBindTransform (glm::mat4 parentBindTransform);
    std::vector<std::shared_ptr<Joint>>& getChildren();
    std::string getName() const;
    std::string getParent() const;
    std::string getAttachPoint() const;
    bool isRoot() const;
    int getIndex() const;
    void setRest();
    JointTransform getRestTransform() const;
private:
    int m_index;
    bool m_root;
    std::string m_name;
    std::string m_parent;
    std::string m_attachPoint;
    std::vector<std::shared_ptr<Joint>> m_children;
    glm::mat4 m_transform;
    // local space to parent space
    glm::mat4 m_localBindTransform;
    // local space to model space
    glm::mat4 m_bindTransform;
    glm::mat4 m_inverseBindTransform;
    JointTransform m_localTransform;
    float m_z;
};

inline std::vector<std::shared_ptr<Joint>>& Joint::getChildren()  {
    return m_children;
}

inline glm::mat4 Joint::getInverseBindTransform() const {
    return m_inverseBindTransform;
}

inline glm::mat4 Joint::getLocalBindTransform() const {
    return m_localBindTransform;
}

inline glm::mat4 Joint::getBindTransform() const {
    return m_bindTransform;
}

inline std::string Joint::getName() const {
    return m_name;
}

inline int Joint::getIndex() const {
    return m_index;
}

inline JointTransform Joint::getRestTransform() const {
    return m_localTransform;
}

inline std::string Joint::getParent() const {
    return m_parent;
}

inline std::string Joint::getAttachPoint() const {
    return m_attachPoint;
}

inline bool Joint::isRoot() const {
    return m_parent.empty();
}

inline float Joint::getZ() const {
    return m_z;
}