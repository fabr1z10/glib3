#pragma once

#include <test/railway.h>
#include <set>

struct Position {
    long resourceId;
    double xHead, xTail;
};

std::ostream& operator<< (std::ostream& os, const Position& pos);


struct TrainPosition {
    std::vector<Position> positions;
};

std::ostream& operator<< (std::ostream& os, const TrainPosition& pos);


struct Activity {
    int resourceId;
    long timeIn;
    long timeOut;
    bool operator< (const Activity& other) const {
        return timeIn < other.timeIn;
    }
    bool operator< (int t) const {
        return timeIn < t;
    }
};

class Solution {
public:
    Solution(const std::string&);
    // get the position of train id at time t
    TrainPosition GetPosition(const std::string& id, long t);
    std::vector<int> GetStations(const std::string& train);
    std::vector<std::string> GetTrainNames() const;
    int GetNumberOfSchedules() const { return schedules.size();}
private:
    std::unordered_map<std::string, std::vector<Activity> > schedules;
};
