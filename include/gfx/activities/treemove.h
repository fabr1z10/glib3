#pragma once

#include <gfx/activities/targetactivity.h>
#include <gfx/entity.h>

class TreeMove : public TargetActivity {
public:
    //! \name Constructors
    //@{
    /*! Moves an entity in the node hierarchy from its current position to a new parent
     */
    TreeMove(const std::string& newParent);

    //Animate(Entity* entity, const std::string& animId, bool forward, int flip = 0);
    //@}
    void Start() override;
    void Run (float dt) override {}
    // action ends when animation is completed.
private:
    std::string m_newParent;
};

