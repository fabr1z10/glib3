#include <gfx/transition.h>
#include <gfx/random.h>

void Transition::AddTransition (const std::string& initialState, const std::string& nextState, float p) {
    m_transitionProbs[initialState][p] = nextState;
}


std::pair<bool, std::string> Transition::Next(const std::string& from) {
    auto it = m_transitionProbs.find(from);
    if (it == m_transitionProbs.end()) {
        return std::make_pair(false, from);
    }

    float p = Random::get().GetUniformReal(0, 1);
    auto it2 = it->second.lower_bound(p);
    if (it2 != it->second.end())
    {
        return std::make_pair(true, it2->second);
    }
    return std::make_pair(false, from);

};