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
protected:
	glm::vec3 m_halfSize;
	glm::vec3 m_shift;
};
