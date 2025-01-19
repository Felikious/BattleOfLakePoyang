#pragma once

#include "Defined.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include "TwoFloats.h"

struct Circle
{
    float m_pos_x = 0.0f;
    float m_pos_y = 0.0f;
    float m_radius = 1.0f;

    Circle()
        : m_pos_x(0), m_pos_y(0), m_radius(1) {
    }
    Circle(float x, float y, float r)
        : m_pos_x(x), m_pos_y(y), m_radius(r) {}

    bool isOverlapping(Circle* ptr_other) {
        Circle other = *ptr_other;
        float dx = m_pos_x - ptr_other->m_pos_x;
        float dy = m_pos_y - ptr_other->m_pos_y;
        float curr_dist = std::sqrt(dx * dx + dy * dy);
        curr_dist = curr_dist - m_radius - other.m_radius;
        if (curr_dist >= -0.001) {
            return false;
        }
        else {
            return true;
        }
    }

    bool isOverlapping(TwoFloats* ptr_other) {
        TwoFloats pos = *ptr_other;
        float other_x = pos.x;
        float other_y = pos.y;
        float dx = m_pos_x - other_x;
        float dy = m_pos_y - other_y;
        float curr_dist = std::sqrt(dx * dx + dy * dy);
        if (curr_dist > m_radius) {
            return false;
        }
        else {
            return true;
        }
    }

    bool isInsideBox(TwoFloats& max, TwoFloats& min) {
        if(m_pos_x-m_radius<=min.x||m_pos_x+m_radius>=max.x)
            return true;
        if (m_pos_y - m_radius <= min.y || m_pos_y + m_radius >= max.x)
            return true;
        return false;
    }

    TwoFloats corr_Poss(TwoFloats& max, TwoFloats& min) {

        if (m_pos_x - m_radius <= min.x)
            return TwoFloats(min.x + m_radius - m_pos_x, 0.0f);
        if (m_pos_x + m_radius >= max.x)
            return TwoFloats(max.x - m_radius - m_pos_x, 0.0f);
        if (m_pos_y - m_radius <= min.y)
            return TwoFloats(0.0f, min.y + m_radius - m_pos_y);
        if (m_pos_y + m_radius >= max.y)
            return TwoFloats(0.0f, max.y - m_radius - m_pos_y);
        return TwoFloats(0.0f, 0.0f);
    }

    TwoFloats corr_Poss(Circle* ptr_other) {

        float corr_dist = m_radius + ptr_other->m_radius;
        float dx = m_pos_x - ptr_other->m_pos_x;
        float dy = m_pos_y - ptr_other->m_pos_y;
        float curr_dist = std::sqrt(dx * dx + dy * dy);
        float overlap = corr_dist - curr_dist;
        if (curr_dist == 0) { return TwoFloats(0, 0); }
        float unitDx = dx / curr_dist;
        float unitDy = dy / curr_dist;
        float scaledDx = unitDx * overlap;
        float scaledDy = unitDy * overlap;

        return TwoFloats(scaledDx, scaledDy);

        //return TwoFloats(m_pos_x, m_pos_y);
    }

    void changeLoc(float x, float y)
    {
        m_pos_x = x;
        m_pos_y = y;
    }

    void setRadius(float r)
    {
        m_radius = r;
    }
};
