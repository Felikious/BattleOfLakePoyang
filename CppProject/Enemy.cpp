#include"Enemy.h"

#include "Defined.h"

#include<sgg/graphics.h>
#include <iostream>
#include <cmath>
#include"Level.h"


void Enemy::update(float dt)
{
	if (state == Rotating) {
		if (rot_status == Left) {
			rotate(1, dt, rot_velocity);
		}
		if (rot_status == Right) {
			rotate(0, dt, rot_velocity);
		}
		if (fabs(m_rotation - m_wanted_rotation) < 3.0f) {
			m_rotation = m_wanted_rotation;
			state = Moving;
		}
	}

	if (NearMe.isOverlapping(m_patrol_points[m_trav_index]) && state == Moving) {

		m_trav_index++;
		m_trav_index = m_trav_index % m_patrol_points.size();

		TwoFloats dest = *m_patrol_points[m_trav_index];

		float dx = dest.x - m_pos_x;
		float dy = dest.y - m_pos_y;

		m_wanted_rotation = atan2(dx, dy);
		m_wanted_rotation = m_wanted_rotation * 180.0f / 3.141592f;
		m_wanted_rotation = fmod(m_wanted_rotation + 360.0f + 270.0f, 360.0f);

		state = Rotating;

		double difference = m_wanted_rotation - m_rotation;

		// Normalize the difference to the range [-180, 180]
		if (difference > 180.0) {
			difference -= 360.0;
		}
		else if (difference < -180.0) {
			difference += 360.0;
		}
		if (difference > 0) {
			rot_status = Left;
		}
		else if (difference < 0) {
			rot_status = Right;
		}
		else {
			state = Moving;
		}


	}

	if (state == Moving) {
		move(1, dt);
	}

	m_seeing_circle->changeLoc(m_pos_x, m_pos_y);

	Ship::update(dt);
}

void Enemy::init()
{
	rot_velocity = 30.0f;
	m_seeing_circle->setRadius(m_seeing_range);
	Ship::init();
	state = Moving;
	rot_status = Left;

	m_HP = 3;

}


void Enemy::fire(float rot_to_fire, float dt)
{
	m_time_to_shoot = m_time_to_shoot + dt;

	if (m_time_to_shoot > m_fire_timer) {
		m_time_to_shoot = 0;
		Ship::fire(rot_to_fire);
	}

}

Enemy::~Enemy()
{
	for (auto p_gob : m_patrol_points)
		if (p_gob) delete p_gob;
	Ship::~Ship();
}

void usable() {/*

	if (((!mult_buttons_rot) && graphics::getKeyState(graphics::SCANCODE_D)) || (mult_buttons_rot && (last_move == 3))) {
		rotate(0, dt, rot_velocity * 1 / 2);
		last_move = 3;
		return;
	}
	if (((!mult_buttons_rot) && graphics::getKeyState(graphics::SCANCODE_A)) || (mult_buttons_rot && (last_move == 4))) {
		rotate(1, dt, rot_velocity * 1 / 2);
		last_move = 4;
		return;
	}
	if (((!mult_buttons_acc) && graphics::getKeyState(graphics::SCANCODE_W)) || (mult_buttons_acc && (last_move == 1))) {
		move(1, dt);
		last_move = 1;
		return;
	}
	if (((!mult_buttons_acc) && graphics::getKeyState(graphics::SCANCODE_S)) || (mult_buttons_acc && (last_move == 0))) {
		move(0, dt);
		last_move = 0;
		return;
	}
	*/
}