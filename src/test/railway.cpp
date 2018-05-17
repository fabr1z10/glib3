#include <test/railway.h>
#include <xml/tinyxml2.h>
#include <iostream>
#include <gfx/error.h>

using namespace tinyxml2;

Railway::Railway() {

    XMLDocument doc;
    std::string fullPath = homeDir + "common/railway/common_railway.xml";
    XMLError e = doc.LoadFile(fullPath.c_str());
    if (e != XML_SUCCESS) {
        std::cout << "We've got a problem loading common railway file " << fullPath <<"\n";
    } else
        std::cout << "ok\n";

    // read all stations
    auto el = doc.FirstChildElement("Railway")->FirstChildElement("Stations");
    for (auto eStation = el->FirstChildElement("Station"); eStation != NULL; eStation = eStation->NextSiblingElement()){
        std::string name = eStation->Attribute("Id");
        int id = AddStation(name);
        Station* station = GetStation(id);


        auto elps = eStation->FirstChildElement("LinePoints");
        for (auto elp = elps->FirstChildElement("LinePoint"); elp != NULL; elp = elp->NextSiblingElement()) {
            int lp = elp->IntAttribute("Id");
            std::string atrack = elp->Attribute("AdjacentTrack");
            station->AddLinePoint(lp, atrack);
        }

        auto ecps = eStation->FirstChildElement("CorrectPaths");
        for (auto ecp = ecps->FirstChildElement("CorrectPath"); ecp != NULL; ecp = ecp->NextSiblingElement()) {
            int i1 = ecp->IntAttribute("InputLinePointId");
            int i2 = ecp->IntAttribute("OutputLinePointId");
            station->AddCorrectPath(i1,i2);
        }

        // read routes
        auto eroutes = eStation->FirstChildElement("Routes");
        for (auto eroute = eroutes->FirstChildElement("Route"); eroute != NULL; eroute = eroute->NextSiblingElement()) {
            std::string name = eroute->Attribute("Id");
            // length in feet
            int length = eroute->IntAttribute("Length");

            std::unique_ptr<StationRoute> sr(new StationRoute(name, length, id));
            station->AddRoute(*(sr.get()));
            int id = sr->GetId();
            m_resources[id] = std::move(sr);

        }

        // read stopping points
        auto esps = eStation->FirstChildElement("StoppingPoints");
        for (auto esp = esps->FirstChildElement("Route"); esp != NULL; esp = esp->NextSiblingElement()) {
            std::string name = esp->Attribute("Id");
            // length in feet
            int length = esp->IntAttribute("Length");

            std::unique_ptr<StoppingPoint> sr(new StoppingPoint(name, length, id));
            station->AddStoppingPoint(*(sr.get()));
            int id = sr->GetId();
            m_resources[id] = std::move(sr);

        }
    }
    std::cout << "Read " << m_stations.size() << " stations." <<std::endl;

    // read all tracks

    auto elt = doc.FirstChildElement("Railway")->FirstChildElement("Tracks");
    for (auto eTrack = elt->FirstChildElement("Track"); eTrack != NULL; eTrack = eTrack->NextSiblingElement()) {
        std::string trackName = eTrack->Attribute("Id");
        std::string stationA = eTrack->Attribute("StationA");
        std::string stationB = eTrack->Attribute("StationB");
        std::string mainName;
        if (eTrack->Attribute("MainName") != nullptr)
            mainName = eTrack->Attribute("MainName");
        auto itA = m_stationNameToId.find(stationA);
        if (itA == m_stationNameToId.end())
            GLIB_FAIL("Unknown station " << stationA);
        auto itB = m_stationNameToId.find(stationB);
        if (itB == m_stationNameToId.end())
            GLIB_FAIL("Unknown station " << stationB);
        int id = AddTrack(trackName, itA->second, itB->second, mainName);
        Track* track = GetTrack(id);
        auto etcs = eTrack->FirstChildElement("TrackCircuits");
        for (auto etc = etcs->FirstChildElement("TrackCircuit"); etc != NULL; etc = etc->NextSiblingElement()) {
            std::string name = etc->Attribute("Id");
            // length in feet
            int length = etc->IntAttribute("Length");
            std::unique_ptr<TrackCircuit> sr(new TrackCircuit(name, length, id));
            track->AddTrackCircuit(sr->GetId());
            int idtc = sr->GetId();
            m_resources[idtc] = std::move(sr);
            m_trackCircuitToId[name] = idtc;
        }
    }
//
//
    std::cout << "Read " << m_tracks.size() << " tracks." <<std::endl;

    // Read running times
    ReadRunningTimes();
}


