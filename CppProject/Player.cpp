#include"Player.h"

#include "Defined.h"

#include<sgg/graphics.h>
#include "GameObject.h"
#include <iostream>
#include"Level.h"


void Player::update(float dt)
{
	if(keys=="WASD")
		keyboardWASD(dt);
	if (keys == "IJKL")
		keyboardIJKL(dt);
	Ship::update(dt);

}

void Player::init()
{

	rot_velocity = 30.0;
	const float velocity = 1.5f;

	Ship::init();

}

void Player::hearts()
{
	if (keys == "WASD") {
		for (int i = 0; i < m_HP; i++) {
			SETCOLOR(m_brush_heart.fill_color, 1.0f, 1.0f, 1.0f);
			m_brush_heart.fill_opacity = 1.0f;
			m_brush_heart.outline_opacity = 0.0f;
			m_brush_heart.texture = GET_FULL_ASSET_PATH(IMG_HEART);
			graphics::drawRect(1.5, 37 - (2 * i), 2, 2, m_brush_heart);
		}
	}
	else if (keys == "IJKL") {
		for (int i = 0; i < m_HP; i++) {
			SETCOLOR(m_brush_heart.fill_color, 1.0f, 1.0f, 1.0f);
			m_brush_heart.fill_opacity = 1.0f;
			m_brush_heart.outline_opacity = 0.0f;
			m_brush_heart.texture = GET_FULL_ASSET_PATH(IMG_HEART);
			graphics::drawRect(38.5, 37 - (2 * i), 2, 2, m_brush_heart);
		}
	}

}
Player::~Player()
{
	Ship::~Ship();
}

void Player::keyboardWASD(float dt) {

	float delta_time = dt / 1000.0f;


	mult_buttons_acc = false;
	mult_buttons_rot = false;

	m_time_to_shoot = m_time_to_shoot + dt;

	if ((graphics::getKeyState(graphics::SCANCODE_LALT)) && (m_time_to_shoot > m_fire_timer)) {
		m_time_to_shoot = 0;
		fire(m_rotation);
	}


	if ((graphics::getKeyState(graphics::SCANCODE_W)) && (graphics::getKeyState(graphics::SCANCODE_S)))
	{
		mult_buttons_acc = true;
	}
	if ((graphics::getKeyState(graphics::SCANCODE_A)) && (graphics::getKeyState(graphics::SCANCODE_D)))
	{
		mult_buttons_rot = true;
	}

	if ((graphics::getKeyState(graphics::SCANCODE_A)) && (graphics::getKeyState(graphics::SCANCODE_W)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(1, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(1, dt);
			move_pulse = 0;
			return;
		}
	}

	if ((graphics::getKeyState(graphics::SCANCODE_A)) && (graphics::getKeyState(graphics::SCANCODE_S)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(1, dt, rot_velocity*3/2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(0, dt);
			move_pulse = 0;
			return;
		}
	}

	if ((graphics::getKeyState(graphics::SCANCODE_D)) && (graphics::getKeyState(graphics::SCANCODE_W)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(0, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(1, dt);
			move_pulse = 0;
			return;
		}
	}
	if ((graphics::getKeyState(graphics::SCANCODE_D)) && (graphics::getKeyState(graphics::SCANCODE_S)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(0, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(0, dt);
			move_pulse = 0;
			return;
		}
	}

	if (((!mult_buttons_rot) && graphics::getKeyState(graphics::SCANCODE_D)) || (mult_buttons_rot && (last_move == 3))) {
		rotate(0, dt, rot_velocity*1/2);
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
}
void Player::keyboardIJKL(float dt) {

	float delta_time = dt / 1000.0f;


	mult_buttons_acc = false;
	mult_buttons_rot = false;


	m_time_to_shoot = m_time_to_shoot + dt;

	if ((graphics::getKeyState(graphics::SCANCODE_RALT)) && (m_time_to_shoot > m_fire_timer)) {
		m_time_to_shoot = 0;
		fire(m_rotation);
	}

	if ((graphics::getKeyState(graphics::SCANCODE_I)) && (graphics::getKeyState(graphics::SCANCODE_K)))
	{
		mult_buttons_acc = true;
	}
	if ((graphics::getKeyState(graphics::SCANCODE_J)) && (graphics::getKeyState(graphics::SCANCODE_L)))
	{
		mult_buttons_rot = true;
	}

	if ((graphics::getKeyState(graphics::SCANCODE_J)) && (graphics::getKeyState(graphics::SCANCODE_I)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(1, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(1, dt);
			move_pulse = 0;
			return;
		}
	}

	if ((graphics::getKeyState(graphics::SCANCODE_J)) && (graphics::getKeyState(graphics::SCANCODE_K)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(1, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(0, dt);
			move_pulse = 0;
			return;
		}
	}

	if ((graphics::getKeyState(graphics::SCANCODE_L)) && (graphics::getKeyState(graphics::SCANCODE_I)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(0, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(1, dt);
			move_pulse = 0;
			return;
		}
	}
	if ((graphics::getKeyState(graphics::SCANCODE_L)) && (graphics::getKeyState(graphics::SCANCODE_K)) && !mult_buttons_acc && !mult_buttons_rot)
	{
		if (move_pulse == 0) {
			rotate(0, dt, rot_velocity * 3 / 2);
			move_pulse = 1;
			return;
		}
		else
		{
			move(0, dt);
			move_pulse = 0;
			return;
		}
	}

	if (((!mult_buttons_rot) && graphics::getKeyState(graphics::SCANCODE_L)) || (mult_buttons_rot && (last_move == 3))) {
		rotate(0, dt, rot_velocity * 1 / 2);
		last_move = 3;
		return;
	}
	if (((!mult_buttons_rot) && graphics::getKeyState(graphics::SCANCODE_J)) || (mult_buttons_rot && (last_move == 4))) {
		rotate(1, dt, rot_velocity * 1 / 2);
		last_move = 4;
		return;
	}
	if (((!mult_buttons_acc) && graphics::getKeyState(graphics::SCANCODE_I)) || (mult_buttons_acc && (last_move == 1))) {
		move(1, dt);
		last_move = 1;
		return;
	}
	if (((!mult_buttons_acc) && graphics::getKeyState(graphics::SCANCODE_K)) || (mult_buttons_acc && (last_move == 0))) {
		move(0, dt);
		last_move = 0;
		return;
	}
}
