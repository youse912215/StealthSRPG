#include "gameResult.h"
#include "constant.h"
#include "DxLib.h"
#include "sceneTransition.h"

GameResult::GameResult() {
	rank = 0;
	/*char_rank = LoadGraph("Source/UI/rank.png");
	char_next = LoadGraph("Source/UI/next.png");
	background = LoadGraph("Source/UI/result.png");*/
}

GameResult::~GameResult() {
	/*DeleteGraph(char_rank);
	DeleteGraph(char_next);
	DeleteGraph(background);*/
}

void GameResult::draw() {
	DrawFormatString(800, 0, GetColor(255, 0, 0), "Rank:%d", rank, false);
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
}

void GameResult::update() {
	if (SceneTransition::game_scene == GAME_RESULT) draw();
}
