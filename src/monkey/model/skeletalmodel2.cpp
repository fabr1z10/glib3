//#define cimg_use_jpeg
//#define cimg_use_png
//#define cimg_display 0
//#include <monkey/CImg.h>
//#include <monkey/model/skeletalmodel2.h>
//#include <monkey/math/geom.h>
//#include <glm/gtc/type_ptr.hpp>
//
//using namespace cimg_library;
//
//SkeletalBone::SkeletalBone(const std::string &id, glm::vec2 pos) : id(id), pos(pos), parent(nullptr) {
//
//}
//
//SkeletalModel2::SkeletalModel2(const ITable & t) {
//
//
//    // get the bones
//    t.foreach<pybind11::dict>("bones", [&] (const pybind11::dict& p) {
//        PyDict p1(p);
//        auto id = p1.get<std::string>("id");
//        auto parent = p1.get<std::string>("parent", "");
//        auto pos = p1.get<glm::vec2>("pos");
//        addBone(id, pos, parent);
//    });
//
//
//    // you can create a skeletal model by passing an image
//    auto file = t.get<std::string>("file");
//    //auto dir = Engine::get().GetGameDirectory();
//    std::stringstream s;
//    s<< "/home/fabrizio/games/smb_py/" << file;
//    CImg<unsigned char> data (s.str().c_str());
//    auto width = data.width();
//    auto height = data.height();
//    int channels = data.spectrum();
//    data.permute_axes ("cxyz");
//    int cellx = 10;
//    int celly = 10;
//    int columns = width / cellx + (width % cellx != 0);
//    int rows = height / celly + (height % celly != 0);
////    for (int i = 0; i < width*height; ++i) {
////        std::cerr << i << "\n-----------------\n";
////        std::cerr << (int) data[4*i]<<"\n";
////        std::cerr << (int) data[4*i+1]<<"\n";
////        std::cerr << (int) data[4*i+2]<<"\n";
////        std::cerr << (int) data[4*i+3]<<"\n";
////        std::cerr << "<-->\n";
////
////    }
//    m_mesh = std::make_shared<TexturedMesh<VertexSkeletal>>(SKELETAL_SHADER, GL_TRIANGLES, file);
//
//    std::vector<VertexSkeletal> vertices;
//    std::vector<unsigned> indices;
//
//    auto addVertex = [&] (float x, float y) {
//        // find the two closest bones for this point
//        float yp = height - y;
//        int index0 = -1;
//        int index1 = -1;
//        float d0 = std::numeric_limits<float>::infinity();
//        float d1 = d0;
//        for (int i = 0; i < m_bones.size(); ++i) {
//            glm::vec2 P (x, yp);
//            float dist = distSq(P, m_bones[i].pos);
//            if (dist<d0) {
//                index1 = index0;
//                d1 = d0;
//                index0 = i;
//                d0 = dist;
//            } else if (dist < d1) {
//                index1 = i;
//                d1 = dist;
//            }
//        }
//        float w0 = d1 / (d0+d1);
//        float w1 = d0 / (d0+d1);
//        vertices.push_back({x, yp, 0.0f, x/width, y/height, index0, index1, w0, w1});
//
//    };
//
//    unsigned int index = 0;
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < columns; ++j) {
//            int offset = 4 * (i * celly * width + j * cellx);
//            glm::ivec2 topleft (j * cellx, i * celly);
//            std::cerr << "checking rect " << j << ", " << i << "\n";
//            bool rectAdded = false;
//            int incy = (topleft.y + celly >= height) ? (height - topleft.y) : celly;
//            int incx = (topleft.x + cellx >= width) ? (width - topleft.x) : cellx;
//
//            for (int l = 0; l < incy; ++l) {
//                if (rectAdded) break;
//                for (int k = 0; k < incx; ++k) {
//                    // check if at least one pixel is not transparent, include it
//                    // add 4 vertices, and assign them to bones!
//                    int index = offset + 4 * (l * width + k);
//                    int alpha = (int) data[index+3];
////                    std::cerr << (int) data[index]<<"\n";
////                    std::cerr << (int) data[index + 1]<<"\n";
////                    std::cerr << (int) data[index + 2]<<"\n";
////                    std::cerr << (int) data[index + 3]<<"\n";
////                    std::cerr << "---\n";
//                    if (alpha > 0) {
//                        // add 4 vertices
//                        addVertex (topleft.x, topleft.y + celly);
//                        addVertex (topleft.x + cellx, topleft.y + celly);
//                        addVertex (topleft.x + cellx, topleft.y);
//                        addVertex (topleft.x, topleft.y);
//                        indices.push_back(index);
//                        indices.push_back(index + 1);
//                        indices.push_back(index + 2);
//                        indices.push_back(index + 3);
//                        indices.push_back(index);
//                        indices.push_back(index + 1);
//                        index += 4;
//
//                        std::cerr << "Adding rect (" << j << ", " << i << ")\n";
//                        rectAdded = true;
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    m_mesh->Init(vertices, indices);
//
//}
//
//void SkeletalModel2::addBone(const std::string &id, glm::vec2 pos, const std::string &parent) {
//
//    m_bonesMap.insert(std::make_pair(id, m_bones.size()));
//    m_bones.emplace_back(SkeletalBone(id, pos));
//    if (!parent.empty()) {
//        int parentId = m_bonesMap.at(parent);
//        m_bones.back().parent = &m_bones[parentId];
//        m_bones[parentId].children.push_back(&m_bones.back());
//    } else {
//        // this is the root
//        m_root = &m_bones.back();
//    }
//
//}
//
//
//
//void SkeletalModel2::recalcBones() {
//
//    std::list<SkeletalBone*> bones;
//    bones.push_back(m_root);
//    while (!bones.empty()) {
//        auto top = bones.front();
//        if (top->parent == nullptr) {
//            top->worldTransform = top->localTransform;
//        } else {
//            top->worldTransform = top->parent->worldTransform * top->localTransform;
//        }
//    }
//}
//
//ShaderType SkeletalModel2::GetShaderType() const {
//    return SKELETAL_SHADER;
//}
//
//Bounds SkeletalModel2::GetBounds() const {
//    // TODO
//    return Bounds(glm::vec3(-1000.0f), glm::vec3(1000.0f));
//}
//
//void SkeletalModel2::Draw(Shader * shader, const std::unordered_map<std::string, glm::mat4> &bonesTransform) {
//
//    // find the world transform
//    std::list<SkeletalBone*> bones;
//    bones.push_back(m_root);
//    while (!bones.empty()) {
//        auto top = bones.front();
//        // get transform for this bone
//        auto it = bonesTransform.find(top->id);
//        glm::mat4 local = (it == bonesTransform.end()) ? it->second : glm::mat4(1.0f);
//        if (top->parent == nullptr) {
//            top->worldTransform = local;
//        } else {
//            top->worldTransform = top->parent->worldTransform * local;
//        }
//    }
//
//    // pass bone transform to shader
//    auto bonesLoc = glGetUniformLocation(shader->GetProgId(), "bones");
//    glUniformMatrix4fv(bonesLoc, m_boneTransform.size(), GL_FALSE, glm::value_ptr(m_boneTransform[0]));
//
//}