#include <platformer/platformerfactory.h>
#include <platformer/factories.h>


PlatformerFactory::PlatformerFactory() : BasicSceneFactory() {

    // platformer states
    m_stateFactories["idle2d"] = std::make_shared<Idle2DStateFactory>();
    m_stateFactories["walk2d"] = std::make_shared<Walk2DStateFactory>();
    m_stateFactories["jump2d"] = std::make_shared<Jump2DStateFactory>();
    m_stateFactories["enemywalk2d"] = std::make_shared<EnemyWalk2DStateFactory>();

}
