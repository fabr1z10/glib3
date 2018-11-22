#include <test/testgfx.h>
#include <gfx/renderingengine.h>
#include <gfx/components/renderer.h>
#include <gfx/meshfactory.h>
#include <test/controller.h>
#include <iostream>
#include <algorithm>
#include <gfx/textmesh.h>
#include <test/timeformatter.h>
#include <glm/gtx/transform.hpp>

void SceneFactory3::Plot(const std::string& id, int x, int y) {

    std::cout << "plotting " << id << " at (" << x << ", " << y << ")\n";
    stationPos[id] = std::make_pair(x, y);
    auto tracks = r.GetStation(id).GetConnectingTracks();
    for (auto& t : tracks) {
        if (t[0] == 'F')
            continue;
        std::string sa = r.GetTrack(t).GetStationA();
        std::string sb = r.GetTrack(t).GetStationB();
        int incx = 0;
        int incy = 0;
        std::string s;
        if (sa == id) {
            s = sb;
            incx = 1;
        } else {
            s = sa;
            incx = -1;
        }
        if (stations.count(s) > 0 && stationPos.count(s) == 0)
            Plot(s, x+incx, y);
    }
}

void SceneFactory3::AdvanceTime(int n) {
    int tentative = m_currentTime + n;
    if (tentative >= m_tMin && tentative <= m_tMax) {
        m_currentTime = tentative;
        TimeFormatter tf(m_currentTime);
        m_timeLabel->UpdateText(tf.toString());
        RefreshTrains();
    }


}

std::shared_ptr<Entity> SceneFactory3::CreateLine(glm::vec2 A, glm::vec2 B, glm::vec3 col) {
    auto node = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    std::string draw = "outline";
    glm::vec4 color(col, 1.0f);
    auto shape = std::make_shared<Line>(A, B);
    auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
    renderer->SetMesh(mesh);
    renderer->SetTint(color);
    node->AddComponent(renderer);
    return node;
}

std::shared_ptr<Entity> SceneFactory3::CreateRect(glm::vec3 pos, float width, float height, glm::vec3 col) {
    auto node = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    std::string draw = "outline";
    glm::vec4 color(col, 1.0f);
    auto shape = std::make_shared<Rect>(width, height, glm::vec2(-width*0.5f, -height*0.5f));
    auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
    renderer->SetMesh(mesh);
    renderer->SetTint(color);
    node->AddComponent(renderer);
    node->SetPosition(pos);
    return node;
}

std::shared_ptr<Entity> SceneFactory3::CreateCircle(glm::vec3 pos, float radius, glm::vec3 col) {
    auto node = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    std::string draw = "solid";
    glm::vec4 color(col, 1.0f);
    auto shape = std::make_shared<Circle>(radius);
    auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
    renderer->SetMesh(mesh);
    renderer->SetTint(color);
    node->AddComponent(renderer);
    node->SetPosition(pos);
    return node;

}

std::shared_ptr<Entity> SceneFactory3::CreateText(const std::string& text, float x, float y, float size, TextAlignment align, glm::vec3 color) {
    auto txtNode = std::make_shared<Entity>();
    auto txtRenderer = std::make_shared<Renderer>();
    std::string font = "main";
    float maxWidth = 800.0f;
    Font *f = Engine::get().GetAssetManager().GetFont(font);
    auto txtMesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
    glm::vec2 offset = txtMesh->getOffset();
    txtRenderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
    txtRenderer->SetTint(glm::vec4(color, 1.0f));
    txtRenderer->SetMesh(txtMesh);
    txtNode->AddComponent(txtRenderer);
    txtNode->SetPosition(glm::vec3(x, y, 0.0f));
    return txtNode;
}


