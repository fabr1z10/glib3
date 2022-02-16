#pragma once


#include <monkey/math/shape.h>


/// this is a 2D shape with a thickness. good for 2.5d games
class Pseudo3DShape : public IShape {
public:
    Pseudo3DShape(const ITab&);
    bool isPointInside (glm::vec3) const override;
    IShape* getInternalShape();
    float getHalfDepth() const;
private:
    float m_halfDepth;
    std::shared_ptr<IShape> m_internalShape;
};


inline float Pseudo3DShape::getHalfDepth() const {
    return m_halfDepth;
}