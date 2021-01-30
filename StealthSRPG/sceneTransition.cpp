#include "sceneTransition.h"
#include "constant.h"

int SceneTransition::game_scene = TUTORIAL;

void SceneTransition::transition_to_result(vector<vector<int>>& map, const int& px, const int& py) {
	if (map[(py / BLOCK_SIZE)][(px / BLOCK_SIZE)] == GOAL) game_scene = GAME_RESULT;
}

void SceneTransition::transition_to_gameover(const bool& isAlive) {
	//game_scene = GAME_OVER;
}
