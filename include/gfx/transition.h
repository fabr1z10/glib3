#pragma once

#include <unordered_map>
#include <map>
#include <string>

class Transition {
public:
    void AddTransition (const std::string& initialState, const std::string& nextState, float p);
    std::pair<bool, std::string> Next(const std::string&);
private:
    std::unordered_map<std::string, std::map<float, std::string> > m_transitionProbs;
};
