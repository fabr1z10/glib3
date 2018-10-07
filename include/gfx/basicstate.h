#include <gfx/components/statemachine.h>
#include <vector>

class Entity;
class Renderer;

// super basic state. There's a play animation
// collision boxes to activate
// a fallback animation if loop
class BasicState : public State {
public:
    BasicState (const std::string& anim, const std::vector<std::string>& colliders);
    void Init(Entity* e) override;
    void End () override {}
    // returns true if state changes
    bool Run (double) override { return false; }
    void Start () override;
protected:
    Entity* m_colliderContainer;
    Renderer* m_renderer;
    std::string m_anim;
    std::vector<Entity*> m_colliders;
    std::vector<std::string> m_activeColliders;
};


class BasicStateFallback : public BasicState {
public:
    BasicStateFallback (const std::string& anim, const std::string& fallbackState, const std::vector<std::string>&);
    bool Run (double) override;

private:
    std::string m_fallback;
};