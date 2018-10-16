#include <platformer/platformerfactory.h>
#include <platformer/factories.h>


PlatformerFactory::PlatformerFactory() : SceneFactory() {

    // platformer states
    m_stateBehaviorFactory.Add<Idle2DStateFactory>("idle2d");
    m_stateBehaviorFactory.Add<Walk2DStateFactory>("walk2d");
    m_stateBehaviorFactory.Add<Jump2DStateFactory>("jump2d");
    m_stateBehaviorFactory.Add<EnemyWalk2DStateFactory>("enemywalk2d");
    m_stateBehaviorFactory.Add<EnemyBounce2DStateFactory>("enemybounce2d");


}
