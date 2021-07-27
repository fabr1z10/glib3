#include <monkey/math/shapes3d/prism.h>
#include <monkey/engine.h>


Prism::Prism(const ITab & t) {
    auto factory = Engine::get().GetSceneFactory();

    auto sh = t["shape"];
    m_shape = factory->make2<IShape>(*sh);
    m_height = t.get<float>("height");

}