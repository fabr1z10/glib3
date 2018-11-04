#include "test/tcs.h"
#include "test/resource.h"
#include <test/solution.h>
#include <iostream>
#include <map>
#include <algorithm>

using namespace tinyxml2;

int GlobalId::_idCount = 0;



//Solution::Solution(const std::string &solutionFile) {
    // Now read solution

//    XMLDocument doc;
//    XMLError e = doc.LoadFile(solutionFile.c_str());
//    if (e != XML_SUCCESS) {
//        std::cout << "We've got a problem loading solution file " << solutionFile << std::endl;
//    } else
//        std::cout << "ok\n";
//
//
//
//    auto el = doc.FirstChildElement("p1:TCS_OUT")->FirstChildElement("p1:Trains");
//    for (auto eTrain = el->FirstChildElement("p1:Train"); eTrain != NULL; eTrain = eTrain->NextSiblingElement()){
//        std::string trainId (eTrain->Attribute("Name"));
//        std::cout << "Reading train " << trainId << "\n";
//        // read all p1:Schedule elements
//        std::vector<TrainSchedule> tschedules;
//        for (auto eSchedule = eTrain->FirstChildElement("p1:Schedule"); eSchedule != NULL; eSchedule = eSchedule->NextSiblingElement()) {
//            TrainSchedule ts;
//            if (eSchedule->FirstChildElement("p1:StationSchedule") != nullptr) {
//                for (auto ets = eSchedule->FirstChildElement("p1:StationSchedule"); ets != NULL; ets = ets->NextSiblingElement()) {
//                    Schedule ss;
//                    ss.timeIn = ets->IntAttribute("TimeIn");
//                    ss.timeOut = ets->IntAttribute("TimeOut");
//                    std::string stId = ets->Attribute("StationId");
//                    ts.resourceId = r.GetStationResourceId(stId);
//                    ss.routeId = ets->Attribute("RouteId");
//                    ts.m_schedules.push_back(ss);
//                }
//
//            } else {
//                for (auto ets = eSchedule->FirstChildElement("p1:TrackSchedule"); ets != NULL; ets = ets->NextSiblingElement()) {
//                    Schedule ss;
//                    ss.timeIn = ets->IntAttribute("TimeIn");
//                    ss.timeOut = ets->IntAttribute("TimeOut");
//                    ss.routeId = ets->Attribute("TrackCircuitId");
//                    std::string trackId = ss.routeId.substr(0, ss.routeId.find('.'));
//                    ts.resourceId = r.GetTrackResourceId(trackId);
//
//                    ts.m_schedules.push_back(ss);
//                }
//            }
//            tschedules.push_back(ts);
//            //
//            // schedules[trainId][ts.GetTimeIn()].push_back(ts);
//        }
//        // sort by time
//        std::sort(tschedules.begin(), tschedules.end(), [] (const TrainSchedule& s1, const TrainSchedule& s2) -> bool { return s1.GetTimeIn() < s2.GetTimeIn(); });
//        schedules[trainId] = tschedules;
//
//    }
//
//
//    for (auto& s : schedules) {
//
//        std::cout << "Schedule for train " << s.first << " has " << s.second.size() << " schedules.\n";
//        for (auto& i : s.second) {
//            std::cout << i.GetTimeIn() << "\t" << i.resourceId << "\t" << r.GetResource(i.resourceId)->ToString() << "\n";
//        }
//    }




//    XMLDocument doc;
//    XMLError e = doc.LoadFile(status.c_str());
//    if (e != XML_SUCCESS) {
//        std::cout << "We've got a problem loading " << status << "\n";
//    } else
//        std::cout << "ok\n";
//    auto el = doc.FirstChildElement("Status");
//    long now = std::atol(el->Attribute("Now"));
//
//    std::cout << "Time now = " << now << std::endl;
//    auto elPositions = el->FirstChildElement("TrainPositions");
//    TCSGraph graph;
//    Data d;
//    for (auto ePos = elPositions->FirstChildElement("CurrentTrainPosition"); ePos != NULL; ePos = ePos->NextSiblingElement()) {
//        // Get the train position
//
//        std::string trainId(ePos->Attribute("TrainId"));
//        std::cout << "Train : " << trainId << " ";
//        auto innerPos = ePos->FirstChildElement("TrainPosition");
//        bool isStation = (innerPos->Attribute("StationId")!= nullptr);
//        if (isStation) {
//            std::string stationId(innerPos->Attribute("StationId"));
//            std::cout << "is in station " << stationId << std::endl;
//            std::cout << "Creating station activity ... ";
//            Station* s =d.GetStation(stationId);
//            graph.AddNode(std::make_shared<StationActivity>(s));
//        } else {
//            std::string trackId(innerPos->Attribute("TrackId"));
//            std::cout << "is in track " << trackId << std::endl;
//            std::cout << "Creating track activity ... ";
//            Track* s =d.GetTrack(trackId);
//            graph.AddNode(std::make_shared<TrackActivity>(s));
//
//        }
//    }


//}

