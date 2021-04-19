#include <monkey/components/markov.h>
#include <monkey/singleton.h>
#include <monkey/random.h>
#include <monkey/engine.h>

MarkovStateMachine::MarkovStateMachine(const ITab& t) : StateMachine() {
	m_initialState = t.get<std::string>("initialState");
	m_currentState = nullptr;
	auto factory = Engine::get().GetSceneFactory();


	t.foreach("states", [&] (const ITab& table) {
		auto state = factory->make2<State>(table);
		this->AddState(state->getId(), state);
	});
	if (t.has("probs")) {
		auto probs = t.get<pybind11::dict>("probs");
		for (const auto& p : probs) {
			auto startState = p.first.cast<std::string>();
			for (const auto& tp : p.second) {
				auto tuple = tp.cast<pybind11::tuple>();
				auto prob = tuple[0].cast<float>();
				auto toState = tuple[1].cast<std::string>();
				m_transitionProbs[startState].push_back(std::make_pair(prob, toState));
			}
		}
	}

}

void MarkovStateMachine::Update(double dt) {
	StateMachine::Update(dt);
	// if no probs are associated to current state, just stay here
	auto it = m_transitionProbs.find(m_currentStateId);
	if (it != m_transitionProbs.end()) {
		// draw a random number in [0, 1)
		float u = Random::get().GetUniformReal(0.0f, 1.0f);
		const auto& vec = it->second;
		for (int i = 0; i < vec.size(); ++i) {
			if (u < vec[i].first) {
				SetState(vec[i].second);
				return;
			}
		}

	}
}