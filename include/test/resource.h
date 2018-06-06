#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <gfx/error.h>
#include <set>
#include <memory>

class GlobalId {
public:
    GlobalId(const std::string& name) : _id(_idCount++), _name{name} {}
    int GetId() const { return _id;}
    std::string GetShortName() const { return _name; }
    virtual std::string GetName() = 0;
protected:
    std::string _name;
    static int _idCount;
    int _id;
};

// resources are: track circuits, routes and stopping points
// each resource has a length
class Resource : public GlobalId {
public:
    Resource(const std::string& name, int length) : GlobalId(name), m_length{length} {}
    int GetLength() const { return m_length;}
    virtual bool isStationRoute() = 0;
    virtual bool isStoppingPoint() = 0;
    virtual bool isTrackCircuit() = 0;
private:
    int _id;
    int m_length;


};

class TrackCircuit : public Resource {
public:
    TrackCircuit (const std::string& name, int length, int trackId) : Resource(name, length), _trackId{trackId} {}
    std::string GetName() override;
    bool isStationRoute() override { return false;}
    bool isStoppingPoint()override { return false;}
    bool isTrackCircuit() override{ return true; }
    int GetTrackId() { return _trackId;}
private:
    int _trackId;
};

class StationRoute : public Resource {
public:
    StationRoute (const std::string& name, int length, int stationId) : Resource(name, length), _stationId{stationId} {}
    std::string GetName() override;
    int GetStationId() const { return _stationId; }
    bool isStationRoute() override { return true;}
    bool isStoppingPoint()override { return false;}
    bool isTrackCircuit() override{ return false; }
private:
    int _stationId;
};

//class StoppingPoint : public Resource {
//public:
//    StoppingPoint (const std::string& name, int length, int stationId) : Resource(name, length), _stationId{stationId} {}
//    std::string GetName() override;
//    int GetStationId() const { return _stationId; }
//    bool isStationRoute() override { return false;}
//    bool isStoppingPoint()override { return true;}
//    bool isTrackCircuit() override{ return false; }
//private:
//    int _stationId;
//};

// each track is made up of a sequence of track circuits
// and connects two stations
class Track : public GlobalId {
public:
    Track(const std::string& name, int stationA, int stationB) : GlobalId(name), _stationA{stationA}, _stationB{stationB} {}
    // get total track length
    int GetLength() const;
    std::string GetName() override;
    const std::vector<int>& GetTrackCircuits() const { return m_trackCircuits; }
    void AddTrackCircuit(int id) {
        m_trackCircuits.push_back(id);
    }
    int GetStationA() const { return _stationA; }
    int GetStationB() const { return _stationB; }
    std::string GetMainName() const { return _mainName; }
    void SetMainName(const std::string& name) {
        _mainName = name;
    }
private:
    // sequence of track circuits from A to B
    std::vector<int> m_trackCircuits;
    std::string _mainName;
    int _stationA;
    int _stationB;
};

enum class PointType {
    LINE_POINT, INTERMEDIATE_POINT, STOPPING_POINT
};

class Point {
public:
    Point(int id) : m_id{id}{}
    virtual~ Point();
    virtual PointType GetType() = 0;
private:
    int m_id;
};

class LinePoint : public Point {
public:
    LinePoint (int id, int connectingTrack) : Point(id), m_connectingTrack{connectingTrack}{}
    PointType GetType() override {return PointType::LINE_POINT; }
private:
    int m_connectingTrack;
};

class IntermediatePoint : public Point {
public:
    IntermediatePoint(int id) : Point(id) {}
    PointType GetType() override {return PointType::INTERMEDIATE_POINT; }
};

class StoppingPoint : public Point {
public:
    StoppingPoint (int id, int length) : Point(id), m_length{length}{}
    PointType GetType() override {return PointType::STOPPING_POINT; }
private:
    int m_length;

};

// a station is made up of routes and stopping points
class Station {
public:
    Station(const std::string& name) : m_name(name) {}
    Path GetPath(int pointFrom, int pointTo);
    int GetPoint(Track);
    void AddPoint ()
private:
    std::string m_name;
    std::unordered_map<int, std::shared_ptr<Point>> m_stationPoints;
};

//struct Schedule {
//    long timeIn, timeOut;
//    std::string routeId;
//};
//
//
//class TrainSchedule {
//public:
//    long GetTimeIn() const { return m_schedules.front().timeIn; }
//    long GetTimeOut() { return m_schedules.back().timeOut; }
//    long resourceId;
//    std::vector<Schedule> m_schedules;
//    bool operator< (const TrainSchedule& other) const {
//        return GetTimeIn() < other.GetTimeIn();
//    }
//    bool operator< (double t) const {
//        return GetTimeIn() < t;
//    }
//};

class Train : public GlobalId {
public:
    Train(const std::string& name, int length, double speed) : GlobalId(name), _length{length}, _speed{speed} {}
    std::string GetName() override;
    int _length;
    char _category;
    double _speed;
};

//
//// each track connects two stations
//class Track : public Resource {
//public:
//    std::string id;
//    int length;
//    std::string m_stationId1;
//    std::string m_stationId2;
//    std::string ToString() override { return "Track " + id; }
//};
//
//class Station : public Resource {
//public:
//    std::string id;
//    std::string name;
//    std::unordered_map<int, std::string> linePoints;
//    std::vector<std::string> adjacentTracks;
//    std::unordered_map<std::string, std::string> connectedTracks;
//    std::string ToString() override { return "Station " + id; }
//};
//
//class Railway {
//
//public:
//    Railway();
//    long GetStationResourceId(const std::string& stationId);
//    long GetTrackResourceId(const std::string& stationId);
//    Resource* GetResource(long id) {
//        return resources[id];
//    }
//private:
//    std::unordered_map<long, Resource*> resources;
//    std::unordered_map<std::string, std::unique_ptr<Station>> stations;
//    std::unordered_map<std::string, std::unique_ptr<Track>> tracks;
//
//};




//inline long Railway::GetStationResourceId(const std::string& stationId) {
//    auto it = stations.find(stationId);
//    if (it == stations.end())
//        GLIB_FAIL("Unknown station " << stationId);
//    return it->second->GetId();
//}
//
//inline long Railway::GetTrackResourceId(const std::string& trackId) {
//    auto it = tracks.find(trackId);
//    if (it == tracks.end())
//        GLIB_FAIL("Unknown station " << trackId);
//    return it->second->GetId();
//
//}
//
//

