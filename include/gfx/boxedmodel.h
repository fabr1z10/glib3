#pragma once

#include <gfx/simplemodel.h>
#include <gfx/math/shape.h>
#include <gfx/hashpair.h>

class BoxedModel : public SimpleModel {
public:
    explicit BoxedModel (std::shared_ptr<SpriteMesh> mesh);
    struct BoxInfo {
        std::shared_ptr<Shape> m_shape;
        std::shared_ptr<Shape> m_attackShape;
        int shapeTag;
        int attackTag;
    };
    
    void AddCollisionData (const std::string& anim, int frame,
                           std::shared_ptr<Shape> collision,
                           std::shared_ptr<Shape> attack);
    std::shared_ptr<Shape> GetShape (const std::string&, int);
    
private:
    std::unordered_map<std::pair<std::string, int>, BoxInfo> m_boxInfo;

};
