#pragma once

#include <gfx/components/animator.h>

enum class CharacterDirection {
    EAST, WEST, NORTH, SOUTH
};

template<class T, class X>
class StateAnimator : public T {
public:
    void Start() override {
        T::Start();
        m_state = m_entity->GetComponent<X>();
    }
    void SetAnimation (const std::string& name) override {
        std::string t = m_state->transform(name);
        if (HasAnimation(t)) {
            T::SetAnimation(t);
        } else {
            T::SetAnimation(name);
        }
    }
    void SetAnimation (const std::string& node, const std::string& animation) override {
        void SetAnimation (const std::string& node, const std::string& name) override {
            std::string t = m_state->transform(name);
            if (HasAnimation(node, t)) {
                T::SetAnimation(t);
            } else {
                T::SetAnimation(node, name);
            }
        }
    }



private:
    X* m_state;
};

class CharacterState {
public:
    std::string transform(const std::string& name) {
        return name;
    }
    CharacterDirection m_dir;
};

