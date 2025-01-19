#pragma once

#include "Defined.h"

#include "GameObject.h"
#include "Circle.h"
#include "TwoFloats.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sgg/graphics.h>
#include <string> 

class Ship : public GameObject
{
public:

    int m_HP = 8;
    int m_full_HP = 8;

    float m_pos_x = 0.0f;
    float m_pos_y = 0.0f;
    
    TwoFloats* max_coord = new TwoFloats(MAX_X, MAX_Y);
    TwoFloats* min_coord = new TwoFloats(MIN_X, MIN_Y);

    float m_width = 4.0f;
    float m_height = 4.0f;

    float m_rotation =  0.0f;
    float m_radiants = 0.0f;
    float m_velocity = 1.5f;
    float rot_velocity = 30.0f;

    float m_fire_timer=100.0f;
    float m_time_to_shoot=0.0f;
    float m_bullet_velocity=40.f;
    
    bool m_player_side = false;

    graphics::Brush m_brush;
    std::vector  <std::string*> m_filename= {
        new std::string("ship (1).png"),
        new std::string("ship (2).png"),
        new std::string("ship (1).png")
    };

    Circle NearMe;
    Circle CC1;
    Circle CC2;
    Circle CC3;
    std::vector <Circle*> myCollisionCircles = { &CC1,&CC2,&CC3 };

    void move(int direction, float dt);
    void rotate(int direction, float dt, float rot_v);
    void updateCC();

    bool isNear(Circle& circle);
    bool isNear(TwoFloats& point);
    bool isNear(Ship& ship);

    bool isColliding(Ship& ship);
    bool isColliding(TwoFloats& pos);
    void isCollidingFixPos(Ship& ship);
    void isCollidingFixPos(TwoFloats& max, TwoFloats& min);

    void correct_Ship_position(Circle& myCircle, Circle& theirCircle);

    //void correct_Ship_position(float x);

    virtual void init();
    virtual void draw();
    virtual void update(float dt);

    virtual void fire(float rot_to_shoot);
    virtual void shipShot();
    virtual void sinking();

    Ship();
    Ship(TwoFloats pos, TwoFloats size, std::vector <std::string*> fn, float v, float shoottimer, float bul_vel, bool p_side);
    virtual ~Ship();

};

