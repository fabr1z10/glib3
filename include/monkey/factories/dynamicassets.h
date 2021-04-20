#pragma once

#include <monkey/yaml.h>
#include <monkey/object.h>
#include <monkey/engine.h>

void nodeHelper(std::list<YAML::Node>& nodes, YAML::Node node, const ITab& args) ;

template<typename T>
std::shared_ptr<T> makeDynamic(const ITab& node, const ITab& args) {
//    auto clone = YAML::Clone(node);
//    std::list<YAML::Node> nodes;
//    //std::cerr << clone << "\n";
//
//    std::cerr << "!!!\n";
//    nodes.push_back(clone);
//    while (!nodes.empty()) {
//        auto current = nodes.front();
//        nodes.pop_front();
//        if (current.Type() == YAML::NodeType::Map) {
//            //std::cerr << "size = " << current.size() << "\n";
//            for (YAML::iterator iter = current.begin(); iter != current.end(); ++iter) {
//                //std::cerr << iter->first << "\n";
//                nodeHelper(nodes, iter->second, args);
////                if (iter->second.Type() == YAML::NodeType::Map || iter->second.Type() == YAML::NodeType::Sequence) {
////                    nodes.push_back(iter->second);
////                } else if (iter->second.Type() == YAML::NodeType::Scalar) {
////                    std::cerr << iter->first << ":: " << iter->second << "\n";
////                    auto str = iter->second.as<std::string>("");
////                    if (str.length() > 2) {
////                        if (str[0] == '$' && str[1] != '$') {
////                            try {
////                                iter->second = args.get<std::string>(str.substr(1));
////                            } catch (...) {
////                                GLIB_FAIL("Can't find <" << str.substr(1) << "> in args");
////                            }
////                        }
////                    }
////                }
//            }
//        } else if (current.Type() == YAML::NodeType::Sequence) {
//            for (auto it : current) {
//                nodeHelper(nodes, it, args);
////                if (it.Type() == YAML::NodeType::Sequence || it.Type() == YAML::NodeType::Map) {
////                    nodes.push_back(it);
////                }
//                //nodeHelper(nodes, &it, args);
//            }
//        }
//
//    }
//    std::cerr << "---------------------\n";
//    std::cerr << clone << "\n";
//    std::cerr << "---------------------\n";
//    //exit(1);
//    return Engine::get().GetSceneFactory()->makeAsset<T>(clone);
//    //exit(1);

}

// create a mesh with dynamic joint ids
std::shared_ptr<Object> makeDynamicSkeletalMesh(const ITab& node, int jointId, int parentJointId,
	float z, float scale, const glm::mat4& transform, glm::vec2 offset);
