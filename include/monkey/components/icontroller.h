#pragma once

#include <monkey/component.h>
#include <glm/glm.hpp>


class IController : public Component {
public:
	IController() = default;
	IController(const ITab&);
	virtual void Move(glm::vec3&) = 0;
    virtual bool grounded() const = 0;
    virtual bool ceiling () const = 0;
    virtual bool side () const = 0;
    using ParentClass = IController;
    void setBounds(glm::vec3 size, glm::vec3 shift);
protected:
    virtual void drawShape() = 0;
	glm::vec3 m_halfSize;
	glm::vec3 m_shift;
    bool m_debug;
    Entity* m_debugShape;

};
