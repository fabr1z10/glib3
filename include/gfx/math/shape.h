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
#include <gfx/visitor.h>
#include <gfx/bounds.h>
#include <string>
#include <vector>

class Shape {
public:
    Shape() : m_offset(glm::vec3(0.0f)) {}
    Shape(glm::vec3 offset) : m_offset(offset) {}
    virtual ~Shape() {}
    virtual bool isPointInside (glm::vec3) const = 0;
    virtual void accept (AcyclicVisitor& v) = 0;
    virtual std::string toString() const = 0;
    Bounds getBounds() const;
    virtual glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) = 0;
    virtual std::vector<glm::vec2> getPoints() = 0;
    virtual std::vector<glm::vec2> getEdges() = 0;
    glm::vec3 GetOffset() const {
        return m_offset;
    }
protected:
    glm::vec3 m_offset;
    Bounds m_bounds;
};

inline Bounds Shape::getBounds() const {
    return m_bounds;
}




#endif /* shape_h */
