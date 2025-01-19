#pragma once

#include "Defined.h"

#include "GameObject.h"
#include "TwoFloats.h"

#include <iostream>
#include <sgg/graphics.h>
#include <string> 
#include <vector> 


#define SETCOLOR(c,r,g,b){c[0]=r; c[1]=g; c[2]=b;}

class RoundShot :public GameObject
{
    
public:
    float m_pos_x;
    float m_pos_y;

    float m_size;

    float m_rotation;

    bool m_side;

    float m_velocity = 40.0f;//im fast as fuck boyyy'

    //bourtsa
    graphics::Brush m_brush;


public:

    RoundShot(TwoFloats spawn, float rotation, float velocity, float size, bool p_side)
        :m_pos_x(spawn.x), m_pos_y(spawn.y), m_rotation(rotation), m_velocity(velocity),m_size(size),m_side(p_side)
    {
        init();
    }

    void move(float dt)
    {
        float m_radiants = m_rotation * 3.14159f / 180.0f;
        float delta_time = dt / 1000.0f;


        m_pos_x = m_pos_x + cos(m_radiants) * delta_time * m_velocity;
        m_pos_y = m_pos_y - sin(m_radiants) * delta_time * m_velocity;
    }

    void init() {
        SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
        //kanontas set color kai meta texture, einai san na vazw colored lences stin eikona
        m_brush.outline_opacity = 0.0f;
        m_brush.texture = GET_FULL_ASSET_PATH(IMG_BULLET);
    }
    void draw()
    {
        if (!m_active)
            return;
        graphics::drawRect(m_pos_x, m_pos_y, 0.5, 0.5, m_brush);
    }

    void update(float dt)
    {
        move(dt);
    }

    void explode();//stamataei

    //bool isActive() { return m_active; }
};