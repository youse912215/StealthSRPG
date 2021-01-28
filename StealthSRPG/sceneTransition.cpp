#include "sceneTransition.h"
#include "constant.h"

int SceneTransition::game_scene = STAGE1;

void SceneTransition::transition_to_result() {
	game_scene = GAME_RESULT;
}
