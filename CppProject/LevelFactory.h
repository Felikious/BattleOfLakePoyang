#pragma once

#include "Defined.h"

#include "TwoFloats.h"
#include "Circle.h"

#include <vector>
#include <iostream>
#include <sgg/graphics.h>

class Level;
class Player;
class Enemy;
class Ship;

class LevelFactory{
private:
	graphics::Brush m_brush_background;

	Level* currentLevel;

	std::vector <float> player_stats = { 3.0f, 400.0f };

	std::vector<std::string*> red = {
		new std::string(IMG_RED_1),
		new std::string(IMG_RED_2),
		new std::string(IMG_RED_3)
	};

	std::vector<std::string*> yellow = {
		new std::string(IMG_YELLOW_1),
		new std::string(IMG_YELLOW_2),
		new std::string(IMG_YELLOW_3)
	};

	std::vector<std::string*> green = {
		new std::string(IMG_GREEN_1),
		new std::string(IMG_GREEN_2),
		new std::string(IMG_GREEN_3)
	};

	float min_x = 2.5;
	float max_x = 37.5;
	float min_y = 2.5;
	float max_y = 37.5;
	
	
	int m_level_now = 0;
	static LevelFactory* m_LevelFactory;
	LevelFactory();
	void setLevel(std::vector <Enemy*> m_enemies, Player* p1, TwoFloats* goal, Player* enemy = nullptr);

	void GameWon();
	void GameLost();

	std::vector <std::string*> player_Sprite = red;
	std::vector <std::string*> player2_Sprite = yellow;
	std::vector <std::string*> enemy_Sprite = yellow;

public:

	bool selected_mult = false;

	static LevelFactory* getLevelFactory();
	static Level* getCurrentLevel();

	void setSelectedShip(int ship);
	//int getSelectedShip() const { return selected_ship; }

	static void resetLevel(){ getLevelFactory()->m_level_now = 0; }
	static void makeLevel();

};
