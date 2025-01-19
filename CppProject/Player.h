#pragma once

#include "Defined.h"

#include "Ship.h"
#include "TwoFloats.h"
#include "GameObject.h"
#include <sgg/graphics.h>

class Player : public Ship {

	graphics::Brush m_brush_heart;
	graphics::Brush m_brush_player;
	int last_move = 0;
	//int updates_before_move_change = 0;
	bool mult_buttons_acc = false;
	bool mult_buttons_rot = false;
	bool move_pulse = 0;

	void keyboardWASD(float dt);
	void keyboardIJKL(float dt);

public:
	Player(TwoFloats pos, TwoFloats size , std::vector <std::string*> fn, float v, std::string keys, float firepower, float bullet_velocity, bool IamP2=true)
		:  Ship(pos, size, fn, v,firepower, bullet_velocity, IamP2),keys(keys) {}

	//	Ship::Ship(TwoFloats pos, TwoFloats size, std::string fn, float v, bool r, float bullet_timer, float bv)
	void update(float dt);
	void init();
	void draw() { Ship::draw(); hearts(); };
	void hearts();
	bool isActive() { return true; }
	std::string keys;
	~Player();

	//Overide, pio poly mnimoniko. Den peirazei kai na to jexasw
};