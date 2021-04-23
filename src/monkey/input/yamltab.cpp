#include <monkey/input/yamltab.h>
#include <monkey/math/util.h>
#include <exprtk.hpp>
int YAMLTab::_asInt() const {
    return m_node.as<int>();
}

float YAMLTab::_asFloat() const {
    return m_node.as<float>();
}

bool YAMLTab::_asBool() const {
    return m_node.as<bool>();
}

std::string YAMLTab::_asString() const {
    return m_node.as<std::string>();
}

glm::vec2 YAMLTab::_asVec2() const {
	auto vec = m_node.as<std::vector<float>>();
	return glm::vec2(vec[0], vec[1]);

}

glm::vec3 YAMLTab::_asVec3() const {
	auto vec = m_node.as<std::vector<float>>();
	return glm::vec3(vec[0], vec[1], vec[2]);

}

glm::vec4 YAMLTab::_asVec4() const {
	auto vec = m_node.as<std::vector<float>>();
	return glm::vec4(vec[0], vec[1], vec[2], vec[3]);

}

glm::mat4 YAMLTab::_asMat4() const {
    
}

std::unique_ptr<ITab> YAMLTab::operator[] (int key) const {
	return std::make_unique<YAMLTab>(m_node[key]);
}

std::unique_ptr<ITab> YAMLTab::operator[] (const std::string & key) const {
    auto node = m_node[key.c_str()];
    if (node) {
        return std::make_unique<YAMLTab>(m_node[key.c_str()]);
    }
    return nullptr;
}

void YAMLTab::foreach(std::function<void(const ITab &)> f) const {
    for (auto &i : m_node) {
        f(YAMLTab(i));
    }
}

void YAMLTab::foreach(const std::string &id, std::function<void(const ITab &)> f) const {
    auto l = m_node[id.c_str()];
    if (l) {
        auto list = l.as<std::vector<YAML::Node>>();
        for (auto &i : list) {
            f(YAMLTab(i));
        }
    }
}

void YAMLTab::foreach(std::function<void(const std::string &, const ITab &)> f) const {
    for (const auto& node : m_node) {
        auto key = node.first.as<std::string>();
        f(key, YAMLTab(node.second));
    }
}

void YAMLTab::foreach(const std::string &id, std::function<void(const std::string &, const ITab &)> f) const {
    auto l = m_node[id.c_str()];
    if (l) {
        for (const auto &node : l) {
            auto key = node.first.as<std::string>();
            f(key, YAMLTab(node.second));
        }
    }
}

bool YAMLTab::has(const std::string &id) const {
    return m_node[id];
}

std::vector<int> YAMLTab::_asVecInt() const {
    return m_node.as<std::vector<int>>();
}

std::vector<float> YAMLTab::_asVecFloat() const {
    return m_node.as<std::vector<float>>();
}

std::vector<std::string> YAMLTab::_asVecStr() const {
    return m_node.as<std::vector<std::string>>();
}

std::shared_ptr<ITab> YAMLTab::clone(const ITab & args) const {
	auto nnode = YAML::Clone(m_node);
	std::cerr << nnode << "\n";
	std::list<YAML::Node> nodes;
	nodes.push_back(nnode);
	while (!nodes.empty()) {
		// process current node
		auto current = nodes.front();
		nodes.pop_front();
		if (current.Type() == YAML::NodeType::Map) {
			for (auto iter : current) {
				nodes.push_back(iter.second);
			}
		} else if (current.Type() == YAML::NodeType::Sequence) {
			if (current.size() > 0) {
				// check if this is a replacement
				auto pp = current[0].as<std::string>("");
				if (pp[0] == '$') {
					auto type = pp.substr(1);
					if (type == "expr") {
						// expression ...
						// we need first the variables, to be fetched from args
						auto variables = current[1].as<std::vector<std::string>>();
						auto exprString = current[2].as<std::string>();

						//float value = glib3::math::parse_expr("2+3.5");
						std::unordered_map<std::string, float> vars;
						for (const auto& var : variables) {
							vars.insert(std::make_pair(var, args.get<float>(var)));
						}
						float value = glib3::math::parse_expr(exprString, vars);
						std::cerr << "the value is " << 22 << "\n";
						current = value;
						// create symbol table

					} else {
						auto varName = current[1].as<std::string>();
						if (args.has(varName)) {
							if (type == "str") {
								current = args.get<std::string>(varName);
							} else if (type == "float") {
								current = args.get<float>(varName);
							}
						} else {
							if (current.size() > 2) {
								current = current[2];
							}
						}
					}
				} else {
					for (auto iter : current) {
						nodes.push_back(iter);
					}
				}
			}
		}
	}
	std::cerr << "===========\n";
	std::cerr << nnode << "\n";

//	for (YAML::iterator iter = nnode.begin(); iter != nnode.end(); iter++) {
//		if (iter->Type() == YAML::NodeType::Map) {
//			std::cerr << " ** found map: " << iter->first << "\n";
//		} else if (iter->Type() == YAML::NodeType::Sequence) {
//			std::cerr << " ** found seq\n";
//		}
//
//	}
	return std::make_shared<YAMLTab>(nnode);
}

void YAMLTab::print(std::ostream & out) const {
	out << m_node;
}