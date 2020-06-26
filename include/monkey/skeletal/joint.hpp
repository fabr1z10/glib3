#pragma once


#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

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
    Joint (int index, std::string name, glm::mat4 bindLocalTransform);

    void addChild (std::shared_ptr<Joint>);

    /// the animated transform that gets loaded up to the shader
    glm::mat4 getAnimatedTransform();

    glm::mat4 getInverseBindTransform() const;

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
    const std::vector<std::shared_ptr<Joint>>& getChildren() const;
    std::string getName() const;
private:
    int m_index;
    std::string m_name;
    std::vector<std::shared_ptr<Joint>> m_children;
    glm::mat4 m_transform;
    glm::mat4 m_localBindTransform;
    glm::mat4 m_inverseBindTransform;
};

inline const std::vector<std::shared_ptr<Joint>>& Joint::getChildren() const {
    return m_children;
}

inline glm::mat4 Joint::getInverseBindTransform() const {
    return m_inverseBindTransform;
}
