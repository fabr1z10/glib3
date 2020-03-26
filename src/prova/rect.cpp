#include "rect.h"

float Rect::width() const {
    return m_width;
}

float Rect::height() const {
    return m_height;
}

float Rect::area() const {
    return m_width * m_height;
}