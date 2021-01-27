#include "sceneTransition.h"
#include "constant.h"

int SceneTransition::game_scene = TUTORIAL;

void SceneTransition::transition_to_result() {
	game_scene = GAME_RESULT;
}
