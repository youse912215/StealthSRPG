#include "gameTitle.h"
#include "DxLib.h"

int GameTitle::button_timer = 0;

GameTitle::GameTitle() {
	title = LoadGraph("Source/UI/title.png");
	button = LoadGraph("Source/UI/start.png");
}

GameTitle::~GameTitle() {
	DeleteGraph(title);
	DeleteGraph(button);
	DeleteGraph(button_timer);
}

void GameTitle::draw() {
	DrawGraph(0, 0, title, true);
	DrawRectGraph(210, 450, 0, button_timer * 64, 540, 64,
	              button, true, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", button_timer, false);
}

void GameTitle::get_timer() {
	button_timer = button_timer >= 3 ? 0 : ++button_timer;
}

void GameTitle::update() {
	get_timer();
	draw();
}
