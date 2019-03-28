#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class TargetActivity : public Activity {
public:
    //! An activity that acts upon an entity
    //! You can provide the entity by giving the unique identifier or the tag
    TargetActivity() : Activity(), m_id(-1), m_entity(nullptr) {}
    TargetActivity(int id);
    TargetActivity(const std::string& tag);

    void Start() override;

    void Reset() override;

    void SetId (int);
    void SetTag (const std::string&);

protected:
    Entity* m_entity;
    int m_id;
    std::string m_tag;
};

inline void TargetActivity::SetId (int id) {
    m_id = id;
}

inline void TargetActivity::SetTag (const std::string& tag) {
    m_tag = tag;
}