void Railway::ReadRunningTimes() {

    XMLDocument doc;
    std::string fullPath = homeDir + "up/config/up_config_CommonRailway.xml";
    XMLError e = doc.LoadFile(fullPath.c_str());
    if (e != XML_SUCCESS) {
        GLIB_FAIL ("We've got a problem loading common railway file " << fullPath );
    } else
        std::cout << "ok\n";

    auto el = doc.FirstChildElement("UP_Config")->FirstChildElement("DefaultTrainStationDetails");
    for (auto eStation = el->FirstChildElement("DefaultStationDetail"); eStation != NULL; eStation = eStation->NextSiblingElement()) {
        std::string currentStation(eStation->Attribute("StationId"));
        Station * s = GetStation(currentStation);
        for (auto eRT = eStation->FirstChildElement("RouteRunningTimes")->FirstChildElement("RouteRunningTime"); eRT != NULL; eRT = eRT->NextSiblingElement()) {
            std::string routeId = eRT->Attribute("routeId");
            int runningTime = eRT->IntAttribute("runningTime");
            char category = eRT->Attribute("category")[0];
            int id = s->GetStationRouteId(routeId);
            m_forwardRunningTime[id][category] = runningTime;
        }
    }

    el = doc.FirstChildElement("UP_Config")->FirstChildElement("DefaultTrackRuntimes");
    for (auto etrack = el->FirstChildElement("DefaultTrackRuntime"); etrack != NULL; etrack = etrack->NextSiblingElement()) {

        std::string direction = etrack->Attribute("Direction");
        bool fwd = direction == "AToB";
        for (auto etr = etrack->FirstChildElement("TrackRuntimeByCategory"); etr != NULL; etr = etr->NextSiblingElement()) {
            char category = etr->Attribute("Category")[0];
            for (auto edtr = etr->FirstChildElement("DefaultTrackCircuitRuntime");
                 edtr != NULL; edtr = edtr->NextSiblingElement()) {
                std::string trackCircuitId = edtr->Attribute("TrackCircuitId");
                int runTime = edtr->IntAttribute("Runtime");
                int id = GetTrackCircuitId(trackCircuitId);
                if (fwd)
                    m_forwardRunningTime[id][category] = runTime;
                else
                    m_backwardRunningTime[id][category] = runTime;
            }
        }
    }
}


int Railway::AddTrain (const std::string& name, int length, float speed) {
    std::unique_ptr<Train> st(new Train(name, length, speed));
    int id = st->GetId();
    m_trainNameToId[name] = id;
    m_trains[id] = std::move(st);
    return id;
}


int Railway::AddStation (const std::string& name) {
    std::unique_ptr<Station> st(new Station(name));
    int id = st->GetId();
    m_stationNameToId[name] = id;
    m_stations[st->GetId()] = std::move(st);
    return id;
}

int Railway::AddTrack (const std::string& name, int stationA, int stationB, const std::string& mainName) {
    std::unique_ptr<Track> tr(new Track(name, stationA, stationB));
    tr->SetMainName(mainName);
    int id = tr->GetId();
    m_trackNameToId[name] = id;
    m_tracks[id] = std::move(tr);
    return id;
}

int Railway::AddTrackCircuit (int trackId, const std::string& name, int length) {
    std::unique_ptr<TrackCircuit> tc(new TrackCircuit(name, length, trackId));
    int id = tc->GetId();
    m_tracks[trackId]->AddTrackCircuit(id);
    m_resources[id] = std::move(tc);
    return id;
}




int Railway::AddStoppingPoint (int trackId, const std::string& name, int length) {

    return 0;
}


Track* Railway::GetTrack(const std::string& name) {
    auto it = m_trackNameToId.find(name);
    if (it == m_trackNameToId.end())
        GLIB_FAIL("Unknown track " << name);
    return m_tracks[it->second].get();
}

Station* Railway::GetStation(const std::string& name) {
    auto it = m_stationNameToId.find(name);
    if (it == m_stationNameToId.end())
    GLIB_FAIL("Unknown station " << name);
    return m_stations[it->second].get();
}


Train* Railway::GetTrain(const std::string& name) {
    auto it = m_trainNameToId.find(name);
    if (it == m_trainNameToId.end())
        GLIB_FAIL("Unknown train " << name);
    return m_trains[it->second].get();
}

Station* Railway::GetStation(int id) {
    auto it = m_stations.find(id);
    if (it == m_stations.end())
    GLIB_FAIL("Unknown station with id " << id);
    return it->second.get();
}

Track* Railway::GetTrack(int id) {
    auto it = m_tracks.find(id);
    if (it == m_tracks.end())
    GLIB_FAIL("Unknown track with id" << id);
    return it->second.get();
}

int Railway::GetStoppingPointId (const std::string& station, const std::string& sp) {
    return GetStation(station)->GetStoppingPointId(sp);
}

int Railway::GetStationRouteId (const std::string& station, const std::string& sr) {
    auto st = GetStation(station);
    return st->GetStationRouteId(sr);
}

int Railway::GetTrackCircuitId (const std::string& tc) {
    auto it = m_trackCircuitToId.find(tc);
    if (it == m_trackCircuitToId.end())
        GLIB_FAIL("Unknown track circuit " << tc);
    return it->second;
}

std::vector<std::string> Railway::GetTracksConnecting(int station1, int station2) {
    Station* s1 = Railway::get().GetStation(station1);
    auto tracks = s1->GetTracks();
    std::vector<std::string> tracksOut;
    for (auto& i :tracks) {
        Track *t = GetTrack(i);
        if (t->GetStationA() == station2 || t->GetStationB() == station2)
            tracksOut.push_back(i);
    }
    return tracksOut;
}

int Railway::GetResourceRunningTime (int resourceId, int trainCategory, bool fwd) {
    if (fwd) {
        return m_forwardRunningTime[resourceId][trainCategory];
    } else {
        return m_backwardRunningTime[resourceId][trainCategory];

    }

}