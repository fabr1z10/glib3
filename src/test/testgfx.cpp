#include <test/testgfx.h>
#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/meshfactory.h>
#include <test/controller.h>
#include <iostream>
#include <algorithm>
#include <gfx/textmesh.h>
#include <test/timeformatter.h>
#include <test/global.h>

StationPlot::StationPlot(const std::string& id) : SceneFactory(), m_stationId(id) {

}
std::shared_ptr<Entity> StationPlot::Create() {

    auto root = std::make_shared<Entity>();

    auto mainNode = std::make_shared<Entity>();
    m_main = mainNode.get();
    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600));
    cam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    mainNode->SetCamera(std::move(cam));
    root->AddChild(mainNode);
    Railway& r = Config::get().GetRailway();
    auto& s = r.GetStation(m_stationId);
    auto lps = s.getLinePoints();
    ExtendFromPoint(s, lps[0], 0, 0);
return root;
}

void StationPlot::ExtendFromPoint(Station& s, int id, float x, float y) {
    if (pointsDone.count(id)>0)
        return;
    pointsDone.insert(id);

    std::cout << "point: " << id << "\n";
    if (s.isLinePoint(id)) {
        auto gfxNode = std::make_shared<Entity>();
        auto r1 = std::make_shared<Renderer>();
        r1->SetMesh(MeshFactory::CreateBoxMesh(2, 2, glm::vec4(1.0f)));
        gfxNode->AddComponent(r1);
        gfxNode->SetPosition(glm::vec3(x, y, 0.0f));
        m_main->AddChild(gfxNode);
    }

    auto& d = s.GetRoutesStartingAt(id);
    int n = 0;
    float dy = 5;
    for (auto& e : d) {
        std::cout << "goes to " << e.endingPoint << "\n";
        //if (s.isLinePoint(e.endingPoint)) {
            // draw line
            glm::vec2 A(1,1);
            glm::vec2 B(5,y+n*dy);
            glm::vec2 C(5+20,y+n*dy);
            auto gfxNode = std::make_shared<Entity>();
            auto r1 = std::make_shared<Renderer>();
            r1->SetMesh(MeshFactory::CreateLineMesh(A, B, glm::vec4(1.0f), 0.0f));
            gfxNode->AddComponent(r1);
            gfxNode->SetPosition(glm::vec3(x, y, 0.0f));
            auto gfxNode2 = std::make_shared<Entity>();
            auto r12 = std::make_shared<Renderer>();
            r12->SetMesh(MeshFactory::CreateLineMesh(B, C, glm::vec4(1.0f), 0.0f));
            gfxNode2->AddComponent(r12);
            gfxNode2->SetPosition(glm::vec3(x, y, 0.0f));
            m_main->AddChild(gfxNode);
            m_main->AddChild(gfxNode2);

            n++;
//        } else if (s.isStoppingPoint(e.endingPoint)) {
//            auto gfxNode = std::make_shared<Entity>();
//            auto r1 = std::make_shared<Renderer>();
//            r1->SetMesh(MeshFactory::CreateLineMesh(glm::vec2(x, y+n*dy), glm::vec2(x+20, y+n*dy), glm::vec4(1.0f), 0.0f));
//            gfxNode->AddComponent(r1);
//            gfxNode->SetPosition(glm::vec3(0, 0, 0.0f));
//            m_main->AddChild(gfxNode);
//            //ExtendFromPoint(s, e, x+20, y+n*dy);
//            n++;
//
//        }
        ExtendFromPoint(s, e.endingPoint, x+20, y+n*dy);
    }
    //return root;

}


std::shared_ptr<Entity> Factory1::Create() {

    auto entity = std::make_shared<Entity>();

    auto gfxNode = std::make_shared<Entity>();
    gfxNode->SetLayer(1);
    auto r1 = std::make_shared<Renderer>();
    r1->SetMesh(MeshFactory::CreateBoxMesh(50, 100, glm::vec4(1.0f)));
    gfxNode->AddComponent(r1);
    gfxNode->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    entity->AddChild(gfxNode);
    
    // create engine node
    auto engineNode = std::make_shared<Entity>();
    
    auto renderingEngine = std::make_shared<RenderingEngine>();
    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600));
    //auto controller = std::make_shared<ViewerController>(cam.get(), this);
    cam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    renderingEngine->AddCamera (std::move(cam));
    renderingEngine->AddShader(COLOR_SHADER);
    engineNode->AddComponent(renderingEngine);
    //engineNode->AddComponent(controller);
    entity->AddChild(engineNode);
    
    return entity;

}

