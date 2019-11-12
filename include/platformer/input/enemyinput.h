#pragma once

#include <gfx/components/inputmethod.h>
#include <map>

class Controller2D;

class EnemyInputMethod : public InputMethod {
public:

    EnemyInputMethod(int status, bool flipIfPlatformEnds, float attackProbability) : InputMethod(),
        m_left(status==1), m_idle(status==0), m_idle2walk(0.0f), m_walk2idle(0.0f), m_flipIfPlatformEnds(flipIfPlatformEnds), m_controller(nullptr), m_attackProbability(attackProbability), m_attackOdds(0){}
    EnemyInputMethod(const EnemyInputMethod& orig) : InputMethod(orig),
        m_left(orig.m_left), m_idle(orig.m_left), m_idle2walk(orig.m_idle2walk), m_walk2idle(orig.m_walk2idle), m_flipIfPlatformEnds(orig.m_flipIfPlatformEnds), m_controller(nullptr) {}
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update (double) override;
    bool isKeyDown(int) override;
    void setLeft (bool);
    std::type_index GetType() override;
    void AddAttackMove (int key, int odds);
    void setTransitionProbabilities (float, float);
    using ParentClass = InputMethod;
private:
    Controller2D * m_controller;
    bool m_left;
    bool m_idle;
    bool m_flipIfPlatformEnds;
    float m_attackProbability;
    std::map<int, int> m_attackMoves;
    int m_attackOdds;
    float m_idle2walk;
    float m_walk2idle;
    Entity* m_target;
};

inline std::type_index EnemyInputMethod::GetType() {
    return std::type_index(typeid(InputMethod));
}
