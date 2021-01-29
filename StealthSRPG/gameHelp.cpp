#include "gameHelp.h"
#include "DxLib.h"

int GameHelp::help_num = 0;

GameHelp::GameHelp() {
	manual = LoadGraph("Source/UI/basic_manual.png");
	enemy_infomation = LoadGraph("Source/UI/enemy_info.png");
	map_infomation = LoadGraph("Source/UI/map_info.png");
}

GameHelp::~GameHelp() {
	DeleteGraph(manual);
	DeleteGraph(enemy_infomation);
	DeleteGraph(map_infomation);
}

void GameHelp::draw() {
	switch (help_num) {
	case 0:
		DrawGraph(0, 0, manual, true);
		break;
	case 1:
		DrawGraph(0, 0, map_infomation, true);
		break;
	case 2:
		DrawGraph(0, 0, enemy_infomation, true);
		break;
	}
}
