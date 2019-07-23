#include <gfx/math/shape.h>

class Box : public Shape
{
public:
    Box (float width, float height, float depth, glm::vec3 offset = glm::vec3(0.0f));
    float width() const;
    float height() const;
    float depth() const;
    bool isPointInside(glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    std::string toString() const override {throw;}
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {throw;}
    std::vector<glm::vec2> getPoints() override {throw;}
    std::vector<glm::vec2> getEdges() override{throw;}
private:
    float m_width;
    float m_height;
    float m_depth;


};

inline float Box::width() const {
    return m_width;
}

inline float Box::depth() const {
    return m_depth;
}
inline float Box::height() const {
    return m_height;
}

