#include <test/resource.h>
#include <test/railway.h>

void Station::AddLinePoint (int id, std::string& trackName) {
    linePoints[id] = trackName;
}

void Station::AddCorrectPath (int l1, int l2) {

    auto it1 = linePoints.find(l1);
    auto it2 = linePoints.find(l2);
    connectedTracks[it1->second] = it2->second;
}

std::string TrackCircuit::GetName() {
    return "TrackCircuit " + _name;
}

std::string StationRoute::GetName() {
    return "Route " + _name;
}

std::string StoppingPoint::GetName() {
    return "Stopping point " + _name;
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

std::vector<std::string> Station::GetTracks() {
    std::vector<std::string> out;
    for (auto& i : linePoints) {
        if (i.second != "-1")
        out.push_back(i.second);
    }
    return out;
}

std::set<int> Station::GetConnectedStations() {
    std::set<int> out;
    for (auto& i : linePoints) {
        if (i.second != "-1") {
            Track* t = Railway::get().GetTrack(i.second);
            out.insert(t->GetStationA() == this->_id ? t->GetStationB() : t->GetStationA());
        }
    }
    return out;


}