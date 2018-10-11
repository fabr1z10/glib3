#include <gfx/state.h>
#include <vector>

class Entity;
class Renderer;

// super basic initializer, just set an animation
class AnimInitializer : public StateInitializer {
public:
    AnimInitializer (const std::string& anim);
    void Init(Entity* e) override;
    void Start () override;
protected:
    Renderer* m_renderer;
    std::string m_anim;
};


class AnimColliderInitializer : public AnimInitializer {
public:
    AnimColliderInitializer (const std::string& anim, const std::vector<std::string>&);
    void Init(Entity* e) override;
    void Start () override;
private:
    Entity* m_entity;
    std::vector<Entity*> m_colliders;
    std::vector<std::string> m_activeColliders;
};