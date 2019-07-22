#pragma once

#include <gfx/component.h>
#include <glm/glm.hpp>


class IController : public Component {
public:
    virtual void Move(glm::vec3&) = 0;
    virtual bool grounded() const = 0;
    virtual bool ceiling () const = 0;
    using ParentClass = IController;

};
