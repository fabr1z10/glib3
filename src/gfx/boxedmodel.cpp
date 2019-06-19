#include <gfx/boxedmodel.h>

BoxedModel::BoxedModel(std::shared_ptr<SpriteMesh> mesh) : SimpleModel(mesh) {}

void BoxedModel::AddCollisionData(const std::string &anim
                             , int frame
                             , std::shared_ptr<Shape> collision
                             , std::shared_ptr<Shape> attack)
{
    auto key = std::make_pair(anim, frame);
    m_boxInfo.insert(std::make_pair(key, BoxInfo({collision, attack})));
}
