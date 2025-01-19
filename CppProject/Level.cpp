#include "Level.h"

#include "Defined.h"

#include"GameState.h"
#include"Player.h"
#include"Ship.h"
#include "Enemy.h"
#include "TwoFloats.h"
#include "LevelFactory.h"
#include "RoundShot.h"

#include <vector>
#include <iostream>



void Level::createBullet(TwoFloats* spawn, float rotation, float velocity, bool side, float size)
{
	m_bullets.push_back(new RoundShot(*spawn, rotation, velocity, size, side));
}



void Level::update(float dt)
{
	if (getPlayer()) {
		if (getPlayer()->isActive())
			getPlayer()->update(dt);
	}
	//inactive when death. Prepare funeral

	if (!dualPlayer) {
		SinglePlayerUpdate(dt);
	}
	else {
		DualPlayerUpdate(dt);

		if ((getPlayer2()->m_HP) == 0)
		{
			GameState::getState()->signal_GameOver = true;
		}
	}

	if (level_inited) {
		if (getPlayer()) {
			if ((getPlayer()->m_HP) == 0)
			{
				GameState::getState()->signal_GameOver = true;
			}
		}
	}
}

void Level::init()
{
	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	//kanontas set color kai meta texture, einai san na vazw colored lences stin eikona
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.fill_opacity = 1.0f;
	m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_MAP);


	SETCOLOR(m_brush_flag.fill_color, 1.0f, 1.0f, 1.0f);
	//kanontas set color kai meta texture, einai san na vazw colored lences stin eikona
	m_brush_flag.fill_opacity = 1.0f;
	m_brush_flag.outline_opacity = 0.0f;
	m_brush_flag.texture = GET_FULL_ASSET_PATH(IMG_FLAG);


	getPlayer()->init();

	for (auto& p_gob : m_enemy_ships)
		if (p_gob) p_gob->init();

	if (dualPlayer and getPlayer2()) {
		getPlayer2()->init();
	}
	GameState::getState()->signal_GameOver = false;

	level_inited = true;
}

void Level::draw()
{
	float h = m_state->get_canvas_height();
	float w = m_state->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);

	for (auto& p_gob : m_enemy_ships) {
		if (p_gob) {
			//INACTIVE SHIPS ARE DRAWN AS SHIPWRECKS
			p_gob->draw();
		}
	}
	for (auto& p_gob : m_bullets) {
		if (p_gob) {
			if (p_gob->isActive())
				p_gob->draw();
		}
	}
	if (getPlayer()->isActive()) {
		getPlayer()->draw();
	}
	if (getPlayer2()->isActive() && getPlayer2()) {
		getPlayer2()->draw();
	}

	drawFlag();
	
}

Level::Level(const std::string& name)
{
}

Level::Level(std::vector<Enemy*> enemy_ships, Player* Player1, TwoFloats* goal, Player* Player2)
	:m_enemy_ships(enemy_ships), m_player1(Player1), m_goal(goal), m_player2(Player2)
{
	init();
}


void Level::enemyCheckPlayer(Enemy* enemy, float dt)
{
	if (getPlayer()->isNear(*enemy->m_seeing_circle)) {


		float dx = getPlayer()->m_pos_x - enemy->m_pos_x;
		float dy = getPlayer()->m_pos_y - enemy->m_pos_y;

		float rot_toshoot = atan2(dx, dy);
		rot_toshoot = rot_toshoot * 180.0f / 3.141592f;
		rot_toshoot = fmod(rot_toshoot + 360.0f + 270.0f, 360.0f);
		enemy->fire(rot_toshoot, dt);

	}
}


void Level::SinglePlayerUpdate(float dt)
{
	for (auto& enemy : m_enemy_ships) {
		if (enemy) {

			enemy->update(dt);

			if (getPlayer()->isNear(*enemy)) {
				getPlayer()->isCollidingFixPos(*enemy);
			}
			enemyCheckPlayer(enemy, dt);
		}
	}

	for (auto& bullet : m_bullets) {
		if (bullet) {

			if (bullet->isActive()) {
				bullet->update(dt);

				m_bull_check_coord->x = bullet->m_pos_x;
				m_bull_check_coord->y = bullet->m_pos_y;




				if (!bullet->m_side) {
					if (getPlayer()->isNear(*m_bull_check_coord)) {
						if (getPlayer()->isColliding(*m_bull_check_coord)) {
							bullet->setActive(false);
							getPlayer()->shipShot();
						}
					}
				}

				if (bullet->m_side) {
					for (auto& enemy : m_enemy_ships) {
						if (enemy->isNear(*m_bull_check_coord)) {
							if (enemy->isColliding(*m_bull_check_coord)) {
								bullet->setActive(false);
								enemy->shipShot();
							}
						}
					}
				}


			}//bulletactive

		}//bullet exists
	}//for bullet

	if (getPlayer()->isNear(*m_goal)) {
		LevelFactory::getLevelFactory()->makeLevel();
	}
}

void Level::DualPlayerUpdate(float dt)
{

	if (getPlayer()->isNear(*getPlayer2()) && getPlayer()->isActive()) {
		getPlayer()->isCollidingFixPos(*getPlayer2());
	}
	if (getPlayer2()->isActive())
		getPlayer2()->update(dt);

	if (getPlayer2()->isNear(*getPlayer()) && getPlayer2()->isActive()) {
		getPlayer2()->isCollidingFixPos(*getPlayer());
	}

	for (auto& bullet : m_bullets) {
		if (bullet) {

			if (bullet->isActive()) {
				bullet->update(dt);

				m_bull_check_coord->x = bullet->m_pos_x;
				m_bull_check_coord->y = bullet->m_pos_y;


				if (!bullet->m_side) {
					if (getPlayer()->isNear(*m_bull_check_coord)) {
						if (getPlayer()->isColliding(*m_bull_check_coord)) {
							bullet->setActive(false);
							getPlayer()->shipShot();
						}
					}
				}

				if (bullet->m_side) {
					if (getPlayer2()->isNear(*m_bull_check_coord)) {
						if (getPlayer2()->isColliding(*m_bull_check_coord)) {
							bullet->setActive(false);
							getPlayer2()->shipShot();
						}
					}
				}


			}//bulletactive

		}//bullet exists
	}


}

void Level::drawFlag() {
	if (dualPlayer)
		return;
	graphics::drawRect(m_goal->x, m_goal->y, 2, 2, m_brush_flag);
}

void Level::GameWon()
{
	GameState::getState()->signal_GameWon = true;
}

Level::~Level()
{
	for (auto p_gob : m_enemy_ships)
		if (p_gob) delete p_gob;

	for (auto p_gob : m_bullets)
		if (p_gob) delete p_gob;

	if (m_bull_check_coord)
		delete m_bull_check_coord;

	if (m_player2) {
		delete m_player2;
		m_player2 = nullptr;
	}
	if (m_player1) {
		delete m_player1;
		m_player1 = nullptr;
	}
}
