#include <test/resource.h>
#include <test/railway.h>
#include <test/global.h>

int StationRoute::GetRunningTime(const std::string& cat, bool) {
    auto it = m_runningTimes.find(cat);
    if (it == m_runningTimes.end())
        GLIB_FAIL("Cannot find category " << cat);
    return it->second;

}

int TrackCircuit::GetRunningTime(const std::string& cat, bool fwd) {
    auto it = m_runningTimes.find(cat);
    if (it == m_runningTimes.end())
    GLIB_FAIL("Cannot find category " << cat);
    return (fwd ? it->second.first : it->second.second);

}

void Station::AddCorrectPath(int in, int out) {
    m_correctPaths[in].insert(out);
}

std::string Station::GetTrackAtLinePoint(int id) const {
    auto it = m_lp.find(id);
    if (it == m_lp.end())
        throw;
    return it->second;

}

bool Station::IsSameSide(int a, int b) {
    Railway& r = Config::get().GetRailway();
    if (m_lp[a] == "-1" || m_lp[b]=="-1")
        return false;
    auto& t1 = r.GetTrack(m_lp[a]);
    auto& t2 = r.GetTrack(m_lp[b]);
    auto sd = GetShortName();
    return ((t1.GetStationA() == sd && t2.GetStationA() == sd) ||
            (t1.GetStationB() == sd && t2.GetStationB() == sd));
}
void Station::AddLinePoint (int id, const std::string& trackName) {
    m_lp[id] = trackName;
}

void Station::AddStationRoute(int origin, int ending, int length) {
    RouteDetail detail {ending, length};
    m_routes[origin].push_back(detail);
}

void Station::AddStoppingPoint (int id, int length){
    m_stoppingPoints[id] = length;
}

std::vector<int> Station::getLinePoints(bool left) {
    Railway& rail = Config::get().GetRailway();
    std::vector<int> lp;
    for (auto& r : m_lp) {
        if (r.second !="-1") {
            if (left) {
                if (rail.GetTrack(r.second).GetStationB() == GetShortName())
                    lp.push_back(r.first);
            } else {
                if (rail.GetTrack(r.second).GetStationA() == GetShortName())
                    lp.push_back(r.first);
            }
        }
    }
    return lp;

}
//
//void Station::AddCorrectPath (int l1, int l2) {
//
//    auto it1 = linePoints.find(l1);
//    auto it2 = linePoints.find(l2);
//    connectedTracks[it1->second] = it2->second;
//}

std::string TrackCircuit::GetName() {
    return "TrackCircuit " + _name;
}

std::string StationRoute::GetName() {
    return "Route " + _name;
}


std::string Track::GetName() {
    return "Track " + _name;
}
std::string Station::GetName() {
    return "Station " + _name;
}
std::string Train::GetName() {
    return "Train " + _name;
}

//std::vector<std::string> Station::GetTracks() {
//    std::vector<std::string> out;
//    for (auto& i : linePoints) {
//        if (i.second != "-1")
//        out.push_back(i.second);
//    }
//    return out;
//}
//
//std::set<int> Station::GetConnectedStations() {
//    std::set<int> out;
//    for (auto& i : linePoints) {
//        if (i.second != "-1") {
//            Track* t = Railway::get().GetTrack(i.second);
//            out.insert(t->GetStationA() == this->_id ? t->GetStationB() : t->GetStationA());
//        }
//    }
//    return out;
//
//
//}