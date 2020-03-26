#pragma once


class Rect {
public:
    Rect (float width, float height) : m_width(width), m_height(height) {}
    float area() const;
    float width() const;
    float height() const;
private:
    float m_width;
    float m_height;
};