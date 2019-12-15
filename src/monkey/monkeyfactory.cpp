#include <monkey/monkeyfactory.h>
#include <monkey/factories.h>
#include <monkey/components/charactercomponent.h>

MonkeyFactory::MonkeyFactory() : SceneFactory() {
    m_componentFactory.Add<WalkAreaComponentFactory>("walkarea");
    m_componentFactory.Add<WalkStopComponentFactory>("hole");
    m_componentFactory.Add<CharacterStateFactory>("character");

    m_activityFactory.Add<WalkToActFactory>("walk");
    //m_activityFactory.Add<WalkSciActFactory>("walksci");

    m_activityFactory.Add<TurnActFactory>("turn");
    m_activityFactory.Add<TurnSciActFactory>("turnsci");
    m_activityFactory.Add<SayActFactory>("say");
    m_activityFactory.Add<EnableBlockActFactory>("enable_wall");
    //AddFactory<WalkAreaComponentFactory>("walkarea");
    //AddFactory<ScalingComponentFactory>("scaling");

}
