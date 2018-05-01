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

class Shape {
public:
    virtual bool isPointInside (glm::vec2) const = 0;
        
};

#endif /* shape_h */
