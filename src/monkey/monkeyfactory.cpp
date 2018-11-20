#include <monkey/monkeyfactory.h>
#include <monkey/factories.h>


MonkeyFactory::MonkeyFactory() : SceneFactory() {
    m_componentFactory.Add<WalkAreaComponentFactory>("walkarea");

    m_activityFactory.Add<WalkToActFactory>("walk");
    m_activityFactory.Add<TurnActFactory>("turn");
    m_activityFactory.Add<SayActFactory>("say");

    //AddFactory<WalkAreaComponentFactory>("walkarea");
    //AddFactory<ScalingComponentFactory>("scaling");

}
