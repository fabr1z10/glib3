#pragma once

class Interpolator1D {
public:
    virtual float get(float) = 0;
    virtual void addNode (float x, float y) = 0;

};

class