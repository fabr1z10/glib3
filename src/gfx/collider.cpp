#include "gfx/collider.h"
#include "gfx/renderer.h"
#include "gfx/entity.h"
#include "gfx/meshfactory.h"

void Collider::SetParent(Entity * entity) {
    Component::SetParent(entity);

    // create a debug mesh
    auto ce = std::make_shared<Entity>();
    auto cer = std::make_shared<Renderer>();
    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    cer->SetMesh(debugMesh);
    ce->AddComponent(cer);
    ce->SetTag("collidermesh");
    m_entity->AddChild(ce);
}