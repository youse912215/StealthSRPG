#include "DxLib.h"
#include "mapAll.h"
#include "mapUI.h"
#include "inputProcess.h"
#include "constant.h"
#include "cursor.h"
#include "sceneTransition.h"
#include "gameHelp.h"
#include "gameResult.h"
#include <cstdlib>

using namespace std;

bool Input::confirmation_flag = false;

Input::Input() : collision_flag{} {
	yes_or_no = true;
	current_map_scene = TUTORIAL;
}

/// <summary>
///　キーボード情報
/// </summary>
void Input::input_info() {
	//最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	//最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

/// <summary>
/// 昼夜変更
/// 夜の敵ターンなら、昼のプレイヤーターンに移行
/// </summary>
void Input::time_change() {
	if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]
		&& Map::scene % 2 == 0 && !MapUI::UI_flag) {
		confirmation_flag = true;
	}


	if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z]
		&& confirmation_flag && yes_or_no) {
		if (range_flag != 1 && Map::scene % 2 == 0 && !MapUI::UI_flag)
			Map::scene = (Map::scene == NIGHT_ENEMY) ? NOON_PLAY : ++Map::scene;
		confirmation_flag = false;
		MapUI::UI_flag = true;
	}
	else if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z]
		&& confirmation_flag && !yes_or_no) {
		confirmation_flag = false;
	}

	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT] && confirmation_flag) {
		yes_or_no = true;
	}
	else if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT] && confirmation_flag) {
		yes_or_no = false;
	}
}

void Input::cursorLeft() {
	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT] && !collision_flag[LEFT]) {
		qx -= BLOCK_SIZE;
		current_x -= BLOCK_SIZE;
	}
}

void Input::cursorRight() {
	if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT] && !collision_flag[RIGHT]) {
		qx += BLOCK_SIZE;
		current_x += BLOCK_SIZE;
	}
}

void Input::cursorUp() {
	if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP] && !collision_flag[UP]) {
		qy -= BLOCK_SIZE;
		current_y -= BLOCK_SIZE;
	}

}

void Input::cursorDown() {
	if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN] && !collision_flag[DOWN]) {
		qy += BLOCK_SIZE;
		current_y += BLOCK_SIZE;
	}
}

/// <summary>
/// x,yの絶対値の合計（移動マス）がカーソルの移動範囲と
/// </summary>
void Input::cursorLimit() {

	if (abs(range_x - current_x)
		+ abs(range_y - current_y)
		== moving_range * BLOCK_SIZE) {

		if (range_x == current_x) {

		}
		else if (range_x < current_x) {
			cursorLeft();
		}
		else if (range_x > current_x) {
			cursorRight();
		}

		if (range_y == current_y) {

		}
		else if (range_y < current_y) {
			cursorUp();
		}
		else if (range_y > current_y) {
			cursorDown();
		}
	}
	else {
		cursorLeft();
		cursorRight();
		cursorUp();
		cursorDown();
	}
}

/// <summary>
/// カーソルの動作処理
/// </summary>
void Input::moving_cursor() {

	if (range_flag == 1 && Map::scene % 2 == 0) {
		cursorLimit();
	}
	else {
		cursorLeft();
		cursorRight();
		cursorUp();
		cursorDown();
	}
}

void Input::collision_flag_update(vector<vector<int>>& map) {
	/* 左側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == SEA) {
		//海のとき
		collision_flag[LEFT] = true;
	}
	else if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		collision_flag[LEFT] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		collision_flag[LEFT] = true;
	}
	else {
		collision_flag[LEFT] = false;
	}

	/* 右側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == SEA) {
		//海のとき
		collision_flag[RIGHT] = true;
	}
	else if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		collision_flag[RIGHT] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		collision_flag[RIGHT] = true;
	}
	else {
		collision_flag[RIGHT] = false;
	}

	/* 上側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == SEA) {
		//海のとき
		collision_flag[UP] = true;
	}
	else if (map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		collision_flag[UP] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		collision_flag[UP] = true;
	}
	else {
		collision_flag[UP] = false;
	}

	/* 下側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == SEA) {
		//海のとき
		collision_flag[DOWN] = true;
	}
	else if (map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		collision_flag[DOWN] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		collision_flag[DOWN] = true;
	}
	else {
		collision_flag[DOWN] = false;
	}
}

void Input::map_scene_update(vector<vector<int>>& map) {
	if (!MapUI::UI_flag && !confirmation_flag) {
		moving_cursor();
		if (range_flag == 1) collision_flag_update(map);
		else {
			if (current_x == BLOCK_SIZE) collision_flag[LEFT] = true;
			else collision_flag[LEFT] = false;
			if (current_x == BLOCK_SIZE * 18) collision_flag[RIGHT] = true;
			else collision_flag[RIGHT] = false;
			if (current_y == BLOCK_SIZE) collision_flag[UP] = true;
			else collision_flag[UP] = false;
			if (current_y == BLOCK_SIZE * 18) collision_flag[DOWN] = true;
			else collision_flag[DOWN] = false;
		}
	}

	if (keys[KEY_INPUT_ESCAPE] && !oldkeys[KEY_INPUT_ESCAPE]) {
		current_map_scene = SceneTransition::game_scene;
		SceneTransition::game_scene = GAME_HELP;
	}
	if (range_flag == -1) time_change();
}

void Input::game_help_update() {
	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT] && GameHelp::help_num > 0) {
		GameHelp::help_num--;
	}
	else if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT] && GameHelp::help_num < 2) {
		GameHelp::help_num++;
	}
}

void Input::return_game() {
	if (keys[KEY_INPUT_ESCAPE] && !oldkeys[KEY_INPUT_ESCAPE]) {
		SceneTransition::game_scene = current_map_scene;
		GameHelp::help_num = 0;
	}
}

void Input::start_game() {
	if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z] && GameHelp::help_num == 2) {
		SceneTransition::game_scene = TUTORIAL;
		GameHelp::help_num = 0;
	}
}

void Input::game_result_update() {
	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT] && GameResult::result_num > 0) {
		GameResult::result_num--;
	}
	else if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT] && GameResult::result_num < 1) {
		GameResult::result_num++;
	}

	if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z]) {
		if (GameResult::result_num == 1) {
			SceneTransition::game_scene = current_map_scene + 1;
			current_map_scene++;
			Map::scene = NOON_PLAY;
			MapUI::UI_flag = true;
		}
		else {
			Map::scene = GAME_TITLE;
		}
	}


}

void Input::game_title_update() {
	if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z]) {
		SceneTransition::game_scene = GAME_INFORMATION;
	}
}
