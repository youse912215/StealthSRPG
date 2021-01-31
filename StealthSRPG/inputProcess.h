#pragma once
#include "cursor.h"
#include <vector>

using namespace std;

class Input : public Cursor {
private:


	void cursorLeft();
	void cursorRight();
	void cursorUp();
	void cursorDown();
	void cursorLimit();
	void moving_cursor();
	void time_change();

public:
	vector<bool> map_collision_flag;
	vector<bool> enemy_collision_flag;
	bool yes_or_no;
	char keys[256] = {0}; //最新のキーボード情報用
	char oldkeys[256] = {0}; //1ループ(フレーム)前のキーボード情報
	static bool confirmation_flag;
	static int current_map_scene;

	Input();
	void input_info();
	void map_scene_update();
	void game_help_update();
	void return_game();
	void start_game();
	void game_result_update(const int& rank);
	void game_title_update();
	void map_collision_decision(vector<vector<int>>& map);
	void enemy_colliision_decesion0(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                                const int& ey3);
	void collision_update();
};
