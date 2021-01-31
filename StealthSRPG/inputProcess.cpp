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
int Input::current_map_scene = TUTORIAL;

Input::Input() : map_collision_flag(4), enemy_collision_flag(4) {
	yes_or_no = true;
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
		Map::turn_count++;
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
	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT]
		&& !map_collision_flag[LEFT] && !enemy_collision_flag[LEFT]) {
		qx -= BLOCK_SIZE;
		current_x -= BLOCK_SIZE;
	}
}

void Input::cursorRight() {
	if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT]
		&& !map_collision_flag[RIGHT] && !enemy_collision_flag[RIGHT]) {
		qx += BLOCK_SIZE;
		current_x += BLOCK_SIZE;
	}
}

void Input::cursorUp() {
	if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP]
		&& !map_collision_flag[UP] && !enemy_collision_flag[UP]) {
		qy -= BLOCK_SIZE;
		current_y -= BLOCK_SIZE;
	}

}

void Input::cursorDown() {
	if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN]
		&& !map_collision_flag[DOWN] && !enemy_collision_flag[DOWN]) {
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

void Input::map_collision_decision(vector<vector<int>>& map) {
	/* 左側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == SEA) {
		//海のとき
		map_collision_flag[LEFT] = true;
	}
	else if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		map_collision_flag[LEFT] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) - 1] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		map_collision_flag[LEFT] = true;
	}
	else {
		map_collision_flag[LEFT] = false;
	}

	/* 右側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == SEA) {
		//海のとき
		map_collision_flag[RIGHT] = true;
	}
	else if (map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		map_collision_flag[RIGHT] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE)][(current_x / BLOCK_SIZE) + 1] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		map_collision_flag[RIGHT] = true;
	}
	else {
		map_collision_flag[RIGHT] = false;
	}

	/* 上側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == SEA) {
		//海のとき
		map_collision_flag[UP] = true;
	}
	else if (map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		map_collision_flag[UP] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE) - 1][(current_x / BLOCK_SIZE)] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		map_collision_flag[UP] = true;
	}
	else {
		map_collision_flag[UP] = false;
	}

	/* 下側が特定条件のとき */
	if (map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == SEA) {
		//海のとき
		map_collision_flag[DOWN] = true;
	}
	else if (map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == TIDE
		&& Map::scene == NIGHT_PLAY && range_flag == 1) {
		//満潮のとき
		map_collision_flag[DOWN] = true;
	}
	else if ((map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == ICE_LAND
			|| map[(current_y / BLOCK_SIZE) + 1][(current_x / BLOCK_SIZE)] == ICE_SEA)
		&& Map::scene == NOON_PLAY && range_flag == 1) {
		//氷穴のとき
		map_collision_flag[DOWN] = true;
	}
	else {
		map_collision_flag[DOWN] = false;
	}
}

void Input::enemy_collision_decision0(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                      const int& ey3) {
	if ((current_x - BLOCK_SIZE == ex1 && current_y == ey1)
		|| (current_x - BLOCK_SIZE == ex2 && current_y == ey2)
		|| (current_x - BLOCK_SIZE == ex3 && current_y == ey3)) {
		enemy_collision_flag[LEFT] = true;
	}
	else enemy_collision_flag[LEFT] = false;

	if ((current_x + BLOCK_SIZE == ex1 && current_y == ey1)
		|| (current_x + BLOCK_SIZE == ex2 && current_y == ey2)
		|| (current_x + BLOCK_SIZE == ex3 && current_y == ey3)) {
		enemy_collision_flag[RIGHT] = true;
	}
	else enemy_collision_flag[RIGHT] = false;

	if ((current_x == ex1 && current_y - BLOCK_SIZE == ey1)
		|| (current_x == ex2 && current_y - BLOCK_SIZE == ey2)
		|| (current_x == ex3 && current_y - BLOCK_SIZE == ey3)) {
		enemy_collision_flag[UP] = true;
	}
	else enemy_collision_flag[UP] = false;

	if ((current_x == ex1 && current_y + BLOCK_SIZE == ey1)
		|| (current_x == ex2 && current_y + BLOCK_SIZE == ey2)
		|| (current_x == ex3 && current_y + BLOCK_SIZE == ey3)) {
		enemy_collision_flag[DOWN] = true;
	}
	else enemy_collision_flag[DOWN] = false;
}

void Input::enemy_collision_decision1(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                      const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
                                      const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
                                      const int& ey8) {
	if ((current_x - BLOCK_SIZE == ex1 && current_y == ey1)
		|| (current_x - BLOCK_SIZE == ex2 && current_y == ey2)
		|| (current_x - BLOCK_SIZE == ex3 && current_y == ey3)
		|| (current_x - BLOCK_SIZE == ex4 && current_y == ey4)
		|| (current_x - BLOCK_SIZE == ex5 && current_y == ey5)
		|| (current_x - BLOCK_SIZE == ex6 && current_y == ey6)
		|| (current_x - BLOCK_SIZE == ex7 && current_y == ey7)
		|| (current_x - BLOCK_SIZE == ex8 && current_y == ey8)) {
		enemy_collision_flag[LEFT] = true;
	}
	else enemy_collision_flag[LEFT] = false;

	if ((current_x + BLOCK_SIZE == ex1 && current_y == ey1)
		|| (current_x + BLOCK_SIZE == ex2 && current_y == ey2)
		|| (current_x + BLOCK_SIZE == ex3 && current_y == ey3)
		|| (current_x + BLOCK_SIZE == ex4 && current_y == ey4)
		|| (current_x + BLOCK_SIZE == ex5 && current_y == ey5)
		|| (current_x + BLOCK_SIZE == ex6 && current_y == ey6)
		|| (current_x + BLOCK_SIZE == ex7 && current_y == ey7)
		|| (current_x + BLOCK_SIZE == ex8 && current_y == ey8)) {
		enemy_collision_flag[RIGHT] = true;
	}
	else enemy_collision_flag[RIGHT] = false;

	if ((current_x == ex1 && current_y - BLOCK_SIZE == ey1)
		|| (current_x == ex2 && current_y - BLOCK_SIZE == ey2)
		|| (current_x == ex3 && current_y - BLOCK_SIZE == ey3)
		|| (current_x == ex4 && current_y - BLOCK_SIZE == ey4)
		|| (current_x == ex5 && current_y - BLOCK_SIZE == ey5)
		|| (current_x == ex6 && current_y - BLOCK_SIZE == ey6)
		|| (current_x == ex7 && current_y - BLOCK_SIZE == ey7)
		|| (current_x == ex8 && current_y - BLOCK_SIZE == ey8)) {
		enemy_collision_flag[UP] = true;
	}
	else enemy_collision_flag[UP] = false;

	if ((current_x == ex1 && current_y + BLOCK_SIZE == ey1)
		|| (current_x == ex2 && current_y + BLOCK_SIZE == ey2)
		|| (current_x == ex3 && current_y + BLOCK_SIZE == ey3)
		|| (current_x == ex4 && current_y + BLOCK_SIZE == ey4)
		|| (current_x == ex5 && current_y + BLOCK_SIZE == ey5)
		|| (current_x == ex6 && current_y + BLOCK_SIZE == ey6)
		|| (current_x == ex7 && current_y + BLOCK_SIZE == ey7)
		|| (current_x == ex8 && current_y + BLOCK_SIZE == ey8)) {
		enemy_collision_flag[DOWN] = true;
	}
	else enemy_collision_flag[DOWN] = false;
}

void Input::enemy_collision_decision2(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                      const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
                                      const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
                                      const int& ey8, const int& ex9, const int& ey9, const int& ex10, const int& ey10,
                                      const int& ex11, const int& ey11) {
	if ((current_x - BLOCK_SIZE == ex1 && current_y == ey1)
		|| (current_x - BLOCK_SIZE == ex2 && current_y == ey2)
		|| (current_x - BLOCK_SIZE == ex3 && current_y == ey3)
		|| (current_x - BLOCK_SIZE == ex4 && current_y == ey4)
		|| (current_x - BLOCK_SIZE == ex5 && current_y == ey5)
		|| (current_x - BLOCK_SIZE == ex6 && current_y == ey6)
		|| (current_x - BLOCK_SIZE == ex7 && current_y == ey7)
		|| (current_x - BLOCK_SIZE == ex8 && current_y == ey8)
		|| (current_x - BLOCK_SIZE == ex9 && current_y == ey9)
		|| (current_x - BLOCK_SIZE == ex10 && current_y == ey10)
		|| (current_x - BLOCK_SIZE == ex11 && current_y == ey11)) {
		enemy_collision_flag[LEFT] = true;
	}
	else enemy_collision_flag[LEFT] = false;

	if ((current_x + BLOCK_SIZE == ex1 && current_y == ey1)
		|| (current_x + BLOCK_SIZE == ex2 && current_y == ey2)
		|| (current_x + BLOCK_SIZE == ex3 && current_y == ey3)
		|| (current_x + BLOCK_SIZE == ex4 && current_y == ey4)
		|| (current_x + BLOCK_SIZE == ex5 && current_y == ey5)
		|| (current_x + BLOCK_SIZE == ex6 && current_y == ey6)
		|| (current_x + BLOCK_SIZE == ex7 && current_y == ey7)
		|| (current_x + BLOCK_SIZE == ex8 && current_y == ey8)
		|| (current_x + BLOCK_SIZE == ex9 && current_y == ey9)
		|| (current_x + BLOCK_SIZE == ex10 && current_y == ey10)
		|| (current_x + BLOCK_SIZE == ex11 && current_y == ey11)) {
		enemy_collision_flag[RIGHT] = true;
	}
	else enemy_collision_flag[RIGHT] = false;

	if ((current_x == ex1 && current_y - BLOCK_SIZE == ey1)
		|| (current_x == ex2 && current_y - BLOCK_SIZE == ey2)
		|| (current_x == ex3 && current_y - BLOCK_SIZE == ey3)
		|| (current_x == ex4 && current_y - BLOCK_SIZE == ey4)
		|| (current_x == ex5 && current_y - BLOCK_SIZE == ey5)
		|| (current_x == ex6 && current_y - BLOCK_SIZE == ey6)
		|| (current_x == ex7 && current_y - BLOCK_SIZE == ey7)
		|| (current_x == ex8 && current_y - BLOCK_SIZE == ey8)
		|| (current_x == ex9 && current_y - BLOCK_SIZE == ey9)
		|| (current_x == ex10 && current_y - BLOCK_SIZE == ey10)
		|| (current_x == ex11 && current_y - BLOCK_SIZE == ey11)) {
		enemy_collision_flag[UP] = true;
	}
	else enemy_collision_flag[UP] = false;

	if ((current_x == ex1 && current_y + BLOCK_SIZE == ey1)
		|| (current_x == ex2 && current_y + BLOCK_SIZE == ey2)
		|| (current_x == ex3 && current_y + BLOCK_SIZE == ey3)
		|| (current_x == ex4 && current_y + BLOCK_SIZE == ey4)
		|| (current_x == ex5 && current_y + BLOCK_SIZE == ey5)
		|| (current_x == ex6 && current_y + BLOCK_SIZE == ey6)
		|| (current_x == ex7 && current_y + BLOCK_SIZE == ey7)
		|| (current_x == ex8 && current_y + BLOCK_SIZE == ey8)
		|| (current_x == ex9 && current_y + BLOCK_SIZE == ey9)
		|| (current_x == ex10 && current_y + BLOCK_SIZE == ey10)
		|| (current_x == ex11 && current_y + BLOCK_SIZE == ey11)) {
		enemy_collision_flag[DOWN] = true;
	}
	else enemy_collision_flag[DOWN] = false;
}

void Input::map_scene_update() {
	if (!MapUI::UI_flag && !confirmation_flag) {
		moving_cursor();
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

void Input::game_result_update(const int& rank) {

	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT] && GameResult::result_num > 0) {
		GameResult::result_num--;
	}
	else if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT] && GameResult::result_num < 1) {
		GameResult::result_num++;
	}

	if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z]) {
		if (GameResult::result_num == 1 && rank != 0) {
			SceneTransition::game_scene = current_map_scene;

		}
		else if (GameResult::result_num == 1 && rank == 0) {
			SceneTransition::game_scene = current_map_scene - 1;
		}
		else {
			SceneTransition::game_scene = GAME_TITLE;
		}
		Map::scene = NOON_PLAY;
		MapUI::UI_flag = true;
	}


}

void Input::game_title_update() {
	if (keys[KEY_INPUT_Z] && !oldkeys[KEY_INPUT_Z]) {
		SceneTransition::game_scene = GAME_INFORMATION;
	}
}

void Input::collision_update() {
	if (current_x == BLOCK_SIZE) map_collision_flag[LEFT] = true;
	else map_collision_flag[LEFT] = false;
	if (current_x == BLOCK_SIZE * 18) map_collision_flag[RIGHT] = true;
	else map_collision_flag[RIGHT] = false;
	if (current_y == BLOCK_SIZE) map_collision_flag[UP] = true;
	else map_collision_flag[UP] = false;
	if (current_y == BLOCK_SIZE * 18) map_collision_flag[DOWN] = true;
	else map_collision_flag[DOWN] = false;
}
