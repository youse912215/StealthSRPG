#include "gameHelp.h"
#include "sceneTransition.h"
#include "constant.h"
#include "DxLib.h"

int GameHelp::help_num = 0;

GameHelp::GameHelp() {
	manual = LoadGraph("Source/UI/basic_manual2.png");
	map_information = LoadGraph("Source/UI/map_info2.png");
	enemy_information = LoadGraph("Source/UI/enemy_info2.png");
	enemy_information_2 = LoadGraph("Source/UI/enemy_info2b.png");
	return_game = LoadGraph("Source/UI/return_game.png");
}

GameHelp::~GameHelp() {
	DeleteGraph(manual);
	DeleteGraph(enemy_information);
	DeleteGraph(map_information);
	DeleteGraph(return_game);
}

void GameHelp::draw() {
	switch (help_num) {
	case 0:
		DrawGraph(0, 0, manual, true);
		break;
	case 1:
		DrawGraph(0, 0, map_information, true);
		break;
	case 2:
		if (SceneTransition::game_scene == GAME_INFORMATION)
			DrawGraph(0, 0, enemy_information_2, true);
		else DrawGraph(0, 0, enemy_information, true);
		break;
	}

	DrawGraph(700, 30, return_game, true);
}
