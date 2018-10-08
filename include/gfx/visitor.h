#pragma once


class AcyclicVisitor {
public:
    virtual ~AcyclicVisitor() {}
};

template <class T>
class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visit(T&) = 0;
};