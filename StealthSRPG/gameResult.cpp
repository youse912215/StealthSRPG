#include "gameResult.h"
#include "constant.h"
#include "DxLib.h"
#include "sceneTransition.h"

int GameResult::result_num = 0;

GameResult::GameResult() {
	rank = 0;
	char_next = LoadGraph("Source/UI/next.png");
	background = LoadGraph("Source/UI/result.png");
}

GameResult::~GameResult() {
	DeleteGraph(char_next);
	DeleteGraph(background);
}

void GameResult::draw() {
	DrawRectGraph(0, 0, WIN_WIDTH * (S - rank), 0,
	              WIN_WIDTH, WIN_HEIGHT, background, true, false);
	if (rank != D) {
		DrawRectGraph(700, 0, 0, 64 * (2 + result_num),
		              256, 64, char_next, true, false);
	}
	else {
		DrawRectGraph(700, 0, 0, 64 * result_num,
		              256, 64, char_next, true, false);
	}

	DrawRectGraph(0, 0, 0, 64 * (5 - result_num),
	              256, 64, char_next, true, false);
}

void GameResult::rank_check(const bool& p_ac, const bool& sw1_ac, const bool& sw2_ac, const bool& sw3_ac) {
	if (!sw1_ac && !sw2_ac && !sw3_ac) rank = C;
	else if ((sw1_ac && !sw2_ac && !sw3_ac)
		|| (!sw1_ac && sw2_ac && !sw3_ac)
		|| (!sw1_ac && !sw2_ac && sw3_ac))
		rank = B;
	else if ((sw1_ac && sw2_ac && !sw3_ac)
		|| (sw1_ac && !sw2_ac && sw3_ac)
		|| (!sw1_ac && sw2_ac && sw3_ac))
		rank = A;
	else if (sw1_ac && sw2_ac && sw3_ac) rank = S;

	if (!p_ac) rank = D;
}

void GameResult::update() {
	if (SceneTransition::game_scene == GAME_RESULT) draw();
}
