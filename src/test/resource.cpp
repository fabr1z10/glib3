#include <test/resource.h>
#include <test/railway.h>

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
void Station::AddLinePoint (int id, const std::string& trackName) {
    m_lp[id] = trackName;
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