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
	void collision_flag_update(vector<vector<int>>& map, const int& ew1_x, const int& ew1_y,
	                           const int& eb1_x, const int& eb1_y);

public:
	bool collision_flag[4];
	char keys[256] = {0}; //最新のキーボード情報用
	char oldkeys[256] = {0}; //1ループ(フレーム)前のキーボード情報

	Input();
	void input_info();
	void update(vector<vector<int>>& map, const int& ew1_x, const int& ew1_y,
	            const int& eb1_x, const int& eb1_y);
};
