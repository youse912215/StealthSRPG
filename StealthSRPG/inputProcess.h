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
	void collision_flag_update(vector<vector<int>>& map);

public:
	bool collision_flag[4];
	bool yes_or_no;
	char keys[256] = {0}; //最新のキーボード情報用
	char oldkeys[256] = {0}; //1ループ(フレーム)前のキーボード情報
	static bool confirmation_flag;
	int current_map_scene;

	Input();
	void input_info();
	void map_scene_update(vector<vector<int>>& map);
	void game_help_update();
	void game_result_update();
};