std::shared_ptr<Entity> SceneFactory3::Create() {
    r = Config::get().GetRailway();
    auto root = std::make_shared<Entity>();


    auto mainNode = std::make_shared<Entity>();
    auto UINode = std::make_shared<Entity>();

    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600));
    cam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    mainNode->SetCamera(std::move(cam));
    mainNode->AddComponent(std::make_shared<ViewerController>(this));
    root->AddChild(mainNode);

    auto camUI = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600));
    camUI->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    UINode->SetCamera(std::move(camUI));
    root->AddChild(UINode);

    auto trainsNode = std::make_shared<Entity>();
    mainNode->AddChild(trainsNode);
    m_trainContainer = trainsNode.get();




    //std::unordered_set<std::string> stationsTraversed;

    for (auto& p :sol.m_plans) {
        for (auto& i : p.second->m_items) {
            if (!i.second.isTrack) {
                stations.insert(i.second.id);
            }
        }
        // for trains that are currently on a track, also add the previous station
        auto it = p.second->m_items.begin();
        if (it->second.isTrack) {
            auto& track = r.GetTrack(it->second.id);
            if (it->second.fwd) {
                stations.insert(track.GetStationA());
            }
            else {
                stations.insert(track.GetStationB());
            }
        }
        // if this is the last track, add the next station
        auto it2 = p.second->m_items.rbegin();
        if (it2->second.isTrack) {
            auto& track = r.GetTrack(it2->second.id);
            if (it2->second.fwd) {
                stations.insert(track.GetStationB());
            }
            else {
                stations.insert(track.GetStationA());
            }

        }

    }





    std::cout << "stations traversed:\n";
    for (auto& s : stations)
        std::cout << s<<"\n";
    Plot(*stations.begin(), 0, 0);



    for (auto& s : stationPos) {
        auto node = std::make_shared<Entity>();
        glm::vec2 stationPos(s.second.first*50, s.second.second*50);
        node->SetPosition(glm::vec3(stationPos, 0.0f));
        auto renderer = std::make_shared<Renderer>();
        std::string draw = "outline";
        glm::vec4 color (1.0f);
        auto shape = std::make_shared<Rect>(10.0f, 10.0f, glm::vec2(-5,-5));
        auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
        renderer->SetMesh(mesh);
        renderer->SetTint(color);
        node->AddComponent(renderer);
        m_stationRenderingInfo[s.first] = stationPos;
        mainNode->AddChild(node);

//        auto txtNode = std::make_shared<Entity>();
//        auto txtRenderer = std::make_shared<Renderer>();
//        std::string text = s.first;
//        std::string font = "main";
//        float size = 6.0f;
//        TextAlignment align = CENTER;
//        float maxWidth = 100.0f;
//        Font* f = Engine::get().GetAssetManager().GetFont(font);
//        auto txtMesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
//        glm::vec2 offset = txtMesh->getOffset();
//        txtRenderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
//        txtRenderer->SetTint(color);
//        txtRenderer->SetMesh(txtMesh);
//        txtNode->AddComponent(txtRenderer);
//        node->AddChild(txtNode);
//
        node->AddChild(CreateText(s.first, 0.0f, 0.0f, 6.0f, CENTER, glm::vec3(1.0f)));
    }

    // plot all tracks
    std::unordered_set<std::string> plottedTracks;
    for (auto& s : stationPos) {
        auto tracksFromStation = r.GetStation(s.first).GetConnectingTracks();
        std::unordered_map<std::string, std::vector<std::string>> stationToTracks;
        for (auto& t : tracksFromStation) {
            if (t[0] == 'F')
                continue;
            auto& track = r.GetTrack(t);
            if (track.GetStationA() == s.first) {
                stationToTracks[track.GetStationB()].push_back(t);
            }
            else {
                stationToTracks[track.GetStationA()].push_back(t);
            }
        }
        int s1x = s.second.first;
        int s1y = s.second.second;
        std::cout << "Station : " << s.first << "\n";

        for (auto& m: stationToTracks) {
            if (stations.count(m.first) > 0) {
                // find positions
                auto it = stationPos.find(m.first);
                int s2x = it->second.first;
                int s2y = it->second.second;
                std::cout << "is connected to station " << m.first << " via tracks ";
                glm::vec2 initialPos;
                glm::vec2 endPos;
                float inc = 10.0 / (m.second.size() + 1);
                if (s2x > s1x) {
                    // station 2 is right of station 1
                    initialPos = glm::vec2(s1x*50+5 ,s1y*50-5 + inc);
                    endPos = glm::vec2(s2x*50-5 ,s2y*50-5 + inc);
                } else {
                    initialPos = glm::vec2(s1x*50-5 ,s1y*50-5 + inc);
                    endPos = glm::vec2(s2x*50+5 ,s2y*50-5 + inc);
                }
                for (auto& tt : m.second) {
                    if (plottedTracks.count(tt) == 0) {
                        auto &track = r.GetTrack(tt);
                        plottedTracks.insert(tt);
                        glm::vec2 labelStart;
                        glm::vec2 dir;
                        glm::vec2 cStart;
                        glm::vec2 cEnd;
                        glm::vec2 cdir;
                        if (track.GetStationA() == s.first) {
                            labelStart = initialPos;
                            dir = endPos - initialPos;
                            cStart = initialPos;
                            cEnd = endPos;
                            cdir = glm::normalize(endPos - initialPos);
                        } else {
                            labelStart = endPos;
                            dir = initialPos -endPos;
                            cStart = endPos;
                            cEnd = initialPos;
                            cdir = glm::normalize(initialPos-endPos);
                        }
                        dir = glm::normalize(dir);
                        //std::cout << "Plotting track " << tt << " between station " << s.first << " at (" << s1x << ", "
                         //         << s1y << ") and " << m.first << " at (" << s2x << ", " << s2y << ")\n";
                        auto node = std::make_shared<Entity>();
                        //node->SetPosition(glm::vec3(s.second.first * 50, s.second.second * 50, 0));
                        auto renderer = std::make_shared<Renderer>();
                        std::string draw = "outline";
                        glm::vec4 color(1.0f);
                        auto shape = std::make_shared<Line>(initialPos, endPos);
                        std::cout << "Track " << tt << " from (" << cStart.x << ", " << cStart.y << ") to (" << cEnd.x << ", " << cEnd.y << ")\n";
                        auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
                        renderer->SetMesh(mesh);
                        renderer->SetTint(color);
                        node->AddComponent(renderer);
                        mainNode->AddChild(node);

                        initialPos.y += inc;
                        endPos.y += inc;
                        // see how many track circuits I have
                        auto tc = r.GetTrack(tt).GetTrackCircuits();
                        float lengthTC = glm::length(endPos -initialPos) / tc.size();
                        int trackLength = r.GetTrack(tt).GetLength();
                        labelStart += dir * 0.5f * lengthTC;
                        float totalGfxLength = glm::length(cEnd-cStart);
                        for (auto &trackCircuit : tc) {
                            std::cout << "plot label for " << trackCircuit->GetShortName()<< "\n";
                            auto txtNode = std::make_shared<Entity>();
                            auto txtRenderer = std::make_shared<Renderer>();
                            std::string text = trackCircuit->GetShortName();
                            int trackCircuitLength = trackCircuit->GetLength();
                            float pct = trackCircuitLength / static_cast<float>(trackLength);
                            std::string font = "main";
                            float size = 1.0f;
                            TextAlignment align = BOTTOM;
                            float maxWidth = 100.0f;
                            Font *f = Engine::get().GetAssetManager().GetFont(font);
                            auto txtMesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
                            glm::vec2 offset = txtMesh->getOffset();
                            txtRenderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
                            txtRenderer->SetTint(color);
                            txtRenderer->SetMesh(txtMesh);
                            txtNode->AddComponent(txtRenderer);

                            labelStart += dir * lengthTC;
                            glm::vec2 cEnd = cStart + cdir * pct * totalGfxLength;
                            txtNode->SetPosition((cStart+cEnd)*0.5f);
                            m_trackCircuitRenderingInfo[text] = glm::vec4(cStart, cEnd);
                            std::cout << "Track circuit " << text << " from (" << cStart.x << ", " << cStart.y << ") to (" << cEnd.x << ", " << cEnd.y << ")\n";
                            cStart = cEnd;
                            mainNode->AddChild(CreateLine(cEnd, cEnd + glm::vec2(0,2), glm::vec3(1.0f)));
                            mainNode->AddChild(txtNode);
                        }
                    }
                }
            }
        }

    }

