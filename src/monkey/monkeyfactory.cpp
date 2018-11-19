#include <monkey/monkeyfactory.h>
#include <monkey/factories.h>


MonkeyFactory::MonkeyFactory() : SceneFactory() {
    m_componentFactory.Add<WalkAreaComponentFactory>("walkarea");

    //AddFactory<WalkAreaComponentFactory>("walkarea");
    //AddFactory<ScalingComponentFactory>("scaling");

}
