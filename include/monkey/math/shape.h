//
//  shape.h
//  glib
//
//  Created by Fabrizio Venturini on 01/05/2018.
//
//

#ifndef shape_h
#define shape_h

#include <glm/glm.hpp>
#include <monkey/visitor.h>
#include <monkey/bounds.h>
#include <monkey/asset.h>
#include <string>
#include <vector>
#include <monkey/itable.h>

enum class ShapeType {
    SEGMENT, RECT, CIRCLE, PLANE, SPHERE, AABB, CONVEXPOLY, COMPOUND, POLY, POLYLINE, PRISM
};


class IShape : public Object {
public:
    IShape() = default;
    explicit IShape(glm::vec3 offset) : Object(), m_offset(offset) {}
    explicit IShape(const ITab& t);
    Bounds getBounds() const;
    glm::vec3 getOffset() const;
    //virtual std::unique_ptr<IShape> transform (const glm::mat4& t) = 0;
    virtual bool isPointInside (glm::vec3) const = 0;
    ShapeType getShapeType() const;
protected:
    Bounds m_bounds;
    glm::vec3 m_offset{};
    ShapeType m_type;
};

inline ShapeType IShape::getShapeType() const {
    return m_type;
}

inline Bounds IShape::getBounds() const {
    return m_bounds;
}

inline glm::vec3 IShape::getOffset() const {
    return m_offset;
}


class Shape2D : public IShape {
public:
    Shape2D() = default;
    explicit Shape2D(const ITab& t) : IShape(t) {}

    virtual glm::vec2 project(glm::vec2, const glm::mat4&) const = 0;
};






//class Shape : public Object {
//public:
//    Shape() : m_offset(glm::vec3(0.0f)) {}
//    Shape(const ITable&);
//    Shape(glm::vec3 offset) : m_offset(offset) {}
//    virtual ~Shape() {}
//    virtual bool isPointInside (glm::vec3) const = 0;
//    virtual void accept (AcyclicVisitor& v) = 0;
//    virtual std::string toString() const = 0;
//    Bounds getBounds() const;
//    virtual glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) = 0;
//    virtual std::vector<glm::vec2> getPoints() = 0;
//    virtual std::vector<glm::vec2> getEdges() = 0;
//    glm::vec3 GetOffset() const {
//        return m_offset;
//    }
//    void setOffset(glm::vec3);
//protected:
//    glm::vec3 m_offset;
//    Bounds m_bounds;
//};
//
//inline Bounds Shape::getBounds() const {
//    return m_bounds;
//}
//
//inline void Shape::setOffset(glm::vec3 offset) {
//    m_offset = offset;
//}


#endif /* shape_h */
