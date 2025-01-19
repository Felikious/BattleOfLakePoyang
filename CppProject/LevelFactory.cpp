#include "LevelFactory.h"

#include "Defined.h"

#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TwoFloats.h"
#include "Circle.h"

#include <vector>
#include <iostream>
#include <sgg/graphics.h>

LevelFactory* LevelFactory::m_LevelFactory = nullptr; 

LevelFactory::LevelFactory()
{
}

LevelFactory* LevelFactory::getLevelFactory()
{

	if (m_LevelFactory == nullptr) {
		m_LevelFactory = new LevelFactory;
	}
	return m_LevelFactory;
	
}

Level* LevelFactory::getCurrentLevel()
{
	return m_LevelFactory->currentLevel;
}

void LevelFactory::setSelectedShip(int ship)
{
	if (ship == 1) {
		player_Sprite = red;
		enemy_Sprite = yellow;
		player_stats = { 4.5f,600.0f };
	}
	if (ship == 2) {
		player_Sprite = yellow;
		enemy_Sprite = red;
		player_stats = { 2.6f,350.0f };
	}
	if (ship == 3) {
		player_Sprite = green;
		enemy_Sprite = red;
		player_stats = { 3.0f, 400.0f };
	}
}

void LevelFactory::makeLevel()
{
	if (getLevelFactory()->selected_mult) {

		TwoFloats* goal = new TwoFloats(-20.5, -20.5);

		Player* Player1 = new Player(
			TwoFloats(10, 10), TwoFloats(4, 4),
			getLevelFactory()->red,
			3.0f, std::string("WASD"),
			400.0f, 30.0f);


		Player* Player2 = new Player(
			TwoFloats(30, 10), TwoFloats(4, 4),
			getLevelFactory()->green,
			3.0f, std::string("IJKL"),
			400.0f, 30.0f, false);

		std::vector <Enemy*> m_enemies = { nullptr };

		getLevelFactory()->setLevel(m_enemies, Player1, goal, Player2);
		getLevelFactory()->m_level_now++;
		getCurrentLevel()->dualPlayer = true;
		getCurrentLevel()->init();
		return;
	}


	if (getLevelFactory()->m_level_now==0)
	{
		TwoFloats* goal = new TwoFloats(35, 5);

		Player* Player1 = new Player(
			TwoFloats(5, 35), TwoFloats(4, 4),
			getLevelFactory()->player_Sprite,
			getLevelFactory()->player_stats[0],
			std::string("WASD"),
			getLevelFactory()->player_stats[1],
			P_BUL_SPEED);

		std::vector <Enemy*> m_enemies;

		std::vector <TwoFloats*> myp_p1 = { 
			new TwoFloats(35, 20),
			new TwoFloats(15, 30),
			new TwoFloats(15, 15) };

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p1,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));
		/*
		std::vector <TwoFloats*> myp_p2 = { new TwoFloats(5, 5), new TwoFloats(15, 15) };
		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p2,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));
		*/
		getLevelFactory()->setLevel(m_enemies, Player1, goal);
		getLevelFactory()->m_level_now++;
		getCurrentLevel()->init();
		return;
	}

	if (getLevelFactory()->m_level_now == 1)
	{
		TwoFloats* goal = new TwoFloats(35, 35);

		Player* Player1 = new Player(
			TwoFloats(5, 5), TwoFloats(4, 4),
			getLevelFactory()->player_Sprite,
			getLevelFactory()->player_stats[0],
			std::string("WASD"),
			getLevelFactory()->player_stats[1],
			P_BUL_SPEED);


		std::vector <Enemy*> m_enemies;

		std::vector <TwoFloats*> myp_p1 = {
			new TwoFloats(30, 15),
			new TwoFloats(20, 5),
			new TwoFloats(35, 5) };

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p1,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));

		std::vector <TwoFloats*> myp_p2 = {
			new TwoFloats(15, 30),
			new TwoFloats(5, 20),
			new TwoFloats(5, 35) };

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p2,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));

		getLevelFactory()->setLevel(m_enemies, Player1, goal);
		getLevelFactory()->m_level_now++;
		getCurrentLevel()->init();
		return;
	}
	if (getLevelFactory()->m_level_now == 2)
	{
		TwoFloats* goal = new TwoFloats(35, 35);

		Player* Player1 = new Player(
			TwoFloats(5, 5), TwoFloats(4, 4),
			getLevelFactory()->player_Sprite,
			getLevelFactory()->player_stats[0],
			std::string("WASD"),
			getLevelFactory()->player_stats[1],
			P_BUL_SPEED);


		std::vector <Enemy*> m_enemies;

		std::vector <TwoFloats*> myp_p1 = {
			new TwoFloats(30, 15),
			new TwoFloats(20, 5),
			new TwoFloats(35, 5) };

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p1,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));

		std::vector <TwoFloats*> myp_p2 = {
			new TwoFloats(15, 30),
			new TwoFloats(5, 20),
			new TwoFloats(5, 35) };

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p2,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));


		std::vector <TwoFloats*> myp_p3 = {
		new TwoFloats(35, 35),
		new TwoFloats(5, 5),};

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p3,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));


		getLevelFactory()->setLevel(m_enemies, Player1, goal);
		getLevelFactory()->m_level_now++;
		getCurrentLevel()->init();
		return;
	}

	if (getLevelFactory()->m_level_now == 3)
	{
		TwoFloats* goal = new TwoFloats(5, 35);

		Player* Player1 = new Player(
			TwoFloats(20, 5), TwoFloats(4, 4),
			getLevelFactory()->player_Sprite,
			getLevelFactory()->player_stats[0],
			std::string("WASD"),
			getLevelFactory()->player_stats[1],
			P_BUL_SPEED);


		std::vector <Enemy*> m_enemies;

		std::vector <TwoFloats*> myp_p1 = {
			new TwoFloats(5, 15),
			new TwoFloats(35, 15)};

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p1,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));


		std::vector <TwoFloats*> myp_p2 = {
			new TwoFloats(5, 35),
			new TwoFloats(35, 35),};

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p2,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));


		std::vector <TwoFloats*> myp_p3 = {
		new TwoFloats(35, 35),
		new TwoFloats(5, 5), };

		m_enemies.push_back(new Enemy(
			TwoFloats(4, 4),
			getLevelFactory()->enemy_Sprite,
			E_SPEED, myp_p3,
			E_FIREPOWER, E_BUL_SPEED, 10.0f));


		getLevelFactory()->setLevel(m_enemies, Player1, goal);
		getLevelFactory()->m_level_now++;
		getCurrentLevel()->init();
		return;
	}
	getCurrentLevel()->GameWon();
}

void LevelFactory::setLevel(std::vector<Enemy*> enemies, Player* p1, TwoFloats* goal, Player* p2)
{
	if (getCurrentLevel())
		delete getCurrentLevel();
	LevelFactory::currentLevel = new Level( enemies, p1, goal, p2);
}

void LevelFactory::GameWon() {}

void LevelFactory::GameLost() {}