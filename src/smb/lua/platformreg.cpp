#include <platformer/luaext.h>
#include <monkey/components/platform.h>
#include <platformer/input/enemyinput.h>
#include <monkey/components/controller2d.h>

void RegisterToPlatform(EntityWrapper character, EntityWrapper platform) {

    auto c = character.m_underlying->GetComponent<Controller2D>();
    auto p = platform.m_underlying->GetComponent<PlatformComponent>();
    p->Register(c);


}
void UnregisterToPlatform(EntityWrapper character, EntityWrapper platform) {
    auto c = character.m_underlying->GetComponent<Controller2D>();
    auto p = platform.m_underlying->GetComponent<PlatformComponent>();
    p->Unregister(c);

}


void SetEnemyDir(EntityWrapper character, bool left) {
    auto enemyInput = dynamic_cast<EnemyInputMethod*>(character.m_underlying->GetComponent<InputMethod>());
    enemyInput->setLeft(left);
}
