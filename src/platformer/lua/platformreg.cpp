#include <platformer/luaext.h>
#include <gfx/components/platform.h>
#include <gfx/components/controller2d.h>

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