//    auto& stations = sol.getStations();
//    int n = 0;
//    float x = 0.0f;
//    for (auto& s : stations) {
//        for (auto& st : s.second) {
//            auto plt = std::make_shared<StationPlot>(st);
//            auto node = plt->Get();
//            node->SetPosition(glm::vec2(x, 0));
//            mainNode->AddChild(node);
//            n++;
//            std::cout << "Plotting station " << st << "\n";
//            x += plt->GetWidth() + 50.0f;
//            m_stations[st] = plt;
//            if (n>2) break;
//        }
//        if (n>2)
//            break;
//
//    }
//    // plot the tracks
//    auto a = std::make_shared<Entity>();
//    auto r1 = std::make_shared<Renderer>();
//    std::vector<glm::vec2> pts;
//    std::vector<std::pair<int,int>> edg;
//
//    for (auto& s : m_stations) {
//        s.second->GetStationId();
//        Railway& r = Config::get().GetRailway();
//        auto tracks = r.GetStation(s.second->GetStationId()).GetConnectingTracks();
//        for (auto& track : tracks) {
//            if (track != "-1") {
//                auto& t = r.GetTrack(track);
//                std::string sa = t.GetStationA();
//                std::string sb = t.GetStationB();
//                auto it1 = m_stations.find(sa);
//                auto it2 = m_stations.find(sb);
//                if (it1 != m_stations.end() && it2 != m_stations.end()) {
//                    glm::vec2 P1 = it1->second->GetTrackPosition(track);
//                    glm::vec2 P2 = it2->second->GetTrackPosition(track);
//                    // draw line connecting tracks
//                    edg.push_back(std::make_pair(pts.size(), pts.size() + 1));
//                    pts.push_back(P1);
//                    pts.push_back(P2);
//                }
//            }
//            std::cout << track << "\n";
//
//        }
//    }
//    PolyLine p(pts,edg);
//    r1->SetMesh(MeshFactory::CreateMesh(p, 0.0f, glm::vec4(0.2f, 0.8f, 0.8f, 1.0f)));
//    a->AddComponent(r1);
//    a->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
//    mainNode->AddChild(a);

    m_currentTime = sol.GetNow();
    m_tMin = m_currentTime;
    m_tMax = m_tMin + 7200;
    TimeFormatter tf(m_currentTime);
    auto timeLabel = CreateText(tf.toString(), -400, 300, 16, TOP_LEFT, glm::vec3(1.0f, 1.0f, 1.0f));
    m_timeLabel = dynamic_cast<TextMesh*>(timeLabel->GetComponent<Renderer>()->GetMesh());
    UINode->AddChild(timeLabel);