struct StationInfo {
    float x, y, height;

};

//void Factory2::DrawLineStemmingFrom(int stationId, float x, float y) {
//
//    auto iter = connections.find(stationId);
//    Station* s = Railway::get().GetStation(stationId);
//    std::cout << "Drawing station " << s->GetName() << " at " << x << ", " << y << "\n";
//    done.insert(stationId);
//    float dy=0;
//    for (auto& c : iter->second) {
//
//        if (done.find(c) == done.end()) {
//            DrawLineStemmingFrom(c, x + 10, y + dy);
//            dy+=10;
//        }
//
//    }
//}
//
//std::shared_ptr<Entity> Factory2::CreateLabel (const std::string& text, glm::vec4 color, glm::vec2 pos, float size, int layer) {
//    auto gfxNode = std::make_shared<Entity>();
//    gfxNode->SetLayer(layer);
//    auto r1 = std::make_shared<Renderer>();
//    Font* f = Engine::get().GetAssetManager().GetFont("main");
//    std::shared_ptr<IMesh> m(new TextMesh(f, text, size, BOTTOM));
//    r1->SetMesh(m);
//    gfxNode->AddComponent(r1);
//    gfxNode->SetPosition(glm::vec3(pos.x, pos.y, 0.0f));
//    return gfxNode;
//}
//
//std::shared_ptr<Entity> Factory2::Create() {
//
//    Engine::get().GetAssetManager().AddFont("main", "/home/fabrizio/Scaricati/arial.ttf");
//
//    auto entity = std::make_shared<Entity>();
////
////    // create one node showing a square
//    float dxs = 80.0f;
//    float height = 50;
//    float width = 20;
//    auto trainNames = m_solution.GetTrainNames();
//    int iTrain = 0;
//    Railway& r = Config::get().GetRailway();
//    for (auto& trainName : trainNames) {
//        auto stations = m_solution.GetStations(trainName);
//        // see if I have any overlapping with existing stations
//        bool overlaps{false};
//        bool goingRight {true};
//        //float startX = 0;
//
//        int overlappingIndex = -1;
//        float overlappingX {0};
//        for (int i = 0; i < stations.size(); ++i) {
//            std::string s = stations[i];
//            if (m_stations.find(s) != m_stations.end()) {
//                // found overlapping!
//                Station& st = r.GetStation(s);
//                std::cout << "Train " << trainName << " overlaps at station " << st.GetName() << "\n";
//                std::cout << "Check if train is going left or right.\n";
//                overlaps = true;
//                overlappingX = m_stations[s].x;
//                if (i < stations.size() - 1) {
//                    auto it = m_stations.find(stations[i + 1]);
//                    if (it != m_stations.end()) {
//                        if (it->second.x < overlappingX) {
//                            goingRight = false;
//                        }
//                    }
//                }
//                std::cout << "Train is going " << (goingRight ? "right" : "left") << "\n";
//                overlappingIndex = i;
//                break;
//
//            }
//        }
//        // if overlapping, start adding nodes at the correct location.
//        // if i is the overlapping index, and x is the coordinate of the 1st overlapping station,
//        // the current train will start at x + (left)*i*dx, where left = -1 or +1
//        // if no overlapping, the train will be parallel, and start at x
//        float dx=10;
//        trainDir[trainName] = goingRight;
//        // add stations AFTER overlapping index
//        // if train is going RIGHT --> positive inc , otherwise negative
//
//
//        float dir = goingRight ? 1.0 : -1.0; //(overlaps ? (overlappingX + (goingRight ? -1.0 : 1.0) * overlappingIndex * dx) : 0.0);
//        float x = overlaps ? overlappingX + dir*dxs : 0.0f;
//
//        // if not overlapping, then overlappingIndex = -1 and therefore everything works fine
//        for (int i = overlappingIndex+1; i < stations.size(); ++i) {
//            if (m_stations.find(stations[i]) == m_stations.end()) {
//                // station not added yet
//                float yt = iTrain*10.0f;
//                m_stations[stations[i]] = StationLocation{x,yt};
//                Station& st = r.GetStation(stations[i]);
//                std::cout << "Adding station " << st.GetName() << " at " << x << ", " << yt << "\n";
//
//            }
//            x+= dir * dxs;
//        }
//        // add stations BEFORE overlapping index
//        x = overlaps ? overlappingX - dir*dxs : 0.0f;
//        for (int i = overlappingIndex-1 ; i >= 0; --i) {
//            if (m_stations.find(stations[i]) == m_stations.end()) {
//                // station not added yet
//                float yt = iTrain*10.0f;
//                m_stations[stations[i]] = StationLocation{x,yt};
//                Station& st = r.GetStation(stations[i]);
//                std::cout << "Adding station " << st.GetName() << " at " << x << ", " << yt << "\n";
//
//            }
//            x-= dir*dxs;
//        }
//
//
//        iTrain++;
//
//
//
//    }
//
//    // draw stations
//
//    for (auto& s : m_stations) {
//        Station& station = r.GetStation(s.first);
//        auto gfxNode = std::make_shared<Entity>();
//        gfxNode->SetLayer(1);
//        auto r1 = std::make_shared<Renderer>();
//        r1->SetMesh(MeshFactory::CreateBoxMesh(width, height, glm::vec4(1.0f)));
//        gfxNode->AddComponent(r1);
//        gfxNode->SetPosition(glm::vec3(s.second.x, s.second.y, 0.0f));
//        entity->AddChild(gfxNode);
//
//        // adding a text with station id
//        entity->AddChild(CreateLabel(station.GetShortName(), glm::vec4(1.0f), glm::vec2(s.second.x, s.second.y + height + 10), 10));
//
//    }
//    int trackDrawn = 0;
//    for (auto& trainName : trainNames) {
//        auto stations = m_solution.GetStations(trainName);
//        for (int i = 1; i<stations.size();++i) {
//            auto tracks = r.GetTracksConnecting(stations[i-1],stations[i]);
//            for (auto& track : tracks) {
//                Track& tr = r.GetTrack(track);
//                //bool reverseOrder = tr.GetStationA() != stations[i-1];
//                double trackLength {0};
//                auto trackCircuits = tr.GetTrackCircuits();
//                //if (reverseOrder)
//                //    std::reverse(std::begin(trackCircuits), std::end(trackCircuits));
//                for (auto& tc : trackCircuits) {
//                    trackLength += tc->GetLength(); // tr.GetT Railway::get().GetResource(tc)->GetLength();
//                }
//                // get index of station A
//                int iA, iB;
//                if (tr.GetStationA() == stations[i-1]) {
//                    iA = i-1;
//                    iB = i;
//
//                } else {
//                    iA = i;
//                    iB = i-1;
//                }
//
//                StationLocation lA = m_stations[stations[iA]];
//                StationLocation lB = m_stations[stations[iB]];
//                float x0, x1, y0, y1;
//                if (lA.x < lB.x) {
//                    x0 = lA.x + width;
//                    x1 = lB.x;
//                    y0 = lA.y;
//                    y1 = lB.y;
//                } else {
//                    x0 = lA.x;
//                    x1 = lB.x + width;
//                    y0 = lA.y;
//                    y1 = lB.y;
//                }
//                float dy {0};
//                if (tr.GetMainName() == "MT 1")
//                    dy = 0;
//                else if (tr.GetMainName()=="MT 2")
//                    dy=10;
//                else if (tr.GetMainName()=="MT 3")
//                    dy = 20;
//                y0 += dy;
//                y1 += dy;
////                if (l1.x < l2.x) {
////                    x0 = l1.x + width;
////                    x1 = l2.x;
////                    y0 = l1.y + dy;
////                    y1 = l2.y + dy;
////                } else {
////                    x0 = l2.x + width;
////                    x1 = l1.x;
////                    y0 = l2.y + dy;
////                    y1 = l1.y + dy;
////                }
//                glm::vec2 P(x0, y0);
//                glm::vec2 unitVec = glm::normalize(glm::vec2(x1, y1) - P);
//                float vecLength = glm::length(glm::vec2(x1, y1) - P);
//
//                for (auto& tc : trackCircuits) {
//                    //auto res = Railway::get().GetResource(tc);
//                    double tcLength = tc->GetLength();
//                    double pctLength = tcLength / trackLength;
//                    m_loc[tc->GetShortName()].pts.push_back(P);
//                    P+= unitVec * vecLength * static_cast<float>(pctLength);
//                    m_loc[tc->GetShortName()].pts.push_back(P);
//                }
//
//                auto gfxNode = std::make_shared<Entity>();
//                gfxNode->SetLayer(1);
//                auto r1 = std::make_shared<Renderer>();
//                r1->SetMesh(MeshFactory::CreateLineMesh(glm::vec2(x0, y0), glm::vec2(x1, y1), glm::vec4(1.0f)));
//                gfxNode->AddComponent(r1);
//                entity->AddChild(gfxNode);
//                entity->AddChild(CreateLabel(tr.GetShortName(), glm::vec4(1.0f), glm::vec2(0.5f*(x0+x1), 0.5f*(y0+y1)), 8));
//                trackDrawn++;
//                std::cout << "Drawing track " << track << " from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ")\n";
//            }
//        }
//    }
//
//    // draw trains
//    auto trainNode = std::make_shared<Entity>();
//    TimeFormatter tf(m_solution.GetNow());
//    trainNode->AddChild(CreateLabel(tf.toString(), glm::vec4(1.0), glm::vec2(-400.0f, 300.0f), 10, 2));
//    m_trainNode = trainNode.get();
//    entity->AddChild(trainNode);
//
//    // create engine node
//    auto engineNode = std::make_shared<Entity>();
//
//    auto renderingEngine = std::make_shared<RenderingEngine>();
//    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600, 1));
//    auto camFixed = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600, 2));
//    auto controller = std::make_shared<ViewerController>(cam.get(), this, m_solution.GetNow());
//    cam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
//    camFixed->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
//    renderingEngine->AddCamera (std::move(cam));
//    renderingEngine->AddCamera (std::move(camFixed));
//    renderingEngine->AddShader(COLOR_SHADER);
//    renderingEngine->AddShader(TEXT_SHADER);
//    engineNode->AddComponent(renderingEngine);
//    engineNode->AddComponent(controller);
//    entity->AddChild(engineNode);
//
//    return entity;
//
//}
////
////
//void Factory2::RefreshTrains(double t) {
//    m_trainNode->ClearAllChildren();
//    TimeFormatter tf(t);
//    std::cout << "Time now: " << tf << "\n";
//    auto trainNames = m_solution.GetTrainNames();
//    for (auto &train : trainNames) {
//        auto pos = m_solution.GetPosition(train, t);
//        glm::vec2 avgPos(0);
//        for (auto &p : pos.positions) {
//            //auto r =     Railway::get().GetResource(p.resourceId);
//            auto r = p.res;
//            auto resType = r->GetType();
//            if (resType == ResourceType::TRACK_CIRCUIT) {
//                double len = r->GetLength();
//                double pctHead = p.xHead / len;
//                double pctTail = p.xTail / len;
//                auto locIt = m_loc.find(r->GetShortName());
//                if (locIt != m_loc.end()) {
//                    //glm::vec2 axis = glm::normalize(locIt->second.pts[1] - locIt->second.pts[0]);
//                    //bool isGoingRight = trainDir[train];
//                    glm::vec2 SP;
//                    glm::vec2 axis;
//
//                    if (p.backwards) {
//                        SP = locIt->second.pts[1];
//                        axis = glm::normalize(locIt->second.pts[0] - locIt->second.pts[1]);
//
//                    } else {
//                        SP = locIt->second.pts[0];
//                        axis = glm::normalize(locIt->second.pts[1] - locIt->second.pts[0]);
//
//                    }
//                    float length = glm::length(locIt->second.pts[1] - locIt->second.pts[0]);
////
////
////                    if (isGoingRight) {
////                        SP = locIt->second.pts[0];
////                    } else {
////                        axis = -axis;
////                        SP = locIt->second.pts[1];
////                    }
//                    glm::vec2 A = SP + axis * (length * static_cast<float>(pctHead));
//                    glm::vec2 B = SP + axis * (length * static_cast<float>(pctTail));
//                    auto gfxNode = std::make_shared<Entity>();
//                    gfxNode->SetLayer(1);
//                    auto r1 = std::make_shared<Renderer>();
//                    r1->SetMesh(MeshFactory::CreateLineMesh(A, B, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f));
//                    avgPos += (A + B) * 0.5f;
//                    gfxNode->AddComponent(r1);
//                    m_trainNode->AddChild(gfxNode);
//                }
//            } else if (resType == ResourceType::STATION_ROUTE) {
//                auto sr = dynamic_cast<StationRoute *>(r);
//                StationLocation loc = m_stations[sr->GetStationId()];
//                avgPos += glm::vec2(loc.x, loc.y);
//            }
//        }
//        avgPos *= (1.0 / static_cast<float>(pos.positions.size()));
//        m_trainNode->AddChild(CreateLabel(train, glm::vec4(1.0, 0.0, 0.0, 1.0), avgPos + glm::vec2(0.0f, -5.0f), 8));
//    }
//    m_trainNode->AddChild(CreateLabel(tf.toString(), glm::vec4(1.0), glm::vec2(-400.0f, 300.0f), 10, 2));
//}
