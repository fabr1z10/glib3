#pragma once

#include <test/railway.h>
#include <set>
#include <map>
//
//struct Position {
//    Resource* res;
//    double xHead, xTail;
//    bool backwards;
//};
//
//std::ostream& operator<< (std::ostream& os, const Position& pos);
//
//
//struct TrainPosition {
//    std::vector<Position> positions;
//};
//
//std::ostream& operator<< (std::ostream& os, const TrainPosition& pos);
//
//
//struct Activity {
//    Activity() : resource{nullptr} {}
//    Activity (Resource& res) : resource(&res) {}
//    Resource* resource;
//    long timeIn;
//    long timeOut;
//    long runningTime;
//    bool isTrack;
//    bool backwards;  // important for tracks
//    //std::string ps, ns;
//    std::string trackOrStationId;
//    bool operator< (const Activity& other) const {
//        return timeIn < other.timeIn;
//    }
//    bool operator< (int t) const {
//        return timeIn < t;
//    }
//};
//
//class Problem {
//public:
//    Problem (const std::string& file);
//};
//
class Schedule {
public:
    Schedule(const std::string& s) : stationId(s){}
    std::string stationId;
};


struct PlanItem {
    std::string resource;
    std::string nextStation;
    std::string previousStation;
    std::string id;
    std::string id2;
    int timeOut;
    bool dwell;
    int runTime;
    bool isTrack;
};

class Plan {
public:
    Plan(const std::string& trainId) : m_trainId(trainId) {}
    void Add (int, PlanItem) ;
    bool Empty() const {
        return m_items.empty();
    }
    PlanItem& GetLastItem(){
        return m_items.end()->second;
    }
    void FillRunningTimes();
    void Dump();
    void SetNextStation(const std::string&);

    std::string m_trainId;
    std::map <int, PlanItem> m_items;
};

inline void Plan::Add (int tin, PlanItem item){
    m_items[tin] = item;
}


class Solution {
public:
    Solution(const std::string& file);
//    // get the position of train id at time t
//    TrainPosition GetPosition(const std::string& id, long t);
//    std::vector<std::string> GetStations(const std::string& train);
//    std::vector<std::string> GetTrainNames() const;
//    int GetNumberOfSchedules() const { return schedules.size();}
//    int GetNow() const;
//    std::string GetStationBefore (const std::string& train, Resource* r);
//    std::string GetStationAfter (const std::string& train, Resource* r);
    std::unordered_map<std::string, std::vector<std::string> >& getStations() {return m_stations;}
    std::unordered_map<std::string, std::unique_ptr<Plan> > m_plans;
private:
    int m_now;
//    std::unordered_map<std::string, int> m_trainLengths;

    std::unordered_map<std::string, std::vector<std::string> > m_stations;
};
//
//inline int Solution::GetNow() const {
//    return m_now;
//}
