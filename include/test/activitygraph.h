#pragma once

#include <memory>
#include <vector>

class Edge;

class Activity {
public:
    int getEST() const;
private:
    std::vector<std::shared_ptr<Edge>> _inEdges;
    std::vector<std::shared_ptr<Edge>> _outEdges;
    // time train head enters the resource
    int _est;
    // time train tail leaves the resource
    int _timeOut;
};


// represents a very generic reosurce activity (node in the activity graph)
// an activity represents the concept of a USER occupying a RESOURCE for an INTERVAL of time [t0, t1]
// In the train case, USER = train, RESOURCE = track circuit, station route or stopping point.
class ResourceActivity : public Activity {
public:

private:
    int _trainId;
    int _resourceId;

};


// a directed edge connecting two activities
class Edge {
public:

private:
    std::shared_ptr<Activity> _head;
    std::shared_ptr<Activity> _tail;

};

class ActivityGraph {
public:
    void AddActivity (std::shared_ptr<Activity> activity);

};


