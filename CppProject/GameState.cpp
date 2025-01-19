#include "GameState.h"

#include "Defined.h"

#include "Level.h"
#include "Player.h"
#include <iostream>
#include "Audio.h"

class LevelFactory;

GameState* m_State_Singleton = nullptr;
Audio* Audio::instance = nullptr;

GameState::GameState() { myLevelFactory = nullptr; }

void GameState::init()
{
	myLevelFactory = LevelFactory::getLevelFactory();
	
	graphics::preloadBitmaps(GET_ASSET_DIR);
}

void GameState::draw()
{
	if (status == STATUS_MAIN_MENU)
	{
		drawMainMenuScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();

	}
	else if (status == STATUS_PAUSE)
	{
		drawPauseScreen();
	}
	else if (status == STATUS_MULT)
	{
		drawMultScreen();
	}
	else if (status == STATUS_CONTROLS)
	{
		drawControlsScreen();
	}
	else if (status == STATUS_WIN)
	{
		drawWinScreen();
	}
	else if (status == STATUS_LOSE)
	{
		drawLoseScreen();
	}
	else if (status == STATUS_SHIP_SELECTION)
	{
	drawShipSelection();
	}
}

void GameState::update(float dt)
{
	if (status == STATUS_MAIN_MENU)
	{
		screen_time = 0.0f;
		lore = true;
		signal_GameWon = false;
		signal_GameOver = false;
		if(myLevelFactory)
			myLevelFactory->resetLevel();
		updateMainMenuScreen(dt);
	}
	else if (status == STATUS_PLAYING)

	{
		if (!(Audio::getInstance()->is_music_playing) && (!(Audio::getInstance()->is_muted)))
		{
			Audio::getInstance()->playMyMusic("song1.mp3", 0.1f, true);
			Audio::getInstance()->is_music_playing = true;
		}
		updateLevelScreen(dt);

	}
	else if (status == STATUS_PAUSE)
	{
		if (Audio::getInstance()->is_music_playing)
		{
			Audio::getInstance()->stopMyMusic();
			Audio::getInstance()->is_music_playing = false;
		}
		updatePauseScreen(dt);
	}
	else if (status == STATUS_MULT)
	{
		updateMultScreen(dt);
	}
	else if (status == STATUS_CONTROLS)
	{
		updateControlsScreen(dt);
	}
	else if (status == STATUS_QUIT) 
	{
		updateQuitScreen(dt);
	}

	else if (status == STATUS_WIN)
	{
		if (Audio::getInstance()->is_music_playing)
		{
			Audio::getInstance()->stopMyMusic();
			Audio::getInstance()->is_music_playing = false;
		}
		updateWinScreen(dt);
	}
	else if (status == STATUS_LOSE)
	{
		if (Audio::getInstance()->is_music_playing)
		{
			Audio::getInstance()->stopMyMusic();
			Audio::getInstance()->is_music_playing = false;
		}
		updateLoseScreen(dt);
	}
	else if (status == STATUS_SHIP_SELECTION)
	{
	updateShipSelection(dt);
	}

}

void GameState::updateLevelScreen(float dt) {

	myLevelFactory->getCurrentLevel()->update(dt);

	Audio::getInstance()->mute(dt);
	if (graphics::getKeyState(graphics::SCANCODE_P) && status == STATUS_PLAYING) {
		status = STATUS_PAUSE;
	}

	if ((signal_GameWon||myLevelFactory->getCurrentLevel()->dualPlayer&& signal_GameOver) && status == STATUS_PLAYING) { //AUTA THA FIGOUN
		status = STATUS_WIN;
	}
	if (signal_GameOver && status == STATUS_PLAYING) {
		status = STATUS_LOSE;
	}
}



void GameState::updateMainMenuScreen(float dt)//diko mas
{

	s_is_pressed(dt);
	w_is_pressed(dt);
	enter_is_pressed_controls(dt);
	
}



void GameState::updatePauseScreen(float dt)//diko mas
{//ENTER
	s_is_pressed(dt);
	w_is_pressed(dt);
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))//ENTER
	{
		if (selected_index == 0)
		{
			status = STATUS_PLAYING;
		}
		else if (selected_index == 1)
		{
			status = STATUS_QUIT;
		}
	}

}

void GameState::updateControlsScreen(float dt) {
	enter_is_pressed_controls(dt);
}


void GameState::updateWinScreen(float dt) {
	ShowScreen(dt);
	selected_index = 0;
}
void GameState::updateLoseScreen(float dt) {
	ShowScreen(dt);
	selected_index = 0;
}

void GameState::updateQuitScreen(float dt) {
	selected_index = 0;
	status = STATUS_MAIN_MENU;
}

void GameState::updateShipSelection(float dt) {
	ShowScreen(dt);
	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		LevelFactory::getLevelFactory()->setSelectedShip(1);
		status = STATUS_PLAYING;
		myLevelFactory->makeLevel();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		LevelFactory::getLevelFactory()->setSelectedShip(2);
		status = STATUS_PLAYING;
		myLevelFactory->makeLevel();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_3))
	{
		LevelFactory::getLevelFactory()->setSelectedShip(3);
		status = STATUS_PLAYING;
		myLevelFactory->makeLevel();
	}
}


void GameState::updateMultScreen(float dt)
{
	ShowScreen(dt);
}

void GameState::drawMainMenuScreen()
{


	//draw options
	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_background.outline_opacity = 0.0f;

	float h = GameState::getState()->get_canvas_height();
	float w = GameState::getState()->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);

	if (selected_index == 0)
	{
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_START_START);
	}
	else if (selected_index == 1)
	{
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_START_MULT);
	}
	else if (selected_index == 2)
	{
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_START_CONTR);
	}

}

