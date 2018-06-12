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

enum class ResourceType { TRACK_CIRCUIT, STATION_ROUTE };

// Resources are: track circuits and station routes
class Resource : public GlobalId {
public:
    Resource(const std::string& name, int length) : GlobalId(name), m_length{length} {}
    int GetLength() const { return m_length;}
    virtual int GetRunningTime(const std::string& cat, bool fwd = false) = 0;
    virtual ResourceType GetType() = 0;
private:
    int _id;
    int m_length;
};

class TrackCircuit : public Resource {
public:
    TrackCircuit (const std::string& name, int length, const std::string& trackId) : Resource(name, length), _trackId{trackId} {}
    std::string GetName() override;
    int GetRunningTime(const std::string& cat, bool fwd = false) override;
    void SetRunningTime (const std::string& cat, bool fwd, int runtime) {
        if (fwd)
            m_runningTimes[cat].first = runtime;
        else
            m_runningTimes[cat].second = runtime;
    }
    ResourceType GetType() override { return ResourceType::TRACK_CIRCUIT; }
    std::string GetTrackId() { return _trackId;}
private:
    std::unordered_map<std::string, std::pair<int, int>> m_runningTimes;
    std::string _trackId;
};

class StationRoute : public Resource {
public:
    StationRoute (const std::string& name, int length, const std::string& stationId) : Resource(name, length), _stationId{stationId} {}
    std::string GetName() override;
    std::string GetStationId() const { return _stationId; }
    int GetRunningTime(const std::string& cat, bool fwd = false) override;
    void SetRunningTime (const std::string& cat, int runtime) {
        m_runningTimes[cat] = runtime;
    }
    ResourceType GetType() override { return ResourceType::STATION_ROUTE; }
private:
    std::unordered_map<std::string, int> m_runningTimes;
    std::string _stationId;
};

// each track is made up of a sequence of track circuits
// and connects two stations
class Track : public GlobalId {
public:
    Track(const std::string& name, const std::string& stationA, const std::string& stationB) : GlobalId(name), _stationA{stationA}, _stationB{stationB} {}
    // get total track length
    int GetLength() const;
    std::string GetName() override;
    std::vector<TrackCircuit*> GetTrackCircuits() const {
        std::vector<TrackCircuit*> tcs;
        for (auto& tc :m_trackCircuits)
            tcs.push_back(tc.get());
        return tcs;

    }
    void AddTrackCircuit(std::unique_ptr<TrackCircuit> tc) {
        m_namedTC[tc->GetShortName()] = tc.get();
        m_trackCircuits.push_back(std::move(tc));
    }
    std::string GetStationA() const { return _stationA; }
    std::string GetStationB() const { return _stationB; }
    std::string GetMainName() const { return _mainName; }
    TrackCircuit& GetTrackCircuit (const std::string& name){
        auto it = m_namedTC.find(name);
        if (it == m_namedTC.end())
        GLIB_FAIL("Track " << GetName() << " does not have track circuit " << name);
        return *(it->second);

    }
    void SetMainName(const std::string& name) {
        _mainName = name;
    }
private:
    // sequence of track circuits from A to B
    std::vector<std::unique_ptr<TrackCircuit> > m_trackCircuits;
    std::unordered_map<std::string, TrackCircuit*> m_namedTC;
    std::string _mainName;
    std::string _stationA;
    std::string _stationB;
};

class Station : public GlobalId {
public:
    Station (const std::string& name) : GlobalId(name) {}
    std::string GetName() override;
    void AddLinePoint (int id, const std::string& trackName);
    void AddCorrectPath(int, int);
    void AddRoute (std::unique_ptr<StationRoute> r) {
        m_stationRoutes[r->GetShortName()] = std::move(r);
    }
    StationRoute& GetRoute(const std::string& name){
        auto it = m_stationRoutes.find(name);
        if (it == m_stationRoutes.end())
            GLIB_FAIL("Station " << GetName() << " does not have route " << name);
        return *(it->second.get());
    }
    std::vector<std::string> GetConnectingTracks() {
        std::vector<std::string> out;
        for (auto& m : m_lp)
            out.push_back(m.second);
        return out;
    }
private:
    std::unordered_map<std::string, std::unique_ptr<StationRoute> > m_stationRoutes;
    std::unordered_map<int, std::string> m_lp;
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

