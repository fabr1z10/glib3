#include <test/testgfx.h>
#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/meshfactory.h>
#include <test/controller.h>
#include <iostream>
#include <algorithm>
#include <gfx/textmesh.h>



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
    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600, 1));
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

void Factory2::DrawLineStemmingFrom(int stationId, float x, float y) {

    auto iter = connections.find(stationId);
    Station* s = Railway::get().GetStation(stationId);
    std::cout << "Drawing station " << s->GetName() << " at " << x << ", " << y << "\n";
    done.insert(stationId);
    float dy=0;
    for (auto& c : iter->second) {

        if (done.find(c) == done.end()) {
            DrawLineStemmingFrom(c, x + 10, y + dy);
            dy+=10;
        }

    }
}

std::shared_ptr<Entity> Factory2::CreateLabel (const std::string& text) {
//    auto gfxNode = std::make_shared<Entity>();
//    gfxNode->SetLayer(1);
//    auto r1 = std::make_shared<Renderer>();
//    std::shared_ptr<IMesh> m(new TextMesh())
//    r1->SetMesh(MeshFactory::CreateBoxMesh(width, height, glm::vec4(1.0f)));
//    gfxNode->AddComponent(r1);
//    gfxNode->SetPosition(glm::vec3(s.second.x, s.second.y, 0.0f));
//    entity->AddChild(gfxNode);
    return nullptr;
}

std::shared_ptr<Entity> Factory2::Create() {

    Engine::get().GetAssetManager().AddFont("main", "/home/fabrizio/Scaricati/a4rial.ttf");

    auto entity = std::make_shared<Entity>();

    // create one node showing a square
    float dxs = 80.0f;
    float height = 50;
    float width = 20;
    auto trainNames = m_solution.GetTrainNames();
    int iTrain = 0;

    for (auto& trainName : trainNames) {
        auto stations = m_solution.GetStations(trainName);
        // see if I have any overlapping with existing stations
        bool overlaps{false};
        bool goingRight {true};
        //float startX = 0;

        int overlappingIndex = -1;
        float overlappingX {0};
        for (int i = 0; i < stations.size(); ++i) {
            int s = stations[i];
            if (m_stations.find(s) != m_stations.end()) {
                // found overlapping!
                Station *st = Railway::get().GetStation(s);
                std::cout << "Train " << trainName << " overlaps at station " << st->GetName() << "\n";
                std::cout << "Check if train is going left or right.\n";
                overlaps = true;
                overlappingX = m_stations[s].x;
                if (i < stations.size() - 1) {
                    auto it = m_stations.find(stations[i + 1]);
                    if (it != m_stations.end()) {
                        if (it->second.x < overlappingX) {
                            goingRight = false;
                        }
                    }
                }
                std::cout << "Train is going " << (goingRight ? "right" : "left") << "\n";
                overlappingIndex = i;
                break;

            }
        }
        // if overlapping, start adding nodes at the correct location.
        // if i is the overlapping index, and x is the coordinate of the 1st overlapping station,
        // the current train will start at x + (left)*i*dx, where left = -1 or +1
        // if no overlapping, the train will be parallel, and start at x
        float dx=10;
        trainDir[trainName] = goingRight;
        float x = (overlaps ? (overlappingX + (goingRight ? -1.0 : 1.0) * overlappingIndex * dx) : 0.0);
        for (int i = 0; i < stations.size(); ++i) {
            if (m_stations.find(stations[i]) == m_stations.end()) {
                // station not added yet
                float yt = iTrain*10.0f;
                m_stations[stations[i]] = StationLocation{x,yt};
                Station *st = Railway::get().GetStation(stations[i]);
                std::cout << "Adding station " << st->GetName() << " at " << x << ", " << yt << "\n";
            }
            x+= (goingRight ? 1.0 : -1.0)*dxs;
        }
        iTrain++;



    }

    // draw stations

    for (auto& s : m_stations) {

        auto gfxNode = std::make_shared<Entity>();
        gfxNode->SetLayer(1);
        auto r1 = std::make_shared<Renderer>();
        r1->SetMesh(MeshFactory::CreateBoxMesh(width, height, glm::vec4(1.0f)));
        gfxNode->AddComponent(r1);
        gfxNode->SetPosition(glm::vec3(s.second.x, s.second.y, 0.0f));
        entity->AddChild(gfxNode);

        // adding a text with station id


    }
    int trackDrawn = 0;
    for (auto& trainName : trainNames) {
        auto stations = m_solution.GetStations(trainName);
        for (int i = 1; i<stations.size();++i) {
            auto tracks = Railway::get().GetTracksConnecting(stations[i-1],stations[i]);
            for (auto& track : tracks) {
                Track* tr = Railway::get().GetTrack(track);
                double trackLength {0};
                const auto& trackCircuits = tr->GetTrackCircuits();
                for (auto& tc : trackCircuits) {
                    trackLength += Railway::get().GetResource(tc)->GetLength();
                }
                StationLocation l1 = m_stations[stations[i-1]];
                StationLocation l2 = m_stations[stations[i]];
                float x0,y0,x1,y1;
                float dy {0};
                if (tr->GetMainName() == "MT 1")
                    dy = 0;
                else if (tr->GetMainName()=="MT 2")
                    dy=10;
                else if (tr->GetMainName()=="MT 3")
                    dy = 20;
                if (l1.x < l2.x) {
                    x0 = l1.x + width;
                    x1 = l2.x;
                    y0 = l1.y + dy;
                    y1 = l2.y + dy;
                } else {
                    x0 = l2.x + width;
                    x1 = l1.x;
                    y0 = l2.y + dy;
                    y1 = l1.y + dy;
                }
                glm::vec2 P(x0,y0);
                glm::vec2 unitVec = glm::normalize(glm::vec2(x1, y1) - P);
                float vecLength = glm::length(glm::vec2(x1, y1) - P);

                for (auto& tc : trackCircuits) {
                    auto res = Railway::get().GetResource(tc);
                    double tcLength = res->GetLength();
                    double pctLength = tcLength / trackLength;
                    m_loc[tc].pts.push_back(P);
                    P+= unitVec * vecLength * static_cast<float>(pctLength);
                    m_loc[tc].pts.push_back(P);
                }
                //if (trackDrawn < 25) {
                    auto gfxNode = std::make_shared<Entity>();
                    gfxNode->SetLayer(1);
                    auto r1 = std::make_shared<Renderer>();
                    r1->SetMesh(MeshFactory::CreateLineMesh(glm::vec2(x0, y0), glm::vec2(x1, y1), glm::vec4(1.0f)));
                    gfxNode->AddComponent(r1);
                    //gfxNode->SetPosition(glm::vec3(x, y, 0.0f));
                    entity->AddChild(gfxNode);
                    trackDrawn++;
                std::cout << "Drawin track " << track << " from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ")\n";
                //}
            }
        }
    }

    // draw trains
    auto trainNode = std::make_shared<Entity>();
    m_trainNode = trainNode.get();
    entity->AddChild(trainNode);







    // create engine node
    auto engineNode = std::make_shared<Entity>();

    auto renderingEngine = std::make_shared<RenderingEngine>();
    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600, 1));
    auto controller = std::make_shared<ViewerController>(cam.get(), this);
    cam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    renderingEngine->AddCamera (std::move(cam));
    renderingEngine->AddShader(COLOR_SHADER);
    engineNode->AddComponent(renderingEngine);
    engineNode->AddComponent(controller);
    entity->AddChild(engineNode);

    return entity;

}


