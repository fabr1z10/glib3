#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class Renderer;

class SetModel : public Activity {
public:
    //! \name Constructors
    //@{
    /*! Update the model attached to an entity's renderer.
     */
    SetModel(const std::string& actorId, const std::string& model, const std::string& animId, int flip = 0);
    //@}
    void Start() override;
    void Reset() override {
        Activity::Reset();
        m_entity = nullptr;
    }
    void Run (float dt) override {}
private:
    int m_flipX;
    Entity* m_entity;
    Renderer* m_renderer;
    std::string m_animId;
    std::string m_model;
    std::string m_actorId;
};

