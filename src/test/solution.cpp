#include <test/solution.h>
#include <xml/tinyxml2.h>
#include <test/timeformatter.h>
#include <algorithm>
#include <iostream>
#include <set>

using namespace tinyxml2;

#include <test/global.h>

//std::ostream& operator<< (std::ostream& os, const Position& pos) {
//    os << Railway::get().GetResource(pos.resourceId)->GetName() << ", [" << pos.xTail << ", " << pos.xHead << "]";
//    return os;
//}

//std::ostream& operator<< (std::ostream& os, const TrainPosition& pos) {
//    if (pos.positions.empty())
//        os << "offline";
//    else
//        for (auto& p : pos.positions)
//            os << p << "\n";
//    return os;
//}
std::vector<std::string> Solution::GetTrainNames() const {
    std::vector<std::string> tn;
    for (auto& s : m_trainLengths)
        tn.push_back(s.first);
    return tn;

}
Solution::Solution(const std::string &solutionFile) {

    Railway &r = Config::get().GetRailway();
    XMLDocument doc;
    std::string fullPath = Config::get().GetHomeDir() + "output/" + solutionFile;
    XMLError e = doc.LoadFile(fullPath.c_str());
    if (e != XML_SUCCESS) {
        std::cout << "We've got a problem loading solution file " << fullPath << std::endl;
    } else {
        std::cout << "Read " << solutionFile << "\n";
    }

    // Get now
    m_now = doc.FirstChildElement("p1:TCS_OUT")->IntAttribute("Now");

    TimeFormatter::setReferenceDay(m_now);
    std::cout << "Time now = " << m_now << "\n";

    auto el = doc.FirstChildElement("p1:TCS_OUT")->FirstChildElement("p1:Trains");
    for (auto eTrain = el->FirstChildElement("p1:Train"); eTrain != NULL; eTrain = eTrain->NextSiblingElement()) {
        std::string trainId(eTrain->Attribute("Name"));
        double speed = eTrain->DoubleAttribute("Speed");
        //r.AddTrain(trainId, 0, speed);
        std::cout << "Reading train " << trainId << std::endl;
        std::string cat = trainId.substr(0,1);
        std::vector<Activity> activities;
        std::string previousStation();
        bool beyondPlanningHorizon = false;
        for (auto eSchedule = eTrain->FirstChildElement("p1:Schedule"); eSchedule != NULL; eSchedule = eSchedule->NextSiblingElement()) {
            if (beyondPlanningHorizon) break;
            for (auto ets = eSchedule->FirstChildElement("p1:StationSchedule"); ets != NULL; ets = ets->NextSiblingElement()) {

                std::string stationId = ets->Attribute("StationId");
                std::string routeId = ets->Attribute("RouteId");
                if (routeId == "-1") {
                    // beyond planning horizon
                    beyondPlanningHorizon = true;
                    break;
                }
                Activity act(r.GetStation(stationId).GetRoute(routeId));
                act.timeIn = ets->IntAttribute("TimeIn");
                act.timeOut = ets->IntAttribute("TimeOut");
                act.isTrack = false;
                act.trackOrStationId = stationId;
                //act.runningTime = act.resource->GetRunningTime(cat);
                // see if the previous track has been traversed forward or back
                activities.push_back(act);
            }
            for (auto ets = eSchedule->FirstChildElement("p1:TrackSchedule");
                 ets != NULL; ets = ets->NextSiblingElement()) {

                std::string trackCircuitId = ets->Attribute("TrackCircuitId");
                std::string trackId = trackCircuitId.substr(0, trackCircuitId.find_first_of('.'));
                Activity act(r.GetTrack(trackId).GetTrackCircuit(trackCircuitId));

                act.timeIn = ets->IntAttribute("TimeIn");
                act.timeOut = ets->IntAttribute("TimeOut");
                act.isTrack = true;
                act.trackOrStationId = trackId;
                activities.push_back(act);
            }
        }
        std::sort (activities.begin(), activities.end());

        // populate running times
        std::string ps;
        for (int i = 0; i<activities.size(); ++i) {
            if (activities[i].isTrack) {
                bool fwd{false};
                if (ps.empty()) {
                    int j = i+1;
                    while (activities[j].isTrack)
                        j++;
                    std::string nextStation = activities[j].trackOrStationId;
                    fwd = r.GetTrack(activities[i].trackOrStationId).GetStationB() == nextStation;
                } else {
                    // std::string prevStation = activities[i-1].trackOrStationId;
                    fwd = r.GetTrack(activities[i].trackOrStationId).GetStationA() == ps;
                }
                activities[i].runningTime = activities[i].resource->GetRunningTime(cat, fwd);
            } else {
                activities[i].runningTime = activities[i].resource->GetRunningTime(cat);
                ps = activities[i].trackOrStationId;
            }

            std::cout << (activities[i].isTrack ? "T " : "S ") << activities[i].resource->GetName() << " " << activities[i].runningTime << "\n";

        }
        // add final activity
        Activity fin;
        fin.timeIn = activities.back().timeOut;
        activities.push_back(fin);
        schedules[trainId] = activities;
    }

    // get the train lengths
    auto el2 = doc.FirstChildElement("p1:TCS_OUT")->FirstChildElement("p1:TrainLengths");
    for (auto el3 = el2->FirstChildElement("p2:TrainLength"); el3 != NULL; el3 = el3->NextSiblingElement()) {
        std::string trainId = el3->Attribute("TrainId");
        int length = el3->IntAttribute("TrainLen");
        m_trainLengths[trainId] = length;
    }

    for (auto& s : schedules) {
        std::string ps;
        for (int i = 0; i < s.second.size(); ++i) {
            if (s.second[i].resource == nullptr)
                continue;
            if (!s.second[i].isTrack)
                ps = s.second[i].trackOrStationId;
            else {
                if (!ps.empty()) {
                    s.second[i].backwards = (ps != Config::get().GetRailway().GetTrack(s.second[i].trackOrStationId).GetStationA());
                }
            }
        }
        ps = "";
        for (int i = s.second.size()-1; i >= 0; --i) {
            if (s.second[i].resource == nullptr)
                continue;
            if (!s.second[i].isTrack)
                ps = s.second[i].trackOrStationId;
            else {
                if (!ps.empty()) {
                    s.second[i].backwards = (ps != Config::get().GetRailway().GetTrack(s.second[i].trackOrStationId).GetStationB());
                }
            }
        }

    }


//    }
//
//    // populate activities running times
//    for (auto& s : schedules) {
//        int previousStation = -1;
//        for (int i = 0; i < s.second.size(); ++i) {
//            Activity& a = s.second[i];
//
//            if (a.isTrack) {
//                // check previous station, unless i = 0
//                bool fwd = false;
//                TrackCircuit* tc = dynamic_cast<TrackCircuit*>(Railway::get().GetResource(a.resourceId));
//                Track* track = Railway::get().GetTrack(tc->GetTrackId());
//                if (previousStation == -1) {
//                    // find next station
//                    int j =i+1;
//                    while (s.second[j].isTrack) j++;
//                    StationRoute* sr = dynamic_cast<StationRoute*>(Railway::get().GetResource(s.second[j].resourceId));
//                    int followingStation = sr->GetStationId();
//                    fwd = track->GetStationB() == followingStation;
//                } else {
//                    fwd = track->GetStationA() == previousStation;
//                }
//                a.runningTime = Railway::get().GetResourceRunningTime(a.resourceId, s.first[0], fwd);
//            } else {
//                a.runningTime = Railway::get().GetResourceRunningTime(a.resourceId, s.first[0], true);
//            }
//        }
//    }
//
//    std::cout << "Read " << schedules.size() << " schedules.\n";
//

}

