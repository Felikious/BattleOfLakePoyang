#include "sgg/graphics.h"

#include "Defined.h"

#include <stdio.h>
#include <string>
#include "GameState.h"


void init() {
	GameState::getState()->init();
}



void draw() {
	GameState::getState()->draw();

}

void update(float dt) {
	GameState::getState()->update(dt);
}




int main(int argc, char** argv) {

	graphics::createWindow(800, 800, "Project");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getState()->get_canvas_width(), GameState::getState()->get_canvas_height());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();
	return 0;
}