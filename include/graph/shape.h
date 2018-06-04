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
#include <graph/visitor.h>

class Shape {
public:
    Shape(){}
    virtual ~Shape() {}
    virtual bool isPointInside (glm::vec2) const = 0;
    virtual void accept (AcyclicVisitor& v) = 0;
        
};

class Rect : public Shape {
public:
    Rect (float width, float height) : Shape(), m_width(width), m_height(height) {

    }
    bool isPointInside(glm::vec2) const override;
    void accept (AcyclicVisitor& v) override;
    float GetWidth () const;
    float GetHeight () const;
private:
    float m_width;
    float m_height;
};

inline float Rect::GetWidth () const {
    return m_width;
}

inline float Rect::GetHeight () const {
    return m_height;
}


#endif /* shape_h */