std::string Solution::GetStationBefore (const std::string& train, Resource* r) {
    auto iter = schedules.find(train);

    for (auto i = iter->second.begin(); i != iter->second.end(); ++i) {
        if (i->resource->GetType() == ResourceType::STATION_ROUTE)
        {

        }
        if (i->resource == r) {
            // mmh, do I have a previous station?
        }
    }
}

std::string Solution::GetStationAfter (const std::string& train, Resource* r) {

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



    // find schedule with t_in <= t, t_out >= t
    int iIn = -1;
    for (int i = 0; i < schedule.size(); ++i) {
        if (schedule[i].timeIn <= t && schedule[i].timeOut >= t)
        {
            iIn = i;
            break;
        }
    }

    auto iter = std::lower_bound(schedule.begin(), schedule.end(), t);
    if (iter->timeIn > t || iter == schedule.end()-1) iter--;
    TrainPosition tp;
    Position pos;
    Activity& act = schedule[iIn];

    // find resource running time
    //int runningTime = act.resource->GetRunningTime() Railway::get().GetResourceRunningTime(pos.resourceId, id[0], )

    // see how far train has entered the resource
    //Train* train = Railway::get().GetTrain(id);

//    Resource* res = Railway::get().GetResource(act.resourceId);
//    double mphToFps = 5280.0 / 3600.0;
    //double distanceCovered = std::min(train->_speed * mphToFps * (t - act.timeIn), static_cast<double>(res->GetLength()));
    int length = act.resource->GetLength();
    double frac = static_cast<double>(t - act.timeIn) / act.runningTime;
    double distanceCovered = length * std::min(1.0, frac);
    // if tailLength is > 0 it means that length - covered > 0 and therefore length > covered, so
    // we occupy previous resources
    int trainLength = m_trainLengths[id];
    double tailLength = trainLength - distanceCovered;
    pos.xHead = distanceCovered;
    pos.xTail = std::max(0.0, -tailLength);
    pos.res = act.resource;
    pos.backwards = act.backwards;
    tp.positions.push_back(pos);
    int i = iIn;
    while (tailLength > 0 && i > 0) {
        // train occupies previous resources
        i--;
        Position pos;
        int resLength = schedule[i].resource->GetLength();
        pos.xHead = resLength;
        pos.xTail = std::max(0.0, static_cast<double>(resLength) - tailLength);
        pos.res = schedule[i].resource;
        pos.backwards = schedule[i].backwards;
        tailLength -= resLength;
        tp.positions.push_back(pos);
    }
    return tp;
}
//
//std::vector<std::string> Solution::GetTrainNames() const {
//    std::vector<std::string> tn;
//    for (auto& m : schedules) tn.push_back(m.first);
//    return tn;
//}

std::vector<std::string> Solution::GetStations(const std::string& trainName) {
    std::vector<std::string> out;
    std::string pid;
    auto iter = schedules.find(trainName);
    if (iter == schedules.end())
        throw;
    for (auto& j : iter->second) {
        if (!j.isTrack && pid != j.trackOrStationId && j.trackOrStationId!="")  {
            out.push_back(j.trackOrStationId);
            pid = j.trackOrStationId;
        }
    }
    return out;
}