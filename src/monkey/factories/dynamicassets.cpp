#include <monkey/factories/dynamicassets.h>
#include <monkey/singleton.h>
#include <monkey/engine.h>
#include <monkey/assetman.h>
#include <monkey/skeletal/skmesh.h>
#include <glm/gtx/transform.hpp>


void nodeHelper(std::list<YAML::Node>& nodes, YAML::Node node, const ITable& args) {
    if (node.Type() == YAML::NodeType::Map || node.Type() == YAML::NodeType::Sequence) {
        nodes.push_back(node);
    } else if (node.Type() == YAML::NodeType::Scalar) {
        auto str = node.as<std::string>("");
        if (str.length() > 2) {
            if (str[0] == '$' && str[1] != '$') {
                // check if default value is provided
                // get type
                    int colonIndex = str.find(':');
                    if (colonIndex == -1) {
                        GLIB_FAIL("placeholder values must have a type between $ and : current value is " << str);
                    }
                    auto typ = str.substr(1, colonIndex-1);
                    auto dindex = str.find('#');
                    auto varName = dindex == std::string::npos ? str.substr(colonIndex+1) :
                            str.substr(colonIndex+1, dindex-colonIndex-1);
                    if (dindex == std::string::npos) {
                        if (typ == "int") {
                            node = args.get<int>(varName);
                        } else if (typ == "float") {
                            node = args.get<float>(varName);
                        } else if (typ == "str") {
                            node = args.get<std::string>(varName);
                        }
                    } else {
                        auto defString = str.substr(dindex+1);
                        if (typ == "int") {
                            node = args.get<int>(varName, std::stoi(defString));
                        } else if (typ == "float") {
                            node = args.get<float>(varName, std::stof(defString));
                        } else if (typ == "str") {
                            node = args.get<std::string>(varName, defString);
                        }
                    }
            }
        }
    }
}
std::shared_ptr<Object> makeDynamicSkeletalMesh(const ITab& node, const ITab& args) {
    using Coord = float;
    using Point = std::array<Coord, 2>;
    using N = uint32_t;

    auto offset = args.get<glm::vec2>("offset", glm::vec2(0.0f));//YamlWrapper::as<glm::vec2>(args, "offset", glm::vec2(0.0f));
    auto z = args.get<float>("z", 0.0f); // args["z"].as<float>(0.0f);
    auto parentJointId = args.get<int>("parentJointId", -1);
    auto jointId = args.get<int>("jointId");
    auto scale = args.get("scale", 1.0f);
    auto transform = args.get<glm::mat4>("transform"); //YamlWrapper::as<glm::mat4>(args, "transform");
    glm::mat4 scalingMat = glm::scale(glm::vec3(scale));

    auto localOrigin = node.get<glm::vec2>("origin");
    auto texName = node.get<std::string>("tex");
    auto tex = Engine::get().GetAssetManager().GetTex(texName);
    float texWidth = tex->GetWidth();
    float texHeight = tex->GetHeight();

    const unsigned stride = 3;
    unsigned rootJointId = 0;
    unsigned parentJointIndex = -1;

    // add key points and dimensions, if any
    auto mesh = std::make_shared<SkeletalMesh>(texName);

    node.foreach("key_points", [&] (const std::string& id, const ITab& t) {
        glm::vec2 klocal = t.as<glm::vec2>() - localOrigin;
        klocal.y = -klocal.y;
        mesh->addKeyPoint(id, klocal);

    });

//    if (meshTemplate.hasKey("dims")) {
//        auto kps = meshTemplate.get<PyDict>("dims").toDict<std::string, glm::vec2>();
//        for (const auto& kp : kps) {
//            m_dims[id][kp.first] = kp.second;
//        }
//    }

    // needs to have at least one joint
//    auto joints = node["joints"].as<std::vector<YAML::Node>>();
//    glm::vec2 localOrigin = YamlWrapper::as<glm::vec2>(joints[0]["pos"]);
//    for (const auto& joint : joints) {
//        auto index = joint["index"].as<int>();
//        // set parent if this joint is child to another joint in the same mesh
//        auto parent = joint["parent"].as<int>(-1);
//        auto pos = YamlWrapper::as<glm::vec2>(joint, "pos");
//        pos -= localOrigin;
//        pos.y = -pos.y;
//        mesh->addJoint(index, parent, pos);
//    }
//




    std::vector<Point> polygon;
    std::vector<VertexSkeletal> vertices;
    std::vector<unsigned> indices;

    auto points = node.get<std::vector<float>>("data");
    for (unsigned int i = 0 ; i < points.size(); i += stride) {
        VertexSkeletal vertex{};
        // get the pixel coords
        glm::vec2 pixel(points[i], points[i+1]);
        float parentWeight = points[i+2];
        glm::vec2 local = pixel - localOrigin;
        // flip y as pixel coordinates increase downward!
        local.y = -local.y;
        // transform local to model
        glm::vec3 modelPos = transform * scalingMat * glm::vec4(local, z, 1.0f);
        vertex.x = modelPos.x + offset.x;
        vertex.y = modelPos.y + offset.y;
        vertex.z = modelPos.z;
        // TODO m_maxBounds.addPoint(glm::vec3(vertex.x, vertex.y, vertex.z));
        vertex.s = pixel.x / texWidth;
        vertex.t = pixel.y / texHeight;
        int i1 = static_cast<int>(points[i+5]);
        int i2 = static_cast<int>(points[i+6]);
        int i3 = static_cast<int>(points[i+7]);
        vertex.index0 = jointId;
        vertex.index1 = (parentJointId == -1) ? 0 : parentJointId;
        vertex.index2 = 0;
        vertex.weight0 = (parentJointId == -1) ? 1.0f : 1.0f - parentWeight;
        vertex.weight1 = (parentJointId == -1) ? 0.0f : parentWeight;
        vertex.weight2 = 0.0f;
        polygon.push_back({vertex.x, vertex.y});
        vertices.push_back(vertex);
    }
    std::vector<std::vector<Point>> p;
    p.push_back(polygon);
    auto tri = mapbox::earcut<N>(p);
    mesh->Init(vertices, tri);
    return mesh;
}