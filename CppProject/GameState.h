#pragma once

#include "Defined.h"

#include <string>
#include <sgg/graphics.h>
#include "Level.h"
#include "player.h"
#include "LevelFactory.h"

class GameObject;

class GameState {

	typedef enum { STATUS_MAIN_MENU, STATUS_MULT, STATUS_CONTROLS, STATUS_PLAYING, STATUS_PAUSE, STATUS_WIN, STATUS_LOSE, STATUS_QUIT, STATUS_SHIP_SELECTION } status_t;

	int selected_index = 0;
	// 
	//Enemy* meteorite = nullptr;
	//void spawnMeteorite();
	//void checkMeteorite();
	//bool checkCollision();
	status_t status = STATUS_MAIN_MENU;

	//methods
	void updateMainMenuScreen(float dt);
	void updateLevelScreen(float dt);
	void updatePauseScreen(float dt);
	void updateQuitScreen(float dt);
	void updateLoseScreen(float dt);
	void updateShipSelection(float dt);
	void updateWinScreen(float dt);
	void updateMultScreen(float dt);
	void updateControlsScreen(float dt);

	void drawMainMenuScreen();
	void drawLevelScreen();
	void drawPauseScreen();
	void drawLoseScreen();
	void drawWinScreen();
	void drawShipSelection();

	void ShowScreen(float dt);

	void drawMultScreen();
	void drawControlsScreen();

	//void select();
	//void highLight();

private:

	std::string m_asset_path = "assets\\";

	float m_canvas_width = 40;
	float m_canvas_height = 40;

	graphics::Brush m_brush_background;
	graphics::Brush m_brush_player;

	static GameState* m_State_Singleton;
	GameState();

	LevelFactory* myLevelFactory;
public:
	//void setDebugMode(bool d) { debug_mode = d; }
	//void getDebugMode() const { return debug_mode; }
	//void update();
	//void init();

	bool signal_GameOver = false; //used by level to signify when GameOver
	bool signal_GameWon = false;  //used by level to signify when GameOver


	TwoFloats boundaries_max = { MAX_X, MAX_Y };
	TwoFloats boundaries_min = { MIN_X, MIN_Y };

	float m_player_y = m_canvas_height / 2.0f;
	float m_player_x = m_canvas_width / 2.0f;

	float get_canvas_height();
	float get_canvas_width();

	void init();
	void draw();
	void update(float dt);

	~GameState();

	static GameState* getState();

	void s_is_pressed(float dt);
	void w_is_pressed(float dt);
	void enter_is_pressed_controls(float dt);


	bool w_pressed = false;
	bool s_pressed = false;
	bool enter_pressed = false;
	bool controls_screen = false;

	float s_press_time = 0.0f;
	float w_press_time = 0.0f;
	float enter_press_time = 0.0f;
	float screen_time = 0.0f;
	bool lore = true;

	const float cooldown = 0.3f;

	// and a lot more info about the game
};
