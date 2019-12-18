#include <platformer/states/walkside.h>
#include <gfx/lua/luawrapper.h>


class BubWalk : public WalkSide {
public:
    BubWalk (luabridge::LuaRef f, float speed, float acceleration, bool fliph, float jumpSpeed);
    BubWalk (const BubWalk& orig);
    std::shared_ptr<State> clone() const override;

    void AttachStateMachine(StateMachine*) override;
    void shoot();
    void ModifyAnimation() override;
private:
    bool m_isShooting;
    luabridge::LuaRef m_f;

};