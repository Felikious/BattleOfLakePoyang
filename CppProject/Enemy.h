#pragma once

#include "Defined.h"

#include "Ship.h"
#include "TwoFloats.h"
#include"GameObject.h"
#include<sgg/graphics.h>


class Enemy : public Ship {

	graphics::Brush m_brush;

	typedef enum { Moving, Rotating } status;
	status state = Moving;

	typedef enum { Right, Left, None } rotating;
	rotating rot_status = None;

	int m_trav_index = 0;
	float m_wanted_rotation = 0;

	std::vector <TwoFloats*> m_patrol_points;

	float m_seeing_range = 10;


public:

	Enemy(TwoFloats size, std::vector <std::string*> fn, float v, std::vector <TwoFloats*> p_p, float b_time, float b_veloc, float range)
		: Ship(*p_p[0], size, fn, v, b_time, b_veloc, false), m_patrol_points(p_p), m_seeing_range(range) {}

	void update(float dt) override;
	void init() override;
	void draw() { Ship::draw(); };
	bool isActive() { return m_active; }

	Circle* m_seeing_circle = new Circle(0, 0, m_seeing_range);

	void fire(float rot_to_shoot, float dt);

	~Enemy();
	//Overide, pio poly mnimoniko. Den peirazei kai na to jexasw
};