void Factory2::RefreshTrains(double t) {
    m_trainNode->ClearAllChildren();
    auto trainNames = m_solution.GetTrainNames();
    for (auto& train : trainNames) {
        auto pos = m_solution.GetPosition(train, t);
        for (auto& p : pos.positions) {

            double len = Railway::get().GetResource(p.resourceId)->GetLength();
            double pctHead = p.xHead / len;
            double pctTail = p.xTail / len;
            auto locIt = m_loc.find(p.resourceId);
            if (locIt != m_loc.end()) {
                glm::vec2 axis = glm::normalize(locIt->second.pts[1] - locIt->second.pts[0]);
                float length = glm::length(locIt->second.pts[1] - locIt->second.pts[0]);
                bool isGoingRight = trainDir[train];
                glm::vec2 SP;
                if (isGoingRight) {
                    SP = locIt->second.pts[0];
                } else {
                    axis = -axis;
                    SP = locIt->second.pts[1];
                }
                glm::vec2 A = SP + axis * (length * static_cast<float>(pctHead));
                glm::vec2 B = SP + axis * (length * static_cast<float>(pctTail));
                auto gfxNode = std::make_shared<Entity>();
                gfxNode->SetLayer(1);
                auto r1 = std::make_shared<Renderer>();
                r1->SetMesh(MeshFactory::CreateLineMesh(A, B, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f));
                gfxNode->AddComponent(r1);
                //gfxNode->SetPosition(glm::vec3(x, y, 0.0f));
                m_trainNode->AddChild(gfxNode);
            }
        }
    }
}
