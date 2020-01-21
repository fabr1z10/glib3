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

template <class G, class T>
class VisitorOutput {
public:
    virtual ~VisitorOutput() {}
    virtual G visit(T&) = 0;
};