void GameState::drawLevelScreen() {
	myLevelFactory->getCurrentLevel()->draw();
	Audio::getInstance()->drawMuteButton();
}


void GameState::drawPauseScreen() {

	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_background.outline_opacity = 0.0f;

	float h = GameState::getState()->get_canvas_height();
	float w = GameState::getState()->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);

	if (selected_index == 0)
	{
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_PAUSE_RESUM);
	}
	else if (selected_index == 1)
	{
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_PAUSE_QUIT);
		myLevelFactory->resetLevel();
	}
}



void GameState::drawMultScreen()
{
	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_background.outline_opacity = 0.0f;
	float h = GameState::getState()->get_canvas_height();
	float w = GameState::getState()->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
	m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_MULT);
}

void GameState::drawControlsScreen()
{
	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_background.outline_opacity = 0.0f;

	float h = GameState::getState()->get_canvas_height();
	float w = GameState::getState()->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);

	m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_CTRL);
}

void GameState::drawWinScreen()
{
	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_background.outline_opacity = 0.0f;

	float h = GameState::getState()->get_canvas_height();
	float w = GameState::getState()->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);

	m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_WIN);
	//Might fuck shit up 
}

void GameState::drawLoseScreen()
{
	SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_background.outline_opacity = 0.0f;

	float h = GameState::getState()->get_canvas_height();
	float w = GameState::getState()->get_canvas_width();
	graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
	m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_LOST);
	//Might fuck shit up 
}
void GameState::drawShipSelection() {

	if (lore == false) {
		SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
		m_brush_background.outline_opacity = 0.0f;
		float h = GameState::getState()->get_canvas_height();
		float w = GameState::getState()->get_canvas_width();
		graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_SHIP_SEL);
	}
	else
	{
		SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
		m_brush_background.outline_opacity = 0.0f;
		float h = GameState::getState()->get_canvas_height();
		float w = GameState::getState()->get_canvas_width();
		graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
		m_brush_background.texture = GET_FULL_ASSET_PATH(IMG_LORE);
	}
}

GameState::~GameState()
{

	if (myLevelFactory->getCurrentLevel())
		delete myLevelFactory->getCurrentLevel();
}

GameState* GameState::getState()
{
	if (m_State_Singleton == nullptr) {
		m_State_Singleton = new GameState;
	}
	return m_State_Singleton;
}

float GameState::get_canvas_height() {
	return m_canvas_height;
}

float GameState::get_canvas_width() {
	return m_canvas_width;
}

void GameState::s_is_pressed(float dt) {

	s_press_time += dt;

	if (graphics::getKeyState(graphics::SCANCODE_S) && (!s_pressed) && (s_press_time >= cooldown)) {
		if (status == STATUS_MAIN_MENU)
		{
			if (selected_index < 2)
			{
				selected_index += 1;
			}
			else
			{
				selected_index = 0;
			}
		}
		else if (status == STATUS_PAUSE)
		{
			if (selected_index < 1)
			{
				selected_index += 1;
			}
			else
			{
				selected_index = 0;
			}
		}
		s_pressed = true;
		s_press_time = 0.0f;
	}
	else if (!graphics::getKeyState(graphics::SCANCODE_S)) {
		s_pressed = false;
	}
}

void GameState::w_is_pressed(float dt) {

	w_press_time += dt;

	if (graphics::getKeyState(graphics::SCANCODE_W) && (!w_pressed) && (w_press_time >= cooldown)) {
		if (status == STATUS_MAIN_MENU)
		{
			if (selected_index > 0)
			{
				selected_index -= 1;
			}
			else
			{
				selected_index = 2;
			}
		}
		else if (status == STATUS_PAUSE)
		{
			if (selected_index > 0)
			{
				selected_index -= 1;
			}
			else
			{
				selected_index = 1;
			}
		}

		w_pressed = true;
		w_press_time = 0.0f;
	}
	else if (!graphics::getKeyState(graphics::SCANCODE_W)) {
		w_pressed = false;
	}
	//return selected_index;
}

void GameState::enter_is_pressed_controls(float dt) {

	enter_press_time += dt;

	if (graphics::getKeyState(graphics::SCANCODE_RETURN) && (!enter_pressed) && (enter_press_time >= cooldown)) {
		enter_pressed = true;

		enter_press_time = 0.0f;
		if (status == STATUS_CONTROLS)
		{
			status = STATUS_MAIN_MENU;
		}
		else
		{

			if (selected_index == 0)
			{
				status= STATUS_SHIP_SELECTION;
			}
			else if (selected_index == 1)
			{
				status = STATUS_MULT;
			}
			else if (selected_index == 2)
			{
				status = STATUS_CONTROLS;
			}
		}
	}
	else if (!graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		enter_pressed = false;
	}
}

void GameState::ShowScreen(float dt) {
	if (((lore == true) || ((status == STATUS_WIN) || status == STATUS_LOSE))) {
		screen_time += dt;
		if ((screen_time > 2000.0f) && (status == STATUS_MULT)) {
			myLevelFactory->selected_mult = true;
			myLevelFactory->makeLevel();
			myLevelFactory->selected_mult = false;
			status = STATUS_PLAYING;
		}
		else if ((screen_time > 7000.0f) && (status == STATUS_SHIP_SELECTION)) {
			lore = false;
			screen_time = 0.0f;
		}
		else if ((screen_time > 3500.0f) && ((status == STATUS_WIN) || status == STATUS_LOSE))
			status = STATUS_MAIN_MENU;

	}
}


GameState* GameState::m_State_Singleton = nullptr;
