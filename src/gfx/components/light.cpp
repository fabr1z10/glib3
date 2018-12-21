#include <gfx/components/light.h>
#include <gfx/engine.h>

void Light::Start() {
    Engine::get().GetRenderingEngine()->AddLight(this);

}

Light::~Light() {
    Engine::get().GetRenderingEngine()->RemoveLight(this);
}