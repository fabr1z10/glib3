//#include <monkey/model/skeletalmodel.h>
//#include <stack>
//#include <monkey/engine.h>
//#include <glm/gtx/transform.hpp>
//#include <monkey/math/geom.h>
//#include <monkey/quadmesh.h>
//#include <monkey/splineanim.h>
//#include <monkey/parabolicanim.h>
//#include <py/include/pybind11/pytypes.h>
//
//namespace py = pybind11;
//
//Bone::Bone() {}
//
//
//
//Bounds SkeletalModel::GetBounds() const {
//    // TODO
//    return Bounds(glm::vec3(-1000.0f), glm::vec3(1000.0f));
//}
//
//void SkeletalModel::addShape(std::shared_ptr<Shape> s) {
//    m_shapes.push_back(s);
//    m_maxBounds.ExpandWith(s->getBounds());
//}
//
//void SkeletalModel::setAnimShape(const std::string &anim, int shapeId) {
//    m_boxInfo[anim] = shapeId;
//    m_maxBounds.ExpandWith(m_shapes[shapeId]->getBounds());
//    m_animBounds[anim] = m_shapes[shapeId]->getBounds();
//}
//
//Bounds SkeletalModel::GetAnimBounds(const std::string & name) const {
//    auto it = m_animBounds.find(name);
//    if (it == m_animBounds.end()) {
//        return Bounds();
//    }
//    return it->second;
//}
//
//int SkeletalModel::getShapeId(const std::string &anim) {
//    auto it = m_boxInfo.find(anim);
//    if (it == m_boxInfo.end())
//        return -1;
//    return it->second;
//}
//
//SkeletalModel::SkeletalModel(const ITable & t) {
//    auto gfx = t.get<std::string>("gfx", "");
//
//    // load the bones
//    int boneCount = 0;
//
//    t.foreach<py::list>("boxes", [&] (py::list p) {
//        auto x0 = p[0].cast<float>();
//        auto y0 = p[1].cast<float>();
//        auto x1 = p[2].cast<float>();
//        auto y1 = p[3].cast<float>();
//        float width = x1 - x0;
//        float height = y1 - y0;
//        auto rect = std::make_shared<Rect>(width, height, glm::vec3(x0, y0, 0.0f));
//        this->addShape(rect);
//    });
//
//    t.foreach<pybind11::dict>("bones", [&] (const pybind11::dict& r) {
//        PyDict ref(r);
//        auto id = ref.get<std::string>("id");
//        auto quad = ref.get<glm::vec4>("quad");
//        auto gfxi = ref.get<std::string>("gfx", gfx);
//        auto parent = ref.get<std::string>("parent", "");
//        auto origin = ref.get<glm::vec2>("origin", glm::vec2(0.0f));
//        auto pos = ref.get<glm::vec2>("pos", glm::vec2(0.0f));
//        auto center = ref.get<glm::vec2>("center", glm::vec2(0.0f));
//        auto scale = ref.get<float>("scale", 1.0f);
//        auto z = ref.get<float>("z");
//
//        // width and height of the quad
//        float w = quad[2];      // TODO scale?
//        float h = quad[3];
//
//        auto mesh = std::make_shared<QuadMesh>(gfxi, w, h, center, quad[0], quad[1], quad[2], quad[3]);
//
//        auto bone = std::make_unique<Bone>();
//        bone->id = boneCount++;
//        bone->center = origin;
//        bone->mesh = mesh;
//        bone->pos = pos;
//        bone->z = z;
//        bone->scale = scale;
//        std::cerr << "bone: " << id << ", quad = (" << quad[0] << ", " << quad[1] << ", " << quad[2] << ", " << quad[3] << ")\n";
//        this->addBone(id, std::move(bone), parent);
//    });
//
//    // load the animations
//    auto anims = t.get<pybind11::dict>("animations");
//    for (auto anim : anims) {
//        auto animId = anim.first.cast<std::string>();
//        if (m_defaultAnimation.empty()) {
//            m_defaultAnimation = animId;
//        }
//        PyDict d1(anim.second.cast<pybind11::dict>());
//        PyDict d(d1.get<pybind11::dict>("anim"));
//
//        int boxId = d1.get<int>("box");
//        int castId = d1.get<int>("cast");
//
//        auto loop = d.get<bool>("loop");
//        auto type = d.get<std::string>("type");
//
//        std::shared_ptr<SkeletalAnimation> sAnim;
//        if (type == "periodic_spline") {
//            int boundltype {-1};
//            int boundrtype {-1};
//            double boundl {0.0};
//            double boundr {0.0};
//            sAnim = std::make_shared<SplineAnimation>(loop, boundltype, boundl, boundrtype, boundr);
//        } else if (type == "monotone_spline") {
//            auto pa = std::make_shared<ParabolicAnimation>(loop);
//            sAnim = pa;
//        }
//        d.foreach<pybind11::list>("keyframes", [&] (const pybind11::list& kf) {
//            float t = kf[0].cast<float>();
//            std::vector<float> angles = kf[1].cast<std::vector<float>>();
//            KeyFrame keyFrame(t, angles);
//            sAnim->addKeyFrame(keyFrame);
//        });
//        sAnim->init();
//
//        // each animation might have a box
//        if (boxId != -1) {
//            //int boxId = d.get<int>("box");
//            this->setAnimShape(animId, boxId);
//        }
//
//        if (castId != -1) {
//            float t = d1.get<float>("cast_time");
//            m_shapeCast[animId] = std::make_pair(castId, t);
//        }
//
//        this->addAnimation(animId, sAnim);
//        std::cout << "ciao " << animId;
//    }
////    t.foreach<PyTable>("animations", [&] (const PyTable& ref) {
////        auto id = ref.get<std::string>("id");
////        auto loop = ref.get<bool>("loop");
////
////        auto type = ref.get<std::string>("animtype");
////
////
////        // load the keyframes
////        //std::vector<std::string> boneIds = table.GetVector<std::string>("bones", true);
////        //anim->setBoneIds(boneIds);
////        //int boneCount = boneIds.size();
////        ref.foreach<PyTable>("frames", [&anim] (const PyTable& keyframe) {
////            auto t = keyframe.get<float>("t");
////            std::vector<float> angles = keyframe.get<std::vector<float>>("frame");
////            //if (angles.size() != boneCount) GLIB_FAIL("The number of angles in each keyframe must match the number of bones!");
////            KeyFrame kf(t, angles);
////            anim->addKeyFrame(kf);
////        });
////        //if (atable.HasKey("box")) {
////        //    glm::vec4 box = atable.Get<glm::vec4>("box");
////        //    model->addAnimSpecificShape(id, box[2], box[3], glm::vec2(box[0], box[1]));
////        //}
////
////        // add a last keyframe equal to the first in order to loop
////        //  anim->addKeyFrame(duration, firstKeyFrame);
////        //        if (atable.HasKey("box")) {
////        //            glm::vec4 box = atable.Get<glm::vec4>("box");
////        //            anim->setBounds(box[2], box[3], glm::vec2(box[0], box[1]));
////        //        }
////        anim->init();
////        addAnimation(id, anim);
////
////    });
//
//    //if (table.HasKey("box")) {
//    //    glm::vec4 box = table.Get<glm::vec4>("box");
//    //    model->setDefaultBounds(box[2], box[3], glm::vec2(box[0], box[1]));
//    //}
//
//
//    //table.ProcessVector("attack", [&] (luabridge::LuaRef ref) {
//    //LuaTable atable(ref);
//    //std::string anim = atable.Get<std::string>("anim");
//    //float t = atable.Get<float>("t");
//    //glm::vec4 box = atable.Get<glm::vec4>("box");
//    //model->addAttack(anim, t, box);
//    //});
//    //return model;
//}
//
//
//ShaderType SkeletalModel::GetShaderType() const {
//    return TEXTURE_SHADER;
//}
//
//std::vector<std::string> SkeletalModel::GetAnimations() const {
//    std::vector<std::string> anims;
//    for (const auto& m : m_animations) anims.push_back(m.first);
//    return anims;
//}
//
//std::string SkeletalModel::GetDefaultAnimation() const {
//    return m_defaultAnimation;
//}
//
////Bounds SkeletalModel::getBoundingBox(const std::vector<float> &angles) {
//	// TODO
////	return Bounds();
////}
//
//void SkeletalModel::Draw(Shader* shader, const std::vector<float>& angles) {
//    // do a depth-first scan of the sk starting from the root
//    std::stack<Bone*> s;
//    auto re = Engine::get().GetRenderingEngine();
//    auto& worldTransform = re->getModelViewMatrix();
//    std::stack<glm::mat4> tm;
//    s.push(m_root);
//    tm.push(glm::mat4(1.0f));
//    glm::mat4 viewMatrix = re->getCurrentCamera()->m_viewMatrix;
//    m_dynamicBounds = Bounds();
//
//    // find node transforms
//    std::vector<glm::mat4> a1;
//    std::vector<Bone*> a2;
//    while (!s.empty()) {
//        // get the top
//        auto& top = s.top();
//        //glm::mat4 nt = top->transform;
//        // apply the angle of this node
//        float angle = 0.0f;
//        if (top->id < angles.size())
//            angle = angles[top->id];
//
//        glm::mat4 m = glm::scale(glm::vec3(top->scale)) * glm::rotate(deg2rad * angle, glm::vec3(0,0,1));
//        glm::mat4 lpos = glm::translate(glm::vec3(top->pos, 0.0f));
//        glm::mat4 local = lpos*m*glm::translate(glm::vec3(-top->center, 0.0f));
//        local[3][2] = top->z;
////        nt[1][0] = m[1][0];
////        nt[1][1] = m[1][1];
////        nt[0][0] = m[0][0];
////        nt[0][1] = m[0][1];
//
//        glm::mat4 nodeTransform = (tm.top() * local);
//        //std::cerr << " drawing node " << top->id << " z = " << nodeTransform[3][2] << "\n";
//
//        Bounds boneBounds = top->mesh->GetBounds();
//        boneBounds.Transform(nodeTransform);
//
//        m_dynamicBounds.ExpandWith(boneBounds);
//
//        a1.push_back(nodeTransform);
//        a2.push_back(top);
//
////        glm::mat4 mvm = viewMatrix * nodeTransform;
////
////
////        // draw this node
////        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
////        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
////        top->mesh->Draw(shader, 0, 0);
//        // pop ...
//        s.pop();
//        tm.pop();
//        // ... and push the children
//
//        for (const auto& child : top->children) {
//            tm.push(nodeTransform);
//            s.push(child);
//        }
//    }
//
//    glm::mat4 shift = glm::translate(glm::vec3(0,-m_dynamicBounds.min.y,0));
//    //std::cout << m_maxBounds.min.y << ", " << m_dynamicBounds.min.y << "\n";
//    worldTransform *= shift;
//    for (size_t i = 0; i< a1.size(); ++i) {
//        glm::mat4 mvm = viewMatrix * worldTransform * a1[i];
//        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
//        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
//        a2[i]->mesh->Draw(shader, 0, 0);
//    }
//}
//
//Bone& SkeletalModel::getBone (const std::string& id) {
//    return *(m_boneMap.at(id));
//}
//
//void SkeletalModel::addBone(const std::string& id, std::unique_ptr<Bone> bone, const std::string& parent) {
//
//    m_bones.push_back(std::move(bone));
//    m_boneMap.insert(std::make_pair(id, m_bones.back().get()));
//    if (parent.empty()) {
//        m_root = m_bones.back().get();
//    } else {
//        getBone(parent).children.push_back(m_bones.back().get());
//    }
//}
//
////void SkeletalModel::setDefaultBounds(float width, float height, glm::vec2 offset) {
////    m_defaultBounds = std::make_shared<Rect>(width, height, glm::vec3(offset, 0.0f));
////    m_maxBounds.ExpandWith(m_defaultBounds->getBounds());
////
////}
////
////void SkeletalModel::addAnimSpecificShape(const std::string &animId, float w, float h, glm::vec2 offset) {
////        auto rect = std::make_shared<Rect>(w, h, glm::vec3(offset, 0.0f));
////        m_maxBounds.ExpandWith(rect->getBounds());
////        m_animSpecificBounds[animId] = rect;
////
////}
//
//Shape* SkeletalModel::getBounds(const std::string &anim) {
//    auto it = m_boxInfo.find(anim);
//
//    if (it == m_boxInfo.end())
//        return nullptr;
//    return m_shapes[it->second].get();
//    //auto it = m_animSpecificBounds.find(anim);
//    // if (it == m_animSpecificBounds.end())
//    //return m_defaultBounds.get();
//    //return it->second.get();
//}
//
////
////std::vector<Bounds> SkeletalModel::getAllBounds() const {
////    std::vector<Bounds> bounds;
////    bounds.push_back(m_defaultBounds->getBounds());
////    for (const auto& a : m_animSpecificBounds) bounds.push_back(a.second->getBounds());
////    for (const auto& b : m_attackInfo) {
////        bounds.push_back(b.second.shape->getBounds());
////    }
////    return bounds;
////
////}
//void SkeletalModel::addAnimation(const std::string& name, std::shared_ptr<SkeletalAnimation> anim) {
//    if (m_defaultAnimation.empty()) m_defaultAnimation = name;
//    m_animations.insert(std::make_pair(name, anim));
//    //auto shape = anim->getBounds();
////    if (shape != nullptr ) {
////        m_maxBounds.ExpandWith(shape->getBounds());
////    }
//}
////
////float SkeletalModel::addAttack(const std::string &anim, float t, glm::vec4 box) {
////    m_attackInfo[anim] = SkeletalAttackInfo{t, std::make_shared<Rect>(box[2], box[3], glm::vec3(box[0], box[1], 0.0f))};
////	// TODO
////	return 0.0f;
////}
//
//int SkeletalModel::hasAttack(const std::string &anim, float t0, float t1) {
//    auto it = m_shapeCast.find(anim);
//    if (it == m_shapeCast.end())
//        return -1;
//    if (it->second.second >= t0 && it->second.second <= t1)
//        return it->second.first;
//    return -1;
//}
//
//SkeletalAnimation* SkeletalModel::getAnimation(const std::string &id) {
//    return m_animations.at(id).get();
//}
//
//std::shared_ptr<Shape> SkeletalModel::shape(int id) {
//    return m_shapes[id];
//}