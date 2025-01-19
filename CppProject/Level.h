#pragma once

#include "Defined.h"

#include <sgg/graphics.h>
#include <iostream>
#include <vector>
#include "Circle.h"
#include "GameObject.h"

class Enemy;
class Ship;
class RoundShot;
class Player;


class Level :public GameObject {
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_flag;
	bool level_inited = false;
	class Player* m_player1 = 0;
	class Player* m_player2 = 0;
	TwoFloats* m_goal = 0;

	std::vector<Enemy*> m_enemy_ships;
	std::vector<RoundShot*> m_bullets;

	TwoFloats* max_coord = new TwoFloats(MAX_X, MAX_Y);
	TwoFloats* min_coord = new TwoFloats(MIN_X, MIN_Y);
	TwoFloats* m_bull_check_coord = new TwoFloats(0, 0);


	void SinglePlayerUpdate(float dt);
	void DualPlayerUpdate(float dt);
	void drawFlag();
public:

	void GameWon();
	bool dualPlayer = false;

	class Player* getPlayer() { return m_player1; }
	class Player* getPlayer2() { return m_player2; }

	void createBullet(TwoFloats* spawn, float rotation, float velocity, bool side, float size = 0.5f);
	void enemyCheckPlayer(Enemy* enemy, float dt);

	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level0");

	Level(
		std::vector<Enemy*> enemy_ships,
		Player* Player1,
		TwoFloats* goal,
		Player* Player2 = nullptr
	);


	~Level();
};