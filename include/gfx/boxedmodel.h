#pragma once

#include <gfx/simplemodel.h>
#include <gfx/math/shape.h>
#include <gfx/hashpair.h>

class BoxedModel : public SimpleModel {
public:
    explicit BoxedModel (std::shared_ptr<SpriteMesh> mesh);
    class BoxInfo {
        std::shared_ptr<Shape> m_shape;
        std::shared_ptr<Shape> m_attackShape;
    };

private:
    std::unordered_map<std::pair<std::string, int>, BoxInfo> m_boxInfo;

};