#include <test/solution.h>
#include <xml/tinyxml2.h>
#include <algorithm>
#include <iostream>
#include <set>

using namespace tinyxml2;

std::ostream& operator<< (std::ostream& os, const Position& pos) {
    os << Railway::get().GetResource(pos.resourceId)->GetName() << ", [" << pos.xTail << ", " << pos.xHead << "]";
    return os;
}

std::ostream& operator<< (std::ostream& os, const TrainPosition& pos) {
    if (pos.positions.empty())
        os << "offline";
    else
        for (auto& p : pos.positions)
            os << p << "\n";
    return os;
}

Solution::Solution(const std::string &solutionFile) {

    Railway& r = Railway::get();
    XMLDocument doc;
    XMLError e = doc.LoadFile(solutionFile.c_str());
    if (e != XML_SUCCESS) {
        std::cout << "We've got a problem loading solution file " << solutionFile << std::endl;
    } else
        std::cout << "Read " << solutionFile << "\n";

    auto el = doc.FirstChildElement("p1:TCS_OUT")->FirstChildElement("p1:Trains");
    for (auto eTrain = el->FirstChildElement("p1:Train"); eTrain != NULL; eTrain = eTrain->NextSiblingElement()){
        std::string trainId (eTrain->Attribute("Name"));
        double speed = eTrain->DoubleAttribute("Speed");
        r.AddTrain(trainId, 0, speed);
        std::cout << "Reading train " << trainId << std::endl;
        std::vector<Activity> activities;
        bool beyondPlanningHorizon = false;
        for (auto eSchedule = eTrain->FirstChildElement("p1:Schedule"); eSchedule != NULL; eSchedule = eSchedule->NextSiblingElement()) {
            if (beyondPlanningHorizon) break;
            for (auto ets = eSchedule->FirstChildElement("p1:StationSchedule"); ets != NULL; ets = ets->NextSiblingElement()) {
                Activity act;
                std::string stationId = ets->Attribute("StationId");
                std::string routeId = ets->Attribute("RouteId");
                if (routeId == "-1") {
                    // beyond planning horizon
                    beyondPlanningHorizon = true;
                    break;
                }
                act.resourceId = r.GetStationRouteId(stationId, routeId);
                act.timeIn = ets->IntAttribute("TimeIn");
                act.timeOut = ets->IntAttribute("TimeOut");
                activities.push_back(act);
            }
            for (auto ets = eSchedule->FirstChildElement("p1:TrackSchedule"); ets != NULL; ets = ets->NextSiblingElement()) {
                Activity act;
                std::string trackCircuitId = ets->Attribute("TrackCircuitId");
                act.resourceId = r.GetTrackCircuitId(trackCircuitId);
                act.timeIn = ets->IntAttribute("TimeIn");
                act.timeOut = ets->IntAttribute("TimeOut");
                activities.push_back(act);
            }
        }

        std::sort (activities.begin(), activities.end());
        // add final activity
        Activity fin{-1, activities.back().timeOut, -1};
        activities.push_back(fin);
        schedules[trainId] = activities;
    }

    std::cout << "Read " << schedules.size() << " schedules.\n";

    // get the train lengths
    auto el2 = doc.FirstChildElement("p1:TCS_OUT")->FirstChildElement("p1:TrainLengths");
    for (auto el3 = el2->FirstChildElement("p2:TrainLength"); el3 != NULL; el3 = el3->NextSiblingElement()) {
        std::string trainId = el3->Attribute("TrainId");
        int length = el3->IntAttribute("TrainLen");
        r.GetTrain(trainId)->_length = length;
    }
}

TrainPosition Solution::GetPosition(const std::string& id, long t) {
    // 1. Get the schedule corresponding to the train
    std::cout << "Query " << id << " at " << t << std::endl;
    auto it = schedules.find(id);
    if (it == schedules.end())
        GLIB_FAIL("Don't have schedule for train " << id);
    auto& schedule = it->second;
    // check if train is offline
    if (t < schedule[0].timeIn || t > schedule.back().timeIn)
        return TrainPosition();
    auto iter = std::lower_bound(schedule.begin(), schedule.end(), t);
    if (iter->timeIn > t || iter == schedule.end()-1) iter--;

    TrainPosition tp;
    Position pos;
    pos.resourceId = iter->resourceId;
    // see how far train has entered the resource
    Train* train = Railway::get().GetTrain(id);
    Resource* res = Railway::get().GetResource(iter->resourceId);
    double mphToFps = 5280.0 / 3600.0;
    double distanceCovered = std::min(train->_speed * mphToFps * (t - iter->timeIn), static_cast<double>(res->GetLength()));
    double tailLength = train->_length - distanceCovered;
    pos.xHead = distanceCovered;
    pos.xTail = std::max(0.0, -tailLength);
    tp.positions.push_back(pos);
    while (tailLength > 0 && iter > schedule.begin()) {
        // train occupies previous resources
        iter--;
        Position pos;
        pos.resourceId = iter->resourceId;
        res = Railway::get().GetResource(iter->resourceId);
        pos.xHead = res->GetLength();
        pos.xTail = std::max(0, res->GetLength() - train->_length);
        tailLength -= res->GetLength();
        tp.positions.push_back(pos);
    }
    return tp;



}

std::vector<std::string> Solution::GetTrainNames() const {
    std::vector<std::string> tn;
    for (auto& m : schedules) tn.push_back(m.first);
    return tn;
}
std::vector<int> Solution::GetStations(const std::string& trainName) {
    std::vector<int> out;
    int pid = -1;
    auto iter = schedules.find(trainName);
    if (iter == schedules.end())
        throw;
    for (auto& j : iter->second) {
        if (j.resourceId != -1) {
            auto res = Railway::get().GetResource(j.resourceId);
            StationRoute *sr = dynamic_cast<StationRoute *>(res);
            if (sr != nullptr && sr->GetStationId() != pid) {
                out.push_back(sr->GetStationId());
                pid = sr->GetStationId();
            }
        }
    }
    return out;
}