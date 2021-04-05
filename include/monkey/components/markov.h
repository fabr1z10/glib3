#pragma once
#include <monkey/components/statemachine.h>

class MarkovStateMachine : public StateMachine {
public:
	MarkovStateMachine(const ITab&);
	void Update(double) override;
	std::type_index GetType() override;
private:
	std::unordered_map<std::string, std::vector<std::pair<float, std::string>>> m_transitionProbs;
};

inline std::type_index MarkovStateMachine::GetType() {
	return std::type_index(typeid(StateMachine));
}