//    auto p = sol.GetTrainPosition("MNPHK", 1526450400);
//    p.Dump();
//
//    p = sol.GetTrainPosition("MNPHK", 1526450678);
//    p.Dump();
//
//    p = sol.GetTrainPosition("MNPHK", 1526450677);
//    p.Dump();
//    p = sol.GetTrainPosition("MNPHK", 1526450679);
//    p.Dump();
    RefreshTrains();
    return root;
}

void SceneFactory3::RefreshTrains() {
    // clear train node
    //return;
    m_trainContainer->ClearAllChildren();
    std::map<std::string, std::vector<std::string>> trainsInStation;
    for (auto& s : sol.m_trainDetails){
        std::string trainId = s.first;
        auto positions = sol.GetTrainPosition(trainId, m_currentTime);

        glm::vec2 HeadPos;
        int count = 0;
        for (auto& pos : positions.pos) {
            // render current position
            if (pos.isTrack) {
                glm::vec4 trackCircuitPos = m_trackCircuitRenderingInfo.at(pos.id2);
                glm::vec2 A(trackCircuitPos[0], trackCircuitPos[1]);
                glm::vec2 B(trackCircuitPos[2], trackCircuitPos[3]);
                glm::vec2 HeadPoint = A + (B - A) * (pos.xHead / pos.length);
                glm::vec2 TailPoint = A + (B - A) * (pos.xTail / pos.length);

                auto node = std::make_shared<Entity>();
                auto renderer = std::make_shared<Renderer>();
                std::string draw = "outline";
                glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
                auto shape = std::make_shared<Line>(TailPoint, HeadPoint);
                auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
                renderer->SetMesh(mesh);
                renderer->SetTint(color);
                node->AddComponent(renderer);
                m_trainContainer->AddChild(node);
                if (count == 0)
                    HeadPos = HeadPoint;
            } else {
                glm::vec2 stationPos = m_stationRenderingInfo.at(pos.id);
                m_trainContainer->AddChild(CreateRect(glm::vec3(stationPos,1.0f), 10.0f,10.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
                if (count == 0) {
                    HeadPos = stationPos + glm::vec2(0,10.f+ trainsInStation.count(pos.id)*2.0f);
                }
                trainsInStation[pos.id].push_back(trainId);
            }
            count++;
        }
        m_trainContainer->AddChild(CreateText(trainId, HeadPos.x, HeadPos.y, 2, BOTTOM, glm::vec3(1.0f, 0.0f, 0.0f)));
        if (positions.stopped) {
            // add a circle next to train name to indicate train is being held
            m_trainContainer->AddChild(CreateCircle(glm::vec3(HeadPos.x - 5.0f, HeadPos.y+0.5f, 1.0f), 1.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
        }

    }


}


StationPlot::StationPlot(const std::string& id) : m_stationId(id), m_blockMin(0) {
    Railway& r = Config::get().GetRailway();
    gfxNode = std::make_shared<Entity>();
    auto& s = r.GetStation(m_stationId);
    auto lps = s.getLinePoints(true);
    //std::vector<glm::vec2> points;

    AddElement(s, lps[0], 0);
    m_startPoint = lps[0];
    ExtendFromPoint(s, lps[0]);
    auto a = std::make_shared<Entity>();
    auto r1 = std::make_shared<Renderer>();
    PolyLine p(m_points, m_edges);
    r1->SetMesh(MeshFactory::CreateMesh(p));
    a->AddComponent(r1);
    a->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    gfxNode->AddChild(a);
    //mainNode->AddChild(gfxNode);
}



std::shared_ptr<Entity> StationPlot::CreateLabel (const std::string& text, glm::vec4 color, glm::vec2 pos, float size) {
    auto a = std::make_shared<Entity>();
    auto r1 = std::make_shared<Renderer>();
    Font* f = Engine::get().GetAssetManager().GetFont("main");
    std::shared_ptr<IMesh> m(new TextMesh(f, text, size, BOTTOM));
    r1->SetMesh(m);
    a->AddComponent(r1);
    a->SetPosition(glm::vec3(pos.x, pos.y, 0.0f));
    return a;
}

void StationPlot::AddConnection (Station& s, int point1, int point2) {
    std::cout << "adding connection  between " << point1 << " and " << point2 << std::endl;
    if (locations[point1].block < locations[point2].block) {
        m_edges.push_back(std::make_pair(locations[point1].j, locations[point2].i));
    } else {
        m_edges.push_back(std::make_pair(locations[point1].i, locations[point2].j));
    }
}


void StationPlot::AddElement (Station& s, int point, int block) {
    // add an element, line point or stopping point to the station, at a given block
    // first we find the y
    float yLevel{0};
    if (blockInfo.count(block) == 0) {
        blockInfo[block] = m_blockMin;
        m_width = block;
    } else {
        blockInfo[block]++;
    }
    yLevel = blockInfo[block] * 20.0f;
    float x1=0;
    float x2=0;
    if (s.isLinePoint(point)) {
        x1 = block ==  0 ? block*30.0f+15.0f : block*30.0f + 5.0f;
        x2 = x1+10.0f;
        std::cout << "Adding line point " << point <<"\n";
        auto label = CreateLabel(std::to_string(point), glm::vec4(1.0f), glm::vec2(block==0 ? x1 : x2, yLevel), 8);
        if (block > 0)
            m_blockMin = blockInfo[block]+1;
        gfxNode->AddChild(label);

        m_linePointLocations[s.GetTrackAtLinePoint(point)] = glm::vec2(block == 0 ? x1 : x2, yLevel);
    } else {
        x1 = block*30.0f+5;
        x2 = x1+20.0f;
        std::cout << "Adding stopping point " << point <<"\n";
        auto label = CreateLabel(std::to_string(point), glm::vec4(1.0f), glm::vec2((x1+x2)*0.5f, yLevel), 6);
        gfxNode->AddChild(label);
    }
    locations[point] = {m_points.size(),m_points.size()+1,block};
    m_edges.push_back(std::make_pair(m_points.size(), m_points.size()+1));
    m_points.push_back(glm::vec2(x1, yLevel));
    m_points.push_back(glm::vec2(x2, yLevel));
    std::cout << "Block " << block << " y= " << yLevel << " x = (" << x1 << ", " << x2 << ")" << std::endl;

}

void StationPlot::ExtendFromPoint(Station& s, int id) {
    if (explored.count(id)>0)
        return;
    explored.insert(id);

    std::cout << "exploring point: " << id << "\n";
    auto& d = s.GetRoutesStartingAt(id);

    for (auto& e : d) {
        std::cout << "goes to " << e.endingPoint << "\n";
        // check if this has already been added
        if (locations.count(e.endingPoint) > 0) {
            AddConnection(s, id, e.endingPoint);
        } else {
            int nextBlock {0};
            if (s.isLinePoint(e.endingPoint)) {
                std::cout << "check if " << e.endingPoint << " is same side of " << m_startPoint << "\n";
                if (s.IsSameSide(m_startPoint, e.endingPoint))
                    nextBlock = locations[id].block-1;
                else
                    nextBlock = locations[id].block+1;
            } else {
                nextBlock = (s.isLinePoint(id) && locations[id].block>0) ? locations[id].block-1 : locations[id].block+1;
            }
            AddElement(s, e.endingPoint, nextBlock);
        }
    }
    for (auto& e : d) {
        ExtendFromPoint(s, e.endingPoint);
    }

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
