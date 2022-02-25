#include <monkey/states/base3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/animrenderer.h>

class NPCWalk : public Base3D {
public:
    NPCWalk(const ITab& t);
    void Init(const ITab& d) override;
    void Run(double) override;
    void End() override;
    void AttachStateMachine(StateMachine*) override;

private:
    float m_jumpSpeed;

    ICollider* m_collider;
    std::string m_idleAnim;
    std::string m_walkAnim;
    std::string m_jUpAnim;
    std::string m_jDownAnim;
    int m_direction; // -1 = going left, 1 = going right
    bool m_fliph;
    bool m_flipIfPlatformEnds;

    // override collision mask
    int m_collisionMaskOverride;
    int m_oldCollisionMask;
};